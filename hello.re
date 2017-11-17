module RGLConstants = {
  let triangles = 4;

let triangle_strip = 5;

let texture0 = 33984;

let texture1 = 33985;

let texture2 = 33986;

let texture_2d = 3553;

let blend = 3042;

let texture_wrap_s = 10242;

let texture_wrap_t = 10243;

let clamp_to_edge = 33071;

let src_alpha = 770;

let one_minus_src_alpha = 771;

let dst_alpha = 772;

let depth_test = 2929;

let rgb = 6407;

let rgba = 6408;

let triangle_fan = 6;

let array_buffer = 34962;

let element_array_buffer = 34963;

let array_buffer_binding = 34964;

let element_array_buffer_binding = 34965;

let stream_draw = 35040;

let static_draw = 35044;

let dynamic_draw = 35048;

let buffer_size = 34660;

let buffer_usage = 34661;

let float_ = 5126;

let unsigned_int = 5125;

let current_vertex_attrib = 34342;

let fragment_shader = 35632;

let vertex_shader = 35633;

let max_vertex_attribs = 34921;

let max_vertex_uniform_vectors = 36347;

let max_varying_vectors = 36348;

let max_combined_texture_image_units = 35661;

let max_vertex_texture_image_units = 35660;

let max_texture_image_units = 34930;

let max_fragment_uniform_vectors = 36349;

let shader_type = 35663;

let delete_status = 35712;

let link_status = 35714;

let validate_status = 35715;

let attached_shaders = 35717;

let active_uniforms = 35718;

let active_attributes = 35721;

let shading_language_version = 35724;

let current_program = 35725;

let compile_status = 35713;

let vendor = 7936;

let renderer = 7937;

let version = 7938;

let float_vec2 = 35664;

let float_vec3 = 35665;

let float_vec4 = 35666;

let int_vec2 = 35667;

let int_vec3 = 35668;

let int_vec4 = 35669;

let bool_ = 35670;

let bool_vec2 = 35671;

let bool_vec3 = 35672;

let bool_vec4 = 35673;

let float_mat2 = 35674;

let float_mat3 = 35675;

let float_mat4 = 35676;

let sampler_2d = 35678;

let sampler_cube = 35680;

let unpack_flip_y_webgl = 37440;

let unpack_premultiply_alpha_webgl = 37441;

let context_lost_webgl = 37442;

let unpack_colorspace_conversion_webgl = 37443;

let browser_default_webgl = 37444;

let vertex_attrib_array_enabled = 34338;

let vertex_attrib_array_size = 34339;

let vertex_attrib_array_stride = 34340;

let vertex_attrib_array_type = 34341;

let vertex_attrib_array_normalized = 34922;

let vertex_attrib_array_pointer = 34373;

let vertex_attrib_array_buffer_binding = 34975;

let depth_buffer_bit = 256;

let stencil_buffer_bit = 1024;

let color_buffer_bit = 16384;

let unsigned_short = 5123;

let unsigned_byte = 5121;

let texture_mag_filter = 10240;

let texture_min_filter = 10241;

let linear = 9729;

let linear_mipmap_nearest = 9985;

};

/*type programT;

external createProgram : unit => programT = "TglCreateProgram";

type shaderT;*/

let gl_vertex_shader = 35633;

let gl_fragment_shader = 35632;

/*external createShader : int => shaderT = "TglCreateShader";

external attachShader : program::programT => shader::shaderT => unit = "TglAttachShader";

external deleteShader : shaderT => unit = "TglDeleteShader";

external shaderSource : shaderT => array string => unit = "TglShaderSource";

external compileShader : shaderT => unit = "TglCompileShader";

external linkProgram : programT => unit = "TglLinkProgram";

external useProgram : programT => unit = "TglUseProgram";

type bufferT;*/

let gl_array_buffer = 34962;

let gl_element_array_buffer = 34963;

let gl_pixel_pack_buffer = 35051;

let gl_pixel_unpack_buffer = 35052;

/*external bindBuffer : target::int => buffer::bufferT => unit = "TglBindBuffer";

/* might not work because passing stack pointer instead of heap pointer (see warning) */
external genBuffers : int => array bufferT = "TglGenBuffers";

external genBuffer : unit => bufferT = "TglGenBuffer";

external clearColor : red::float => green::float => blue::float => alpha::float => unit = "TglClearColor";

type textureT;

/* might not work because passing stack pointer instead of heap pointer (see warning) */
external genTextures : int => array textureT = "TglGenTextures";

external genTexture : unit => textureT = "TglGenTexture";*/

let gl_texture0 = 33984;

let gl_texture1 = 33985;

let gl_texture2 = 33986;

let gl_texture3 = 33987;

let gl_texture4 = 33988;

let gl_texture5 = 33989;

let gl_texture6 = 33990;

let gl_texture7 = 33991;

let gl_texture8 = 33992;

let gl_texture9 = 33993;

let gl_texture10 = 33994;

let gl_texture11 = 33995;

let gl_texture12 = 33996;

let gl_texture13 = 33997;

let gl_texture14 = 33998;

let gl_texture15 = 33999;

let gl_texture16 = 34000;

let gl_texture17 = 34001;

let gl_texture18 = 34002;

let gl_texture19 = 34003;

let gl_texture20 = 34004;

let gl_texture21 = 34005;

let gl_texture22 = 34006;

let gl_texture23 = 34007;

let gl_texture24 = 34008;

let gl_texture25 = 34009;

let gl_texture26 = 34010;

let gl_texture27 = 34011;

let gl_texture28 = 34012;

let gl_texture29 = 34013;

let gl_texture30 = 34014;

let gl_texture31 = 34015;

/*external activeTexture : context::contextT => int => unit = "TglActiveTexture";*/

let gl_texture_1d = 3552;

let gl_texture_2d = 3553;

let gl_texture_3d = 32879;

let gl_texture_cube_map = 34067;

/*external bindTexture : context::contextT => target::int => texture::textureT => unit = "TglBindTexture";*/

let gl_texture_mag_filter = 10240;

