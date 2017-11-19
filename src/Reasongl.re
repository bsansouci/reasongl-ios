open GLConstants;

open Bindings;

/*let render
      ::window
      ::mouseDown
      ::mouseUp
      ::mouseMove
      ::keyDown
      ::keyUp
      ::windowResize
      ::displayFunc
      () => {
    Callback.register "update" displayFunc;
  };
  */
let vertexShaderSource = {|
  attribute vec3 aVertexPosition;
  attribute vec3 aVertexColor;

  uniform mat4 uPMatrix;
  uniform mat3 normalMatrix;

  varying lowp vec4 vColor;

  void main(void) {
    gl_Position = uPMatrix * vec4(aVertexPosition, 1.0);
    vColor = vec4(aVertexColor, 1.0);
  }
|};

let fragmentShaderSource = {|
  varying lowp vec4 vColor;

  void main(void) {
    gl_FragColor = vColor;
  }
|};

/*let vertexData =
  Bigarray.of_array
    Bigarray.Float32
    [|
      0.5,
      (-0.5),
      0.,
      255.,
      0.0,
      0.0,
      (-0.5),
      (-0.5),
      0.,
      255.,
      0.0,
      0.0,
      0.5,
      0.5,
      0.,
      255.,
      0.0,
      0.0,
      (-0.5),
      (-0.5),
      0.,
      255.,
      0.0,
      0.0,
      0.5,
      0.5,
      0.,
      255.,
      0.0,
      0.0,
      (-0.5),
      0.5,
      0.,
      255.,
      0.0,
      0.0
    |];*/
/*let setupGL vc context => {
    setCurrentContext context;
    let program = createProgram ::context;
    let vertexShader = createShader ::context shaderType::gl_vertex_shader;
    shaderSource ::context shader::vertexShader source::[|vertexShaderSource|];
    compileShader ::context shader::vertexShader;
    print_endline (getShaderInfoLog ::context shader::vertexShader);
    attachShader ::context ::program shader::vertexShader;
    let fragmentShader = createShader ::context shaderType::gl_fragment_shader;
    shaderSource ::context shader::fragmentShader source::[|fragmentShaderSource|];
    compileShader ::context shader::fragmentShader;
    print_endline (getShaderInfoLog ::context shader::fragmentShader);
    attachShader ::context ::program shader::fragmentShader;
    linkProgram ::context ::program;
    print_endline (getProgramInfoLog ::context ::program);
    let umvp = getUniformLocation ::context ::program name::"uPMatrix";
    deleteShader ::context shader::vertexShader;
    deleteShader ::context shader::fragmentShader;
    setProgram vc program;
    setUmvp vc umvp;
    enable ::context gl_depth_test;
    let vertexArray = genVertexArray ::context;
    bindVertexArray ::context ::vertexArray;
    setVertexArray vc vertexArray;
    let vertexBuffer = (createBuffer ::context 1).(0);
    bindBuffer ::context target::gl_array_buffer buffer::vertexBuffer;
    setVertexBuffer vc vertexBuffer;
    bufferData
      ::context target::gl_array_buffer data::vertexData usage::gl_static_draw;
    let aVertexPosition = getAttribLocation ::context ::program name::"aVertexPosition";
    enableVertexAttribArray ::context attribute::aVertexPosition;
    vertexAttribPointer
      ::context
      attribute::aVertexPosition
      size::3
      type_::gl_float
      normalize::false
      stride::24
      offset::0;
    let aVertexColor = getAttribLocation ::context ::program name::"aVertexColor";
    enableVertexAttribArray ::context attribute::aVertexColor;
    vertexAttribPointer
      ::context
      attribute::aVertexColor
      size::3
      type_::gl_float
      normalize::false
      stride::24
      offset::12;
    /* unbindVertexArray ::context; */
    print_endline @@ "program log info " ^ getProgramInfoLog ::context ::program
  };*/
module Mat4 = {
  type t;
  external create : unit => t = "Mat4_create";
  external ortho :
    (
      ~out: t,
      ~left: float,
      ~right: float,
      ~bottom: float,
      ~top: float,
      ~near: float,
      ~far: float
    ) =>
    unit =
    "Mat4_ortho_byte" "Mat4_ortho_native";
};

