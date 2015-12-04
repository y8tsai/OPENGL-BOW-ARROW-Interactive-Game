#include "math3d.h"
#include <iostream>

/**
 *                                      Vector3
 * ======================================================================================
 */
vec3::vec3() {
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
}

vec3::vec3(float x, float y, float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}


vec3::vec3(const float (&el)[3]) {
	v[0] = el[0];
	v[1] = el[1];
	v[2] = el[2];
}

vec3 vec3::operator+(const vec3 &b) const {
	return vec3( v[0]+b.v[0], v[1]+b.v[1], v[2]+b.v[2] );
}

vec3 vec3::operator-(const vec3 &b) const {
	return vec3( v[0]-b.v[0], v[1]-b.v[1], v[2]-b.v[2] );
}

vec3 vec3::operator-() const {
	return vec3( -v[0], -v[1], -v[2] );
}

vec3& vec3::negate() {
	v[0] = -v[0];
	v[1] = -v[1];
	v[2] = -v[2];
	return *this;
}

vec3 vec3::operator*(float f) const {
	return vec3( f*v[0], f*v[1], f*v[2] );
}

vec3 vec3::operator*(const vec3 &b) const {
	return vec3( v[0], v[1], v[2] );
}

vec3 vec3::cross(const vec3 &b) const {
	return vec3( v[1]*b.v[2] - v[2]*b.v[1], v[2]*b.v[0] - v[0]*b.v[2], v[0]*b.v[1] - v[1]*b.v[0] );
}

float vec3::dot(const vec3 &b) const {
	return ( v[0]*b.v[0] + v[1]*b.v[1] + v[2]*b.v[2] );
}

void vec3::scale(float f) {
	v[0] = f*v[0];
	v[1] = f*v[1];
	v[2] = f*v[2];
}

void vec3::scale(float x, float y, float z) {
	v[0] = x*v[0];
	v[1] = y*v[1];
	v[2] = z*v[2];
}

void vec3::scale(const vec3 &b) {
	v[0] = b.v[0] * v[0];
	v[1] = b.v[1] * v[1];
	v[2] = b.v[2] * v[2];
}

