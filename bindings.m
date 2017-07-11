#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <caml/callback.h>

#include <Foundation/Foundation.h>

#import "ViewController.h"
#import <OpenGLES/ES2/glext.h>
#import <stdint.h>

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

// EAGLContext *globalContext;

CAMLprim value bindAttribLocation(value c, value program, value attrib, value name) {
  CAMLparam4(c, program, attrib, name);
  glBindAttribLocation(Int_val(program), Int_val(attrib), String_val(name));
  CAMLreturn(Val_int(0));
}

CAMLprim value getUniformLocation(value c, value program, value name) {
  CAMLparam3(c, program, name);
  CAMLreturn(unboxed(glGetUniformLocation(Int_val(program), String_val(name))));
}

CAMLprim value createProgram(value c) {
  CAMLparam1(c);
  NSLog(@"blabla");
  GLuint p = glCreateProgram();
  NSLog(@"program %u", p);
  CAMLreturn(unboxed(p));
}

CAMLprim value linkProgram(value c, value program) {
  CAMLparam2(c, program);
  glLinkProgram(Int_val(program));
  CAMLreturn(Val_int(0));
}

CAMLprim value compileShader(value c, value shader) {
  CAMLparam2(c, shader);
  glCompileShader(Int_val(shader));
  CAMLreturn(Val_int(0));
}

CAMLprim value attachShader(value c, value program, value shader) {
  CAMLparam3(c, program, shader);
  glAttachShader(Int_val(program), Int_val(shader));
  CAMLreturn(Val_int(0));
}

CAMLprim value deleteShader(value c, value shader) {
  CAMLparam2(c, shader);
  glDeleteShader(Int_val(shader));
  CAMLreturn(Val_int(0));
}

CAMLprim value shaderSource(value c, value shader, value source) {
  CAMLparam3(c, shader, source);
  const GLchar *sourceStr = (GLchar *)String_val(source);
  glShaderSource(Int_val(shader), 1, &sourceStr, NULL);
  CAMLreturn(Val_int(0));
}

CAMLprim value createShader(value c, value t) {
  CAMLparam2(c, t);
  CAMLreturn(unboxed(glCreateShader(Int_val(t))));
}

CAMLprim value getShaderInfoLog(value c, value s) {
  CAMLparam2(c, s);
  GLint logLength;
  GLuint shader = Int_val(s);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		GLchar *log = (GLchar *)malloc(logLength);
		glGetShaderInfoLog(shader, logLength, &logLength, log);
		CAMLreturn(caml_copy_string(log));
	} else {
    CAMLreturn(caml_copy_string(""));
  }
}

CAMLprim value getProgramInfoLog(value c, value p) {
  CAMLparam2(c, p);
  GLint logLength;
  GLuint program = Int_val(p);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		GLchar *log = (GLchar *)malloc(logLength);
		glGetProgramInfoLog(program, logLength, &logLength, log);
		CAMLreturn(caml_copy_string(log));
	} else {
    CAMLreturn(caml_copy_string(""));
  }
}

CAMLprim value setCurrentContext(value c) {
  CAMLparam1(c);
  [EAGLContext setCurrentContext:(EAGLContext *)Field(c, 0)];
  CAMLreturn(Val_int(0));
}

CAMLprim value getAttribLocation(value c, value program, value attribName) {
  CAMLparam3(c, program, attribName);
  int ret = unboxed(glGetAttribLocation(Int_val(program), String_val(attribName)));
  CAMLreturn(ret);
}

CAMLprim value enableVertexAttribArray(value c, value attrib) {
  CAMLparam2(c, attrib);
  glEnableVertexAttribArray(Int_val(attrib));
  CAMLreturn(Val_int(0));
}

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

CAMLprim value vertexAttribPointer(value c, value attrib, value size, value type_, value normalize, value stride, value offset) {
  CAMLparam5(c, attrib, size, type_, normalize);
  CAMLxparam2(stride, offset);
  glVertexAttribPointer(Int_val(attrib), Int_val(size), Int_val(type_), Bool_val(normalize), Int_val(stride), BUFFER_OFFSET(Int_val(offset)));
  CAMLreturn(Val_int(0));
}

CAMLprim value vertexAttribPointerByte(value *argv) {
  return vertexAttribPointer(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

// Vertex Buffer stuff
CAMLprim value createBuffer(value c) {
  CAMLparam1(c);
  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  CAMLreturn(Val_int(vertexBuffer));
}

CAMLprim value bindBuffer(value c, value constant, value vertexBuffer) {
  CAMLparam3(c, constant, vertexBuffer);
  glBindBuffer(Int_val(constant), Int_val(vertexBuffer));
  CAMLreturn(Val_int(0));
}

CAMLprim value bufferData(value c, value constant, value data, value usage) {
  CAMLparam4(c, constant, data, usage);
  glBufferData(Int_val(constant), Field(data, 0), (GLvoid *)Field(data, 1), Int_val(usage));
  CAMLreturn(Val_int(0));
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

CAMLprim value makeFloat32Array(value size, value arr) {
  CAMLparam2(arr, size);
  CAMLlocal1(ret);
  int s = Int_val(size);
  float *data = (float *)malloc(s * sizeof(float));
  for(int i = 0; i < s; i++) {
    data[i] = Double_field(arr, i);
  }
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = s * sizeof(float);
  Field(ret, 1) = (long)data;
  CAMLreturn(ret);
}

// Vertex Array stuff
CAMLprim value genVertexArrays(value c) {
  CAMLparam1(c);
  GLuint vertexArray;
  glGenVertexArraysOES(1, &vertexArray);
  CAMLreturn(Val_int(vertexArray));
}

CAMLprim value bindVertexArray(value c, value vertexArray) {
  CAMLparam2(c, vertexArray);
  glBindVertexArrayOES(Int_val(vertexArray));
  CAMLreturn(Val_int(0));
}

CAMLprim value enable(value c, value constant) {
  CAMLparam2(c, constant);
  glEnable(Int_val(constant));
  CAMLreturn(Val_int(0));
}

// ---------------------

CAMLprim value isNil(value s) {
  CAMLparam1(s);
  CAMLreturn(Val_int((int)((id)Field(s, 0) == nil)));
}

CAMLprim value setProgram(value s, value program) {
  CAMLparam2(s, program);
  id s2 = (id)(void *)Field(s, 0);
  GameViewController *game = (GameViewController *)s2;
  game.program = (GLuint)Int_val(program);
  CAMLreturn(Val_int(0));
}

CAMLprim value setUmvp(value s, value umvp) {
  CAMLparam2(s, umvp);
  id s2 = (id)(void *)Field(s, 0);
  GameViewController *game = (GameViewController *)s2;
  game.umvp = (GLint)Int_val(umvp);
  CAMLreturn(Val_int(0));
}

CAMLprim value setVertexArray(value s, value vertexArray) {
  CAMLparam2(s, vertexArray);
  id s2 = (id)(void *)Field(s, 0);
  GameViewController *game = (GameViewController *)s2;
  game.vertexArray = (GLuint)Int_val(vertexArray);
  CAMLreturn(Val_int(0));
}

CAMLprim value setVertexBuffer(value s, value vertexBuffer) {
  CAMLparam2(s, vertexBuffer);
  id s2 = (id)(void *)Field(s, 0);
  GameViewController *game = (GameViewController *)s2;
  game.vertexBuffer = (GLuint)Int_val(vertexBuffer);
  CAMLreturn(Val_int(0));
}


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
  Field(ret, 0) = (long)(__bridge_retained void*)s;
  caml_callback(*closure_f, ret);
  CAMLreturn0;
}
