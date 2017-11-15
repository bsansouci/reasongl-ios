#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <caml/callback.h>

#include <Foundation/Foundation.h>

#import "ViewController.h"
#import <OpenGLES/ES2/glext.h>
#import <stdint.h>

#import <GLKit/GLKit.h>

static value oreturn(void *v) {
  CAMLparam0();
  CAMLlocal1(ret);
  ret = caml_alloc_small(1, 0);
  Field(ret, 0) = (long)v;
  return ret;
}

static value unboxed(GLuint i) {
  return Val_int(i);
}

CAMLprim value TglGetError() {
  CAMLparam0();
  CAMLreturn(Val_int(glGetError()));
}

CAMLprim value TglCreateProgram(value context) {
  CAMLparam1(context);
  CAMLreturn(Val_int(glCreateProgram()));
}

CAMLprim value TglCreateShader(value context, value shaderType) {
  CAMLparam2(context, shaderType);
  CAMLreturn(Val_int(glCreateShader(Int_val(shaderType))));
}

void TglAttachShader(value context, value program, value shader) {
  CAMLparam3(context, program, shader);
  glAttachShader(Int_val(program), Int_val(shader));
  CAMLreturn0;
}

void TglDeleteShader(value context, value shader) {
  CAMLparam2(context, shader);
  glDeleteShader(Int_val(shader));
  CAMLreturn0;
}

void TglShaderSource(value context, value shader, value stringArray) {
  CAMLparam3(context, shader, stringArray);
  int numOfElements = Wosize_val(stringArray);
  const GLchar **arrOfElements = malloc(sizeof(GLchar *) * numOfElements);
  GLint *arrOfLengths = malloc(sizeof(GLint) * numOfElements);
  for(int i = 0; i < numOfElements; ++i) {
    value e = Field(stringArray, i);
    arrOfElements[i] = String_val(e);
    arrOfLengths[i] = caml_string_length(e);
  }
  glShaderSource(Int_val(shader), numOfElements, arrOfElements, arrOfLengths);
  CAMLreturn0;
}

void TglCompileShader(value context, value shader) {
  CAMLparam2(context, shader);
  glCompileShader(Int_val(shader));
  CAMLreturn0;
}

void TglLinkProgram(value context, value program) {
  CAMLparam2(context, program);
  glLinkProgram(Int_val(program));
  CAMLreturn0;
}

void TglUseProgram(value context, value program) {
  CAMLparam2(context, program);
  glUseProgram(Int_val(program));
  CAMLreturn0;
}

CAMLprim value TglGenBuffers(value context, value count) {
  CAMLparam2(context, count);
  CAMLlocal1(ret);

  int size = Int_val(count);
  unsigned int *buffers = malloc(sizeof(unsigned int) * size);
  glGenBuffers(size, buffers);

  ret = caml_alloc_small(size, 0);
  for (int i = 0; i < size; ++i) {
    Field(ret, i) = Val_int(buffers[i]);
  }
  CAMLreturn(ret);
}

CAMLprim value TglGenBuffer(value context) {
  CAMLparam1(context);
  unsigned int buffers = 0;
  glGenBuffers(1, &buffers);
  CAMLreturn(Val_int(buffers));
}

void TglClearColor(value context, value r, value g, value b, value a) {
  CAMLparam5(context, r, g, b, a);
  glClearColor(Double_val(r), Double_val(g), Double_val(b), Double_val(a));
  CAMLreturn0;
}

void TglBindBuffer(value context, value kind, value buffer) {
  CAMLparam3(context, kind, buffer);
  glBindBuffer(Int_val(kind), Int_val(buffer));
  CAMLreturn0;
}

CAMLprim value TglGenTextures(value context, value count) {
  CAMLparam2(context, count);
  CAMLlocal1(ret);

  int size = Int_val(count);
  unsigned int *textures = malloc(sizeof(unsigned int) * size);
  glGenTextures(size, textures);

  ret = caml_alloc_small(size, 0);
  for (int i = 0; i < size; ++i) {
    Field(ret, i) = Val_int(textures[i]);
  }

  CAMLreturn(ret);
}

CAMLprim value TglGenTexture(value context) {
  CAMLparam1(context);
  unsigned int textures = 0;
  glGenTextures(1, &textures);
  CAMLreturn(Val_int(textures));
}

void TglActiveTexture(value context, value textureUnit) {
  CAMLparam2(context, textureUnit);
  glActiveTexture(Int_val(textureUnit));
  CAMLreturn0;
}