float vec3::length() const {
	return sqrtf(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

vec3& vec3::normalize() {
	float l = length();
	if( l != 0.0 ) {
		v[0] = v[0] / l;
		v[1] = v[1] / l;
		v[2] = v[2] / l;
	}
	return *this;
}

float* vec3::ptr() {
	return &v[0];
}

void vec3::print(std::string comment) {
	std::cout << comment << std::endl;
	printf("< %g, %g, %g >\n", v[0], v[1], v[2]); 
}

void vec3::clear() {
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
}

/**
 *                                      Vector4
 * ======================================================================================
 */
vec4::vec4() {
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 0.0f;
}

vec4::vec4(float x, float y, float z, float w) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

vec4::vec4(const float (&el)[4]) {
	v[0] = el[0];
	v[1] = el[1];
	v[2] = el[2];
	v[3] = el[3];
}

vec4 vec4::operator+(const vec4 &b) const {
	return vec4( v[0]+b.v[0], v[1]+b.v[1], v[2]+b.v[2], v[3]+b.v[3] );
}

vec4 vec4::operator-(const vec4 &b) const {
	return vec4( v[0]-b.v[0], v[1]-b.v[1], v[2]-b.v[2], v[3]+b.v[3] );
}

vec4 vec4::operator-() const {
	return vec4( -v[0], -v[1], -v[2], -v[3] );
}

vec4& vec4::dehomogenize() {
	if( v[3] != 0.0f ) {
		v[0] = v[0] / v[3];
		v[1] = v[1] / v[3];
		v[2] = v[2] / v[3];
		v[3] = 1.0f;
	} else {
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 0.0f;
		v[3] = 1.0f;
	}
	return *this;
}
vec3 vec4::toVec3() {
	return vec3(v[0], v[1], v[2]);
}

float* vec4::ptr() {
	return &v[0];
}

void vec4::print(std::string comment) {
	std::cout << comment << std::endl;
	printf("< %g, %g, %g, %g >\n", v[0], v[1], v[2], v[3]);
}

/**
 *                                      Matrix 4x4
 * ======================================================================================
 */

mat4::mat4() {
	for( int i = 0; i < 4; ++i ) {
		for( int j = 0; j < 4; ++j ) {
			m[i][j] = 0.0f;
		}
	}
}

mat4::mat4(const float (&el)[4][4]) {
	for( int i=0; i < 4; ++i ) {
        for( int j=0; j < 4; ++j) {
            m[i][j] = el[i][j];
        }
    }
}

mat4::mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}


mat4 mat4::operator*(const mat4 &b) const {
	mat4 r;
	for(int i = 0; i < 4; ++i) {
        for( int j = 0; j < 4; ++j) {
            r.m[i][j] = m[i][0]*b.m[0][j] + m[i][1]*b.m[1][j] + m[i][2]*b.m[2][j] + m[i][3]*b.m[3][j];
        }
    }
	return r;
}

vec4 mat4::operator*(const vec4 &b) const {
	vec4 r;
	r.v[0] = m[0][0]*b.v[0] + m[0][1]*b.v[1] + m[0][2]*b.v[2] + m[0][3]*b.v[3];
    r.v[1] = m[1][0]*b.v[0] + m[1][1]*b.v[1] + m[1][2]*b.v[2] + m[1][3]*b.v[3];
    r.v[2] = m[2][0]*b.v[0] + m[2][1]*b.v[1] + m[2][2]*b.v[2] + m[2][3]*b.v[3];
    r.v[3] = m[3][0]*b.v[0] + m[3][1]*b.v[1] + m[3][2]*b.v[2] + m[3][3]*b.v[3];
	return r;
}

mat4& mat4::operator=(const mat4 &b) {
	if( this != &b ) {
		for( int i=0; i<4; ++i ) {
			for( int j=0; j<4; ++j ) {
				m[i][j] = b.m[i][j];
			}
		}
	}
	return *this;
}

mat4& mat4::makeIdentity() {
	for( int i=0; i < 4; ++i ) {
        for( int j=0; j < 4; ++j ) {
            m[i][j] = ( i == j ? 1.0f : 0.0f );
        }
    }
	return *this;
}

mat4& mat4::makeTranspose() {
	float t;
	for( int i = 0; i < 4; ++i ) {
        for( int j = i; j < 4; ++j ) {
            
			if( i == j ) {
				continue;
			}

            t = m[j][i];
            m[j][i] = m[i][j];
            m[i][j] = t;
        }
    }
	return *this;
}

mat4& mat4::makeRotateX(float deg) {
	float rad = DEG2RAD(deg);
	makeIdentity();
	m[1][1] = cosf(rad);
	m[1][2] = -sinf(rad);
	m[2][1] = sinf(rad);
	m[2][2] = cosf(rad);
	return *this;
}

mat4& mat4::makeRotateY(float deg) {
	float rad = DEG2RAD(deg);
	makeIdentity();
	m[0][0] = cosf(rad);
	m[0][2] = sinf(rad);
	m[2][0] = -sinf(rad);
	m[2][2] = cos(rad);
	return *this;
}

mat4& mat4::makeRotateZ(float deg) {
	float rad = DEG2RAD(deg);
	makeIdentity();
	m[0][0] = cosf(rad);
	m[0][1] = -sinf(rad);
	m[1][0] = sinf(rad);
	m[1][1] = cos(rad);
	return *this;
}

mat4& mat4::makeRotate(float deg, vec3 &axis) {
	makeIdentity();
	axis.normalize();
	float rad = DEG2RAD(deg),
		  cs = cosf(deg),
		  sn = sinf(deg),
		  ax = axis.v[0],
		  ay = axis.v[1],
		  az = axis.v[2];

	m[0][0] = 1 + (ax * ax - 1) * (1 - cs);
    m[0][1] = -az * sn + ax * ay * (1 - cs);
    m[0][2] = ay * sn + ax * az * (1 - cs);
    
    m[1][0] = az * sn +  ax * ay * (1 - cs);
    m[1][1] = 1 + (ay * ay - 1) * (1 - cs);
    m[1][2] = -ax * sn + ay * az * (1 - cs);
    
    m[2][0] = -ay * sn + az * ax * (1 - cs);
    m[2][1] = ax * sn + az * ay * (1 - cs);
    m[2][2] = 1 + (az * az - 1) * (1 - cs);

	return *this;
}

mat4 mat4::rigidInverse() {
	float ex = -m[3][0] * m[0][0] - m[3][1] * m[0][1] - m[3][2] * m[0][2];
    float ey = -m[3][0] * m[1][0] - m[3][1] * m[1][1] - m[3][2] * m[1][2];
    float ez = -m[3][0] * m[2][0] - m[3][1] * m[2][1] - m[3][2] * m[2][2];
    mat4 inv = mat4({
        {m[0][0], m[1][0], m[2][0], 0.0f},
        {m[0][1], m[1][1], m[2][1], 0.0f},
        {m[0][2], m[1][2], m[2][2], 0.0f},
        {ex,      ey,      ez,      1.0f}
    });
    return inv;
}

mat4& mat4::scale(float x, float y, float z) {
	makeIdentity();
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	return *this;
}

mat4& mat4::scale(const vec3 &b) {
	makeIdentity();
	m[0][0] = b.v[0];
	m[1][1] = b.v[1];
	m[2][2] = b.v[2];
	return *this;
}

mat4& mat4::translate(float x, float y, float z) {
	makeIdentity();
	m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
	return *this;
}

mat4& mat4::translate(const vec3 &b) {
	makeIdentity();
	m[0][3] = b.v[0];
    m[1][3] = b.v[1];
    m[2][3] = b.v[2];
	return *this;
}

mat4& mat4::setTranslate(const vec3 &b) {
	m[0][3] = b.v[0];
	m[1][3] = b.v[1];
	m[2][3] = b.v[2];
	m[3][3] = 1.0f;
	return *this;
}

vec3 mat4::getTranslate() const {
	return vec3(m[0][3], m[1][3], m[2][3]);
}


float* mat4::ptr() {
	return &m[0][0];
}

void mat4::print(std::string comment) {
	std::cout << comment << std::endl;
	printf("mat4:: [%g %g %g %g\n", m[0][0], m[0][1], m[0][2], m[0][3]);
    printf("        %g %g %g %g\n", m[1][0], m[1][1], m[1][2], m[1][3]);
    printf("        %g %g %g %g\n", m[2][0], m[2][1], m[2][2], m[2][3]);
    printf("        %g %g %g %g]\n", m[3][0], m[3][1], m[3][2], m[3][3]);
    
}


/**
 *                                      Quaternion
 * ======================================================================================
 */

quat::quat() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

quat::quat(vec3 v) {
	x = v.v[0];
	y = v.v[1];
	z = v.v[2];
	w = 0.0f;
}

quat& quat::operator=(const quat& b) {
	if( this != &b) {
		x = b.x;
		y = b.y;
		z = b.z;
		w = b.w;
	}
	return *this;
}

quat quat::operator*(const quat& b) {
	quat res;
	res.x = w*b.x + x*b.w + y*b.z - z*b.y;
	res.y = w*b.y - x*b.z + y*b.w + z*b.x;
	res.z = w*b.z + x*b.y - y*b.x + z*b.w;
	res.w = w*b.w - x*b.x - y*b.y - z*b.z;
	return res;
}

quat quat::conjugate() const {
	quat conj;
	conj.x = -x;
	conj.y = -y;
	conj.z = -z;
	conj.w = w;
	return conj;
}

float quat::length() const {
	return sqrtf( x*x + y*y + z*z + w*w );
}

quat quat::normalize() {
	float l = length();
	if( l != 0.0 ) {
		x = x / l;
		y = y / l;
		z = z / l;
		w = w / l;
	}
	return *this;
}

quat quat::rotate(float rad, vec3 axis) {
	quat rotated; 
	rotated.x = axis.v[0] * sinf(rad/2);
	rotated.y = axis.v[1] * sinf(rad/2);
	rotated.z = axis.v[2] * sinf(rad/2);
	rotated.w = cosf(rad/2);
	return rotated;
}


vec3 quat::tovec3(quat q) {
	vec3 v;
	v.v[0] = q.x;
	v.v[1] = q.y;
	v.v[2] = q.z;
	return v;
}

/**
 *                                      SSE Vector3
 * ======================================================================================
 */

ssvec3::ssvec3() : v(_mm_setzero_ps()) {}

ssvec3::ssvec3(__m128 m) : v(m) {}

ssvec3::ssvec3(float x, float y, float z) { v = _mm_set_ps(0.0f, z, y, x); }

ssvec3 ssvec3::operator+(const ssvec3 &b) const { return _mm_add_ps(v, b.v); }

ssvec3 ssvec3::operator-(const ssvec3 &b) const { return _mm_sub_ps(v, b.v); }

ssvec3 ssvec3::operator-() const { return _mm_sub_ps(_mm_set1_ps(0.0f), v); }

ssvec3 ssvec3::operator*(float f) const { return ssvec3(_mm_mul_ps(_mm_set1_ps(f), v)); }

float ssvec3::dot(const ssvec3 &b) const {
    // make sure w component is 0
    __m128 temp = _mm_mul_ps(v, b.v);
    __m128 temp2 = _mm_shuffle_ps(temp, temp, 0xFE);
    temp2 = _mm_add_ps(temp, temp2);
    return _mm_cvtss_f32(_mm_add_ps(temp2, _mm_shuffle_ps(temp, temp, 0xFD)));
}

ssvec3 ssvec3::cross(const ssvec3 &b) const {
    const static _Uint32t mask0 = _MM_SHUFFLE( 0, 0, 2, 1 );
    const static _Uint32t mask1 = _MM_SHUFFLE( 0, 1, 0, 2 );
    return _mm_sub_ps(
        _mm_mul_ps(_mm_shuffle_ps(v, v, mask0), _mm_shuffle_ps(b.v, b.v, mask1)),
        _mm_mul_ps(_mm_shuffle_ps(v, v, mask1), _mm_shuffle_ps(b.v, b.v, mask0))
    );
}

void ssvec3::scale(float f) {
    v = _mm_mul_ps(_mm_set1_ps(f), v);
}

void ssvec3::scale(float f1, float f2, float f3) {
    v = _mm_mul_ps(_mm_set_ps(0.0f, f3, f2, f1),  v);
}

float* ssvec3::ptr() {
    return v.m128_f32;
}

float ssvec3::length() const {
    __m128 temp = _mm_mul_ps(v, v);
    __m128 temp2 = _mm_shuffle_ps(temp, temp, 0xFD);
    temp2 = _mm_add_ps(temp, temp2);
    temp2 = _mm_add_ps(temp2, _mm_shuffle_ps(temp, temp, 0xFE));
    return _mm_cvtss_f32(_mm_sqrt_ps(temp2));
}

ssvec3 ssvec3::normalize() const {
    __m128 temp = _mm_mul_ps(v, v);
    __m128 temp2 = _mm_shuffle_ps(temp, temp, 0xFD);
    temp2 = _mm_add_ps(temp, temp2);
    temp2 = _mm_add_ps(temp2, _mm_shuffle_ps(temp, temp, 0xFE));
    __m128 sqr = _mm_rsqrt_ps(temp2);
    return _mm_mul_ps(v, _mm_shuffle_ps(sqr, sqr, 0x00) );
}

float ssvec3::angle(const ssvec3 &b) const {
    float l = b.length();
    return acosf( dot(b)/l ) / l;
}

void ssvec3::print() {
    printf("vec3 : %g %g %g\n", v.m128_u32[0] , v.m128_u32[1], v.m128_u32[2]);
}



/**
 *                                      SSE Vector4
 * ======================================================================================
 */

ssvec4::ssvec4() : v(_mm_setzero_ps()) {}

ssvec4::ssvec4(__m128 m) : v(m) {}

ssvec4::ssvec4(float x, float y, float z, float w) { v = _mm_set_ps(w, z, y, x); }

ssvec4 ssvec4::operator+(const ssvec4 &b) const { return _mm_add_ps(v, b.v); }

ssvec4 ssvec4::operator-(const ssvec4 &b) const { return _mm_sub_ps(v, b.v); }

ssvec4 ssvec4::operator-() const { return _mm_sub_ps(_mm_set1_ps(0.0f), v); }

ssvec4 ssvec4::operator*(const ssvec4 &b) const { return _mm_mul_ps(v, b.v); }

ssvec4 ssvec4::operator*(const float &f) const { return _mm_mul_ps(_mm_set1_ps(f), v); }

void ssvec4::dehomogenize() {
    v = _mm_div_ps(v, _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3)));
}

