#pragma once
#include <armv7-functions/common.h>

namespace ARM7_FUNC_NAMESPACE {

ARMV7_FUNC_API void vec4_dot(float& result, const vector4_t& a, const vector4_t& b) {
	register vector4_t tmp;
	asm volatile (
	"# %q[tmp].x = dot(%q[a].xyzw, %q[b].xyzw);\n\t"
	"vmul.f32   %q[tmp],    %q[a],   %q[b]\n\t"
	"vadd.f32   %e[tmp],    %e[tmp], %f[tmp]\n\t"
	"vpadd.f32  %e[tmp],    %e[tmp]"
	: [tmp] "=&w" (tmp) : [a] "w" (a), [b] "w" (b) : );
	result = vgetq_lane_f32(tmp, 0);
}

} // ARM7_FUNC_NAMESPACE