void TglBindTexture(value context, value kind, value texture) {
  CAMLparam3(context, kind, texture);
  glBindTexture(Int_val(kind), Int_val(texture));
  CAMLreturn0;
}

void TglTexParameteri(value context, value kind, value pname, value param) {
  CAMLparam4(context, kind, pname, param);
  glTexParameteri(Int_val(kind), Int_val(pname), Int_val(param));
  CAMLreturn0;
}

void TglEnable(value context, value thing) {
  CAMLparam2(context, thing);
  glEnable(Int_val(thing));
  CAMLreturn0;
}

void TglDisable(value context, value thing) {
  CAMLparam2(context, thing);
  glDisable(Int_val(thing));
  CAMLreturn0;
}

void TglBlendFunc(value context, value sfactor, value dfactor) {
  CAMLparam3(context, sfactor, dfactor);
  glBlendFunc(Int_val(sfactor), Int_val(dfactor));
  CAMLreturn0;
}

// @Todo Comment both of those functions out because ... big array...
// Will port later.
//      Ben - July 11th 2017
// 
// CAMLprim value TglReadPixels_RGBA(value x, value y, value width, value height) {
//   CAMLparam4(x, y, width, height);
//   CAMLlocal1(ret);

//   // Allocate a pointer for caml_ba_alloc's sake.
//   intnat *size = malloc(sizeof(intnat));
//   *size = Int_val(width) * Int_val(height) * 4;

//   char *data = malloc(*size * sizeof(char));

//   glReadPixels(Int_val(x), Int_val(y), Int_val(width), Int_val(height), GL_RGBA, GL_UNSIGNED_BYTE, data);

//   // return array of size `size` of dimension 1 of uint8 (char).
//   ret = caml_ba_alloc(CAML_BA_UINT8, 1, data, size);
//   CAMLreturn(ret);
// }

// void TglTexImage2D_RGBA_native(value target, value level, value width, value height, value border, value data) {
//   CAMLparam5(target, level, width, height, border);
//   CAMLxparam1(data);
//   glTexImage2D(Int_val(target), Int_val(level), 4, Int_val(width), Int_val(height), Int_val(border), GL_RGBA, GL_UNSIGNED_BYTE, Caml_ba_data_val(data));
//   CAMLreturn0;
// }

// void TglTexImage2D_RGBA_bytecode(value * argv, int argn) {
//   TglTexImage2D_RGBA_native(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
// }

void setCurrentContext(value c) {
  CAMLparam1(c);
  [EAGLContext setCurrentContext:(EAGLContext *)Field(c, 0)];
  CAMLreturn0;
}

void TglUniform1i(value context, value location, value v) {
  CAMLparam3(context, location, v);
  glUniform1i(Int_val(location), Int_val(v));
  CAMLreturn0;
}

void TglUniform1f(value context, value location, value v) {
  CAMLparam3(context, location, v);
  glUniform1f(Int_val(location), Double_val(v));
  CAMLreturn0;
}

// Write our own bigarray wrapper. Below is that version for bufferData. We 
// could maybe just use bigarray but I haven't figured out how to compile it 
// to ios.
// 
// void TglBufferData(value target, value data, value usage) {
//   CAMLparam3(target, data, usage);
//   glBufferData(Int_val(target), caml_ba_byte_size(Caml_ba_array_val(data)), Caml_ba_data_val(data), Int_val(usage));
//   CAMLreturn0;
// }
void bufferData(value context, value constant, value data, value usage) {
  CAMLparam4(context, constant, data, usage);
  glBufferData(Int_val(constant), Field(data, 0), (GLvoid *)Field(data, 1), Int_val(usage));
  CAMLreturn0;
}

void TglViewport(value context, value x, value y, value width, value height) {
  CAMLparam5(context, x, y, width, height);
  glViewport(Int_val(x), Int_val(y), Int_val(width), Int_val(height));
  CAMLreturn0;
}

void TglClear(value context, value mask) {
  CAMLparam1(mask);
  glClear(Int_val(mask));
  CAMLreturn0;
}

CAMLprim value TglGetUniformLocation(value context, value program, value name) {
  CAMLparam3(context, program, name);
  CAMLreturn(Val_int(glGetUniformLocation(Int_val(program), String_val(name))));
}

CAMLprim value TglGetAttribLocation(value context, value program, value name) {
  CAMLparam3(context, program, name);
  CAMLreturn(Val_int(glGetAttribLocation(Int_val(program), String_val(name))));
}

