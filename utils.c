
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

uint32_t swapEndian(uint32_t val) {
  return ((val << 24) & 0xff000000)
         | ((val << 8) & 0x00ff0000)
         | ((val >> 8) & 0x0000ff00)
         | ((val >> 24) & 0x000000ff);
}

void strTrim(char* str) {
  strTrimLeft(str);
  strTrimRight(str);
}

void strTrimLeft(char* str) {
  char* p = str;
  char* out = str;
  while (*p && isWhitespace(*p)) {
    p++;
  }
  while (*p) {
    *out++ = *p++;
  }
}

void strTrimRight(char* str) {
  char* p = str + strlen(str) - 1;
  while (p >= str && isWhitespace(*p)) {
    *p-- = '\0';
  }
}

int isWhitespace(char ch) {
  switch (ch) {
  case '\n':
  case '\r':
  case '\t':
  case ' ':
    return 1;
  }
  return 0;
}

char* urlDecode(char* str) {
  char tmp[3];
  char* in = str;
  char* out = str;
  while (*in) {
    if (*in == '+') {
      in++;
      *out++ = ' ';
    } else if (*in == '%') {
      in++;
      tmp[0] = *in++;
      tmp[1] = *in++;
      tmp[2] = '\0';
      *out++ = (char)strtol(tmp, NULL, 16);
    } else {
      *out++ = *in++;
    }
  }
  *out = '\0';
  return str;
}

void printMemory(uint8_t* buffer, uint32_t length) {
  uint8_t col;
  for (uint32_t offset = 0; offset < length; offset += 16) {
    printf("%08lX ", offset);
    for (col = 0; col < 16; col++) {
      if (offset + col < length) {
        printf("%02X ", buffer[offset + col]);
      } else {
        printf("   ");
      }
    }
    for (col = 0; col < 16; col++) {
      if (offset + col < length) {
        char ch = buffer[offset + col];
        if (ch >= '.' && ch <= '~') {
          printf("%c", ch);
        } else {
          printf(".");
        }
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}