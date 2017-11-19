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
