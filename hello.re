type contextT;

type gameViewControllerT;

type openGLT =
  | EAGLRenderingAPIOpenGLES1
  | EAGLRenderingAPIOpenGLES2
  | EAGLRenderingAPIOpenGLES3;

type _GLKViewDrawableDepthFormatT =
  | GLKViewDrawableDepthFormatNone
  | GLKViewDrawableDepthFormat16
  | GLKViewDrawableDepthFormat24;

external makeContext : openGLT => option contextT = "newEAGLContext";

type _GLKViewT;

external setContext : 'GLKViewT => contextT => unit = "setContext";

external getView : gameViewControllerT => _GLKViewT = "getGLKView";

external setDrawableDepthFormat : _GLKViewT => _GLKViewDrawableDepthFormatT => unit = "setDrawableDepthFormat";

external isNil : 'a => bool = "isNil";

external setCurrentContext : contextT => unit = "setCurrentContext";

/* type programT; */
/* external glCreateProgram : unit => programT = "glCreateProgramwrapper"; */
module Constants = {
  let vertex_shader = 35633;
  let fragment_shader = 35632;
  let depth_test = 2929;
  let array_buffer = 34962;
  let float_ = 5126;
  let static_draw = 35044;
};

type programT;

type shaderT;

/* external clearColor : context::contextT => r::float => g::float => b::float => a::float => unit = "clearColor"; */
external createProgram : context::contextT => programT = "createProgram";

external createShader : context::contextT => shaderType::int => shaderT = "createShader";

external attachShader : context::contextT => program::programT => shader::shaderT => unit = "attachShader";

external deleteShader : context::contextT => shader::shaderT => unit = "deleteShader";

external shaderSource : context::contextT => shader::shaderT => source::string => unit = "shaderSource";

external compileShader : context::contextT => shader::shaderT => unit = "compileShader";

external linkProgram : context::contextT => program::programT => unit = "linkProgram";

/* external useProgram : context::contextT => program::programT => unit = "useProgram"; */
external getShaderInfoLog : context::contextT => shader::shaderT => string = "getShaderInfoLog";

external getProgramInfoLog : context::contextT => program::programT => string = "getProgramInfoLog";

type uniformT;

external getUniformLocation : context::contextT => program::programT => name::string => uniformT = "getUniformLocation";

type _GLKVertexAttrib =
  | GLKVertexAttribPosition
  | GLKVertexAttribNormal
  | GLKVertexAttribColor
  | GLKVertexAttribTexCoord0
  | GLKVertexAttribTexCoord1;

external enable : context::contextT => int => unit = "enable";

type vertexArrayT = int;

external genVertexArrays : context::contextT => vertexArrayT = "genVertexArrays";

external _bindVertexArray : context::contextT => vertexArray::int => unit = "bindVertexArray";

let bindVertexArray ::context vertexArray::(vertexArray: vertexArrayT) =>
  _bindVertexArray ::context ::vertexArray;

let unbindVertexArray ::context => _bindVertexArray ::context vertexArray::0;

type bufferT;

type attributeT;

external createBuffer : context::contextT => bufferT = "createBuffer";

external bindBuffer : context::contextT => target::int => buffer::bufferT => unit = "bindBuffer";

type bigarrayT;

external bufferData : context::contextT => target::int => data::bigarrayT => usage::int => unit = "bufferData";

external getAttribLocation : context::contextT => program::programT => name::string => attributeT = "getAttribLocation";

external enableVertexAttribArray : context::contextT => attribute::attributeT => unit = "enableVertexAttribArray";

external vertexAttribPointer : context::contextT =>
                               attribute::attributeT =>
                               size::int =>
                               type_::int =>
                               normalize::bool =>
                               stride::int =>
                               offset::int =>
                               unit = "vertexAttribPointerByte" "vertexAttribPointer";

external setProgram : gameViewControllerT => programT => unit = "setProgram";

external setUmvp : gameViewControllerT => uniformT => unit = "setUmvp";

external setVertexArray : gameViewControllerT => vertexArrayT => unit = "setVertexArray";

external setVertexBuffer : gameViewControllerT => bufferT => unit = "setVertexBuffer";

external makeFloat32Array : int => array float => bigarrayT = "makeFloat32Array";