let gl_texture_min_filter = 10241;

let gl_texture_wrap_s = 10242;

let gl_texture_wrap_t = 10243;

let gl_texture_min_lod = 33082;

let gl_texture_max_lod = 33083;

let gl_texture_base_level = 33084;

let gl_texture_max_level = 33085;

let gl_texture_wrap_r = 32882;

let gl_texture_priority = 32870;

let gl_texture_compare_mode = 34892;

let gl_texture_compare_func = 34893;

/* last 2 are part of glext, not sure if this is actually available in webgl. */
let gl_depth_texture_mode = 34891;

let gl_generate_mipmap = 33169;

/*external texParameteri : target::int => pname::int => param::int => unit = "TglTexParameteri";*/

let gl_alpha_test = 3008;

let gl_auto_normal = 3456;

let gl_blend = 3042;

let gl_clip_plane0 = 12288;

let gl_clip_plane1 = 12289;

let gl_clip_plane2 = 12290;

let gl_clip_plane3 = 12291;

let gl_clip_plane4 = 12292;

let gl_clip_plane5 = 12293;

let gl_color_logic_op = 3058;

let gl_color_material = 2903;

let gl_color_sum = 33880;

let gl_color_table = 32976;

let gl_convolution_1d = 32784;

let gl_convolution_2d = 32785;

let gl_cull_face = 2884;

let gl_depth_test = 2929;

let gl_dither = 3024;

let gl_fog = 2912;

let gl_histogram = 32804;

let gl_index_logic_op = 3057;

let gl_light0 = 16384;

let gl_light1 = 16385;

let gl_light2 = 16386;

let gl_light3 = 16387;

let gl_light4 = 16388;

let gl_light5 = 16389;

let gl_light6 = 16390;

let gl_light7 = 16391;

let gl_lighting = 2896;

let gl_line_smooth = 2848;

let gl_line_stipple = 2852;

let gl_map1_color_4 = 3472;

let gl_map1_index = 3473;

let gl_map1_normal = 3474;

let gl_map1_texture_coord_1 = 3475;

let gl_map1_texture_coord_2 = 3476;

let gl_map1_texture_coord_3 = 3477;

let gl_map1_texture_coord_4 = 3478;

let gl_map1_vertex_3 = 3479;

let gl_map1_vertex_4 = 3480;

let gl_map2_color_4 = 3504;

let gl_map2_index = 3505;

let gl_map2_normal = 3506;

let gl_map2_texture_coord_1 = 3507;

let gl_map2_texture_coord_2 = 3508;

let gl_map2_texture_coord_3 = 3509;

let gl_map2_texture_coord_4 = 3510;

let gl_map2_vertex_3 = 3511;

let gl_map2_vertex_4 = 3512;

let gl_minmax = 32814;

let gl_multisample = 32925;

let gl_normalize = 2977;

let gl_point_smooth = 2832;

/* only in glext */
let gl_point_sprite = 34913;

let gl_polygon_offset_fill = 32823;

let gl_polygon_offset_line = 10754;

let gl_polygon_offset_point = 10753;

let gl_polygon_smooth = 2881;

let gl_polygon_stipple = 2882;

let gl_post_color_matrix_color_table = 32978;

let gl_post_convolution_color_table = 32977;

let gl_rescale_normal = 32826;

let gl_sample_alpha_to_coverage = 32926;

let gl_sample_alpha_to_one = 32927;

let gl_sample_coverage = 32928;

let gl_separable_2d = 32786;

let gl_scissor_test = 3089;

let gl_stencil_test = 2960;

let gl_texture_gen_s = 3168;

let gl_texture_gen_t = 3169;

let gl_texture_gen_r = 3170;

let gl_texture_gen_q = 3171;

/* only in glext */
let gl_vertex_program_point_size = 34370;

/* only in glext */
let gl_vertex_program_two_side = 34371;

/*external enable : int => unit = "TglEnable";

*/
external disable : int => unit = "TglDisable" [@@noalloc];
let gl_zero = 0;

let gl_one = 1;

let gl_src_color = 768;

let gl_one_minus_src_color = 769;

let gl_src_alpha = 770;

let gl_one_minus_src_alpha = 771;

let gl_dst_alpha = 772;

let gl_one_minus_dst_alpha = 773;

let gl_dst_color = 774;

let gl_one_minus_dst_color = 775;

let gl_src_alpha_saturate = 776;

let gl_constant_color = 32769;

let gl_one_minus_constant_color = 32770;

let gl_constant_alpha = 32771;

let gl_one_minus_constant_alpha = 32772;

/*external readPixels_RGBA : x::int =>
                           y::int =>
                           width::int =>
                           height::int =>
                           Bigarray.Array1.t int Bigarray.int8_unsigned_elt Bigarray.c_layout = "TglReadPixels_RGBA";*/

let gl_proxy_texture_2d = 32868;

let gl_texture_cube_map_positive_x = 34069;

let gl_texture_cube_map_negative_x = 34070;

let gl_texture_cube_map_positive_y = 34071;

let gl_texture_cube_map_negative_y = 34072;

let gl_texture_cube_map_positive_z = 34073;

let gl_texture_cube_map_negative_z = 34074;

let gl_proxy_texture_cube_map = 34075;

let gl_alpha = 6406;

let gl_alpha4 = 32827;

let gl_alpha8 = 32828;

let gl_alpha12 = 32829;

let gl_alpha16 = 32830;

let gl_compressed_alpha = 34025;

let gl_compressed_luminance = 34026;

let gl_compressed_luminance_alpha = 34027;

let gl_compressed_intensity = 34028;

let gl_compressed_rgb = 34029;

let gl_compressed_rgba = 34030;

let gl_depth_component = 6402;

let gl_depth_component16 = 33189;

let gl_depth_component24 = 33190;

let gl_depth_component32 = 33191;

let gl_luminance = 6409;

let gl_luminance4 = 32831;

let gl_luminance8 = 32832;

let gl_luminance12 = 32833;

let gl_luminance16 = 32834;