module Reprocessing_Shaders = {
  let vertexShaderSource = {|
  attribute vec2 aVertexPosition;
  attribute vec4 aVertexColor;

  uniform mat4 uPMatrix;

  varying vec4 vColor;

  void main(void) {
    gl_Position = uPMatrix * vec4(aVertexPosition, 0.0, 1.0);
    vColor = aVertexColor;
  }
|};
  let fragmentShaderSource = {|
  varying vec4 vColor;
  varying vec2 vTextureCoord;

  void main(void) {
    gl_FragColor = vColor;
  }
|};
};

type glCamera = {projectionMatrix: Mat4.t};

type batchT = {
  vertexArray: Bigarray.t(float, Bigarray.float32_elt),
  elementArray: Bigarray.t(int, Bigarray.int16_unsigned_elt),
  mutable vertexPtr: int,
  mutable elementPtr: int
};

type strokeCapT =
  | Round
  | Square
  | Project;

type colorT = {
  r: int,
  g: int,
  b: int
};

type styleT = {
  strokeColor: option(colorT),
  strokeWeight: int,
  strokeCap: strokeCapT,
  fillColor: option(colorT)
};

type glEnv = {
  camera: glCamera,
  gl: contextT,
  vertexArrayPtr: vertexArrayT,
  pMatrixUniform: uniformT,
  vertexBuffer: bufferT,
  elementBuffer: bufferT,
  aVertexColor: attributeT,
  aVertexPosition: attributeT,
  batch: batchT,
  mutable style: styleT
};

module Env = {
  let width = (_) => 375;
  let height = (_) => 667;
};

let circularBufferSize = 6 * 10000;

let vertexSize = 8;

