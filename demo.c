#include "iconv.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define BUF_SIZE 1024

int main(void) {
  iconv_t toEbcdic = iconv_open("ebcdic-xml-us","utf-8");
  if ((iconv_t)-1 == toEbcdic) {
    puts("toEbcdic open failed");
    return 1;
  }
  char *message = "Hello, world!";
  char *messagePtr = message;
  size_t messageBytesLeft = strlen(message);
  char ebcdic[BUF_SIZE] = {};
  char *ebcdicPtr = &ebcdic[0];
  size_t ebcdicBytesLeft = BUF_SIZE;
  size_t ebcdicResult = iconv(toEbcdic,
                              &messagePtr, &messageBytesLeft,
                              &ebcdicPtr, &ebcdicBytesLeft);
  printf(("%m\n"
          " message: %p\n"
          " messagePtr: %p\n"
          " messageBytesLeft: %d\n"
          " ebcdic: %p\n"
          " ebcdicPtr: %p\n"
          " ebcdicBytesLeft: %d\n"
          " ebcdicResult: %d\n"),
         message, messagePtr, messageBytesLeft,
         ebcdic, ebcdicPtr, ebcdicBytesLeft,
         ebcdicResult);
  if (-1 == ebcdicResult) {
    return 1;
  };
  if (0 != iconv_close(toEbcdic)) {
    puts("toEbcdic close failed");
    return 1;
  };
  iconv_t fromEbcdic = iconv_open("UTF-8", "ebcdic-xml-us");
  if ((iconv_t) -1 == fromEbcdic) {
    puts("fromEbcdic open failed");
    return 1;
  }
  char out[BUF_SIZE] = {};
  char *outPtr = &out[0];
  size_t outBytesLeft = BUF_SIZE;
  ebcdicPtr = &ebcdic[0];
  size_t outResult = iconv(fromEbcdic,
                           &ebcdicPtr, &ebcdicResult,
                           &outPtr, &outBytesLeft);
  printf(("%m\n"
          " ebcdic: %p\n"
          " ebcdicPtr: %p\n"
          " ebcdicResult: %d\n"
          " out: %p\n"
          " outPtr: %p\n"
          " outBytesLeft: %d\n"
          " outResult: %d\n"),
          ebcdic, ebcdicPtr, ebcdicResult,
          out, outPtr, outBytesLeft, outResult);
  if (-1 == outResult) {
    return 1;
  }
  if (0 != iconv_close(fromEbcdic)) {
    puts("fromEbcdic close failed");
    return 1;
  }
  puts(out);
  return 0;
}
