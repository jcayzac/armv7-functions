#pragma once

#include <armv7-functions/config.h>
#include <armv7-functions/config-defaults.h>

// A few sanity checks
#ifndef __FAST_MATH__
	#error "Please add -ffast-math to your compile flags"
#endif

#ifndef __ARM_NEON__
	#error "Please add -mfpu=neon to your compile flags"
#endif

// Most needed header
#include <arm_neon.h>

// Standard defines, prefixed with ARMV7_FUNC_*.
#define ARMV7_FUNC_API static inline __attribute__((always_inline))
#define ARMV7_FUNC_PI  0x1.921FB54442D18p1f
#define ARMV7_FUNC_2PI 0x1.921FB54442D18p2f

// Standard types
namespace ARM7_FUNC_NAMESPACE {
	typedef float32x4_t   vector3_t;
	typedef float32x4_t   vector4_t;
	typedef float32x4x4_t matrix44_t;
}