let gl_luminance4_alpha4 = 32835;

let gl_luminance6_alpha2 = 32836;

let gl_luminance8_alpha8 = 32837;

let gl_luminance12_alpha4 = 32838;

let gl_luminance12_alpha12 = 32839;

let gl_luminance16_alpha16 = 32840;

let gl_intensity = 32841;

let gl_intensity4 = 32842;

let gl_intensity8 = 32843;

let gl_intensity12 = 32844;

let gl_intensity16 = 32845;

let gl_r3_g3_b2 = 10768;

let gl_rgb4 = 32847;

let gl_rgb5 = 32848;

let gl_rgb8 = 32849;

let gl_rgb10 = 32850;

let gl_rgb12 = 32851;

let gl_rgb16 = 32852;

let gl_rgba2 = 32853;

let gl_rgba4 = 32854;

let gl_rgb5_a1 = 32855;

let gl_rgba8 = 32856;

let gl_rgb10_a2 = 32857;

let gl_rgba12 = 32858;

let gl_rgba16 = 32859;

let gl_sluminance_alpha = 35908;

let gl_sluminance8_alpha8 = 35909;

let gl_sluminance = 35910;

let gl_sluminance8 = 35911;

let gl_srgb = 35904;

let gl_srgb8 = 35905;

let gl_srgb_alpha = 35906;

let gl_srgb8_alpha8 = 35907;

/*external texImage2D_RGBA : target::int =>
                           level::int =>
                           width::int =>
                           height::int =>
                           border::int =>
                           data::Bigarray.Array1.t 'a 'b Bigarray.c_layout =>
                           unit = "TglTexImage2D_RGBA_bytecode" "TglTexImage2D_RGBA_native";

type uniformT;



*/


let gl_stream_draw = 35040;

let gl_stream_read = 35041;

let gl_stream_copy = 35042;

let gl_static_draw = 35044;

let gl_static_read = 35045;

let gl_static_copy = 35046;

let gl_dynamic_draw = 35048;

let gl_dynamic_read = 35049;

let gl_dynamic_copy = 35050;

/*external bufferData : target::int =>
                      data::Bigarray.Array1.t 'a 'b Bigarray.c_layout =>
                      usage::int =>
                      unit = "TglBufferData";


*/

let gl_color_buffer_bit = 16384;

let gl_depth_buffer_bit = 256;

let gl_accum_buffer_bit = 512;

let gl_stencil_buffer_bit = 1024;

/*

external getUniformLocation : program::programT => name::string => uniformT = "TglGetUniformLocation";

type attribT;

external getAttribLocation : program::programT => name::string => attribT = "TglGetAttribLocation";

external enableVertexAttribArray : attribT => unit = "TglEnableVertexAttribArray";
*/
let gl_byte = 5120;

let gl_unsigned_byte = 5121;

let gl_short = 5122;

let gl_unsigned_short = 5123;

let gl_int = 5124;

let gl_unsigned_int = 5125;

let gl_float = 5126;

let gl_double = 5130;

/*external vertexAttribPointer : index::attribT =>
                               size::int =>
                               typ::int =>
                               normalized::bool =>
                               stride::int =>
                               offset::int =>
                               unit = "TglVertexAttribPointer_bytecode"
                                      "TglVertexAttribPointer_native";
*/
let gl_shader_type = 35663;

let gl_delete_status = 35712;

let gl_compile_status = 35713;

let gl_link_status = 35714;

let gl_validate_status = 35715;

let gl_info_log_length = 35716;

let gl_attached_shaders = 35717;

let gl_active_uniforms = 35718;

let gl_active_uniform_max_length = 35719;

let gl_shader_source_length = 35720;

let gl_active_attributes = 35721;

let gl_active_attribute_max_length = 35722;

/*external getProgramiv : program::programT => pname::int => int = "TglGetProgramiv";

external getShaderiv : shader::shaderT => pname::int => int = "TglGetShaderiv";

external getShaderInfoLog : shaderT => string = "TglGetShaderInfoLog";

external getProgramInfoLog : programT => string = "TglGetProgramInfoLog";

external getShaderSource : shaderT => string = "TglGetShaderSource";
*/
let gl_points = 0;

let gl_lines = 1;

let gl_line_loop = 2;

let gl_line_strip = 3;

let gl_triangles = 4;

let gl_triangle_strip = 5;

let gl_triangle_fan = 6;

let gl_quads = 7;

let gl_quad_strip = 8;

let gl_polygon = 9;

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

external setContext : 'GLKViewT => contextT => unit = "setContext" [@@noalloc];
external setPreferredFramesPerSecond : 'GLKViewT => int => unit = "setPreferredFramesPerSecond" [@@noalloc];

external getView : gameViewControllerT => _GLKViewT = "getGLKView";

external setDrawableDepthFormat : _GLKViewT => _GLKViewDrawableDepthFormatT => unit = "setDrawableDepthFormat" [@@noalloc];



/*external isNil : 'a => bool = "isNil";*/

/*type textureT;

/* might not work because passing stack pointer instead of heap pointer (see warning) */
external genTextures : context::contextT => int => array textureT = "TglGenTextures";

external genTexture : context::contextT => textureT = "TglGenTexture";*/
external blendFunc : context::contextT => sfactor::int => dfactor::int => unit = "TglBlendFunc" [@@noalloc];

external setCurrentContext : contextT => unit = "setCurrentContext" [@@noalloc];

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

external clear : context::contextT => int => unit = "TglClear" [@@noalloc];

external viewport : context::contextT => x::int => y::int => width::int => height::int => unit = "TglViewport" [@@noalloc];

/* external clearColor : context::contextT => r::float => g::float => b::float => a::float => unit = "clearColor"; */
external createProgram : context::contextT => programT = "TglCreateProgram";

external createShader : context::contextT => shaderType::int => shaderT = "TglCreateShader";

external attachShader : context::contextT => program::programT => shader::shaderT => unit = "TglAttachShader";

external deleteShader : context::contextT => shader::shaderT => unit = "TglDeleteShader";

