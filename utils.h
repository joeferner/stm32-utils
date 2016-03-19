
#ifndef _STM32LIB_UTILS_H_
#define _STM32LIB_UTILS_H_

#include <stdint.h>

#ifndef min
# define min(a,b) ( ((a) < (b)) ? (a) : (b) )
#endif
#ifndef max
# define max(a,b) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef clamp
#  define clamp(x, min, max) ( ((x) < (min)) ? (min) : ( ((x) > (max)) ? (max) : (x) ) )
#endif
#ifndef testBits
#  define testBits(x, bits) ( ((x) & (bits)) == (bits) )
#endif

#ifdef UTILS_DEBUG
#define UTILS_DEBUG_OUT(format, ...) printf("%s:%d: " format, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define UTILS_DEBUG_OUT(format, ...)
#endif

#define returnNonOKHALStatus(fn) {  \
  HAL_StatusTypeDef status = fn;    \
  if (status != HAL_OK) {           \
    return status;                  \
  }                                 \
}

#define assertNonOKHALStatus(fn) {  \
  HAL_StatusTypeDef status = fn;    \
  if (status != HAL_OK) {           \
    UTILS_DEBUG_OUT("assert %d\n", status); \
    while(1);                       \
  }                                 \
}

uint32_t swapEndian(uint32_t val);
void strTrim(char* str);
void strTrimLeft(char* str);
void strTrimRight(char* str);
int isWhitespace(char ch);
char* urlDecode(char* str);
void printMemory(uint8_t* buffer, uint32_t length);

#endif
