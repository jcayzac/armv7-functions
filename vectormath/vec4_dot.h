#pragma once
#include <armv7-functions/common.h>

ARMV7_FUNC_API void vec4_dot(float& result, const float32x4_t& a, const float32x4_t& b) {
	register float32x4_t tmp;
	asm volatile (
	"# dot product of %q1.xyzw with %q2.xyzw:\n\t"
	"vmul.f32  %e0, %e1, %e2\n\t"
	"vmla.f32  %e0, %f1, %f2\n\t"
	"vpadd.f32 %e0, %e0\n\t"
	: "=&w" (tmp) : "w" (a), "w" (b) : );
	result = vgetq_lane_f32(tmp, 0);
}

