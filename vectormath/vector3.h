#pragma once
#include <armv7-functions/common.h>
#include <armv7-functions/vectormath/vec4_reciprocal.h>
// TODO:
// #include <armv7-functions/vectormath/vec4_reciprocal_squareroot.h>
#error "Please don't use this, it's not ready"

namespace ARM7_FUNC_NAMESPACE {

class Vector3Static;
class Vector3 {
private:
	float32x4_t val;
	friend class Vector3Static;

public:
	Vector3()
	{ }

	Vector3(const Vector3 & vec)
	: val(vec.val)
	{ }

	Vector3(const float32_t& x, const float32_t& y, const float32_t& z) {
		setX(x);
		setY(y);
		setZ(z);
	}

	explicit
	Vector3(const float32_t& scalar)
	: val(vdupq_n_f32(scalar))
	{ }

	explicit
	Vector3(const float32x4_t& v)
	: val(v)
	{ }

	Vector3& operator=(const Vector3& vec) {
		val=vec.val;
		return *this;
	}

	Vector3& setX(const float32_t& x) {
		return setElem(0, x);
	}

	Vector3& setY(const float32_t& y) {
		return setElem(1, y);
	}

	Vector3& setZ(const float32_t& z) {
		return setElem(2, z);
	}

	float32_t getX() const {
		return getElem(0);
	}

	float32_t getY() const {
		return getElem(1);
	}

	float32_t getZ() const {
		return getElem(2);
	}

	Vector3& setElem(int idx, const float32_t& value) {
		val = vsetq_lane_f32(value, val, idx);
		return *this;
	}

	float32_t getElem(int idx) const {
		return vgetq_lane_f32(val, idx);
	}

	float32_t operator[](int idx) const {
		return getElem(idx);
	}

	const Vector3 operator+(const Vector3& vec) const {
		return Vector3(val + vec.val);
	}

	const Vector3 operator-(const Vector3& vec) const {
		return Vector3(val - vec.val);
	}

	const Vector3 operator*(const float32_t& scalar) const {
		return Vector3(val * vdupq_n_f32(scalar));
	}

	const Vector3 operator/(const float32_t& scalar) const {
		float32x4_t tmp;
		vec4_reciprocal(tmp, vdupq_n_f32(scalar));
		return Vector3(val * tmp);
	}

	Vector3& operator+=(const Vector3& vec) {
		val += vec.val;
		return *this;
	}

	Vector3& operator-=(const Vector3& vec) {
		val -= vec.val;
		return *this;
	}

	Vector3& operator*=(const float32_t& scalar) {
		val *= vdupq_n_f32(scalar);
		return *this;
	}

	Vector3& operator/=(const float32_t& scalar) {
		float32x4_t tmp;
		vec4_reciprocal(tmp, vdupq_n_f32(scalar));
		val *= tmp;
		return *this;
	}

	const Vector3 operator-( ) const {
		return Vector3(-val);
	}

	static const Vector3& xAxis() {
		static Vector3 instance((float32x4_t) { 1.f, 0.f, 0.f, 0.f });
		return instance;
	}

	static const Vector3& yAxis() {
		static Vector3 instance((float32x4_t) { 0.f, 1.f, 0.f, 0.f });
		return instance;
	}

	static const Vector3& zAxis() {
		static Vector3 instance((float32x4_t) { 0.f, 0.f, 1.f, 0.f });
		return instance;
	}

} __attribute__((aligned(16)));

class Vector3Static {
public:
	static const Vector3 mulPerElem(const Vector3& vec0, const Vector3& vec1) {
		return Vector3(vec0.val * vec1.val);
	}
	static const Vector3 divPerElem(const Vector3& vec0, const Vector3& vec1 ) {
		return mulPerElem(vec0, recipPerElem(vec1));
	}
	static const Vector3 recipPerElem(const Vector3& vec) {
		float32x4_t tmp;
		vec4_reciprocal(tmp, vec.val);
		return Vector3(tmp);
	}

	static const Vector3 sqrtPerElem(const Vector3& vec) {
		float32x4_t tmp;
		// TODO:
		// vec4_reciprocal_squareroot(tmp, vec.val);
		// vec4_reciprocal(tmp, tmp);
		return Vector3(tmp);
	}

	static const Vector3 rsqrtPerElem(const Vector3& vec) {
		float32x4_t tmp;
		// TODO:
		// vec4_reciprocal_squareroot(tmp, vec.val);
		return Vector3(tmp);
	}

	static const Vector3 absPerElem(const Vector3& vec);
	static const Vector3 copySignPerElem(const Vector3& vec0, const Vector3& vec1);
	static const Vector3 maxPerElem(const Vector3& vec0, const Vector3& vec1);
	static const Vector3 minPerElem(const Vector3& vec0, const Vector3& vec1);
	static float maxElem(const Vector3& vec);
	static float minElem(const Vector3& vec);
	static float sum(const Vector3& vec);
	static float dot(const Vector3& vec0, const Vector3 & vec1);
	static float lengthSqr(const Vector3& vec);
	static float length(const Vector3& vec);
	static const Vector3 normalize(const Vector3& vec);
	static const Vector3 cross(const Vector3& vec0, const Vector3& vec1);
};

inline const Vector3 operator*(const float32_t& scalar, const Vector3& vec) {
	return vec*scalar;
}

inline const Vector3 mulPerElem(const Vector3& vec0, const Vector3& vec1) {
	return Vector3Static::mulPerElem(vec0, vec1);
}

inline const Vector3 divPerElem(const Vector3& vec0, const Vector3& vec1) {
	return Vector3Static::divPerElem(vec0, vec1);
}

inline const Vector3 recipPerElem(const Vector3& vec) {
	return Vector3Static::recipPerElem(vec);
}

inline const Vector3 sqrtPerElem( const Vector3 & vec );
inline const Vector3 rsqrtPerElem( const Vector3 & vec );
inline const Vector3 absPerElem( const Vector3 & vec );
inline const Vector3 copySignPerElem( const Vector3 & vec0, const Vector3 & vec1 );
inline const Vector3 maxPerElem( const Vector3 & vec0, const Vector3 & vec1 );
inline const Vector3 minPerElem( const Vector3 & vec0, const Vector3 & vec1 );
inline float maxElem( const Vector3 & vec );
inline float minElem( const Vector3 & vec );
inline float sum( const Vector3 & vec );
inline float dot( const Vector3 & vec0, const Vector3 & vec1 );
inline float lengthSqr( const Vector3 & vec );
inline float length( const Vector3 & vec );
inline const Vector3 normalize( const Vector3 & vec );
inline const Vector3 cross( const Vector3 & vec0, const Vector3 & vec1 );

//inline const Matrix3 outer( const Vector3 & vec0, const Vector3 & vec1 );
//inline const Vector3 rowMul( const Vector3 & vec, const Matrix3 & mat );
//inline const Matrix3 crossMatrix( const Vector3 & vec );
//inline const Matrix3 crossMatrixMul( const Vector3 & vec, const Matrix3 & mat );

inline const Vector3 lerp( float t, const Vector3 & vec0, const Vector3 & vec1 );
inline const Vector3 slerp( float t, const Vector3 & unitVec0, const Vector3 & unitVec1 );
inline const Vector3 select( const Vector3 & vec0, const Vector3 & vec1, bool select1 );

} // ARM7_FUNC_NAMESPACE

