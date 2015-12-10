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

	float operator[](int i) const;  // retrieval
	float& operator[](int i);		// assignment
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

class mat3 {
public:
	mat3();
	mat3(const mat3&);
	mat3(float, float, float,
         float, float, float,
         float, float, float);

	mat3& operator=(const mat3&);

	float m[3][3];
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

	vec3 operator*(const vec3&) const;

	mat4& makeIdentity();
	mat4 makeTranspose();
	mat4& makeRotateX(float deg);
	mat4& makeRotateY(float deg);
	mat4& makeRotateZ(float deg);
	mat4& makeRotate(float deg, vec3 &axis);
	mat3 getRotation();
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
	static mat4 tomat4(quat q);
	static quat rotate(float rad, vec3 axis);

};
#endif
