open Reasongl;
open GLConstants;
open Bindings;


/* https://www.youtube.com/watch?v=KkyIDI6rQJI
   Purple rain processing demo */
type dropT = {
  x: int,
  y: int,
  z: int,
  len: int,
  yspeed: int,
  color: colorT,
  time: int
};

let make = (w, (ymin, ymax), time) => {
  let z = Utils.random(~min=0, ~max=20);
  {
    x: Utils.random(~min=0, ~max=w),
    y: Utils.random(~min=ymin, ~max=ymax),
    z,
    len: Utils.remap(~value=z, ~low1=0, ~high1=20, ~low2=10, ~high2=20),
    yspeed: Utils.remap(~value=z, ~low1=0, ~high1=20, ~low2=5, ~high2=15),
    color:
      Utils.lerpColor(
        ~low=Utils.white,
        ~high=Utils.color(~r=0, ~g=43, ~b=226),
        ~value=Utils.randomf(~min=0.3, ~max=1.)
      ),
    time
  }
};

let drawGeometry =
    (
      ~vertexArray: Bigarray.t(float, Bigarray.float32_elt),
      ~elementArray: Bigarray.t(int, Bigarray.int16_unsigned_elt),
      ~mode,
      ~count,
      /*::textureBuffer*/
      env
    ) => {
  /* Bind `vertexBuffer`, a pointer to chunk of memory to be sent to the GPU to the "register" called
     `array_buffer` */
  bindBuffer(~context=env.gl, ~target=gl_array_buffer, ~buffer=env.vertexBuffer);

  /*** Copy all of the data over into whatever's in `array_buffer` (so here it's `vertexBuffer`) **/
  bufferData(~context=env.gl, ~target=gl_array_buffer, ~data=vertexArray, ~usage=gl_stream_draw);

  /*** Tell the GPU about the shader attribute called `aVertexPosition` so it can access the data per vertex */
  vertexAttribPointer(
    ~context=env.gl,
    ~attribute=env.aVertexPosition,
    ~size=2,
    ~type_=gl_float,
    ~normalize=false,
    ~stride=vertexSize * 4,
    ~offset=0
  );

  /*** Same as above but for `aVertexColor` **/
  vertexAttribPointer(
    ~context=env.gl,
    ~attribute=env.aVertexColor,
    ~size=4,
    ~type_=gl_float,
    ~normalize=false,
    ~stride=vertexSize * 4,
    ~offset=2 * 4
  );

  /*** Same as above but for `aTextureCoord` **/
  /*vertexAttribPointer
    context::env.gl
    attribute::env.aTextureCoord
    size::2
    type_::gl_float
    normalize::false
    stride::(vertexSize * 4)
    offset::(6 * 4);*/

  /*** Tell OpenGL about what the uniform called `uSampler` is pointing at, here it's given 0 which is what
       texture0 represent.  **/
  /*uniform1i context::env.gl location::env.uSampler value::0;*/

  /*** Bind `elementBuffer`, a pointer to GPU memory to `element_array_buffer`. That "register" is used for
       the data representing the indices of the vertex. **/
  bindBuffer(~context=env.gl, ~target=gl_element_array_buffer, ~buffer=env.elementBuffer);

  /*** Copy the `elementArray` into whatever buffer is in `element_array_buffer` **/
  bufferData(
    ~context=env.gl,
    ~target=gl_element_array_buffer,
    ~data=elementArray,
    ~usage=gl_stream_draw
  );
  uniformMatrix4fv(
    ~context=env.gl,
    ~location=env.pMatrixUniform,
    ~transpose=false,
    ~value=env.camera.projectionMatrix
  );

  /*** We bind `texture` to texture_2d, like we did for the vertex buffers in some ways (I think?) **/
  /*bindTexture
    context::env.gl target::gl_texture_2d texture::textureBuffer;*/
  /*bindVertexArray context::env.gl vertexArray::env.vertexArrayPtr;*/

  /*** Final call which actually tells the GPU to draw. **/
  drawElements(~context=env.gl, ~mode, ~count, ~type_=gl_unsigned_short, ~offset=0)
};

let flushGlobalBatch = (env) =>
  if (env.batch.elementPtr > 0) {
    /*let textureBuffer =
      switch env.batch.currTex {
      | None => env.batch.nullTex
      | Some textureBuffer => textureBuffer
      };*/
    clearColor(~context=env.gl, ~red=1., ~green=0., ~blue=0., ~alpha=1.);
    clear(~context=env.gl, 16384 lor 256);
    drawGeometry(
      ~vertexArray=Bigarray.subFloat32(env.batch.vertexArray, ~offset=0, ~len=env.batch.vertexPtr),
      ~elementArray=
        Bigarray.subUnit16(env.batch.elementArray, ~offset=0, ~len=env.batch.elementPtr),
      ~mode=gl_triangles,
      ~count=env.batch.elementPtr,
      /*::textureBuffer*/
      env
    );
    /*env.batch.currTex = None;*/
    env.batch.vertexPtr = 0;
    env.batch.elementPtr = 0
  };

let run = (~setup, ~draw, ()) =>
  /* Register a global render. */
  globalRender :=
    Some(
      (env) => {
        let state = ref(setup(env));
        Callback.register(
          "update",
          (_) => {
            state := draw(state^, env);

            /*** Flush buffers */
            flushGlobalBatch(env)
          }
        )
      }
    );

type state = {
  lst: array(dropT),
  running: bool,
  time: int
};

let setup = (env) => {
  let lst = Array.init(500, (_) => make(Env.width(env), ((-500), (-50)), 0));
  {lst, time: 0, running: true}
};

let draw = ({lst, running, time}, env) => {
  Draw.background(Utils.color(~r=230, ~g=230, ~b=250), env);
  /*Draw.fill (Utils.color r::100 g::0 b::0) env;*/
  Utils.randomSeed(time);
  let lst =
    Array.map(
      (drop) =>
        switch (drop.y + drop.yspeed * (time - drop.time)) {
        | y when y > Env.height(env) + 500 => make(Env.width(env), ((-500), (-50)), time)
        | y when y < (-500) =>
          make(Env.width(env), (Env.height(env) + 50, Env.height(env) + 500), time)
        | _ => drop
        },
      lst
    );
  Array.iter(
    (drop) => {
      Draw.fill(drop.color, env);
      Draw.ellipse(
        ~center=(drop.x, drop.y + drop.yspeed * (time - drop.time)),
        ~radx=Utils.remap(~value=drop.z, ~low1=0, ~high1=20, ~low2=1, ~high2=3),
        ~rady=drop.yspeed,
        env
      )
    },
    lst
  );
  {lst, running, time: running ? time + 1 : time}
};

/*let mouseDown state _env => {...state, running: false};

  let mouseUp state _env => {...state, running: true};

  let mouseDragged ({time} as state) env => {
    let (pmouseX, _) = Env.pmouse env;
    let (mouseX, _) = Env.mouse env;
    let newTime = time - (pmouseX - mouseX);
    {...state, time: newTime}
  };*/
/*run ::setup ::draw ::mouseDown ::mouseUp ::mouseDragged ();*/
run(~setup, ~draw, ());