float* ssvec4::ptr() {
    return v.m128_f32;
}

void ssvec4::print() {
    printf("vec4 : %g %g %g %g\n", v.m128_f32[0], v.m128_f32[1], v.m128_f32[2], v.m128_f32[3]);
}

/**
 *                                      SSE Matrix4
 * ======================================================================================
 */

ssmat4::ssmat4() {
    m[0] = _mm_setzero_ps();
    m[1] = _mm_setzero_ps();
    m[2] = _mm_setzero_ps();
    m[3] = _mm_setzero_ps();
}

ssmat4::ssmat4(__m128 el[4]) {
    m[0] = el[0];
    m[1] = el[1];
    m[2] = el[2];
    m[3] = el[3];
}

ssmat4::ssmat4(const float (&el)[4][4]) {
    m[0] = _mm_set_ps(el[0][3], el[0][2], el[0][1], el[0][0]);
    m[1] = _mm_set_ps(el[1][3], el[1][2], el[1][1], el[1][0]);
    m[2] = _mm_set_ps(el[2][3], el[2][2], el[2][1], el[2][0]);
    m[3] = _mm_set_ps(el[3][3], el[3][2], el[3][1], el[3][0]);
}

ssmat4::ssmat4(float m00, float m01, float m02, float m03,
           float m10, float m11, float m12, float m13,
           float m20, float m21, float m22, float m23,
           float m30, float m31, float m32, float m33) {
    m[0] = _mm_set_ps(m03, m02, m01, m00);
    m[1] = _mm_set_ps(m13, m12, m11, m10);
    m[2] = _mm_set_ps(m23, m22, m21, m20);
    m[3] = _mm_set_ps(m33, m32, m31, m30);
    
}