let setupGL = (vc, context) => {
  setCurrentContext(context);
  viewport(~context, ~x=(-1), ~y=(-1), ~width=Env.width(), ~height=Env.height());
  clearColor(~context, ~red=0., ~green=0., ~blue=0., ~alpha=1.);
  clear(~context, 16384 lor 256);

  /*** Camera is a simple record containing one matrix used to project a point in 3D onto the screen. **/
  let camera = {projectionMatrix: Mat4.create()};
  let buffers = createBuffer(~context, 2);
  let vertexBuffer = buffers[0];
  let elementBuffer = buffers[1];
  let program = createProgram(~context);
  let vertexShader = createShader(~context, ~shaderType=gl_vertex_shader);
  shaderSource(~context, ~shader=vertexShader, ~source=[|vertexShaderSource|]);
  compileShader(~context, ~shader=vertexShader);
  print_endline @@ "vertexShader logs: " ++ getShaderInfoLog(~context, ~shader=vertexShader);
  attachShader(~context, ~program, ~shader=vertexShader);
  let fragmentShader = createShader(~context, ~shaderType=gl_fragment_shader);
  shaderSource(~context, ~shader=fragmentShader, ~source=[|fragmentShaderSource|]);
  compileShader(~context, ~shader=fragmentShader);
  print_endline @@ "fragmentShader logs: " ++ getShaderInfoLog(~context, ~shader=fragmentShader);
  attachShader(~context, ~program, ~shader=fragmentShader);
  linkProgram(~context, ~program);
  print_endline @@ "program logs: " ++ getProgramInfoLog(~context, ~program);
  deleteShader(~context, ~shader=vertexShader);
  deleteShader(~context, ~shader=fragmentShader);
  /*setProgram vc program;*/
  useProgram(~context, program);

  /*** Get the attribs ahead of time to be used inside the render function **/
  let aVertexPosition = getAttribLocation(~context, ~program, ~name="aVertexPosition");
  enableVertexAttribArray(~context, ~attribute=aVertexPosition);
  let aVertexColor = getAttribLocation(~context, ~program, ~name="aVertexColor");
  enableVertexAttribArray(~context, ~attribute=aVertexColor);
  let pMatrixUniform = getUniformLocation(~context, ~program, ~name="uPMatrix");
  /* @HACK this function is fuckd */
  uniformMatrix4fv(
    ~context,
    ~location=pMatrixUniform,
    ~transpose=false,
    ~value=camera.projectionMatrix
  );
  /*setUmvp vc pMatrixUniform;*/

  /*** Get attribute and uniform locations for later usage in the draw code. **/
  /*let aTextureCoord =
      getAttribLocation ::context ::program name::"aTextureCoord";
    enableVertexAttribArray ::context attribute::aTextureCoord;

    /** Generate texture buffer that we'll use to pass image data around. **/
    let texture = genTexture ::context;

    * This tells OpenGL that we're going to be using texture0. OpenGL imposes a limit on the number of
        texture we can manipulate at the same time. That limit depends on the device. We don't care as we'll just
        always use texture0. *
    activeTexture ::context RGLConstants.texture0;

    /** Bind `texture` to `texture_2d` to modify it's magnification and minification params. **/
    bindTexture ::context target::RGLConstants.texture_2d ::texture;
    let uSampler = Gl.getUniformLocation ::context ::program name::"uSampler";*/

  /*** Load a dummy texture. This is because we're using the same shader for things with and without a texture */
  /*Gl.texImage2D_RGBA
      ::context
      target::RGLConstants.texture_2d
      level::0
      width::1
      height::1
      border::0
      data::(Gl.Bigarray.of_array Gl.Bigarray.Uint8 [|0, 0, 0, 0|]);
    Gl.texParameteri
      ::context
      target::RGLConstants.texture_2d
      pname::RGLConstants.texture_mag_filter
      param::RGLConstants.linear;
    Gl.texParameteri
      ::context
      target::RGLConstants.texture_2d
      pname::RGLConstants.texture_min_filter
      param::RGLConstants.linear_mipmap_nearest;*/

  /*** Enable blend and tell OpenGL how to blend. */
  enable(~context, RGLConstants.blend);
  blendFunc(~context, ~sfactor=RGLConstants.src_alpha, ~dfactor=RGLConstants.one_minus_src_alpha);

  /***
   * Will mutate the projectionMatrix to be an ortho matrix with the given boundaries.
   * See this link for quick explanation of what this is.
   * https://shearer12345.github.io/graphics/assets/projectionPerspectiveVSOrthographic.png
   */
  Mat4.ortho(
    ~out=camera.projectionMatrix,
    ~left=0.,
    ~right=float_of_int @@ Env.width(),
    ~bottom=float_of_int @@ Env.height(),
    ~top=0.,
    ~near=(-1024.),
    ~far=1024.
  );
  {
    camera,
    vertexArrayPtr: genVertexArray(~context),
    gl: context,
    batch: {
      vertexArray: Bigarray.create(Bigarray.Float32, circularBufferSize * vertexSize),
      elementArray: Bigarray.create(Bigarray.Uint16, circularBufferSize),
      vertexPtr: 0,
      elementPtr: 0
    },
    style: {
      fillColor: Some({r: 0, g: 0, b: 0}),
      strokeWeight: 10,
      strokeCap: Round,
      strokeColor: Some({r: 0, g: 0, b: 0})
    },
    vertexBuffer,
    elementBuffer,
    aVertexPosition,
    aVertexColor,
    pMatrixUniform
  }
};

let globalRender: ref(option((glEnv) => unit)) = ref(None);

let f = (vc: gameViewControllerT) =>
  switch (makeContext(EAGLRenderingAPIOpenGLES2)) {
  | None => failwith("context was nil")
  | Some(context) =>
    setContext(vc, context);
    setPreferredFramesPerSecond(vc, 60);
    let view = getView(vc);
    setContext(view, context);
    setDrawableDepthFormat(view, GLKViewDrawableDepthFormat24);
    let env = setupGL(vc, context);
    switch globalRender^ {
    | None => failwith("this shouldn't happen")
    | Some(render) => render(env)
    }
  };

Callback.register("main", f);

let toColorFloat = (i) => float_of_int(i) /. 255.;