external shaderSource : context::contextT => shader::shaderT => source::(array string) => unit = "TglShaderSource";

external compileShader : context::contextT => shader::shaderT => unit = "TglCompileShader";

external linkProgram : context::contextT => program::programT => unit = "TglLinkProgram";

 external useProgram : context::contextT => programT => unit = "TglUseProgram"; 
external getShaderInfoLog : context::contextT => shader::shaderT => string = "TglGetShaderInfoLog";

external getProgramInfoLog : context::contextT => program::programT => string = "TglGetProgramInfoLog";

type uniformT;
external uniform1f : location::uniformT => val::float => unit = "TglUniform1f"[@@noalloc];
external uniform1i : context::contextT => location::uniformT => value::int => unit = "TglUniform1i" [@@noalloc];
external getUniformLocation : context::contextT => program::programT => name::string => uniformT = "TglGetUniformLocation";

type _GLKVertexAttrib =
  | GLKVertexAttribPosition
  | GLKVertexAttribNormal
  | GLKVertexAttribColor
  | GLKVertexAttribTexCoord0
  | GLKVertexAttribTexCoord1;

external enable : context::contextT => int => unit = "TglEnable" [@@noalloc];

type vertexArrayT;

external genVertexArray : context::contextT => vertexArrayT = "TglGenVertexArrayOES";

external bindVertexArray : context::contextT => vertexArray::vertexArrayT => unit = "TglBindVertexArrayOES" [@@noalloc];

/*let bindVertexArray ::context vertexArray::(vertexArray: vertexArrayT) =>
  _bindVertexArray ::context ::vertexArray;*/

/*let unbindVertexArray ::context => _bindVertexArray ::context vertexArray::0;*/

type bufferT;

type attributeT;

external uniformMatrix4fv : 
  context::contextT => location::uniformT => transpose::bool => value::'a => unit = "TglUniformMatrix4fv"[@@noalloc];

external createBuffer : context::contextT => int => array bufferT = "TglGenBuffers";

external bindBuffer : context::contextT => target::int => buffer::bufferT => unit = "TglBindBuffer" [@@noalloc];

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
   external ofArrayFloat64: array 'a => t 'a 'b = "ofArrayFloat64";
   external ofArrayFloat32: array 'a => t 'a 'b = "ofArrayFloat32";
   let of_array (type a) (type b) (k: kind a b) (arr: array a) : t a b => switch k {
    | Float64 => ofArrayFloat64 arr
    | Float32 => ofArrayFloat32 arr
    | Int16 => failwith "not implemented"
    | Uint16 => failwith "not implemented"
    | Int8 => failwith "not implemented"
    | Uint8 => failwith "not implemented"
    | Char => failwith "not implemented"
    | Int => failwith "not implemented"
    | Int64 => failwith "not implemented"
    | Int32 => failwith "not implemented"
   };
  external dim: t 'a 'b => int = "bigarrayDim";
  /*external get: t 'a 'b => int => 'a = "bigarrayGet"; */
  external setFloat64: t 'a 'b => int => 'a => unit = "bigarraySetFloat64" [@@noalloc];
  external setFloat32: t 'a 'b => int => 'a => unit = "bigarraySetFloat32" [@@noalloc];
  external setUint16: t 'a 'b => int => 'a => unit = "bigarraySetUint16" [@@noalloc];
  external getUint16: t 'a 'b => int => 'a = "bigarrayGetUint16";
  
  external subFloat32: t 'a 'b => offset::int => len::int => t 'a 'b = "bigarraySubFloat32";
  external subUnit16: t 'a 'b => offset::int => len::int => t 'a 'b = "bigarraySubUint16";
};
external bufferData : context::contextT => target::int => data::Bigarray.t 'a 'b => usage::int => unit = "bufferData" [@@noalloc];

external getAttribLocation : context::contextT => program::programT => name::string => attributeT = "TglGetAttribLocation";

external enableVertexAttribArray : context::contextT => attribute::attributeT => unit = "TglEnableVertexAttribArray" [@@noalloc];

external vertexAttribPointer : context::contextT =>
                               attribute::attributeT =>
                               size::int =>
                               type_::int =>
                               normalize::bool =>
                               stride::int =>
                               offset::int =>
                               unit = "TglVertexAttribPointer_bytecode" "TglVertexAttribPointer_native" [@@noalloc];

/*external setProgram : gameViewControllerT => programT => unit = "setProgram";*/

/*external setUmvp : gameViewControllerT => uniformT => unit = "setUmvp";*/

/*external setVertexArray : gameViewControllerT => vertexArrayT => unit = "setVertexArray";*/

/*external setVertexBuffer : gameViewControllerT => bufferT => unit = "setVertexBuffer";*/

external clearColor : context::contextT => red::float => green::float => blue::float => alpha::float => unit = "TglClearColor" [@@noalloc];

/*external glGenTextures : context::contextT => count::int => array textureT = "TglGenTextures";*/

external drawElements : context::contextT => mode::int => count::int => type_::int => offset::int => unit = "TglDrawElements" [@@noalloc];

external getError : unit => int = "TglGetError";

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
        out::t =>
        left::float =>
        right::float =>
        bottom::float =>
        top::float =>
        near::float =>
        far::float => unit = "Mat4_ortho_byte" "Mat4_ortho_native";
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
  vertexArray: Bigarray.t float Bigarray.float32_elt,
  elementArray: Bigarray.t int Bigarray.int16_unsigned_elt,
  mutable vertexPtr: int,
  mutable elementPtr: int,
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
  strokeColor: option colorT,
  strokeWeight: int,
  strokeCap: strokeCapT,
  fillColor: option colorT
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
  mutable style: styleT,
};

module Env = {
  let width _ => 375;
  let height _ => 667;
};
  let circularBufferSize = 6 * 10000;
  let vertexSize = 8;
