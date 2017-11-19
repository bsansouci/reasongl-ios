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
  ((double *)Field(arr, 1))[Int_val(i)] = Double_val(v);
}

void bigarraySetFloat32(value arr, value i, value v) {
  ((float *)Field(arr, 1))[Int_val(i)] = (float)Double_val(v);
}

void bigarraySetUint16(value arr, value i, value v) {
  ((uint16_t *)Field(arr, 1))[Int_val(i)] = (uint16_t)Int_val(v);
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