/*
 * This array packs all of the values that the shaders need: vertices, colors and texture coordinates.
 * We put them all in one as an optimization, so there are less back and forths between us and the GPU.
 *
 * The vertex array looks like:
 *
 * |<--------  8 * 4 bytes  ------->|
 *  --------------------------------
 * |  x  y  |  r  g  b  a  |  s  t  |  x2  y2  |  r2  g2  b2  a2  |  s2  t2  | ....
 *  --------------------------------
 * |           |              |
 * +- offset: 0 bytes, stride: 8 * 4 bytes (because we need to move by 8*4 bytes to get to the next x)
 *             |              |
 *             +- offset: 3 * 4 bytes, stride: 8 * 4 bytes
 *                            |
 *                            +- offset: (3 + 4) * 4 bytes, stride: 8 * 4 bytes
 *
 *
 * The element array is just an array of indices of vertices given that each vertex takes 8 * 4 bytes.
 * For example, if the element array looks like [|0, 1, 2, 1, 2, 3|], we're telling the GPU to draw 2
 * triangles: one with the vertices 0, 1 and 2 from the vertex array, and one with the vertices 1, 2 and 3.
 * We can "point" to duplicated vertices in our geometry to avoid sending those vertices.
 */
let addRectToGlobalBatch =
    (
      env,
      ~bottomRight as (x1, y1),
      ~bottomLeft as (x2, y2),
      ~topRight as (x3, y3),
      ~topLeft as (x4, y4),
      ~color as {r, g, b}
    ) => {
  /*maybeFlushBatch texture::None el::6 vert::32 env;*/
  let setFloat32 = Bigarray.setFloat32;
  let (r, g, b) = (toColorFloat(r), toColorFloat(g), toColorFloat(b));
  let i = env.batch.vertexPtr;
  let vertexArrayToMutate = env.batch.vertexArray;
  setFloat32(vertexArrayToMutate, i + 0, x1);
  setFloat32(vertexArrayToMutate, i + 1, y1);
  setFloat32(vertexArrayToMutate, i + 2, r);
  setFloat32(vertexArrayToMutate, i + 3, g);
  setFloat32(vertexArrayToMutate, i + 4, b);
  setFloat32(vertexArrayToMutate, i + 5, 1.);
  setFloat32(vertexArrayToMutate, i + 6, 0.0);
  setFloat32(vertexArrayToMutate, i + 7, 0.0);
  setFloat32(vertexArrayToMutate, i + 8, x2);
  setFloat32(vertexArrayToMutate, i + 9, y2);
  setFloat32(vertexArrayToMutate, i + 10, r);
  setFloat32(vertexArrayToMutate, i + 11, g);
  setFloat32(vertexArrayToMutate, i + 12, b);
  setFloat32(vertexArrayToMutate, i + 13, 1.);
  setFloat32(vertexArrayToMutate, i + 14, 0.0);
  setFloat32(vertexArrayToMutate, i + 15, 0.0);
  setFloat32(vertexArrayToMutate, i + 16, x3);
  setFloat32(vertexArrayToMutate, i + 17, y3);
  setFloat32(vertexArrayToMutate, i + 18, r);
  setFloat32(vertexArrayToMutate, i + 19, g);
  setFloat32(vertexArrayToMutate, i + 20, b);
  setFloat32(vertexArrayToMutate, i + 21, 1.);
  setFloat32(vertexArrayToMutate, i + 22, 0.0);
  setFloat32(vertexArrayToMutate, i + 23, 0.0);
  setFloat32(vertexArrayToMutate, i + 24, x4);
  setFloat32(vertexArrayToMutate, i + 25, y4);
  setFloat32(vertexArrayToMutate, i + 26, r);
  setFloat32(vertexArrayToMutate, i + 27, g);
  setFloat32(vertexArrayToMutate, i + 28, b);
  setFloat32(vertexArrayToMutate, i + 29, 1.);
  setFloat32(vertexArrayToMutate, i + 30, 0.0);
  setFloat32(vertexArrayToMutate, i + 31, 0.0);
  let ii = i / vertexSize;
  let j = env.batch.elementPtr;
  let elementArrayToMutate = env.batch.elementArray;
  let setUint16 = Bigarray.setUint16;
  setUint16(elementArrayToMutate, j + 0, ii);
  setUint16(elementArrayToMutate, j + 1, ii + 1);
  setUint16(elementArrayToMutate, j + 2, ii + 2);
  setUint16(elementArrayToMutate, j + 3, ii + 1);
  setUint16(elementArrayToMutate, j + 4, ii + 2);
  setUint16(elementArrayToMutate, j + 5, ii + 3);
  env.batch.vertexPtr = i + 4 * vertexSize;
  env.batch.elementPtr = j + 6
};

