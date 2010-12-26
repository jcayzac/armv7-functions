#pragma once
#include <armv7-functions/common.h>
#include <armv7-functions/vectormath/vec4_reciprocal.h>

namespace ARM7_FUNC_NAMESPACE {

ARMV7_FUNC_API void vec4_homogenize(vector4_t& vec) {
	asm volatile("#begin vec4_homogenize" :::);
	register vector4_t wwww, wwww_recp;

	// This use a neon>arm transfer! why??
	// tmp1 = vdupq_n_f32(vgetq_lane_f32(vec, 3));
	asm volatile("vdup.f32 %q[wwww], %f[xyzw][1]" : [wwww] "=&w" (wwww) : [xyzw] "w" (vec) : );

	vec4_reciprocal(wwww_recp, wwww);
	vec *= wwww_recp;
	asm volatile("#end vec4_homogenize" :::);
}

} // ARM7_FUNC_NAMESPACE

