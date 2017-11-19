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

external makeContext : openGLT => option(contextT) = "newEAGLContext";

type _GLKViewT;

[@noalloc] external setContext : ('GLKViewT, contextT) => unit = "setContext";

[@noalloc] external setPreferredFramesPerSecond : ('GLKViewT, int) => unit =
  "setPreferredFramesPerSecond";

external getView : gameViewControllerT => _GLKViewT = "getGLKView";

[@noalloc] external setDrawableDepthFormat : (_GLKViewT, _GLKViewDrawableDepthFormatT) => unit =
  "setDrawableDepthFormat";

/*external isNil : 'a => bool = "isNil";*/
/*type textureT;

  /* might not work because passing stack pointer instead of heap pointer (see warning) */
  external genTextures : context::contextT => int => array textureT = "TglGenTextures";

  external genTexture : context::contextT => textureT = "TglGenTexture";*/
[@noalloc] external blendFunc : (~context: contextT, ~sfactor: int, ~dfactor: int) => unit =
  "TglBlendFunc";

[@noalloc] external setCurrentContext : contextT => unit = "setCurrentContext";

/* type programT; */
/* external glCreateProgram : unit => programT = "glCreateProgramwrapper"; */
/*module Constants = {
    let vertex_shader = 35633;
    let fragment_shader = 35632;
    let depth_test = 2929;
    let array_buffer = 34962;
    let float_ = 5126;
    let static_draw = 35044;
  };*/
type programT;

type shaderT;

[@noalloc] external clear : (~context: contextT, int) => unit = "TglClear";

[@noalloc]
external viewport : (~context: contextT, ~x: int, ~y: int, ~width: int, ~height: int) => unit =
  "TglViewport";

/* external clearColor : context::contextT => r::float => g::float => b::float => a::float => unit = "clearColor"; */
external createProgram : (~context: contextT) => programT = "TglCreateProgram";

external createShader : (~context: contextT, ~shaderType: int) => shaderT = "TglCreateShader";

external attachShader : (~context: contextT, ~program: programT, ~shader: shaderT) => unit =
  "TglAttachShader";

external deleteShader : (~context: contextT, ~shader: shaderT) => unit = "TglDeleteShader";

external shaderSource : (~context: contextT, ~shader: shaderT, ~source: array(string)) => unit =
  "TglShaderSource";

external compileShader : (~context: contextT, ~shader: shaderT) => unit = "TglCompileShader";

external linkProgram : (~context: contextT, ~program: programT) => unit = "TglLinkProgram";

external useProgram : (~context: contextT, programT) => unit = "TglUseProgram";

external getShaderInfoLog : (~context: contextT, ~shader: shaderT) => string =
  "TglGetShaderInfoLog";

external getProgramInfoLog : (~context: contextT, ~program: programT) => string =
  "TglGetProgramInfoLog";

type uniformT;

[@noalloc] external uniform1f : (~location: uniformT, ~value: float) => unit = "TglUniform1f";

[@noalloc] external uniform1i : (~context: contextT, ~location: uniformT, ~value: int) => unit =
  "TglUniform1i";

external getUniformLocation : (~context: contextT, ~program: programT, ~name: string) => uniformT =
  "TglGetUniformLocation";

type _GLKVertexAttrib =
  | GLKVertexAttribPosition
  | GLKVertexAttribNormal
  | GLKVertexAttribColor
  | GLKVertexAttribTexCoord0
  | GLKVertexAttribTexCoord1;

[@noalloc] external enable : (~context: contextT, int) => unit = "TglEnable";

type vertexArrayT;

external genVertexArray : (~context: contextT) => vertexArrayT = "TglGenVertexArrayOES";

[@noalloc] external bindVertexArray : (~context: contextT, ~vertexArray: vertexArrayT) => unit =
  "TglBindVertexArrayOES";

/*let bindVertexArray ::context vertexArray::(vertexArray: vertexArrayT) =>
  _bindVertexArray ::context ::vertexArray;*/
/*let unbindVertexArray ::context => _bindVertexArray ::context vertexArray::0;*/
type bufferT;

type attributeT;

[@noalloc]
external uniformMatrix4fv :
  (~context: contextT, ~location: uniformT, ~transpose: bool, ~value: 'a) => unit =
  "TglUniformMatrix4fv";

external createBuffer : (~context: contextT, int) => array(bufferT) = "TglGenBuffers";

[@noalloc] external bindBuffer : (~context: contextT, ~target: int, ~buffer: bufferT) => unit =
  "TglBindBuffer";

module Bigarray = {
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
  external createFloat64array : int => t(float, float64_elt) = "createFloat64array";
  external createFloat32array : int => t(float, float32_elt) = "createFloat32array";
  external createInt16array : int => t(int, int16_signed_elt) = "createInt16array";
  external createUint16array : int => t(int, int16_unsigned_elt) = "createUint16array";
  external createInt8array : int => t(int, int8_signed_elt) = "createInt8array";
  external createUint8array : int => t(int, int8_unsigned_elt) = "createUint8array";
  external createChararray : int => t(char, int8_unsigned_elt) = "createChararray";
  external createIntarray : int => t(int, int_elt) = "createIntarray";
  external createInt64array : int => t(int64, int64_elt) = "createInt64array";
  external createInt32array : int => t(int32, int32_elt) = "createInt32array";
  external getSize : t('a, 'b) => int = "getSize";
  let create = (type a, type b, k: kind(a, b), size: int) : t(a, b) =>
    switch k {
    | Float64 => createFloat64array(size)
    | Float32 => createFloat32array(size)
    | Int16 => createInt16array(size)
    | Uint16 => createUint16array(size)
    | Int8 => createInt8array(size)
    | Uint8 => createUint8array(size)
    | Char => createChararray(size)
    | Int => createIntarray(size)
    | Int64 => createInt64array(size)
    | Int32 => createInt32array(size)
    };
  external ofArrayFloat64 : array('a) => t('a, 'b) = "ofArrayFloat64";
  external ofArrayFloat32 : array('a) => t('a, 'b) = "ofArrayFloat32";
  let of_array = (type a, type b, k: kind(a, b), arr: array(a)) : t(a, b) =>
    switch k {
    | Float64 => ofArrayFloat64(arr)
    | Float32 => ofArrayFloat32(arr)
    | Int16 => failwith("not implemented")
    | Uint16 => failwith("not implemented")
    | Int8 => failwith("not implemented")
    | Uint8 => failwith("not implemented")
    | Char => failwith("not implemented")
    | Int => failwith("not implemented")
    | Int64 => failwith("not implemented")
    | Int32 => failwith("not implemented")
    };
  external dim : t('a, 'b) => int = "bigarrayDim";
  /*external get: t 'a 'b => int => 'a = "bigarrayGet"; */
  [@noalloc] external setFloat64 : (t('a, 'b), int, 'a) => unit = "bigarraySetFloat64";
  [@noalloc] external setFloat32 : (t('a, 'b), int, 'a) => unit = "bigarraySetFloat32";
  [@noalloc] external setUint16 : (t('a, 'b), int, 'a) => unit = "bigarraySetUint16";
  external getUint16 : (t('a, 'b), int) => 'a = "bigarrayGetUint16";
  external subFloat32 : (t('a, 'b), ~offset: int, ~len: int) => t('a, 'b) = "bigarraySubFloat32";
  external subUnit16 : (t('a, 'b), ~offset: int, ~len: int) => t('a, 'b) = "bigarraySubUint16";
};

[@noalloc]
external bufferData :
  (~context: contextT, ~target: int, ~data: Bigarray.t('a, 'b), ~usage: int) => unit =
  "bufferData";

external getAttribLocation : (~context: contextT, ~program: programT, ~name: string) => attributeT =
  "TglGetAttribLocation";

[@noalloc]
external enableVertexAttribArray : (~context: contextT, ~attribute: attributeT) => unit =
  "TglEnableVertexAttribArray";

[@noalloc]
external vertexAttribPointer :
  (
    ~context: contextT,
    ~attribute: attributeT,
    ~size: int,
    ~type_: int,
    ~normalize: bool,
    ~stride: int,
    ~offset: int
  ) =>
  unit =
  "TglVertexAttribPointer_bytecode" "TglVertexAttribPointer_native";

/*external setProgram : gameViewControllerT => programT => unit = "setProgram";*/
/*external setUmvp : gameViewControllerT => uniformT => unit = "setUmvp";*/
/*external setVertexArray : gameViewControllerT => vertexArrayT => unit = "setVertexArray";*/
/*external setVertexBuffer : gameViewControllerT => bufferT => unit = "setVertexBuffer";*/
[@noalloc]
external clearColor :
  (~context: contextT, ~red: float, ~green: float, ~blue: float, ~alpha: float) => unit =
  "TglClearColor";

/*external glGenTextures : context::contextT => count::int => array textureT = "TglGenTextures";*/
[@noalloc]
external drawElements :
  (~context: contextT, ~mode: int, ~count: int, ~type_: int, ~offset: int) => unit =
  "TglDrawElements";

external getError : unit => int = "TglGetError";