module Utils = {
  let white = {r: 255, g: 255, b: 255};
  let black = {r: 0, g: 0, b: 0};
  let red = {r: 255, g: 0, b: 0};
  let green = {r: 0, g: 255, b: 0};
  let blue = {r: 0, g: 0, b: 255};
  let pi = 4.0 *. atan(1.0);
  let two_pi = 2.0 *. pi;
  let half_pi = 0.5 *. pi;
  let quarter_pi = 0.25 *. pi;
  let tau = two_pi;
  let foi = float_of_int;
  let lookup_table: ref(array(int)) = ref([||]);
  let color = (~r, ~g, ~b) : colorT => {r, g, b};
  /*Calculation Functions*/
  let round = (i) => floor(i +. 0.5);
  let sq = (x) => x * x;
  let rec pow = (~base, ~exp) =>
    switch exp {
    | 0 => 1
    | 1 => base
    | n =>
      let b = pow(~base, ~exp=n / 2);
      b
      * b
      * (
        if (n mod 2 == 0) {
          1
        } else {
          base
        }
      )
    };
  let constrain = (~amt, ~low, ~high) => max(min(amt, high), low);
  let remapf = (~value, ~low1, ~high1, ~low2, ~high2) =>
    low2 +. (high2 -. low2) *. ((value -. low1) /. (high1 -. low1));
  let remap = (~value, ~low1, ~high1, ~low2, ~high2) =>
    int_of_float(
      remapf(
        ~value=foi(value),
        ~low1=foi(low1),
        ~high1=foi(high1),
        ~low2=foi(low2),
        ~high2=foi(high2)
      )
    );
  let norm = (~value, ~low, ~high) => remapf(~value, ~low1=low, ~high1=high, ~low2=0., ~high2=1.);
  let randomf = (~min, ~max) => Random.float(max -. min) +. min;
  let random = (~min, ~max) => Random.int(max - min) + min;
  let randomSeed = (seed) => Random.init(seed);
  let randomGaussian = () => {
    let u1 = ref(0.0);
    let u2 = ref(0.0);
    while (u1^ <= min_float) {
      u1 := Random.float(1.0);
      u2 := Random.float(1.0)
    };
    sqrt((-2.0) *. log(u1^)) *. cos(two_pi *. u2^)
  };
  let lerpf = (~low, ~high) => remapf(~low1=0., ~high1=1., ~low2=low, ~high2=high);
  let lerp = (~low, ~high, ~value) => int_of_float(lerpf(~low=foi(low), ~high=foi(high), ~value));
  let distf = (~p1 as (x1: float, y1: float), ~p2 as (x2: float, y2: float)) => {
    let dx = x2 -. x1;
    let dy = y2 -. y1;
    sqrt(dx *. dx +. dy *. dy)
  };
  let dist = (~p1 as (x1, y1), ~p2 as (x2, y2)) =>
    distf(~p1=(foi(x1), foi(y1)), ~p2=(foi(x2), foi(y2)));
  let magf = (vec) => distf(~p1=(0., 0.), ~p2=vec);
  let mag = (vec) => dist(~p1=(0, 0), ~p2=vec);
  let lerpColor = (~low, ~high, ~value) => {
    r: lerp(~low=low.r, ~high=high.r, ~value),
    g: lerp(~low=low.g, ~high=high.g, ~value),
    b: lerp(~low=low.b, ~high=high.b, ~value)
  };
  let degrees = (x) => 180.0 /. pi *. x;
  let radians = (x) => pi /. 180.0 *. x;
  let noise = (x, y, z) => {
    let p = lookup_table^;
    let fade = (t) => t *. t *. t *. (t *. (t *. 6.0 -. 15.0) +. 10.0);
    let grad = (hash, x, y, z) =>
      switch (hash land 15) {
      | 0 => x +. y
      | 1 => -. x +. y
      | 2 => x -. y
      | 3 => -. x -. y
      | 4 => x +. z
      | 5 => -. x +. z
      | 6 => x -. z
      | 7 => -. x -. z
      | 8 => y +. z
      | 9 => -. y +. z
      | 10 => y -. z
      | 11 => -. y -. z
      | 12 => y +. x
      | 13 => -. y +. z
      | 14 => y -. x
      | 15 => -. y -. z
      | _ => 0.0
      };
    let xi = int_of_float(x) land 255;
    let yi = int_of_float(y) land 255;
    let zi = int_of_float(z) land 255;
    let xf = x -. floor(x);
    let yf = y -. floor(y);
    let zf = z -. floor(z);
    let u = fade(xf);
    let v = fade(yf);
    let w = fade(zf);
    let aaa = p[p[p[xi] + yi] + zi];
    let aba = p[p[p[xi] + (yi + 1)] + zi];
    let aab = p[p[p[xi] + yi] + (zi + 1)];
    let abb = p[p[p[xi] + (yi + 1)] + (zi + 1)];
    let baa = p[p[p[xi + 1] + yi] + zi];
    let bba = p[p[p[xi + 1] + (yi + 1)] + zi];
    let bab = p[p[p[xi + 1] + yi] + (zi + 1)];
    let bbb = p[p[p[xi + 1] + (yi + 1)] + (zi + 1)];
    let x1 = lerpf(~low=grad(aaa, xf, yf, zf), ~high=grad(baa, xf -. 1.0, yf, zf), ~value=u);
    let x2 =
      lerpf(
        ~low=grad(aba, xf, yf -. 1.0, zf),
        ~high=grad(bba, xf -. 1.0, yf -. 1.0, zf),
        ~value=u
      );
    let y1 = lerpf(~low=x1, ~high=x2, ~value=v);
    let x1 =
      lerpf(
        ~low=grad(aab, xf, yf, zf -. 1.0),
        ~high=grad(bab, xf -. 1.0, yf, zf -. 1.0),
        ~value=u
      );
    let x2 =
      lerpf(
        ~low=grad(abb, xf, yf -. 1.0, zf -. 1.0),
        ~high=grad(bbb, xf -. 1.0, yf -. 1.0, zf -. 1.0),
        ~value=u
      );
    let y2 = lerpf(~low=x1, ~high=x2, ~value=v);
    (lerpf(~low=y1, ~high=y2, ~value=w) +. 1.0) /. 2.0
  };
  let shuffle = (array) => {
    let array = Array.copy(array);
    let length = Array.length(array);
    for (i in 0 to 256 - 1) {
      let j = Random.int(length - i);
      let tmp = array[i];
      array[i] = array[i + j];
      array[i + j] = tmp
    };
    array
  };
  let noiseSeed = (seed) => {
    let state = Random.get_state();
    Random.init(seed);
    let array = Array.make(256, 0);
    let array = Array.mapi((i, _) => i, array);
    let array = shuffle(array);
    let double_array = Array.append(array, array);
    lookup_table := double_array;
    Random.set_state(state)
  };
};