let setupGL vc context => {
  setCurrentContext context;
  viewport ::context x::(-1) y::(-1) width::(Env.width ()) height::(Env.height ());
  clearColor ::context red::0. green::0. blue::0. alpha::1.;
  clear
    ::context
    (16384 lor 256);

  /** Camera is a simple record containing one matrix used to project a point in 3D onto the screen. **/
  let camera = {projectionMatrix: Mat4.create ()};
  let buffers = createBuffer ::context 2;
  let vertexBuffer = buffers.(0);
  let elementBuffer = buffers.(1);
  let program = createProgram ::context;
  let vertexShader = createShader ::context shaderType::gl_vertex_shader;
  shaderSource ::context shader::vertexShader source::[|vertexShaderSource|];
  compileShader ::context shader::vertexShader;
  print_endline @@ "vertexShader logs: " ^ (getShaderInfoLog ::context shader::vertexShader);
  attachShader ::context ::program shader::vertexShader;
  let fragmentShader = createShader ::context shaderType::gl_fragment_shader;
  shaderSource ::context shader::fragmentShader source::[|fragmentShaderSource|];
  compileShader ::context shader::fragmentShader;
  print_endline @@ "fragmentShader logs: " ^ (getShaderInfoLog ::context shader::fragmentShader);
  attachShader ::context ::program shader::fragmentShader;
  linkProgram ::context ::program;
  print_endline @@ "program logs: " ^  (getProgramInfoLog ::context ::program);
  deleteShader ::context shader::vertexShader;
  deleteShader ::context shader::fragmentShader;
  /*setProgram vc program;*/
  useProgram ::context program;

  /** Get the attribs ahead of time to be used inside the render function **/
  let aVertexPosition =
    getAttribLocation ::context ::program name::"aVertexPosition";
  enableVertexAttribArray ::context attribute::aVertexPosition;
  let aVertexColor =
    getAttribLocation ::context ::program name::"aVertexColor";
  enableVertexAttribArray ::context attribute::aVertexColor;
  let pMatrixUniform =
    getUniformLocation ::context ::program name::"uPMatrix";
    /* @HACK this function is fuckd */
  uniformMatrix4fv
    ::context location::pMatrixUniform transpose::false value::camera.projectionMatrix;
  /*setUmvp vc pMatrixUniform;*/
  
  /** Get attribute and uniform locations for later usage in the draw code. **/
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

  /** Load a dummy texture. This is because we're using the same shader for things with and without a texture */
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

  /** Enable blend and tell OpenGL how to blend. */
  enable ::context RGLConstants.blend;
  blendFunc
    ::context sfactor::RGLConstants.src_alpha dfactor::RGLConstants.one_minus_src_alpha;

  /**
   * Will mutate the projectionMatrix to be an ortho matrix with the given boundaries.
   * See this link for quick explanation of what this is.
   * https://shearer12345.github.io/graphics/assets/projectionPerspectiveVSOrthographic.png
   */
  Mat4.ortho
    out::camera.projectionMatrix
    left::0.
    right::(float_of_int @@ Env.width ())
    bottom::(float_of_int @@ Env.height ())
    top::0.
    near::(-1024.)
    far::1024.;
  {
    camera,
    vertexArrayPtr: genVertexArray ::context,
    gl: context,
    batch: {
      vertexArray:
        Bigarray.create
          Bigarray.Float32 (circularBufferSize * vertexSize),
      elementArray: Bigarray.create Bigarray.Uint16 circularBufferSize,
      vertexPtr: 0,
      elementPtr: 0,
    },
    style:{
      fillColor: Some {r: 0, g: 0, b: 0},
      strokeWeight: 10,
      strokeCap: Round,
      strokeColor: Some {r: 0, g: 0, b: 0}
    },
    vertexBuffer,
    elementBuffer,
    aVertexPosition,
    aVertexColor,
    pMatrixUniform,
  }
};

let globalRender = ref None;

let f (vc: gameViewControllerT) => {
  switch (makeContext EAGLRenderingAPIOpenGLES2) {
    | None => 
      failwith "context was nil"
    | Some context =>
      setContext vc context;
      setPreferredFramesPerSecond vc 60;
      let view = getView vc;
      setContext view context;
      setDrawableDepthFormat view GLKViewDrawableDepthFormat24;
      let env = setupGL vc context;
      switch !globalRender {
        | None => failwith "this shouldn't happen"
        | Some render => render env
      };
  };
};

Callback.register "main" f;


let toColorFloat i => float_of_int i /. 255.;


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
let addRectToGlobalBatch
    env
    bottomRight::(x1, y1)
    bottomLeft::(x2, y2)
    topRight::(x3, y3)
    topLeft::(x4, y4)
    color::{r, g, b} => {
  /*maybeFlushBatch texture::None el::6 vert::32 env;*/
  let setFloat32 = Bigarray.setFloat32;
  let (r, g, b) = (toColorFloat r, toColorFloat g, toColorFloat b);
  let i = env.batch.vertexPtr;
  let vertexArrayToMutate = env.batch.vertexArray;
  setFloat32 vertexArrayToMutate (i + 0) x1;
  setFloat32 vertexArrayToMutate (i + 1) y1;
  setFloat32 vertexArrayToMutate (i + 2) r;
  setFloat32 vertexArrayToMutate (i + 3) g;
  setFloat32 vertexArrayToMutate (i + 4) b;
  setFloat32 vertexArrayToMutate (i + 5) 1.;
  setFloat32 vertexArrayToMutate (i + 6) 0.0;
  setFloat32 vertexArrayToMutate (i + 7) 0.0;
  setFloat32 vertexArrayToMutate (i + 8) x2;
  setFloat32 vertexArrayToMutate (i + 9) y2;
  setFloat32 vertexArrayToMutate (i + 10) r;
  setFloat32 vertexArrayToMutate (i + 11) g;
  setFloat32 vertexArrayToMutate (i + 12) b;
  setFloat32 vertexArrayToMutate (i + 13) 1.;
  setFloat32 vertexArrayToMutate (i + 14) 0.0;
  setFloat32 vertexArrayToMutate (i + 15) 0.0;
  setFloat32 vertexArrayToMutate (i + 16) x3;
  setFloat32 vertexArrayToMutate (i + 17) y3;
  setFloat32 vertexArrayToMutate (i + 18) r;
  setFloat32 vertexArrayToMutate (i + 19) g;
  setFloat32 vertexArrayToMutate (i + 20) b;
  setFloat32 vertexArrayToMutate (i + 21) 1.;
  setFloat32 vertexArrayToMutate (i + 22) 0.0;
  setFloat32 vertexArrayToMutate (i + 23) 0.0;
  setFloat32 vertexArrayToMutate (i + 24) x4;
  setFloat32 vertexArrayToMutate (i + 25) y4;
  setFloat32 vertexArrayToMutate (i + 26) r;
  setFloat32 vertexArrayToMutate (i + 27) g;
  setFloat32 vertexArrayToMutate (i + 28) b;
  setFloat32 vertexArrayToMutate (i + 29) 1.;
  setFloat32 vertexArrayToMutate (i + 30) 0.0;
  setFloat32 vertexArrayToMutate (i + 31) 0.0;
  let ii = i / vertexSize;
  let j = env.batch.elementPtr;
  let elementArrayToMutate = env.batch.elementArray;
  let setUint16 = Bigarray.setUint16;
  setUint16 elementArrayToMutate (j + 0) ii;
  setUint16 elementArrayToMutate (j + 1) (ii + 1);
  setUint16 elementArrayToMutate (j + 2) (ii + 2);
  setUint16 elementArrayToMutate (j + 3) (ii + 1);
  setUint16 elementArrayToMutate (j + 4) (ii + 2);
  setUint16 elementArrayToMutate (j + 5) (ii + 3);
  env.batch.vertexPtr = i + 4 * vertexSize;
  env.batch.elementPtr = j + 6
};

