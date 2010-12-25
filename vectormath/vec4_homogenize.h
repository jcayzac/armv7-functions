#pragma once
#include <armv7-functions/common.h>

ARMV7_FUNC_API void vec4_homogenize(float32x4_t& vec) {
	register float32x4_t tmp1;
	register float32x4_t tmp2;
	register float32x4_t tmp3;
	asm volatile (
	"# %q[vec] = %q[vec]/%q[vec].w\n\t"
	"vdup.f32   %q[tmp1],  	%f[vec][1]\n\t"
	"vrecpe.f32 %q[tmp2],  	%q[tmp1]\n\t"
	"vrecps.f32 %q[tmp3],  	%q[tmp2],  	%q[tmp1]\n\t"
#ifndef QUICK_AND_DIRTY_NORMALIZATION
	"vmul.f32   %q[tmp2],  	%q[tmp2],  	%q[tmp3]\n\t"
	"vrecps.f32 %q[tmp3],  	%q[tmp2],  	%q[tmp1]\n\t"
#endif
	"vmul.f32   %q[vec],  	%q[tmp2],  	%q[tmp3]"
	: [vec] "=w" (vec), [tmp1] "=&w" (tmp1), [tmp2] "=&w" (tmp2), [tmp3] "=&w" (tmp3)
	: "0" (vec)
	:
	);
}