let drawArc =
    (
      env,
      (xCenterOfCircle: float, yCenterOfCircle: float),
      radx: float,
      rady: float,
      start: float,
      stop: float,
      isPie: bool,
      {r, g, b}
    ) => {
  let noOfFans = int_of_float(radx +. rady) / 4 + 10;
  /*maybeFlushBatch texture::None vert::(8 * noOfFans) el::(3 * noOfFans) env;*/
  let pi = 4.0 *. atan(1.0);
  let anglePerFan = 2. *. pi /. float_of_int(noOfFans);
  let (r, g, b) = (toColorFloat(r), toColorFloat(g), toColorFloat(b));
  /*print_endline @@ "r " ^ (string_of_float r) ^ "g " ^ (string_of_float g) ^ "b " ^ string_of_float b;*/
  let verticesData = env.batch.vertexArray;
  let elementData = env.batch.elementArray;
  let setFloat32 = Bigarray.setFloat32;
  let setUint16 = Bigarray.setUint16;
  let getUint16 = Bigarray.getUint16;
  let vertexArrayOffset = env.batch.vertexPtr;
  let elementArrayOffset = env.batch.elementPtr;
  let start_i =
    if (isPie) {
      /* Start one earlier and force the first point to be the center */
      int_of_float(start /. anglePerFan)
      - 2
    } else {
      int_of_float(start /. anglePerFan) - 1
    };
  let stop_i = int_of_float(stop /. anglePerFan) - 1;
  for (i in start_i to stop_i) {
    let (xCoordinate, yCoordinate) =
      if (isPie && i - start_i == 0) {
        (
          /* force the first point to be the center */
          xCenterOfCircle,
          yCenterOfCircle
        )
      } else {
        let angle = anglePerFan *. float_of_int(i + 1);
        (xCenterOfCircle +. cos(angle) *. radx, yCenterOfCircle +. sin(angle) *. rady)
      };
    let ii = (i - start_i) * vertexSize + vertexArrayOffset;
    setFloat32(verticesData, ii + 0, xCoordinate);
    setFloat32(verticesData, ii + 1, yCoordinate);
    setFloat32(verticesData, ii + 2, r);
    setFloat32(verticesData, ii + 3, g);
    setFloat32(verticesData, ii + 4, b);
    setFloat32(verticesData, ii + 5, 1.0);
    setFloat32(verticesData, ii + 6, 0.0);
    setFloat32(verticesData, ii + 7, 0.0);
    /* For the first three vertices, we don't do any deduping. Then for the subsequent ones, we'll actually
       have 3 elements, one pointing at the first vertex, one pointing at the previously added vertex and one
       pointing at the current vertex. This mimicks the behavior of triangle_fan. */
    if (i - start_i < 3) {
      setUint16(elementData, i - start_i + elementArrayOffset, ii / vertexSize)
    } else {
      /* We've already added 3 elements, for i = 0, 1 and 2. From now on, we'll add 3 elements _per_ i.
         To calculate the correct offset in `elementData` we remove 3 from i as if we're starting from 0 (the
         first time we enter this loop i = 3), then for each i we'll add 3 elements (so multiply by 3) BUT for
         i = 3 we want `jj` to be 3 so we shift everything by 3 (so add 3). Everything's also shifted by
         `elementArrayOffset` */
      let jj = (i - start_i - 3) * 3 + elementArrayOffset + 3;
      setUint16(elementData, jj, vertexArrayOffset / vertexSize);
      setUint16(elementData, jj + 1, getUint16(elementData, jj - 1));
      setUint16(elementData, jj + 2, ii / vertexSize)
    }
  };
  env.batch.vertexPtr = env.batch.vertexPtr + noOfFans * vertexSize;
  env.batch.elementPtr = env.batch.elementPtr + (stop_i - start_i - 3) * 3 + 3
};