module Utils = {
  let white = {r: 255, g: 255, b: 255};

let black = {r: 0, g: 0, b: 0};

let red = {r: 255, g: 0, b: 0};

let green = {r: 0, g: 255, b: 0};

let blue = {r: 0, g: 0, b: 255};

let pi = 4.0 *. atan 1.0;

let two_pi = 2.0 *. pi;

let half_pi = 0.5 *. pi;

let quarter_pi = 0.25 *. pi;

let tau = two_pi;

  let foi = float_of_int;

let lookup_table: ref (array int) = ref [||];

let color ::r ::g ::b :colorT => {r, g, b};

/*Calculation Functions*/
let round i => floor (i +. 0.5);

let sq x => x * x;

let rec pow ::base ::exp =>
  switch exp {
  | 0 => 1
  | 1 => base
  | n =>
    let b = pow ::base exp::(n / 2);
    b * b * (
      if (n mod 2 == 0) {
        1
      } else {
        base
      }
    )
  };

let constrain ::amt ::low ::high => max (min amt high) low;

let remapf ::value ::low1 ::high1 ::low2 ::high2 =>
  low2 +. (high2 -. low2) *. ((value -. low1) /. (high1 -. low1));

let remap ::value ::low1 ::high1 ::low2 ::high2 =>
  int_of_float (
    remapf
      value::(foi value)
      low1::(foi low1)
      high1::(foi high1)
      low2::(foi low2)
      high2::(foi high2)
  );

let norm ::value ::low ::high =>
  remapf ::value low1::low high1::high low2::0. high2::1.;

let randomf ::min ::max => Random.float (max -. min) +. min;

let random ::min ::max => Random.int (max - min) + min;

let randomSeed seed => Random.init seed;

let randomGaussian () => {
  let u1 = ref 0.0;
  let u2 = ref 0.0;
  while (!u1 <= min_float) {
    u1 := Random.float 1.0;
    u2 := Random.float 1.0
  };
  sqrt ((-2.0) *. log !u1) *. cos (two_pi *. !u2)
};

let lerpf ::low ::high => remapf low1::0. high1::1. low2::low high2::high;

let lerp ::low ::high ::value =>
  int_of_float (lerpf low::(foi low) high::(foi high) ::value);

let distf p1::(x1: float, y1: float) p2::(x2: float, y2: float) => {
  let dx = x2 -. x1;
  let dy = y2 -. y1;
  sqrt (dx *. dx +. dy *. dy)
};

let dist p1::(x1, y1) p2::(x2, y2) =>
  distf p1::(foi x1, foi y1) p2::(foi x2, foi y2);

let magf vec => distf p1::(0., 0.) p2::vec;

let mag vec => dist p1::(0, 0) p2::vec;

let lerpColor ::low ::high ::value => {
  r: lerp low::low.r high::high.r ::value,
  g: lerp low::low.g high::high.g ::value,
  b: lerp low::low.b high::high.b ::value
};

let degrees x => 180.0 /. pi *. x;

let radians x => pi /. 180.0 *. x;

let noise x y z => {
  let p = !lookup_table;
  let fade t => t *. t *. t *. (t *. (t *. 6.0 -. 15.0) +. 10.0);
  let grad hash x y z =>
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
  let xi = int_of_float x land 255;
  let yi = int_of_float y land 255;
  let zi = int_of_float z land 255;
  let xf = x -. floor x;
  let yf = y -. floor y;
  let zf = z -. floor z;
  let u = fade xf;
  let v = fade yf;
  let w = fade zf;
  let aaa = p.(p.(p.(xi) + yi) + zi);
  let aba = p.(p.(p.(xi) + (yi + 1)) + zi);
  let aab = p.(p.(p.(xi) + yi) + (zi + 1));
  let abb = p.(p.(p.(xi) + (yi + 1)) + (zi + 1));
  let baa = p.(p.(p.(xi + 1) + yi) + zi);
  let bba = p.(p.(p.(xi + 1) + (yi + 1)) + zi);
  let bab = p.(p.(p.(xi + 1) + yi) + (zi + 1));
  let bbb = p.(p.(p.(xi + 1) + (yi + 1)) + (zi + 1));
  let x1 =
    lerpf low::(grad aaa xf yf zf) high::(grad baa (xf -. 1.0) yf zf) value::u;
  let x2 =
    lerpf
      low::(grad aba xf (yf -. 1.0) zf)
      high::(grad bba (xf -. 1.0) (yf -. 1.0) zf)
      value::u;
  let y1 = lerpf low::x1 high::x2 value::v;
  let x1 =
    lerpf
      low::(grad aab xf yf (zf -. 1.0))
      high::(grad bab (xf -. 1.0) yf (zf -. 1.0))
      value::u;
  let x2 =
    lerpf
      low::(grad abb xf (yf -. 1.0) (zf -. 1.0))
      high::(grad bbb (xf -. 1.0) (yf -. 1.0) (zf -. 1.0))
      value::u;
  let y2 = lerpf low::x1 high::x2 value::v;
  (lerpf low::y1 high::y2 value::w +. 1.0) /. 2.0
};

let shuffle array => {
  let array = Array.copy array;
  let length = Array.length array;
  for i in 0 to (256 - 1) {
    let j = Random.int (length - i);
    let tmp = array.(i);
    array.(i) = array.(i + j);
    array.(i + j) = tmp
  };
  array
};

let noiseSeed seed => {
  let state = Random.get_state ();
  Random.init seed;
  let array = Array.make 256 0;
  let array = Array.mapi (fun i _ => i) array;
  let array = shuffle array;
  let double_array = Array.append array array;
  lookup_table := double_array;
  Random.set_state state
};
};