module Bigarray = {
  type t 'a 'b;
  type float64_elt;
  type float32_elt;
  type int16_unsigned_elt;
  type int16_signed_elt;
  type int8_unsigned_elt;
  type int8_signed_elt;
  type int_elt;
  type int32_elt;
  type int64_elt;
  type kind 'a 'b =
    | Float64 :kind float float64_elt
    | Float32 :kind float float32_elt
    | Int16 :kind int int16_signed_elt
    | Uint16 :kind int int16_unsigned_elt
    | Int8 :kind int int8_signed_elt
    | Uint8 :kind int int8_unsigned_elt
    | Char :kind char int8_unsigned_elt
    | Int :kind int int_elt
    | Int64 :kind int64 int64_elt
    | Int32 :kind int32 int32_elt;
  external createFloat64array : int => t float float64_elt = "createFloat64array";
  external createFloat32array : int => t float float32_elt = "createFloat32array";
  external createInt16array : int => t int int16_signed_elt = "createInt16array";
  external createUint16array : int => t int int16_unsigned_elt = "createUint16array";
  external createInt8array : int => t int int8_signed_elt = "createInt8array";
  external createUint8array : int => t int int8_unsigned_elt = "createUint8array";
  external createChararray : int => t char int8_unsigned_elt = "createChararray";
  external createIntarray : int => t int int_elt = "createIntarray";
  external createInt64array : int => t int64 int64_elt = "createInt64array";
  external createInt32array : int => t int32 int32_elt = "createInt32array";
  external getSize : t 'a 'b => int = "getSize";
  let create (type a) (type b) (k: kind a b) (size: int) :t a b =>
    switch k {
    | Float64 => createFloat64array size
    | Float32 => createFloat32array size
    | Int16 => createInt16array size
    | Uint16 => createUint16array size
    | Int8 => createInt8array size
    | Uint8 => createUint8array size
    | Char => createChararray size
    | Int => createIntarray size
    | Int64 => createInt64array size
    | Int32 => createInt32array size
    };
  /* let of_array: kind 'a 'b => array 'a => t 'a 'b; */
  /* let dim arr => getSize arr; */
  /* let get: t 'a 'b => int => 'a; */
  /* let set: t 'a 'b => int => 'a => unit; */
  /* let sub: t 'a 'b => offset::int => len::int => t 'a 'b; */
};

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

let vertexData =
  makeFloat32Array
    36
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
    |];

let setupGL vc context => {
  setCurrentContext context;
  let program = createProgram ::context;
  let vertexShader = createShader ::context shaderType::Constants.vertex_shader;
  shaderSource ::context shader::vertexShader source::vertexShaderSource;
  compileShader ::context shader::vertexShader;
  print_endline (getShaderInfoLog ::context shader::vertexShader);
  attachShader ::context ::program shader::vertexShader;
  let fragmentShader = createShader ::context shaderType::Constants.fragment_shader;
  shaderSource ::context shader::fragmentShader source::fragmentShaderSource;
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
  enable ::context Constants.depth_test;
  let vertexArray = genVertexArrays ::context;
  bindVertexArray ::context ::vertexArray;
  setVertexArray vc vertexArray;
  let vertexBuffer = createBuffer ::context;
  bindBuffer ::context target::Constants.array_buffer buffer::vertexBuffer;
  setVertexBuffer vc vertexBuffer;
  bufferData
    ::context target::Constants.array_buffer data::vertexData usage::Constants.static_draw;
  let aVertexPosition = getAttribLocation ::context ::program name::"aVertexPosition";
  enableVertexAttribArray ::context attribute::aVertexPosition;
  vertexAttribPointer
    ::context
    attribute::aVertexPosition
    size::3
    type_::Constants.float_
    normalize::false
    stride::24
    offset::0;
  let aVertexColor = getAttribLocation ::context ::program name::"aVertexColor";
  enableVertexAttribArray ::context attribute::aVertexColor;
  vertexAttribPointer
    ::context
    attribute::aVertexColor
    size::3
    type_::Constants.float_
    normalize::false
    stride::24
    offset::12;
  /* unbindVertexArray ::context; */
  print_endline @@ "program log info " ^ getProgramInfoLog ::context ::program
};

let f (vc: gameViewControllerT) => {
  switch (makeContext EAGLRenderingAPIOpenGLES2) {
    | None => 
      failwith "context was nil"
    | Some context =>
      setContext vc context;
      let view = getView vc;
      setContext view context;
      setDrawableDepthFormat view GLKViewDrawableDepthFormat24;
      setupGL vc context
  };
};

Callback.register "main" f;
