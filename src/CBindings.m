#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <caml/callback.h>
#include <caml/bigarray.h>

#include <Foundation/Foundation.h>

#import "ViewController.h"
#import <OpenGLES/ES2/glext.h>
#import <stdint.h>

#import <GLKit/GLKit.h>

void bigarray_unsafe_blit(value arr1, value arr2, value offset, value numOfBytes) {
  char *arr1Data = Caml_ba_data_val(arr1);
  char *arr2Data = Caml_ba_data_val(arr2);
  memcpy(arr2Data + Int_val(offset) * Int_val(numOfBytes), arr1Data, caml_ba_byte_size(Caml_ba_array_val(arr1)));
}

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

/** These are unique to ios */

void setContext(value s, value c) {
  id s2 = (id)(void *)Field(s, 0);
  GameViewController *game = (GameViewController *)s2;
  game.context = (EAGLContext *)Field(c, 0);
}

void setPreferredFramesPerSecond(value s, value f) {
  id s2 = (id)(void *)Field(s, 0);
  GameViewController *game = (GameViewController *)s2;
  game.preferredFramesPerSecond = Int_val(f);
}

void setDrawableDepthFormat(value s, value f) {
  GLKView *view = (GLKView *)Field(s, 0);
  view.drawableDepthFormat = Int_val(f);
}

void setCurrentContext(value c) {
  [EAGLContext setCurrentContext:(EAGLContext *)Field(c, 0)];
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

void reasonglMain(GameViewController *viewController) {
  CAMLparam0();
  CAMLlocal1(ocamlViewController);
  value *reasongl_main = caml_named_value("reasonglMain");
  ocamlViewController = caml_alloc_small(1, 0);
  Field(ocamlViewController, 0) = (long)viewController;
  caml_callback(*reasongl_main, ocamlViewController);
  CAMLreturn0;
}

void reasonglUpdate(GameViewController *s) {
  static dispatch_once_t onceToken;
  static value *closure_f;
  dispatch_once(&onceToken, ^{
    closure_f = caml_named_value("reasonglUpdate");
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
