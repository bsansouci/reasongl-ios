let module Gl
/* Uncomment this to see what still needs to be done */
/* : RGLInterface.t */
 = {
  include Bindings;
  include Tgls;

  let target = "native-ios";
  module type FileT = {type t; let readFile: (~filename: string, ~cb: string => unit) => unit;};
  module File: FileT = {
    type t;
    let readFile = (~filename, ~cb) => {
      failwith("readFile not implemented");
    };
  };

  module type WindowT = {
    type t;
    let getWidth: t => int;
    let getHeight: t => int;
    let getPixelWidth: t => int;
    let getPixelHeight: t => int;
    let getPixelScale: t => float;
    let init: (~argv: array(string), (t) => unit) => unit;
    let setWindowSize: (~window: t, ~width: int, ~height: int) => unit;
    let getContext: t => contextT;
  };

  module Window: WindowT = {
    type t = {viewController: gameViewControllerT, context: contextT};
    let getWidth = (window) => 375; /** TODO make general */
    let getHeight = (window) => 667;
    /** TODO these are probably wrong */
    let getPixelWidth = (window) => getWidth(window) * 2;
    let getPixelHeight = (window) => getHeight(window) * 2;
    let getPixelScale = (window) => 2.;

    let setWindowSize = (~window, ~width, ~height) => {
      /* umm this can't happen.
      one thing we could do is have an "intrinsic size" and a "real size",
      and this makes it so we scale whatever they're drawing to the actual
      size of the phone.
      But I don't love that idea.
       */
      ()
    };

    let getContext = ({context}) => context;
    let init = (~argv: array(string), cb) => {
      Callback.register("reasonglMain", (vc: gameViewControllerT) => {
        switch (makeContext(EAGLRenderingAPIOpenGLES2)) {
        | None => failwith("Unable to setup OpenGL rendering context :(")
        | Some(context) =>
          setContext(vc, context);
          setPreferredFramesPerSecond(vc, 60);
          let view = getView(vc);
          setContext(view, context);
          setDrawableDepthFormat(view, GLKViewDrawableDepthFormat24);
          cb({viewController: vc, context})
        };
      })
    };
  };

  let render = (~window, ~mouseDown=?, ~mouseUp=?, ~mouseMove=?, ~keyDown=?, ~keyUp=?, ~windowResize=?, ~displayFunc, ()) => {
    let lastDraw = ref(Sys.time());
    Callback.register("reasonglUpdate", (_) => {
      let now = Sys.time();
      displayFunc((now -. lastDraw^) /. 1000.); /* I think it wants ms */
      lastDraw := now;
    })
  };

  let module Events: RGLEvents.t = {
    include RGLEvents.T;
    let keycodeMap = (keycode) => {
      Nothing
    }
  };

  module type Bigarray = {
    type t('a, 'b);
    type float64_elt;
    type float32_elt;
    type int16_unsigned_elt;
    type int16_signed_elt;
    type int8_unsigned_elt;
    type int8_signed_elt;
    type int_elt;
    type int32_elt;
    type int64_elt;
    type kind('a, 'b) =
      | Float64: kind(float, float64_elt)
      | Float32: kind(float, float32_elt)
      | Int16: kind(int, int16_signed_elt)
      | Uint16: kind(int, int16_unsigned_elt)
      | Int8: kind(int, int8_signed_elt)
      | Uint8: kind(int, int8_unsigned_elt)
      | Char: kind(char, int8_unsigned_elt)
      | Int: kind(int, int_elt)
      | Int64: kind(int64, int64_elt)
      | Int32: kind(int32, int32_elt);
    let create: (kind('a, 'b), int) => t('a, 'b);
    let of_array: (kind('a, 'b), array('a)) => t('a, 'b);
    let dim: t('a, 'b) => int;
    let blit: (t('a, 'b), t('a, 'b)) => unit;
    let unsafe_blit: (t('a, 'b), t('a, 'b), ~offset: int, ~numOfBytes: int) => unit;
    let get: (t('a, 'b), int) => 'a;
    let unsafe_get: (t('a, 'b), int) => 'a;
    let set: (t('a, 'b), int, 'a) => unit;
    let unsafe_set: (t('a, 'b), int, 'a) => unit;
    let sub: (t('a, 'b), ~offset: int, ~len: int) => t('a, 'b);
  };

  module Bigarray = Bigarray;




  /* TODO implement all of this */
  let disable = (~context: contextT, int) => ();
  let texParameteri = (~context: contextT, ~target: int, ~pname: int, ~param: int) => ();
  let createTexture = (~context: contextT) => failwith("Cannot create texture");
  let activeTexture = (~context: contextT, int) => ();
  let bindTexture = (~context: contextT, ~target: int, ~texture: textureT) => ();

  let drawElementsInstanced = (~context: contextT, ~mode: int, ~count: int, ~type_: int, ~indices: int, ~primcount: int) =>
    ();

  let texSubImage2D =
    (
      ~context: contextT,
      ~target: int,
      ~level: int,
      ~xoffset: int,
      ~yoffset: int,
      ~width: int,
      ~height: int,
      ~format: int,
      ~type_: int,
      ~pixels: Bigarray.t('a, 'b)
    ) =>
    ();
  let readPixels_RGBA =
    (~context: contextT, ~x: int, ~y: int, ~width: int, ~height: int) =>
    failwith("Cannot read pixels");
  type imageT;
  let getImageWidth = (image) => failwith("Not impl");
  let getImageHeight = (image) => failwith("Not impl");

  type loadOptionT =
    | LoadAuto
    | LoadL
    | LoadLA
    | LoadRGB
    | LoadRGBA;
  let loadImage =
    (~filename: string, ~loadOption, ~callback: option(imageT) => unit, unit) =>
    failwith("Not impl");
  let texImage2DWithImage = (~context: contextT, ~target: int, ~level: int, ~image: imageT) => ();


  let shaderSource = (~context, ~shader, ~source) => {
    Tgls.shaderSource(~context, ~shader, ~source=[|source|])
  };
  let getShaderSource = (~context: contextT, shaderT) => failwith("not impl");
  let drawArrays = (~context: contextT, ~mode: int, ~first: int, ~count: int) => ();

  type shaderParamsT =
    | Shader_delete_status
    | Compile_status
    | Shader_type;
  type programParamsT =
    | Program_delete_status
    | Link_status
    | Validate_status;
  let getProgramParameter =
    (~context: contextT, ~program: programT, ~paramName: programParamsT) => failwith("not impl");
  let getShaderParameter = (~context: contextT, ~shader: shaderT, ~paramName: shaderParamsT) => failwith("not impl");

  module type Mat4T = {
    type t;
    let to_array: t => array(float);
    let create: unit => t;
    let identity: (~out: t) => unit;
    let translate: (~out: t, ~matrix: t, ~vec: array(float)) => unit;
    let scale: (~out: t, ~matrix: t, ~vec: array(float)) => unit;
    let rotate: (~out: t, ~matrix: t, ~rad: float, ~vec: array(float)) => unit;
    let ortho:
      (
        ~out: t,
        ~left: float,
        ~right: float,
        ~bottom: float,
        ~top: float,
        ~near: float,
        ~far: float
      ) =>
      unit;
  };

  module Mat4: Mat4T = {
    type t = unit;
    let to_array = (()) => [||];
    let create = () => ();
    let identity: (~out: t) => t = (~out) => ();
    let translate = (~out, ~matrix, ~vec) => ();
    let scale = (~out, ~matrix, ~vec) => ();
    let rotate = (~out, ~matrix, ~rad, ~vec) => ();
    let ortho = (~out, ~left, ~right, ~bottom, ~top, ~near, ~far) => ();
  };

  let vertexAttribDivisor = (~context: contextT, ~attribute: attributeT, ~divisor: int) => ();

  let uniform2f = (~context: contextT, ~location: uniformT, ~v1: float, ~v2: float) => ();
  let uniform3f =
    (~context: contextT, ~location: uniformT, ~v1: float, ~v2: float, ~v3: float) => ();
  let uniform4f =
    (~context: contextT, ~location: uniformT, ~v1: float, ~v2: float, ~v3: float, ~v4: float) =>
    ();
  let texImage2D_RGBA =
    (
      ~context: contextT,
      ~target: int,
      ~level: int,
      ~width: int,
      ~height: int,
      ~border: int,
      ~data: Bigarray.t('a, 'b)
    ) =>
    ();




};


