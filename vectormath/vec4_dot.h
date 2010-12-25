#pragma once
#include <armv7-functions/common.h>

ARMV7_FUNC_API void vec4_dot(float& result, const float32x4_t& a, const float32x4_t& b) {
	register float32x4_t tmp;
	asm volatile (
	"# dot product of %q[a].xyzw with %q[b].xyzw: \n\t"
	"vmul.f32   %q[tmp],    %q[a],   %q[b]        \n\t"
	"vadd.f32   %e[tmp],    %e[tmp], %f[tmp]      \n\t"
	"vpadd.f32  %e[tmp],    %e[tmp]               \n\t"
	: [tmp] "=&w" (tmp) : [a] "w" (a), [b] "w" (b) : );
	result = vgetq_lane_f32(tmp, 0);
}

