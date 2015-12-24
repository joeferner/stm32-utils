
#include "test.h"
#include "math.h"
#include <stdio.h>

int tests_run;

static char* all_tests();
static char* math_test();

int main(int argc, char* argv[]) {
  printf("-------- BEGIN TEST --------\n");
  char* result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  } else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}

static char* all_tests() {
  mu_run_test(math_test);
  return 0;
}