let drawArc
    env
    (xCenterOfCircle: float, yCenterOfCircle: float)
    (radx: float)
    (rady: float)
    (start: float)
    (stop: float)
    (isPie: bool)
    {r, g, b} => {
  let noOfFans = int_of_float (radx +. rady) / 4 + 10;
  /*maybeFlushBatch texture::None vert::(8 * noOfFans) el::(3 * noOfFans) env;*/
  let pi = 4.0 *. atan 1.0;
  let anglePerFan = 2. *. pi /. float_of_int noOfFans;
  let (r, g, b) = (toColorFloat r, toColorFloat g, toColorFloat b);
  /*print_endline @@ "r " ^ (string_of_float r) ^ "g " ^ (string_of_float g) ^ "b " ^ string_of_float b;*/
  let verticesData = env.batch.vertexArray;
  let elementData = env.batch.elementArray;
  let setFloat32 = Bigarray.setFloat32;
  let setUint16 = Bigarray.setUint16;
  let getUint16 = Bigarray.getUint16;
  let vertexArrayOffset = env.batch.vertexPtr;
  let elementArrayOffset = env.batch.elementPtr;
  let start_i =
    if isPie {
      /* Start one earlier and force the first point to be the center */
      int_of_float (start /. anglePerFan) - 2
    } else {
      int_of_float (start /. anglePerFan) - 1
    };
  let stop_i = int_of_float (stop /. anglePerFan) - 1;
  for i in start_i to stop_i {
    let (xCoordinate, yCoordinate) =
      (
        if (isPie && i - start_i == 0) {
          (
            /* force the first point to be the center */
            xCenterOfCircle,
            yCenterOfCircle
          )
        } else {
          let angle = anglePerFan *. float_of_int (i + 1);
          (
            xCenterOfCircle +. cos angle *. radx,
            yCenterOfCircle +. sin angle *. rady
          )
        }
      );
    let ii = (i - start_i) * vertexSize + vertexArrayOffset;
    setFloat32 verticesData (ii + 0) xCoordinate;
    setFloat32 verticesData (ii + 1) yCoordinate;
    setFloat32 verticesData (ii + 2) r;
    setFloat32 verticesData (ii + 3) g;
    setFloat32 verticesData (ii + 4) b;
    setFloat32 verticesData (ii + 5) 1.0;
    setFloat32 verticesData (ii + 6) 0.0;
    setFloat32 verticesData (ii + 7) 0.0;
    /* For the first three vertices, we don't do any deduping. Then for the subsequent ones, we'll actually
       have 3 elements, one pointing at the first vertex, one pointing at the previously added vertex and one
       pointing at the current vertex. This mimicks the behavior of triangle_fan. */
    if (i - start_i < 3) {
      setUint16 elementData (i - start_i + elementArrayOffset) (ii / vertexSize)
    } else {
      /* We've already added 3 elements, for i = 0, 1 and 2. From now on, we'll add 3 elements _per_ i.
         To calculate the correct offset in `elementData` we remove 3 from i as if we're starting from 0 (the
         first time we enter this loop i = 3), then for each i we'll add 3 elements (so multiply by 3) BUT for
         i = 3 we want `jj` to be 3 so we shift everything by 3 (so add 3). Everything's also shifted by
         `elementArrayOffset` */
      let jj = (i - start_i - 3) * 3 + elementArrayOffset + 3;
      setUint16 elementData jj (vertexArrayOffset / vertexSize);
      setUint16 elementData (jj + 1) (getUint16 elementData (jj - 1));
      setUint16 elementData (jj + 2) (ii / vertexSize)
    }
  };
  env.batch.vertexPtr = env.batch.vertexPtr + noOfFans * vertexSize;
  env.batch.elementPtr = env.batch.elementPtr + (stop_i - start_i - 3) * 3 + 3
};

module Draw = {
  let fill color (env: glEnv) =>
    env.style = {...env.style, fillColor: Some color};
  let background color (env: glEnv) => {
    clear
      context::env.gl
      (16384 lor 256);
    let w = float_of_int (Env.width env);
    let h = float_of_int (Env.height env);
    addRectToGlobalBatch
      env
      bottomRight::(w, h)
      bottomLeft::(0., h)
      topRight::(w, 0.)
      topLeft::(0., 0.)
      ::color
  };
  
  let drawEllipse env center (radx: float) (rady: float) c =>
    drawArc env center radx rady 0. Utils.tau false c;
  
