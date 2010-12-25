#pragma once
#include <armv7-functions/common.h>

ARMV7_FUNC_API void mat44_multiply(float32x4x4_t& result, const float32x4x4_t& a, const float32x4x4_t& b) {
	asm (
	"\n\t# multiply two matrices...\n\t"
	"vldmia %1, { q4-q7 }\n\t"
	"vldmia %2, { q8-q11 } \n\t"
	"vmul.f32 q0, q8, d8[0]\n\t"
	"vmul.f32 q1, q8, d10[0]\n\t"
	"vmul.f32 q2, q8, d12[0]\n\t"
	"vmul.f32 q3, q8, d14[0]\n\t"
	"vmla.f32 q0, q9, d8[1]\n\t"
	"vmla.f32 q1, q9, d10[1]\n\t"
	"vmla.f32 q2, q9, d12[1]\n\t"
	"vmla.f32 q3, q9, d14[1]\n\t"
	"vmla.f32 q0, q10, d9[0]\n\t"
	"vmla.f32 q1, q10, d11[0]\n\t"
	"vmla.f32 q2, q10, d13[0]\n\t"
	"vmla.f32 q3, q10, d15[0]\n\t"
	"vmla.f32 q0, q11, d9[1]\n\t"
	"vmla.f32 q1, q11, d11[1]\n\t"
	"vmla.f32 q2, q11, d13[1]\n\t"
	"vmla.f32 q3, q11, d15[1]\n\t"
	"vstmia %0, { q0-q3 }"
	:
	: "r" (result.val), "r" (a.val), "r" (b.val)
	: "memory", "q0", "q1", "q2", "q3", "q4", "q5", "q6", "q7", "q8", "q9", "q11" //clobber
	);
}
