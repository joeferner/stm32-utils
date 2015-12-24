
#ifndef _UTILS_TEST_H_
#define _UTILS_TEST_H_

#include <stdio.h>
#include <stdint.h>

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_assert_equals_int(expected, found) do { if ((expected)!=(found)) { printf("FAIL: expected: %d found: %d (%s:%d)\n", expected, found, __FILE__, __LINE__); return "not equal"; } } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; if (message) return message; } while (0)
extern int tests_run;

#endif