void TglEnableVertexAttribArray(value context, value attrib) {
  CAMLparam2(context, attrib);
  glEnableVertexAttribArray(Int_val(attrib));
  CAMLreturn0;
}

void TglVertexAttribPointer_native(value context, value index, value size, value typ, value normalized, value stride, value offset) {
  CAMLparam5(context, index, size, typ, normalized);
  CAMLxparam2(stride, offset);
  long o = (long)Int_val(offset);
  glVertexAttribPointer(Int_val(index), Int_val(size), Int_val(typ), Bool_val(normalized), Int_val(stride), (const GLvoid *)o);
  CAMLreturn0;
}

void TglVertexAttribPointer_bytecode(value * argv, int argn) {
  TglVertexAttribPointer_native(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

CAMLprim value TglGetProgramiv(value context, value program, value pname) {
  CAMLparam3(context, program, pname);
  GLint ret;
  glGetProgramiv(Int_val(program), Int_val(pname), &ret);
  CAMLreturn(Val_int(ret));
}

CAMLprim value TglGetShaderiv(value context, value shader, value pname) {
  CAMLparam3(context, shader, pname);
  GLint ret;
  glGetShaderiv(Int_val(shader), Int_val(pname), &ret);
  CAMLreturn(Val_int(ret));
}

CAMLprim value TglGetShaderInfoLog(value context, value shader) {
  CAMLparam2(context, shader);
  CAMLlocal1(ret);

  GLint exactLength;
  glGetShaderiv(Int_val(shader), GL_INFO_LOG_LENGTH, &exactLength);
  GLchar *buffer = malloc(exactLength * sizeof(char));
  glGetShaderInfoLog(Int_val(shader), exactLength - 1, NULL, buffer);

  ret = caml_copy_string(buffer);
  CAMLreturn(ret);
}

CAMLprim value TglGetProgramInfoLog(value context, value program) {
  CAMLparam2(context, program);
  CAMLlocal1(ret);

  GLint exactLength;
  glGetProgramiv(Int_val(program), GL_INFO_LOG_LENGTH, &exactLength);

  GLchar *buffer = malloc(exactLength * sizeof(char));
  glGetProgramInfoLog(Int_val(program), exactLength - 1, NULL, buffer);
  ret = caml_copy_string(buffer);
  CAMLreturn(ret);
}

CAMLprim value TglGetShaderSource(value context, value shader) {
  CAMLparam2(context, shader);
  CAMLlocal1(ret);

  GLint exactLength;
  glGetShaderiv(Int_val(shader), GL_SHADER_SOURCE_LENGTH, &exactLength);

  GLchar *buffer = malloc(exactLength * sizeof(char));
  glGetShaderSource(Int_val(shader), exactLength - 1, NULL, buffer);
  ret = caml_copy_string(buffer);
  CAMLreturn(ret);
}

void TglDrawArrays(value context, value mode, value first, value count) {
  CAMLparam4(context, mode, first, count);
  glDrawArrays(Int_val(mode), Int_val(first), Int_val(count));
  CAMLreturn0;
}

void TglDrawElements(value context, value mode, value first, value typ, value offset) {
  CAMLparam5(context, mode, first, typ, offset);
  long o = (long)Int_val(offset);
  // printf("test before %d, %d, %d, %ld\n", Int_val(mode), Int_val(first), Int_val(typ), o);
  glDrawElements(Int_val(mode), Int_val(first), Int_val(typ), (const GLvoid *)o);
  // printf("test after\n");
  CAMLreturn0;
}

void TglUniformMatrix4fv(value context, value location, value transpose, value val) {
  CAMLparam4(context, location, transpose, val);
  // int size = Wosize_val(val);
  // float *matrix = malloc(sizeof(float) * size);
  // for (int i = 0; i < size; ++i){
  //   matrix[i] = Double_field(val, i);
  // }
  // printf("test1 %0.6f\n", ((GLKMatrix4 *)Field(val, 0))->m[0]);
  // printf("test2 %0.6f\n", ((GLKMatrix4 *)Field(val, 0))->m[1]);
  // printf("test3 %0.6f\n", ((GLKMatrix4 *)Field(val, 0))->m[2]);
  // printf("test4 %0.6f\n", ((GLKMatrix4 *)Field(val, 0))->m[3]);
  // printf("test5 %0.6f\n", ((GLKMatrix4 *)Field(val, 0))->m[4]);
  // printf("test6 %0.6f\n", ((GLKMatrix4 *)Field(val, 0))->m[5]);
  glUniformMatrix4fv(Int_val(location), 1, Bool_val(transpose), ((GLKMatrix4 *)Field(val, 0))->m);
  CAMLreturn0;
}

/* =========================================================== */
//  Here comes our "bigarray" implementation

CAMLprim value ofArrayFloat64(value arr) {
  CAMLparam1(arr);
  CAMLlocal1(ret);
  int numOfElements = Wosize_val(arr);
  int byteSize = numOfElements * sizeof(double);
  double *data = (double *)malloc(byteSize);
  for (int i = 0; i < numOfElements; i++) {
    data[i] = Double_field(arr, i);
  }
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)data;
  CAMLreturn(ret);
}

CAMLprim value ofArrayFloat32(value arr) {
  CAMLparam1(arr);
  CAMLlocal1(ret);
  int numOfElements = Wosize_val(arr);
  int byteSize = numOfElements * sizeof(float);
  float *data = (float *)malloc(byteSize);
  for (int i = 0; i < numOfElements; i++) {
    data[i] = (float)Double_field(arr, i);
  }
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)data;
  CAMLreturn(ret);
}

