#pragma once
#include <armv7-functions/common.h>

ARMV7_FUNC_API void mat44_multiply(float32x4x4_t& result, const float32x4x4_t& a, const float32x4x4_t& b) {
	// result = first column of B x first row of A
	result.val[0] = vmulq_lane_f32(b.val[0], vget_low_f32(a.val[0]), 0);
	result.val[1] = vmulq_lane_f32(b.val[0], vget_low_f32(a.val[1]), 0);
	result.val[2] = vmulq_lane_f32(b.val[0], vget_low_f32(a.val[2]), 0);
	result.val[3] = vmulq_lane_f32(b.val[0], vget_low_f32(a.val[3]), 0);
	// result += second column of B x second row of A
	result.val[0] = vmlaq_lane_f32(result.val[0], b.val[1], vget_low_f32(a.val[0]), 1);
	result.val[1] = vmlaq_lane_f32(result.val[1], b.val[1], vget_low_f32(a.val[1]), 1);
	result.val[2] = vmlaq_lane_f32(result.val[2], b.val[1], vget_low_f32(a.val[2]), 1);
	result.val[3] = vmlaq_lane_f32(result.val[3], b.val[1], vget_low_f32(a.val[3]), 1);
	// result += third column of B x third row of A
	result.val[0] = vmlaq_lane_f32(result.val[0], b.val[2], vget_high_f32(a.val[0]), 0);
	result.val[1] = vmlaq_lane_f32(result.val[1], b.val[2], vget_high_f32(a.val[1]), 0);
	result.val[2] = vmlaq_lane_f32(result.val[2], b.val[2], vget_high_f32(a.val[2]), 0);
	result.val[3] = vmlaq_lane_f32(result.val[3], b.val[2], vget_high_f32(a.val[3]), 0);
	// result += last column of B x last row of A
	result.val[0] = vmlaq_lane_f32(result.val[0], b.val[3], vget_high_f32(a.val[0]), 1);
	result.val[1] = vmlaq_lane_f32(result.val[1], b.val[3], vget_high_f32(a.val[1]), 1);
	result.val[2] = vmlaq_lane_f32(result.val[2], b.val[3], vget_high_f32(a.val[2]), 1);
	result.val[3] = vmlaq_lane_f32(result.val[3], b.val[3], vget_high_f32(a.val[3]), 1);

#if 0
	// Original, hand-written assembly:
	// Pros:
	//    * used vldmia/vstmia, which gcc can't at this point
	//    * used Um constraints and %m operand, allowing gcc
	//      to use "sp" where it made sense
	// Cons:
	//    * performed the full matrix multiplication, even
	//      when only a sub-expression was really used. The
	//      intrinsics code abode, OTOH, has parts optimized
	//      away by the compiler.
	asm volatile(
	"vldmia   %m[a], {q4-q7}\n\t"
	"vldmia   %m[b], {q8-q11}\n\t"
	"vmul.f32 q0,  q8,  d8[0]\n\t"
	"vmul.f32 q1,  q8, d10[0]\n\t"
	"vmul.f32 q2,  q8, d12[0]\n\t"
	"vmul.f32 q3,  q8, d14[0]\n\t"
	"vmla.f32 q0,  q9,  d8[1]\n\t"
	"vmla.f32 q1,  q9, d10[1]\n\t"
	"vmla.f32 q2,  q9, d12[1]\n\t"
	"vmla.f32 q3,  q9, d14[1]\n\t"
	"vmla.f32 q0, q10,  d9[0]\n\t"
	"vmla.f32 q1, q10, d11[0]\n\t"
	"vmla.f32 q2, q10, d13[0]\n\t"
	"vmla.f32 q3, q10, d15[0]\n\t"
	"vmla.f32 q0, q11,  d9[1]\n\t"
	"vmla.f32 q1, q11, d11[1]\n\t"
	"vmla.f32 q2, q11, d13[1]\n\t"
	"vmla.f32 q3, q11, d15[1]\n\t"
	"vstmia   %m[result], {q0-q3}"
	:
	: [result] "Um" (result), [a] "Um" (a), [b] "Um" (b)
	: "memory",
	  "q0", "q1", "q2", "q3",
	  "q4", "q5", "q6", "q7",
	  "q8", "q9","q10", "q11"
	);
#endif
}