void ssmat4::set(float m00, float m01, float m02, float m03,
               float m10, float m11, float m12, float m13,
               float m20, float m21, float m22, float m23,
               float m30, float m31, float m32, float m33) {
    m[0] = _mm_set_ps(m03, m02, m01, m00);
    m[1] = _mm_set_ps(m13, m12, m11, m10);
    m[2] = _mm_set_ps(m23, m22, m21, m20);
    m[3] = _mm_set_ps(m33, m32, m31, m30);
}

// It's 20% faster but wasn't the 2x speed up I was hoping for.
// Will have to investigate later.
ssmat4 ssmat4::operator*(const ssmat4& b) const {
    ssmat4 temp = b;
    temp.makeTranspose();
    __m128 r[4];
    for(int i = 0; i < 4; ++i) {
        __m128 c0 = _mm_mul_ps(m[i], temp.m[0]);
        __m128 c1 = _mm_mul_ps(m[i], temp.m[1]);
        __m128 c2 = _mm_mul_ps(m[i], temp.m[2]);
        __m128 c3 = _mm_mul_ps(m[i], temp.m[3]);
        _MM_TRANSPOSE4_PS(c0, c1, c2, c3);
        r[i] = _mm_add_ps(c0, _mm_add_ps(c1, _mm_add_ps(c2, c3)));
    }
    return r;
}