//  @HACK will segfault for access other than double
CAMLprim value bigarrayGet(value arr, value i) {
  CAMLparam2(arr, i);
  CAMLreturn(caml_copy_double(((double *)Field(arr, 1))[Int_val(i)]));
}

void bigarraySetFloat64(value arr, value i, value v) {
  CAMLparam3(arr, i, v);
  ((double *)Field(arr, 1))[Int_val(i)] = Double_val(v);
  CAMLreturn0;
}

void bigarraySetFloat32(value arr, value i, value v) {
  CAMLparam3(arr, i, v);
  ((float *)Field(arr, 1))[Int_val(i)] = (float)Double_val(v);
  CAMLreturn0;
}

void bigarraySetUint16(value arr, value i, value v) {
  CAMLparam3(arr, i, v);
  ((uint16_t *)Field(arr, 1))[Int_val(i)] = (uint16_t)Int_val(v);
  CAMLreturn0;
}

CAMLprim value bigarrayGetUint16(value arr, value i, value v) {
  CAMLparam3(arr, i, v);
  CAMLreturn(Val_int(((uint16_t *)Field(arr, 1))[Int_val(i)]));
}

CAMLprim value bigarrayDim() {
  printf("Dim not implemented. Dying\n");
  exit(0);
}

// @HACK
CAMLprim value bigarraySubFloat32(value arr, value offset, value length) {
  CAMLparam3(arr, offset, length);
  CAMLlocal1(ret);
  
  int byteSize = Int_val(length) * sizeof(float);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)(((float *)Field(arr, 1)) + sizeof(float) * Int_val(offset));
  CAMLreturn(ret);
}

CAMLprim value bigarraySubUint16(value arr, value offset, value length) {
  CAMLparam3(arr, offset, length);
  CAMLlocal1(ret);
  
  int byteSize = Int_val(length) * sizeof(uint16_t);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)(((uint16_t *)Field(arr, 1)) + sizeof(uint16_t) * Int_val(offset));
  CAMLreturn(ret);
}

CAMLprim value createFloat64array(value numOfElements) {
  CAMLparam1(numOfElements);
  CAMLlocal1(ret);
  int byteSize = Int_val(numOfElements) * sizeof(double);
  double *data = (double *)malloc(byteSize);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)data;
  CAMLreturn(ret);
}

CAMLprim value createFloat32array(value numOfElements) {
  CAMLparam1(numOfElements);
  CAMLlocal1(ret);
  int byteSize = Int_val(numOfElements) * sizeof(float);
  float *data = (float *)malloc(byteSize);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)data;
  CAMLreturn(ret);
}

CAMLprim value createInt16array(value numOfElements) {
  CAMLparam1(numOfElements);
  CAMLlocal1(ret);
  int byteSize = Int_val(numOfElements) * sizeof(int16_t);
  int16_t *data = (int16_t *)malloc(byteSize);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)data;
  CAMLreturn(ret);
}

CAMLprim value createUint16array(value numOfElements) {
  CAMLparam1(numOfElements);
  CAMLlocal1(ret);
  int byteSize = Int_val(numOfElements) * sizeof(uint16_t);
  uint16_t *data = (uint16_t *)malloc(byteSize);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)data;
  CAMLreturn(ret);
}

