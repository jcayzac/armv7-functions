#pragma once

// A few sanity checks
#ifndef __FAST_MATH__
	#error "Please add -ffast-math to your compile flags"
#endif

#ifndef __ARM_NEON__
	#error "Please add -ffpu=neon to your compile flags"
#endif

// Most needed header
#include <arm_neon.h>

// Standard defines, prefixed with ARMV7_FUNC_*.
#define ARMV7_FUNC_API static inline __attribute__((always_inline))
#define ARMV7_FUNC_PI  0x1.921FB54442D18p1f
#define ARMV7_FUNC_2PI 0x1.921FB54442D18p2f

