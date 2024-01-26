#include <stdint.h>
#include <string.h>

#include "ieee754_clf.h"

typedef union {
  double dbl;
  unsigned long long bit_rep; // bit representation
} dbl_t;

float_class_t classify(double x) {
  dbl_t new_x;
  const unsigned kNumOfBytes = 64;
  const unsigned kMantissasSize = 52;
  const unsigned long long kExpMaxVal = 2047ull;
  const unsigned long long kExpMask = 2047ull << 52;
  const unsigned long long kExpAbsMask = ~kExpMask;
  const unsigned long long kAbsValMask = ~(1ull << 63);
  const unsigned long long kSignMask = 1ull << 63;
  const unsigned long long kZero = 0;
  const unsigned long long kOne = 1;
  new_x.dbl = x;
  // check sign
  if (((new_x.bit_rep & kSignMask) >> (kNumOfBytes - 1)) == kOne) {
    // has minus
    if ((((new_x.bit_rep & kAbsValMask) & kExpMask) >> kMantissasSize) ==
        kExpMaxVal) {
      return (((new_x.bit_rep & kAbsValMask) & kExpAbsMask) == kZero) ? MinusInf
                                                                      : NaN;
    } else if ((((new_x.bit_rep & kAbsValMask) & kExpMask) >> kMantissasSize) ==
               kZero) {
      return (((new_x.bit_rep & kAbsValMask) & kExpAbsMask) == kZero)
                 ? MinusZero
                 : MinusDenormal;
    } else {
      return MinusRegular;
    }
  } else {
    // hasn't minus
    if ((((new_x.bit_rep & kAbsValMask) & kExpMask) >> kMantissasSize) ==
        kExpMaxVal) {
      return (((new_x.bit_rep & kAbsValMask) & kExpAbsMask) == kZero) ? Inf
                                                                      : NaN;
    } else if ((((new_x.bit_rep & kAbsValMask) & kExpMask) >> kMantissasSize) ==
               kZero) {
      return (((new_x.bit_rep & kAbsValMask) & kExpAbsMask) == kZero)
                 ? Zero
                 : Denormal;
    } else {
      return Regular;
    }
  }
}
