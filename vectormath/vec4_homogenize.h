#pragma once
#include <armv7-functions/common.h>

ARMV7_FUNC_API void vec4_homogenize(float32x4_t& vec) {
	register float32x4_t _1;
	register float32x4_t _2;
	register float32x4_t _3;
	asm volatile (
	"\n\t# make %q0 homogenous\n\t"
	"vdup.f32   %q1, %f0[1] @ %q1 = vec4(%q0.w)\n\t"
	"vrecpe.f32 %q2, %q1		@ %q2 = approx(1/%q1)\n\t"
	"vrecps.f32 %q3, %q2, %q1   @ %q3 = next approximation step\n\t"
#ifndef QUICK_AND_DIRTY_NORMALIZATION
	"vmul.f32   %q2, %q2, %q3   @ %q2 = refine(%q2)\n\t"
	"vrecps.f32 %q3, %q2, %q1   @ %q3 = next approximation step\n\t"
#endif
	"vmul.f32   %q0, %q2, %q3   @ %q0.xyzw *= 1/%q1\n\t\n\t"
	: "=w" (vec), "=w" (_1), "=w" (_2), "=w" (_3)
	: "0" (vec)
	:
	);
}