CAMLprim value createInt8array(value numOfElements) {
  CAMLparam1(numOfElements);
  CAMLlocal1(ret);
  int byteSize = Int_val(numOfElements) * sizeof(int8_t);
  int8_t *data = (int8_t *)malloc(byteSize);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)data;
  CAMLreturn(ret);
}

CAMLprim value createUint8array(value numOfElements) {
  CAMLparam1(numOfElements);
  CAMLlocal1(ret);
  int byteSize = Int_val(numOfElements) * sizeof(uint8_t);
  uint8_t *data = (uint8_t *)malloc(byteSize);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)data;
  CAMLreturn(ret);
}

CAMLprim value createChararray(value numOfElements) {
  CAMLparam1(numOfElements);
  CAMLlocal1(ret);
  int byteSize = Int_val(numOfElements) * sizeof(char);
  char *data = (char *)malloc(byteSize);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)data;
  CAMLreturn(ret);
}

CAMLprim value createIntarray(value numOfElements) {
  CAMLparam1(numOfElements);
  CAMLlocal1(ret);
  int byteSize = Int_val(numOfElements) * sizeof(int);
  int *data = (int *)malloc(byteSize);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)data;
  CAMLreturn(ret);
}

CAMLprim value createInt32array(value numOfElements) {
  CAMLparam1(numOfElements);
  CAMLlocal1(ret);
  int byteSize = Int_val(numOfElements) * sizeof(int32_t);
  int32_t *data = (int32_t *)malloc(byteSize);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)data;
  CAMLreturn(ret);
}

CAMLprim value createInt64array(value numOfElements) {
  CAMLparam1(numOfElements);
  CAMLlocal1(ret);
  int byteSize = Int_val(numOfElements) * sizeof(int64_t);
  int64_t *data = (int64_t *)malloc(byteSize);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = byteSize;
  Field(ret, 1) = (value)data;
  CAMLreturn(ret);
}

CAMLprim value getSize(value arr) {
  CAMLparam1(arr);
  CAMLreturn(Val_int(Field(arr, 0)));
}

// CAMLprim value makeFloat32Array(value size, value arr) {
//   CAMLparam2(arr, size);
//   CAMLlocal1(ret);
//   int s = Int_val(size);
//   float *data = (float *)malloc(s * sizeof(float));
//   for(int i = 0; i < s; i++) {
//     data[i] = Double_field(arr, i);
//   }
//   ret = caml_alloc_small(2, 0);
//   Field(ret, 0) = s * sizeof(float);
//   Field(ret, 1) = (long)data;
//   CAMLreturn(ret);
// }

// Vertex Array stuff
CAMLprim value TglGenVertexArrayOES(value c) {
  CAMLparam1(c);
  GLuint *vertexArray = malloc(sizeof(GLuint));
  glGenVertexArraysOES(1, vertexArray);
  CAMLreturn(Val_int(*vertexArray));
}

void TglBindVertexArrayOES(value c, value vertexArray) {
  CAMLparam2(c, vertexArray);
  // printf("glBindVertexArrayOES: %d\n", Int_val(vertexArray));
  glBindVertexArrayOES(Int_val(vertexArray));
  // printf("glBindVertexArrayOES AFTER: %d\n", Int_val(vertexArray));
  CAMLreturn0;
}

// ---------------------

// CAMLprim value isNil(value s) {
//   CAMLparam1(s);
//   CAMLreturn(Val_int((int)((id)Field(s, 0) == nil)));
// }

// CAMLprim value setProgram(value s, value program) {
//   CAMLparam2(s, program);
//   id s2 = (id)(void *)Field(s, 0);
//   GameViewController *game = (GameViewController *)s2;
//   game.program = (GLuint)Int_val(program);
//   CAMLreturn(Val_int(0));
// }

// CAMLprim value setUmvp(value s, value umvp) {
//   CAMLparam2(s, umvp);
//   id s2 = (id)(void *)Field(s, 0);
//   GameViewController *game = (GameViewController *)s2;
//   game.umvp = (GLint)Int_val(umvp);
//   CAMLreturn(Val_int(0));
// }

// CAMLprim value setVertexArray(value s, value vertexArray) {
//   CAMLparam2(s, vertexArray);
//   id s2 = (id)(void *)Field(s, 0);
//   GameViewController *game = (GameViewController *)s2;
//   game.vertexArray = (GLuint)Int_val(vertexArray);
//   CAMLreturn(Val_int(0));
// }

