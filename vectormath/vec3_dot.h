#pragma once
#include <armv7-functions/common.h>

ARMV7_FUNC_API void vec3_dot(float& result, const float32x4_t& a, const float32x4_t& b) {
	register float32x4_t _0;
	register int _1;
	register float32x4_t ta = a; //ta = vsetq_lane_f32(0.f, ta, 3);
	register float32x4_t tb = b; //tb = vsetq_lane_f32(0.f, tb, 3);
	asm volatile (
	"# dot product of %q2.xyz with %q3.xyz:\n\t"
	"vmul.f32  %e0, %e2, %e3\n\t"
	"movs            %1, #0\n\t"
	"vmov.32     %f2[1], %1\n\t"
	"vmov.32     %f3[1], %1\n\t"
	"vmla.f32  %e0, %f2, %f3\n\t"
	"vpadd.f32 %e0, %e0\n\t"
	: "=&w" (_0), "=&r" (_1), "=&w" (ta), "=&w" (tb) :: );
	result = vgetq_lane_f32(_0, 0);
}

