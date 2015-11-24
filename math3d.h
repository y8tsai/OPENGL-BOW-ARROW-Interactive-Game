#ifndef __MATH3D_H__
#define __MATH3D_H__

#include <math.h>
#include <smmintrin.h>

// This SIMD math for parallel computations. Compiler will complain if you
// mix this with the math constructs we made for class. Feel free to add to it

// It's better to use FPU (single instruction, single data) for vec3
// because extra wasted 32 bits or more (need to be aligned to 16)
// can cause cache miss. But, for science, right?
__declspec(align(16)) class vec3 {
public:
    vec3();
    vec3(__m128 v);
    vec3(float x, float y, float z);
    vec3 operator+(const vec3 &) const;
    vec3 operator-(const vec3 &) const;
    vec3 operator-() const;
    
    vec3 operator*(float) const;
    float dot(const vec3 &) const;
    vec3 cross(const vec3 &) const;
    
    void scale(float);
    void scale(float, float, float);
    float* ptr();

    float length() const;
    vec3 normalize() const;
    float angle(const vec3 &) const;
    void print();

    __m128 v;
    
};


__declspec(align(16)) class vec4 {
public:
    vec4();
    vec4(__m128 v);
    vec4(float x, float y, float z, float w);
    vec4 operator+(const vec4&) const;
    vec4 operator-(const vec4&) const;
    vec4 operator-() const;
    
    vec4 operator*(const vec4&) const;
    vec4 operator*(const float&) const;
    void dehomogenize();
    
    float* ptr();
    void print();
    
    __m128 v;
    
};


__declspec(align(16)) class mat4 {
public:
    mat4();
    mat4(__m128[4]);
    mat4(const float (&el)[4][4]);
    mat4(float, float, float, float,
         float, float, float, float,
         float, float, float, float,
         float, float, float, float);

    void set(float, float, float, float,
             float, float, float, float,
             float, float, float, float,
             float, float, float, float);
    
    mat4 operator*(const mat4&) const;
    vec4 operator*(const vec4&) const;
    mat4& operator=(const mat4&);
    
	static mat4 transpose(const mat4&);
	static mat4 identity();
    void makeIdentity();
    void makeTranspose();
    
    float* ptr();
    void print();
    
    __m128 m[4]; // row-major
};

//__declspec(align(16)) class quat {
//public:
//	float x, y, z, w;
//
//	quat();
//	quat& operator=(const quat&);
//	quat& operator*(const quat&);
//	quat& conjugate() const;
//	float length() const;
//	quat& normalize();
//	quat& rotate(float rad, vec3 axis);
//
//};
//
//
//quat::quat() {
//	x = 0;
//	y = 0;
//	z = 0;
//	w = 0;
//}
//
//quat& quat::operator=(const quat& b) {
//	if( this != &b) {
//		x = b.x;
//		y = b.y;
//		z = b.z;
//		w = b.w;
//	}
//	return *this;
//}
//
//quat& quat::operator*(const quat& b) {
//	quat res;
//	res.x = w * b.w + x*b.w + y*b.z - z*b.y;
//	res.y = w*b.y - x*b.z + y*b.w + z*b.x;
//	res.z = w*b.z + x*b.y - y*b.x + z*b.w;
//	res.w = w*b.w - x*b.x - y*b.y - z*b.z;
//	return res;
//}
//
//quat& quat::conjugate() const {
//	quat conj;
//	conj.x = -x;
//	conj.y = -y;
//	conj.z = -z;
//	return conj;
//}
//
//float quat::length() const {
//	return sqrtf( x*x + y*y + z*z + w*w );
//}
//
//quat& quat::normalize() {
//	float l = length();
//	if( l != 0.0 ) {
//		x = x / l;
//		y = y / l;
//		z = z / l;
//		w = w / l;
//	}
//	return *this;
//}
//
//quat& quat::rotate(float rad, vec3 axis) {
//	quat rotated; 
//	rotated.x = axis.v.m128_f32[0] * sinf(rad/2);
//	rotated.y = axis.v.m128_f32[1] * sinf(rad/2);
//	rotated.z = axis.v.m128_f32[2] * sinf(rad/2);
//	rotated.w = cosf(rad/2);
//}

#endif
