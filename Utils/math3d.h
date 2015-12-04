#ifndef __MATH3D_H__
#define __MATH3D_H__

#include <math.h>
#include <iostream>
#include <string>
#include <smmintrin.h>

#define PI 3.14159265359f

#define DEG2RAD(G) G * PI / 180.0f
#define RAD2DEG(G) G * 180.0f / PI


class vec3 {
public:
	vec3();
	vec3(float x, float y, float z);
	vec3(const float (&el)[3]);
	vec3 operator+(const vec3&) const;
	vec3 operator-(const vec3&) const;
	vec3 operator-() const;
	vec3& negate();

	vec3 operator*(float) const;
	vec3 operator*(const vec3&) const;
	vec3 cross(const vec3&) const;
	float dot(const vec3&) const;

	void scale(float);
	void scale(float, float, float);
	void scale(const vec3&);

	float length() const;
	vec3& normalize();			// returns reference to itself after normalization

	float* ptr();
	void print(std::string comment);
	void clear(); //zero out

	float v[3];
};

class vec4 {
public:
	vec4();
	vec4(float x, float y, float z, float w);
	vec4(const float (&el)[4]);
	vec4 operator+(const vec4&) const;
	vec4 operator-(const vec4&) const;
	vec4 operator-() const;
	vec4& dehomogenize();
	vec3 toVec3(); //return everything but w

	float* ptr();
	void print(std::string comment);

	float v[4];
};

class mat4 {
public:
	mat4();
	mat4(const float (&el)[4][4]);
	mat4(float, float, float, float,
         float, float, float, float,
         float, float, float, float,
         float, float, float, float);

	mat4 operator*(const mat4&) const;
	vec4 operator*(const vec4&) const;
	mat4& operator=(const mat4&);

	mat4& makeIdentity();
	mat4& makeTranspose();
	mat4& makeRotateX(float deg);
	mat4& makeRotateY(float deg);
	mat4& makeRotateZ(float deg);
	mat4& makeRotate(float deg, vec3 &axis);
	mat4 rigidInverse();

	mat4& scale(float x, float y, float z);
	mat4& scale(const vec3&);
	mat4& translate(float x, float y, float z);
	mat4& translate(const vec3&);
	mat4& setTranslate(const vec3&);
	vec3 getTranslate() const;

	float* ptr();
	void print(std::string comment);

	float m[4][4];
};

class quat {
public:
	float x, y, z, w;

	quat();
	quat(vec3 v);
	quat& operator=(const quat&);
	quat operator*(const quat&);
	quat conjugate() const;
	float length() const;
	quat normalize();

	static vec3 tovec3(quat q);
	static quat rotate(float rad, vec3 axis);

};


// This SIMD math for parallel computations. Compiler will complain if you
// mix this with the math constructs we made for class.
// ** All SIMD math constructs will be prefixed with `ss`

__declspec(align(16)) class ssvec3 {
public:
    ssvec3();
    ssvec3(__m128 v);
    ssvec3(float x, float y, float z);
    ssvec3 operator+(const ssvec3 &) const;
    ssvec3 operator-(const ssvec3 &) const;
    ssvec3 operator-() const;
    
    ssvec3 operator*(float) const;
    float dot(const ssvec3 &) const;
    ssvec3 cross(const ssvec3 &) const;
    
    void scale(float);
    void scale(float, float, float);
    float* ptr();

    float length() const;
    ssvec3 normalize() const;
    float angle(const ssvec3 &) const;
    void print();

    __m128 v;
    
};


__declspec(align(16)) class ssvec4 {
public:
    ssvec4();
    ssvec4(__m128 v);
    ssvec4(float x, float y, float z, float w);
    ssvec4 operator+(const ssvec4&) const;
    ssvec4 operator-(const ssvec4&) const;
    ssvec4 operator-() const;
    
    ssvec4 operator*(const ssvec4&) const;
    ssvec4 operator*(const float&) const;
    void dehomogenize();
    
    float* ptr();
    void print();
    
    __m128 v;
    
};


__declspec(align(16)) class ssmat4 {
public:
    ssmat4();
    ssmat4(__m128[4]);
    ssmat4(const float (&el)[4][4]);
    ssmat4(float, float, float, float,
         float, float, float, float,
         float, float, float, float,
         float, float, float, float);

    void set(float, float, float, float,
             float, float, float, float,
             float, float, float, float,
             float, float, float, float);
    
    ssmat4 operator*(const ssmat4&) const;
    ssvec4 operator*(const ssvec4&) const;
    ssmat4& operator=(const ssmat4&);
    
	static ssmat4 transpose(const ssmat4&);
	static ssmat4 identity();
    void makeIdentity();
    void makeTranspose();
    
    float* ptr();
    void print();
    
    __m128 m[4]; // row-major
};


#endif