ssvec4 ssmat4::operator*(const ssvec4& b) const {
    __m128 r0 = _mm_mul_ps(m[0], b.v);
    __m128 r1 = _mm_mul_ps(m[1], b.v);
    __m128 r2 = _mm_mul_ps(m[2], b.v);
    __m128 r3 = _mm_mul_ps(m[3], b.v);
    _MM_TRANSPOSE4_PS(r0, r1, r2, r3);
    return _mm_add_ps(r0, _mm_add_ps(r1, _mm_add_ps(r2, r3)));
}

ssmat4& ssmat4::operator=(const ssmat4& b) {
    m[0] = b.m[0];
    m[1] = b.m[1];
    m[2] = b.m[2];
    m[3] = b.m[3];
    return *this;
}


ssmat4 ssmat4::transpose(const ssmat4& b) {
	ssmat4 ret = b;
	ret. makeTranspose();
	return ret;
}

ssmat4 ssmat4::identity() {
	ssmat4 ret;
	ret.makeIdentity();
	return ret;
}

void ssmat4::makeIdentity() {
   m[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
   m[1] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
   m[2] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
   m[3] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
}

void ssmat4::makeTranspose() {
    _MM_TRANSPOSE4_PS(m[0], m[1], m[2], m[3]);
}

float* ssmat4::ptr() {
    return m[0].m128_f32;
}

void ssmat4::print() {
    printf("mat4:: [%g %g %g %g\n", m[0].m128_f32[0], m[0].m128_f32[1], m[0].m128_f32[2], m[0].m128_f32[3] );
    printf("        %g %g %g %g\n", m[1].m128_f32[0], m[1].m128_f32[1], m[1].m128_f32[2], m[1].m128_f32[3]);
    printf("        %g %g %g %g\n", m[2].m128_f32[0], m[2].m128_f32[1], m[2].m128_f32[2], m[2].m128_f32[3]);
    printf("        %g %g %g %g]\n", m[3].m128_f32[0], m[3].m128_f32[1], m[3].m128_f32[2], m[3].m128_f32[3]);
}