module Draw = {
  let fill = (color, env: glEnv) => env.style = {...env.style, fillColor: Some(color)};
  let background = (color, env: glEnv) => {
    clear(~context=env.gl, 16384 lor 256);
    let w = float_of_int(Env.width(env));
    let h = float_of_int(Env.height(env));
    addRectToGlobalBatch(
      env,
      ~bottomRight=(w, h),
      ~bottomLeft=(0., h),
      ~topRight=(w, 0.),
      ~topLeft=(0., 0.),
      ~color
    )
  };
  let drawEllipse = (env, center, radx: float, rady: float, c) =>
    drawArc(env, center, radx, rady, 0., Utils.tau, false, c);
  let ellipsef = (~center, ~radx, ~rady, env: glEnv) =>
    switch env.style.fillColor {
    | None => () /* Don't draw fill */
    | Some(fill) => drawEllipse(env, center, radx, rady, fill)
    /*switch env.style.strokeColor {
      | None => () /* Don't draw stroke */
      | Some stroke =>
        drawArcStroke
          env
          center
          radx
          rady
          0.
          Utils.tau
          false
          false
          env.matrix
          stroke
          env.style.strokeWeight
      }*/
    };
  let ellipse = (~center as (cx, cy), ~radx, ~rady, env: glEnv) =>
    ellipsef(
      ~center=(float_of_int(cx), float_of_int(cy)),
      ~radx=float_of_int(radx),
      ~rady=float_of_int(rady),
      env
    );
};
