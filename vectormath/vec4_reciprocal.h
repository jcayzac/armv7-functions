#pragma once
#include <armv7-functions/common.h>

namespace ARM7_FUNC_NAMESPACE {

namespace details {

	template<int steps>
	struct NewtonRaphsonStepper {
		static inline __attribute__((always_inline)) void exec(float32x4_t& x_recp, const float32x4_t& x) {
			x_recp*= vrecpsq_f32(x_recp, x);
			NewtonRaphsonStepper<steps-1>::exec(x_recp, x);
		}
	};

	template<>
	struct NewtonRaphsonStepper<0> {
		static inline __attribute__((always_inline)) void exec(float32x4_t& x_recp, const float32x4_t& x) { }
	};
}

ARMV7_FUNC_API void vec4_reciprocal(vector4_t& result, const vector4_t& vec) {
	asm volatile("#begin vec4_reciprocal" :::);
	result = vrecpeq_f32(vec);
	details::NewtonRaphsonStepper<ARM7_FUNC_NORMALIZATION_RECIPROCAL_STEPS>::exec(result, vec);
	asm volatile("#end vec4_reciprocal" :::);
}

} // ARM7_FUNC_NAMESPACE

