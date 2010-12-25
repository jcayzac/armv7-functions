#pragma once
#include <armv7-functions/common.h>

ARMV7_FUNC_API void vec3_dot(float& result, const float32x4_t& a, const float32x4_t& b) {
	register float32x4_t tmp;
	register const int zero(0);
	asm volatile (
	"# %q[tmp].x = dot(%q[a].xyz, %q[b].xyz);\n\t"
	"vmul.f32   %q[tmp],    %q[a],   %q[b]\n\t"
	"vmov.32    %f[tmp][1],	%[zero]\n\t"
	"vadd.f32   %e[tmp],    %e[tmp], %f[tmp]\n\t"
	"vpadd.f32  %e[tmp],    %e[tmp]"
	: [tmp] "=&w" (tmp) : [a] "w" (a), [b] "w" (b), [zero] "r" (zero): );
	result = vgetq_lane_f32(tmp, 0);
}

