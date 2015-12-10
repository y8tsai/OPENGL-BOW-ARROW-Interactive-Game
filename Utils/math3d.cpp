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
float vec3::operator[](int i) const {
	if( i > -1 && i < 3)
		return v[i];
}

float& vec3::operator[](int i) {
	return v[i];
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
	v[0] = (l == 0.0 ? 0.0f : v[0] / l );
	v[1] = (l == 0.0 ? 0.0f : v[1] / l );
	v[2] = (l == 0.0 ? 0.0f : v[2] / l );
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

vec3 mat4::operator*(const vec3 &b) const {
	vec3 r;
	r.v[0] = m[0][0] * b.v[0] + m[0][1] * b.v[1] + m[0][2] * b.v[2];
	r.v[1] = m[1][0] * b.v[0] + m[1][1] * b.v[1] + m[1][2] * b.v[2];
	r.v[2] = m[2][0] * b.v[0] + m[2][1] * b.v[1] + m[2][2] * b.v[2];
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

mat4 mat4::makeTranspose() {
	float t;
	mat4 transposed = *this;
	for( int i = 0; i < 4; ++i ) {
        for( int j = i; j < 4; ++j ) {
            
			if( i == j ) {
				continue;
			}

            t = transposed.m[j][i];
            transposed.m[j][i] = transposed.m[i][j];
            transposed.m[i][j] = t;
        }
    }
	return transposed;
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

mat4 quat::tomat4(quat q) {
	mat4 m;
	float xx = q.x * q.x;
	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float xw = q.x * q.w;

	float yy = q.y * q.y;
	float yz = q.y * q.z;
	float yw = q.y * q.w;
	
	float zz = q.z * q.z;
	float zw = q.z * q.w;

	m.m[0][0] = 1 - 2 * (yy + zz); m.m[0][1] = 2 * (xy - zw);       m.m[0][2] = 2 * (xz + yw);     m.m[0][3] = 0;
	m.m[1][0] = 2 * (xy + zw);     m.m[1][1] = 1 - 2 * ( xx + zz);  m.m[1][2] = 2 * (yz -xw);      m.m[1][3] = 0;
	m.m[2][0] = 2 * (xz -yw);	   m.m[2][1] = 2 * (yz +xw);        m.m[2][2] = 1 - 2 * (xx + yy); m.m[2][3] = 0;
	m.m[3][0] = 0;                 m.m[3][1] = 0;                   m.m[3][2] = 0;                 m.m[3][3] = 1;

	return m;
}