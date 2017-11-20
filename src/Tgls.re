open Bindings;

type textureT;

/* might not work because passing stack pointer instead of heap pointer (see warning) */
external genTextures : (~context: contextT, int) => array(textureT) = "TglGenTextures";

external genTexture : (~context: contextT) => textureT = "TglGenTexture";

external activeTexture : (~context: contextT, int) => unit = "TglActiveTexture";

external bindTexture : (~context: contextT, ~target: int, ~texture: textureT) => unit = "TglBindTexture";

[@noalloc] external blendFunc : (~context: contextT, int, int) => unit =
  "TglBlendFunc";

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


[@noalloc]
external texImage2D_RGBA :
  (
    ~target: int,
    ~level: int,
    ~width: int,
    ~height: int,
    ~border: int,
    ~data: Bigarray.Array1.t('a, 'b, Bigarray.c_layout)
  ) =>
  unit =
  "TglTexImage2D_RGBA_bytecode" "TglTexImage2D_RGBA_native";

external readPixels_RGBA :
  (~x: int, ~y: int, ~width: int, ~height: int) =>
  Bigarray.Array1.t(int, Bigarray.int8_unsigned_elt, Bigarray.c_layout) =
"TglReadPixels_RGBA";


[@noalloc] external texParameteri : (~context: contextT, ~target: int, ~pname: int, ~param: int) => unit =
"TglTexParameteri";


[@noalloc] external clear : (~context: contextT, ~mask: int) => unit = "TglClear";

[@noalloc]
external viewport : (~context: contextT, ~x: int, ~y: int, ~width: int, ~height: int) => unit =
  "TglViewport";

/* external clearColor : context::contextT => r::float => g::float => b::float => a::float => unit = "clearColor"; */
external createProgram : (~context: contextT) => programT = "TglCreateProgram";

external createShader : (~context: contextT, int) => shaderT = "TglCreateShader";

external attachShader : (~context: contextT, ~program: programT, ~shader: shaderT) => unit =
  "TglAttachShader";

external deleteShader : (~context: contextT, shaderT) => unit = "TglDeleteShader";

external shaderSource : (~context: contextT, ~shader: shaderT, ~source: array(string)) => unit =
  "TglShaderSource";

external compileShader : (~context: contextT, shaderT) => unit = "TglCompileShader";

external linkProgram : (~context: contextT, programT) => unit = "TglLinkProgram";

external useProgram : (~context: contextT, programT) => unit = "TglUseProgram";

external getShaderInfoLog : (~context: contextT, shaderT) => string =
  "TglGetShaderInfoLog";

external getProgramInfoLog : (~context: contextT, programT) => string =
  "TglGetProgramInfoLog";


[@noalloc] external getProgramiv : (~context: contextT, ~program: programT, ~pname: int) => int = "TglGetProgramiv";

[@noalloc] external getShaderiv : (~context: contextT, ~shader: shaderT, ~pname: int) => int = "TglGetShaderiv";

type uniformT;

[@noalloc] external uniform1f : (~context: contextT, ~location: uniformT, ~value: float) => unit = "TglUniform1f";

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
  (~context: contextT, ~location: uniformT, ~transpose: bool, ~value: array(float)) => unit =
  "TglUniformMatrix4fv";

[@noalloc]
external uniformMatrix4fv_glk :
  (~context: contextT, ~location: uniformT, ~transpose: bool, ~value: 'a) => unit =
  "TglUniformMatrix4fv_glk";

external createBuffers : (~context: contextT, int) => array(bufferT) = "TglGenBuffers";
external createBuffer : (~context: contextT) => bufferT = "TglGenBuffer";

[@noalloc] external bindBuffer : (~context: contextT, ~target: int, ~buffer: bufferT) => unit =
  "TglBindBuffer";

[@noalloc]
external bufferData :
  (~context: contextT, ~target: int, ~data: Bigarray.Array1.t('a, 'b, Bigarray.c_layout), ~usage: int) => unit =
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
  (~context: contextT, ~r: float, ~g: float, ~b: float, ~a: float) => unit =
  "TglClearColor";

/*external glGenTextures : context::contextT => count::int => array textureT = "TglGenTextures";*/
[@noalloc]
external drawElements :
  (~context: contextT, ~mode: int, ~count: int, ~type_: int, ~offset: int) => unit =
  "TglDrawElements";

external getError : unit => int = "TglGetError";
