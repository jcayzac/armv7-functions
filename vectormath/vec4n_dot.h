#pragma once
#include <armv7-functions/common.h>

// Compute the dot product of two vectors of 4n floats
ARMV7_FUNC_API void vec4n_dot(float& result, const float32x4_t* a, const float32x4_t* b, unsigned int n) {
	register float32x4_t tmp, va, vb;
	asm volatile (
	"# %q[tmp].x = dot(%q[va][i], %q[vb][i]) for (i=0; i<n; i++);\n\t"
	"vmov.f32 %q[tmp], #0.0\n\t"
	"1:\n\t"
	"vldmia    %[a]!, {%q[va]}\n\t"
	"vldmia    %[b]!, {%q[vb]}\n\t"
	"vmla.f32  %q[tmp], %q[va], %q[vb]\n\t"
	"subs      %[n], %[n], #16\n\t"
	"bne 1b\n\t"
	"vadd.f32  %e[tmp], %e[tmp], %f[tmp]\n\t"
	"vpadd.f32 %e[tmp], %e[tmp]"
	: [tmp] "=&w" (tmp), [a] "=r" (a), [b] "=r" (b), [n] "=r" (n), [va] "=w" (va), [vb] "=w" (vb)
	: "1" (a), "2" (b), "3" (n)
	: "memory", "cc"
	);
	result = vgetq_lane_f32(tmp, 0);
}

