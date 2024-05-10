#include "utils.h"

float convertToPositive(float number) {
  return number < 0 ? -number : number;
}

float convertToNegative(float number) {
  return number > 0 ? -number : number;
}