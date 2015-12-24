
#include "test.h"
#include "../math.h"

static char* math_trig_int16_atan2deg();
static char* math_testSmallestDeltaBetweenAnglesInDegrees();

char* math_test() {
  mu_run_test(math_trig_int16_atan2deg);
  mu_run_test(math_testSmallestDeltaBetweenAnglesInDegrees);
  return NULL;
}

static char* math_trig_int16_atan2deg() {
  mu_assert_equals_int(0, trig_int16_atan2deg(0, 0));
  mu_assert_equals_int(0, trig_int16_atan2deg(1, 0));
  mu_assert_equals_int(90, trig_int16_atan2deg(0, 1));
  mu_assert_equals_int(180, trig_int16_atan2deg(-1, 0));
  mu_assert_equals_int(270, trig_int16_atan2deg(0, -1));
  return NULL;
}

static char* math_testSmallestDeltaBetweenAnglesInDegrees() {
  mu_assert_equals_int(0, smallestDeltaBetweenAnglesInDegrees(0, 0));
  mu_assert_equals_int(1, smallestDeltaBetweenAnglesInDegrees(0, 1));
  mu_assert_equals_int(-1, smallestDeltaBetweenAnglesInDegrees(1, 0));
  mu_assert_equals_int(2, smallestDeltaBetweenAnglesInDegrees(359, 1));
  mu_assert_equals_int(-2, smallestDeltaBetweenAnglesInDegrees(1, 359));
  mu_assert_equals_int(180, smallestDeltaBetweenAnglesInDegrees(0, 180));
  mu_assert_equals_int(-179, smallestDeltaBetweenAnglesInDegrees(0, 181));
  return NULL;
}