// CAMLprim value setVertexBuffer(value s, value vertexBuffer) {
//   CAMLparam2(s, vertexBuffer);
//   id s2 = (id)(void *)Field(s, 0);
//   GameViewController *game = (GameViewController *)s2;
//   game.vertexBuffer = (GLuint)Int_val(vertexBuffer);
//   CAMLreturn(Val_int(0));
// }


CAMLprim value setContext(value s, value c) {
  CAMLparam2(s, c);
  id s2 = (id)(void *)Field(s, 0);
  GameViewController *game = (GameViewController *)s2;
  game.context = (EAGLContext *)Field(c, 0);
  CAMLreturn(Val_int(0));
}

CAMLprim value setDrawableDepthFormat(value s, value f) {
  CAMLparam2(s, f);
  GLKView *view = (GLKView *)Field(s, 0);
  view.drawableDepthFormat = Int_val(f);
  CAMLreturn(Val_int(0));
}

CAMLprim value newEAGLContext(value num) {
  CAMLparam1(num);
  EAGLContext *ctx = [[EAGLContext alloc] initWithAPI:(Int_val(num) + 1)];
  if (ctx == NULL) {
    CAMLreturn(Val_int(0));
  }
  CAMLreturn(oreturn((void *)oreturn(ctx)));
}

CAMLprim value getGLKView(value s) {
  CAMLparam1(s);
  id s2 = (id)(void *)Field(s, 0);
  GameViewController *game = (GameViewController *)s2;
  GLKView *v = (GLKView *)game.view;
  CAMLreturn(oreturn(v));
}

void doReasonThingsWithSelf(GameViewController *s) {
  CAMLparam0();
  CAMLlocal1(ret);
  value *closure_f = caml_named_value("main");
  ret = caml_alloc_small(1, 0);
  Field(ret, 0) = (long)s;
  caml_callback(*closure_f, ret);
  CAMLreturn0;
}

void doUpdate(GameViewController *s) {
  static dispatch_once_t onceToken;
  static value *closure_f;
  dispatch_once(&onceToken, ^{
    closure_f = caml_named_value("update");
  });
  
  caml_callback(*closure_f, caml_copy_double(s.timeSinceLastDraw));
}

void Mat4_ortho_native(value out, value left, value right, value bottom, value top, value near, value far) {
  CAMLparam5(out, left, right, bottom, top);
  CAMLxparam2(near, far);
  GLKMatrix4 *m = (GLKMatrix4 *)Field(out, 0);
  GLKMatrix4 c = GLKMatrix4MakeOrtho(Double_val(left), Double_val(right), Double_val(bottom), Double_val(top), Double_val(near), Double_val(far));
  
  m->m[0] = c.m[0];
  m->m[1] = c.m[1];
  m->m[2] = c.m[2];
  m->m[3] = c.m[3];
  m->m[4] = c.m[4];
  m->m[5] = c.m[5];
  m->m[6] = c.m[6];
  m->m[7] = c.m[7];
  m->m[8] = c.m[8];
  m->m[9] = c.m[9];
  m->m[10] = c.m[10];
  m->m[11] = c.m[11];
  m->m[12] = c.m[12];
  m->m[13] = c.m[13];
  m->m[14] = c.m[14];
  m->m[15] = c.m[15];

  CAMLreturn0;
}

void Mat4_ortho_byte(value * argv, int argn) {
  Mat4_ortho_native(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

CAMLprim value Mat4_create() {
  CAMLparam0();
  CAMLlocal1(ret);
  
  GLKMatrix4 *m = malloc(sizeof(GLKMatrix4));
  m->m[0] = 1.0;
  m->m[1] = 0.0;
  m->m[2] = 0.0;
  m->m[3] = 0.0;
  
  m->m[4] = 0.0;
  m->m[5] = 1.0;
  m->m[6] = 0.0;
  m->m[7] = 0.0;
  
  m->m[8] = 0.0;
  m->m[9] = 0.0;
  m->m[10] = 1.0;
  m->m[11] = 0.0;
  
  m->m[12] = 0.0;
  m->m[13] = 0.0;
  m->m[14] = 0.0;
  m->m[15] = 1.0;
  
  ret = caml_alloc_small(1, 0);
  Field(ret, 0) = (long)m;
  CAMLreturn(ret);
}