   let ellipsef ::center ::radx ::rady (env: glEnv) => {
    switch env.style.fillColor {
    | None => () /* Don't draw fill */
    | Some fill => drawEllipse env center radx rady fill
    };
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

let ellipse center::(cx, cy) ::radx ::rady (env: glEnv) =>
  ellipsef
    center::(float_of_int cx, float_of_int cy)
    radx::(float_of_int radx)
    rady::(float_of_int rady)
    env;
};





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

let make w (ymin, ymax) time => {
  let z = Utils.random min::0 max::20;
  {
    x: Utils.random min::0 max::w,
    y: Utils.random min::ymin max::ymax,
    z,
    len: Utils.remap value::z low1::0 high1::20 low2::10 high2::20,
    yspeed: Utils.remap value::z low1::0 high1::20 low2::5 high2::15,
    color:
      Utils.lerpColor
        low::Utils.white
        high::(Utils.color r::138 g::43 b::226)
        value::(Utils.randomf min::0.3 max::1.),
    time
  }
};

let drawGeometry
    vertexArray::(vertexArray: Bigarray.t float Bigarray.float32_elt)
    elementArray::(
      elementArray: Bigarray.t int Bigarray.int16_unsigned_elt
    )
    ::mode
    ::count
    /*::textureBuffer*/
    env => {
  
  /* Bind `vertexBuffer`, a pointer to chunk of memory to be sent to the GPU to the "register" called
     `array_buffer` */
  bindBuffer
    context::env.gl target::gl_array_buffer buffer::env.vertexBuffer;

  /** Copy all of the data over into whatever's in `array_buffer` (so here it's `vertexBuffer`) **/
  bufferData
    context::env.gl
    target::gl_array_buffer
    data::vertexArray
    usage::gl_stream_draw;

  /** Tell the GPU about the shader attribute called `aVertexPosition` so it can access the data per vertex */
  vertexAttribPointer
    context::env.gl
    attribute::env.aVertexPosition
    size::2
    type_::gl_float
    normalize::false
    stride::(vertexSize * 4)
    offset::0;

  /** Same as above but for `aVertexColor` **/
  vertexAttribPointer
    context::env.gl
    attribute::env.aVertexColor
    size::4
    type_::gl_float
    normalize::false
    stride::(vertexSize * 4)
    offset::(2 * 4);

  /** Same as above but for `aTextureCoord` **/
  /*vertexAttribPointer
    context::env.gl
    attribute::env.aTextureCoord
    size::2
    type_::gl_float
    normalize::false
    stride::(vertexSize * 4)
    offset::(6 * 4);*/

  /** Tell OpenGL about what the uniform called `uSampler` is pointing at, here it's given 0 which is what
      texture0 represent.  **/
  /*uniform1i context::env.gl location::env.uSampler value::0;*/

  /** Bind `elementBuffer`, a pointer to GPU memory to `element_array_buffer`. That "register" is used for
      the data representing the indices of the vertex. **/
  bindBuffer
    context::env.gl
    target::gl_element_array_buffer
    buffer::env.elementBuffer;

  /** Copy the `elementArray` into whatever buffer is in `element_array_buffer` **/
  bufferData
    context::env.gl
    target::gl_element_array_buffer
    data::elementArray
    usage::gl_stream_draw;
  
  uniformMatrix4fv
    context::env.gl location::env.pMatrixUniform transpose::false value::env.camera.projectionMatrix;
  /** We bind `texture` to texture_2d, like we did for the vertex buffers in some ways (I think?) **/
  /*bindTexture
    context::env.gl target::gl_texture_2d texture::textureBuffer;*/
  
  /*bindVertexArray context::env.gl vertexArray::env.vertexArrayPtr;*/
  /** Final call which actually tells the GPU to draw. **/
  drawElements
    context::env.gl ::mode ::count type_::gl_unsigned_short offset::0
};

let flushGlobalBatch env =>
  if (env.batch.elementPtr > 0) {
    /*let textureBuffer =
      switch env.batch.currTex {
      | None => env.batch.nullTex
      | Some textureBuffer => textureBuffer
      };*/
    clearColor context::env.gl red::1. green::0. blue::0. alpha::1.;
    clear
      context::env.gl
      (16384 lor 256);
    drawGeometry
      vertexArray::(
        Bigarray.subFloat32
          env.batch.vertexArray offset::0 len::env.batch.vertexPtr
      )
      elementArray::(
        Bigarray.subUnit16
          env.batch.elementArray offset::0 len::env.batch.elementPtr
      )
      mode::gl_triangles
      count::env.batch.elementPtr
      /*::textureBuffer*/
      env;
    /*env.batch.currTex = None;*/
    env.batch.vertexPtr = 0;
    env.batch.elementPtr = 0
  };
  

let run ::setup ::draw () => {
  /* Register a global render. */
  globalRender := Some (fun env => {
    let state = ref (setup env);
    Callback.register "update" (fun _ => {
      state := draw !state env;
      /** Flush buffers */
      flushGlobalBatch env;
    });
  });
};

type state = {
  lst: array dropT,
  running: bool,
  time: int
};

let setup env => {
  let lst = Array.init 500 (fun _ => make (Env.width env) ((-500), (-50)) 0);
  {lst, time: 0, running: true}
};

let draw {lst, running, time} env => {
  Draw.background (Utils.color r::230 g::230 b::250) env;
  /*Draw.fill (Utils.color r::100 g::0 b::0) env;*/
  Utils.randomSeed time;
  let lst =
    Array.map
      (
        fun drop =>
          switch (drop.y + drop.yspeed * (time - drop.time)) {
          | y when y > Env.height env + 500 =>
            make (Env.width env) ((-500), (-50)) time
          | y when y < (-500) =>
            make
              (Env.width env) (Env.height env + 50, Env.height env + 500) time
          | _ => drop
          }
      )
      lst;
  Array.iter
    (
      fun drop => {
        Draw.fill drop.color env;
        Draw.ellipse
          center::(drop.x, drop.y + drop.yspeed * (time - drop.time))
          radx::(Utils.remap value::drop.z low1::0 high1::20 low2::1 high2::3)
          rady::drop.yspeed
          env
      }
    )
    lst;
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
run ::setup ::draw ();

print_endline Test.hello;
