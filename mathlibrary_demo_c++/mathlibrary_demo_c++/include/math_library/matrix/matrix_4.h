#ifndef __MATRIX4_H__
#define __MATRIX4_H__ 1

#include "vector_3.h"
#include "vector_4.h"
#include "matrix_3.h"

#include <stdio.h>

class Matrix4x4{
 public:

  Matrix4x4();
  Matrix4x4(float a[16]);
  Matrix4x4(float value);
  Matrix4x4(const float* value);
  Matrix4x4(const Matrix4x4& copy);
  ~Matrix4x4();

  Matrix4x4 Identity() const;
  Matrix4x4 Multiply(const Matrix4x4& other) const;

  float Determinant() const;
  Matrix4x4 Adjoint() const;
  bool GetInverse(Matrix4x4& out) const;
  bool Inverse();

  Matrix4x4 Transpose() const;


  static Matrix4x4 Translate(const Vector3& distance);
  static Matrix4x4 Translate(float x, float y, float z);

  static Matrix4x4 Scale(const Vector3& scale);
  static Matrix4x4 Scale(float x, float y, float z);

  static Matrix4x4 RotateX(float radians);
  static Matrix4x4 RotateY(float radians);
  static Matrix4x4 RotateZ(float radians);

  static Matrix4x4 GetTransform(const Vector3& translate, const Vector3& scale,
                      float rotateX, float rotateY, float rotateZ);

  static Matrix4x4 GetTransform(float trans_x, float trans_y, float trans_z,
                      float scale_x, float scale_y, float scale_Z,
                      float rotateX, float rotateY, float rotateZ);

  Matrix4x4 PerspectiveMatrix(float fov, float aspect,
	  float near, float far) const;

  Matrix4x4 OrthoMatrix(float right, float left, float top, float valueottom,
	  float near, float far) const;

  Vector4 GetColum(int colum) const;
  Vector4 GetLine(int line) const;

  Matrix4x4 operator+(const Matrix4x4& other) const;
  Matrix4x4& operator+=(const Matrix4x4& other);
  Matrix4x4 operator+(float value) const;
  Matrix4x4& operator+=(float value);
  Matrix4x4 operator-(const Matrix4x4& other) const;
  Matrix4x4& operator-=(const Matrix4x4& other);
  Matrix4x4 operator-(float value) const;
  Matrix4x4& operator-=(float value);
  Matrix4x4& operator*=(float value);
  Matrix4x4 operator*(float value) const;
  Matrix4x4& operator/=(float value);
  Matrix4x4 operator/(float value) const;
  bool operator==(const Matrix4x4& other);
  bool operator!=(const Matrix4x4& other);
  void operator=(const Matrix4x4& other);

  float m[16];
};


inline Matrix4x4::Matrix4x4() {
	m[0] = 0.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
	m[4] = 0.0f; m[5] = 0.0f; m[6] = 0.0f; m[7] = 0.0f;
	m[8] = 0.0f; m[9] = 0.0f; m[10] = 0.0f; m[11] = 0.0f;
	m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 0.0f;
}
inline Matrix4x4::Matrix4x4(float array[16]) {
	m[0] = array[0]; m[1] = array[1]; m[2] = array[2]; m[3] = array[3];
	m[4] = array[4]; m[5] = array[5]; m[6] = array[6]; m[7] = array[7];
	m[8] = array[8]; m[9] = array[9]; m[10] = array[10]; m[11] = array[11];
	m[12] = array[12]; m[13] = array[13]; m[14] = array[14]; m[15] = array[15];
}
inline Matrix4x4::Matrix4x4(const float* value) {
	m[0] = value[0]; m[1] = value[1]; m[2] = value[2]; m[3] = value[3];
	m[4] = value[4]; m[5] = value[5]; m[6] = value[6]; m[7] = value[7];
	m[8] = value[8]; m[9] = value[9]; m[10] = value[10]; m[11] = value[11];
	m[12] = value[12]; m[13] = value[13]; m[14] = value[14]; m[15] = value[15];
}
inline Matrix4x4::Matrix4x4(float value) {
	m[0] = value; m[1] = value; m[2] = value; m[3] = value;
	m[4] = value; m[5] = value; m[6] = value; m[7] = value;
	m[8] = value; m[9] = value; m[10] = value; m[11] = value;
	m[12] = value; m[13] = value; m[14] = value; m[15] = value;
}
inline Matrix4x4::Matrix4x4(const Matrix4x4& copy) {
	m[0] = copy.m[0]; m[1] = copy.m[1]; m[2] = copy.m[2]; m[3] = copy.m[3];
	m[4] = copy.m[4]; m[5] = copy.m[5]; m[6] = copy.m[6]; m[7] = copy.m[7];
	m[8] = copy.m[8]; m[9] = copy.m[9]; m[10] = copy.m[10]; m[11] = copy.m[11];
	m[12] = copy.m[12]; m[13] = copy.m[13]; m[14] = copy.m[14]; m[15] = copy.m[15];
}
inline Matrix4x4::~Matrix4x4() {}

inline Matrix4x4 Matrix4x4::Identity() const {
	float tmp[16];
	tmp[0] = 1.0f; tmp[1] = 0.0f; tmp[2] = 0.0f; tmp[3] = 0.0f;
	tmp[4] = 0.0f; tmp[5] = 1.0f; tmp[6] = 0.0f; tmp[7] = 0.0f;
	tmp[8] = 0.0f; tmp[9] = 0.0f; tmp[10] = 1.0f; tmp[11] = 0.0f;
	tmp[12] = 0.0f; tmp[13] = 0.0f; tmp[14] = 0.0f; tmp[15] = 1.0f;

	return Matrix4x4(tmp);
}
inline Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& other)const  {
	float tmp[16];
	tmp[0] = m[0] * other.m[0] + m[1] * other.m[4] + m[2] * other.m[8] + m[3] * other.m[12];
	tmp[1] = m[0] * other.m[1] + m[1] * other.m[5] + m[2] * other.m[9] + m[3] * other.m[13];
	tmp[2] = m[0] * other.m[2] + m[1] * other.m[6] + m[2] * other.m[10] + m[3] * other.m[14];
	tmp[3] = m[0] * other.m[3] + m[1] * other.m[7] + m[2] * other.m[11] + m[3] * other.m[15];
	tmp[4] = m[4] * other.m[0] + m[5] * other.m[4] + m[6] * other.m[8] + m[7] * other.m[12];
	tmp[5] = m[4] * other.m[1] + m[5] * other.m[5] + m[6] * other.m[9] + m[7] * other.m[13];
	tmp[6] = m[4] * other.m[2] + m[5] * other.m[6] + m[6] * other.m[10] + m[7] * other.m[14];
	tmp[7] = m[4] * other.m[3] + m[5] * other.m[7] + m[6] * other.m[11] + m[7] * other.m[15];
	tmp[8] = m[8] * other.m[0] + m[9] * other.m[4] + m[10] * other.m[8] + m[11] * other.m[12];
	tmp[9] = m[8] * other.m[1] + m[9] * other.m[5] + m[10] * other.m[9] + m[11] * other.m[13];
	tmp[10] = m[8] * other.m[2] + m[9] * other.m[6] + m[10] * other.m[10] + m[11] * other.m[14];
	tmp[11] = m[8] * other.m[3] + m[9] * other.m[7] + m[10] * other.m[11] + m[11] * other.m[15];
	tmp[12] = m[12] * other.m[0] + m[13] * other.m[4] + m[14] * other.m[8] + m[15] * other.m[12];
	tmp[13] = m[12] * other.m[1] + m[13] * other.m[5] + m[14] * other.m[9] + m[15] * other.m[13];
	tmp[14] = m[12] * other.m[2] + m[13] * other.m[6] + m[14] * other.m[10] + m[15] * other.m[14];
	tmp[15] = m[12] * other.m[3] + m[13] * other.m[7] + m[14] * other.m[11] + m[15] * other.m[15];
	return Matrix4x4(tmp);
}
inline float Matrix4x4::Determinant() const {
	float tmp = m[12] * m[9] * m[6] * m[3] - m[8] * m[13] * m[6] * m[3] -
		m[12] * m[5] * m[10] * m[3] + m[4] * m[13] * m[10] * m[3] +
		m[8] * m[5] * m[14] * m[3] - m[4] * m[9] * m[14] * m[3] -
		m[12] * m[9] * m[2] * m[7] + m[8] * m[13] * m[2] * m[7] +
		m[12] * m[1] * m[10] * m[7] - m[0] * m[13] * m[10] * m[7] -
		m[8] * m[1] * m[14] * m[7] + m[0] * m[9] * m[14] * m[7] +
		m[12] * m[5] * m[2] * m[11] - m[4] * m[13] * m[2] * m[11] -
		m[12] * m[1] * m[6] * m[11] + m[0] * m[13] * m[6] * m[11] +
		m[4] * m[1] * m[14] * m[11] - m[0] * m[5] * m[14] * m[11] -
		m[8] * m[5] * m[2] * m[15] + m[4] * m[9] * m[2] * m[15] +
		m[8] * m[1] * m[6] * m[15] - m[0] * m[9] * m[6] * m[15] -
		m[4] * m[1] * m[10] * m[15] + m[0] * m[5] * m[10] * m[15];
	return tmp;
}
inline Matrix4x4 Matrix4x4::Adjoint() const {
	float tmp[9] = { m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15] };
	float tmp1[9] = { m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15] };
	float tmp2[9] = { m[4], m[5], m[7], m[8], m[9], m[11], m[12], m[13], m[15] };
	float tmp3[9] = { m[4], m[5], m[6], m[8], m[9], m[10], m[12], m[13], m[14] };
	float tmp4[9] = { m[1], m[2], m[3], m[9], m[10], m[11], m[13], m[14], m[15] };
	float tmp5[9] = { m[0], m[2], m[3], m[8], m[10], m[11], m[12], m[14], m[15] };
	float tmp6[9] = { m[0], m[1], m[3], m[8], m[9], m[11], m[12], m[13], m[15] };
	float tmp7[9] = { m[0], m[1], m[2], m[8], m[9], m[10], m[12], m[13], m[14] };
	float tmp8[9] = { m[1], m[2], m[3], m[5], m[6], m[7], m[13], m[14], m[15] };
	float tmp9[9] = { m[0], m[2], m[3], m[4], m[6], m[7], m[12], m[14], m[15] };
	float tmp10[9] = { m[0], m[1], m[3], m[4], m[5], m[7], m[12], m[13], m[15] };
	float tmp11[9] = { m[0], m[1], m[2], m[4], m[5], m[6], m[12], m[13], m[14] };
	float tmp12[9] = { m[1], m[2], m[3], m[5], m[6], m[7], m[9], m[10], m[11] };
	float tmp13[9] = { m[0], m[2], m[3], m[4], m[6], m[7], m[8], m[10], m[11] };
	float tmp14[9] = { m[0], m[1], m[3], m[4], m[5], m[7], m[8], m[9], m[11] };
	float tmp15[9] = { m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10] };

	Matrix3x3 ma = Matrix3x3(tmp);Matrix3x3 ma1 = Matrix3x3(tmp1);
	Matrix3x3 ma2 = Matrix3x3(tmp2);Matrix3x3 ma3 = Matrix3x3(tmp3);
	Matrix3x3 ma4 = Matrix3x3(tmp4);Matrix3x3 ma5 = Matrix3x3(tmp5);
	Matrix3x3 ma6 = Matrix3x3(tmp6);Matrix3x3 ma7 = Matrix3x3(tmp7);
	Matrix3x3 ma8 = Matrix3x3(tmp8);Matrix3x3 ma9 = Matrix3x3(tmp9);
	Matrix3x3 ma10 = Matrix3x3(tmp10);Matrix3x3 ma11 = Matrix3x3(tmp11);
	Matrix3x3 ma12 = Matrix3x3(tmp12);Matrix3x3 ma13 = Matrix3x3(tmp13);
	Matrix3x3 ma14 = Matrix3x3(tmp14);Matrix3x3 ma15 = Matrix3x3(tmp15);

	float final_tmp[16] = {
		ma.Determinant(), (-1)*ma1.Determinant(), ma2.Determinant(), (-1)*ma3.Determinant(),
		(-1)*ma4.Determinant(), ma5.Determinant(), (-1)*ma6.Determinant(), ma7.Determinant(),
		ma8.Determinant(), (-1)*ma9.Determinant(), ma10.Determinant(), (-1)*ma11.Determinant(),
		(-1)*ma12.Determinant(), ma13.Determinant(), (-1)*ma14.Determinant(), ma15.Determinant()
 };
	return Matrix4x4(final_tmp);
}
inline bool Matrix4x4::Inverse() {
	if (this->Determinant() == 0.0f)return false;
	*this = this->Adjoint().Transpose() / Determinant();
	return true;
}
inline bool Matrix4x4::GetInverse(Matrix4x4& out) const {
	if (out.Determinant() == 0.0f)return false;
	out.Adjoint().Transpose() / Determinant();
	return true;
}
inline Matrix4x4 Matrix4x4::Transpose() const {
	float tmp[16];
	tmp[0] = m[0]; tmp[1] = m[4]; tmp[2] = m[8]; tmp[3] = m[12];
	tmp[4] = m[1]; tmp[5] = m[5]; tmp[6] = m[9]; tmp[7] = m[13];
	tmp[8] = m[2]; tmp[9] = m[6]; tmp[10] = m[10]; tmp[11] = m[14];
	tmp[12] = m[3]; tmp[13] = m[7]; tmp[14] = m[11]; tmp[15] = m[15];
	return Matrix4x4(tmp);
}
inline Matrix4x4 Matrix4x4::Translate(const Vector3& distance) {
	float tmp[16];
	tmp[0] = 1.0f; tmp[1] = 0.0f; tmp[2] = 0.0f; tmp[3] = distance.x;
	tmp[4] = 0.0f; tmp[5] = 1.0f; tmp[6] = 0.0f; tmp[7] = distance.y;
	tmp[8] = 0.0f ;tmp[9] = 0.0f; tmp[10] = 1.0f; tmp[11] = distance.z;
	tmp[12] = 0.0f; tmp[13] = 0.0f; tmp[14] = 0.0f; tmp[15] = 1.0f;
	return Matrix4x4(tmp);
}
inline Matrix4x4 Matrix4x4::Translate(float x, float y, float z){
	float tmp[16];
	tmp[0] = 1.0f; tmp[1] = 0.0f; tmp[2] = 0.0f; tmp[3] = x;
	tmp[4] = 0.0f; tmp[5] = 1.0f; tmp[6] = 0.0f; tmp[7] = y;
	tmp[8] = 0.0f; tmp[9] = 0.0f; tmp[10] = 1.0f; tmp[11] = z;
	tmp[12] = 0.0f; tmp[13] = 0.0f; tmp[14] = 0.0f; tmp[15] = 1.0f;
	return Matrix4x4(tmp);
}
inline Matrix4x4 Matrix4x4::Scale(const Vector3& scale){
	float tmp[16];
	tmp[0] = scale.x; tmp[1] = 0.0f; tmp[2] = 0.0f; tmp[3] = 0.0f;
	tmp[4] = 0.0f; tmp[5] = scale.y; tmp[6] = 0.0f; tmp[7] = 0.0f;
	tmp[8] = 0.0f; tmp[9] = 0.0f; tmp[10] = scale.z; tmp[11] = 0.0f;
	tmp[12] = 0.0f; tmp[13] = 0.0f; tmp[14] = 0.0f; tmp[15] = 1.0f;
	return Matrix4x4(tmp);
}
inline Matrix4x4 Matrix4x4::Scale(float x, float y, float z){
	float tmp[16];
	tmp[0] = x; tmp[1] = 0.0f; tmp[2] = 0.0f; tmp[3] = 0.0f;
	tmp[4] = 0.0f; tmp[5] = y; tmp[6] = 0.0f; tmp[7] = 0.0f;
	tmp[8] = 0.0f; tmp[9] = 0.0f; tmp[10] = z; tmp[11] = 0.0f;
	tmp[12] = 0.0f; tmp[13] = 0.0f; tmp[14] = 0.0f; tmp[15] = 1.0f;
	return Matrix4x4(tmp);
}
inline Matrix4x4 Matrix4x4::RotateX(float radians){
	float tmp[16];
	float valueCos = cos(radians);
	float valueSin = sin(radians);
	tmp[0] = 1.0f; tmp[1] = 0.0f; tmp[2] = 0.0f; tmp[3] = 0.0f;
	tmp[4] = 0.0f; tmp[5] = valueCos; tmp[6] = -valueSin; tmp[7] = 0.0f;
	tmp[8] = 0.0f; tmp[9] = valueSin; tmp[10] = valueCos; tmp[11] = 0.0f;
	tmp[12] = 0.0f; tmp[13] = 0.0f; tmp[14] = 0.0f; tmp[15] = 1.0f;
	return Matrix4x4(tmp);
}
inline Matrix4x4 Matrix4x4::RotateY(float radians){
	float tmp[16];
	float valueCos = cosf(radians);
	float valueSin = sinf(radians);
	tmp[0] = valueCos; tmp[1] = 0.0f; tmp[2] = valueSin; tmp[3] = 0.0f;
	tmp[4] = 0.0f; tmp[5] = 1.0f; tmp[6] = 0.0f; tmp[7] = 0.0f;
	tmp[8] = -valueSin; tmp[9] = 0.0f; tmp[10] = valueCos; tmp[11] = 0.0f;
	tmp[12] = 0.0f; tmp[13] = 0.0f; tmp[14] = 0.0f; tmp[15] = 1.0f;
	return Matrix4x4(tmp);
}

inline Matrix4x4 Matrix4x4::RotateZ(float radians) {
	float tmp[16];
	float valueCos = cosf(radians);
	float valueSin = sinf(radians);
	tmp[0] = valueCos; tmp[1] = -valueSin; tmp[2] = 0.0f; tmp[3] = 0.0f;
	tmp[4] = valueSin; tmp[5] = valueCos; tmp[6] = 0.0f; tmp[7] = 0.0f;
	tmp[8] = 0.0f; tmp[9] = 0.0f; tmp[10] = 1.0f; tmp[11] = 0.0f;
	tmp[12] = 0.0f; tmp[13] = 0.0f; tmp[14] = 0.0f; tmp[15] = 1.0f;
	return Matrix4x4(tmp);
}

inline Matrix4x4 Matrix4x4::GetTransform(const Vector3& translate,
								const Vector3& scale,
								float rotateX, float rotateY, float rotateZ)   {
	Matrix4x4 tmp;
	tmp = tmp.Identity();
	tmp = tmp.Multiply(Scale(scale));
	tmp = tmp.Multiply(RotateZ(rotateZ));
	tmp = tmp.Multiply(RotateX(rotateX));
	tmp = tmp.Multiply(RotateY(rotateY));
	tmp = tmp.Multiply(Translate(translate));

	Matrix4x4 rotation;
	rotation = rotation.RotateX(rotateX).Multiply(rotation.RotateY(rotateY)).Multiply(rotation.RotateZ(rotateZ));

	Matrix4x4 translation;
	Matrix4x4 scaling;
	Matrix4x4 result;
	result = translation.Translate(translate).Multiply(rotation.Multiply(scaling.Scale(scale)));


	return result;
}

inline Matrix4x4 Matrix4x4::GetTransform(float trans_x, float trans_y, float trans_z,
	float scale_x, float scale_y, float scale_z,
	float rotateX, float rotateY, float rotateZ)  {
	Matrix4x4 tmp;
	tmp = tmp.Identity();
	tmp = tmp.Multiply(Scale(scale_x, scale_y, scale_z));
	tmp = tmp.Multiply(RotateZ(rotateZ));
	tmp = tmp.Multiply(RotateX(rotateX));
	tmp = tmp.Multiply(RotateY(rotateY));
	tmp = tmp.Multiply(Translate(trans_x, trans_y, trans_z));

	Matrix4x4 rotation;
	rotation = rotation.RotateX(rotateX).Multiply(rotation.RotateY(rotateY)).Multiply(rotation.RotateZ(rotateZ));

	Matrix4x4 translation;
	Matrix4x4 scaling;
	Matrix4x4 result;
	result = translation.Translate(trans_x, trans_y, trans_z).Multiply(rotation.Multiply(scaling.Scale(scale_x, scale_y, scale_z)));


	return result;
}

inline Matrix4x4 Matrix4x4::PerspectiveMatrix(float fov, float aspect, float, float) const
{
	
	return Matrix4x4();
}

inline Vector4 Matrix4x4::GetColum(int colum) const {
	Vector4 tmp;
	switch (colum)
	{
	case 0: tmp.x = m[0]; tmp.y = m[4]; tmp.z = m[8]; tmp.w = m[12]; break;
	case 1: tmp.x = m[1]; tmp.y = m[5]; tmp.z = m[9]; tmp.w = m[13]; break;
	case 2: tmp.x = m[2]; tmp.y = m[6]; tmp.z = m[10]; tmp.w = m[14]; break;
	case 3: tmp.x = m[3]; tmp.y = m[7]; tmp.z = m[11]; tmp.w = m[15]; break;
	}
	return Vector4(tmp);
}

inline Vector4 Matrix4x4::GetLine(int line) const {
	Vector4 tmp;
	switch (line)
	{
	case 0: tmp.x = m[0]; tmp.y = m[1]; tmp.z = m[2]; tmp.w = m[3]; break;
	case 1: tmp.x = m[4]; tmp.y = m[5]; tmp.z = m[6]; tmp.w = m[7]; break;
	case 2: tmp.x = m[8]; tmp.y = m[9]; tmp.z = m[10]; tmp.w = m[11]; break;
	case 3: tmp.x = m[12]; tmp.y = m[13]; tmp.z = m[14]; tmp.w = m[15]; break;
	}
	return Vector4(tmp);
}

inline Matrix4x4 Matrix4x4::OrthoMatrix(float right, float left, float top, float valueottom,
	float near, float far) const {

	return Matrix4x4();
}
inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const {
	float tmp[16] = { m[0] + other.m[0], m[1] + other.m[1], m[2] + other.m[2], m[3] + other.m[3]
						,m[4] + other.m[4], m[5] + other.m[5], m[6] + other.m[6], m[7] + other.m[7]
						,m[8] + other.m[8], m[9] + other.m[9], m[10] + other.m[10], m[11] + other.m[11]
						,m[12] + other.m[12], m[13] + other.m[13], m[14] + other.m[14], m[15] + other.m[15] };
	return Matrix4x4(tmp);
}
inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other) {
	float tmp[16] = { m[0] += other.m[0], m[1] += other.m[1], m[2] += other.m[2], m[3] += other.m[3]
					,m[4] += other.m[4], m[5] += other.m[5], m[6] += other.m[6], m[7] += other.m[7]
					,m[8] += other.m[8], m[9] += other.m[9], m[10] += other.m[10], m[11] += other.m[11]
					,m[12] += other.m[12], m[13] += other.m[13], m[14] += other.m[14], m[15] += other.m[15] };
	return Matrix4x4(tmp);
}
inline Matrix4x4 Matrix4x4::operator+(float value) const {
	float tmp[16] = { m[0] + value, m[1] + value, m[2] + value, m[3] + value
					,m[4] + value, m[5] + value, m[6] + value, m[7] + value
					,m[8] + value, m[9] + value, m[10] + value, m[11] + value
					,m[12] + value, m[13] + value, m[14] + value, m[15] + value };
	return Matrix4x4(tmp);
}
inline Matrix4x4& Matrix4x4::operator+=(float value) {
	float tmp[16] = { m[0] += value, m[1] += value, m[2] += value, m[3] += value
					,m[4] += value, m[5] += value, m[6] += value, m[7] += value
					,m[8] += value, m[9] += value, m[10] += value, m[11] += value
					,m[12] += value, m[13] += value, m[14] += value, m[15] += value };
	return Matrix4x4(tmp);
}
inline Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const {
	float tmp[16] = { m[0] - other.m[0], m[1] - other.m[1], m[2] - other.m[2], m[3] - other.m[3]
					,m[4] - other.m[4], m[5] - other.m[5], m[6] - other.m[6], m[7] - other.m[7]
					,m[8] - other.m[8], m[9] - other.m[9], m[10] - other.m[10], m[11] - other.m[11]
					,m[12] - other.m[12], m[13] - other.m[13], m[14] - other.m[14], m[15] - other.m[15] };
	return Matrix4x4(tmp);
}
inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other) {
	float tmp[16] = { m[0] -= other.m[0], m[1] -= other.m[1], m[2] -= other.m[2], m[3] -= other.m[3]
					,m[4] -= other.m[4], m[5] -= other.m[5], m[6] -= other.m[6], m[7] -= other.m[7]
					,m[8] -= other.m[8], m[9] -= other.m[9], m[10] -= other.m[10], m[11] -= other.m[11]
					,m[12] -= other.m[12], m[13] -= other.m[13], m[14] -= other.m[14], m[15] -= other.m[15] };
	return Matrix4x4(tmp);
}
inline Matrix4x4 Matrix4x4::operator-(float value) const {
	float tmp[16] = { m[0] - value, m[1] - value, m[2] - value, m[3] - value
					,m[4] - value, m[5] - value, m[6] - value, m[7] - value
					,m[8] - value, m[9] - value, m[10] - value, m[11] - value
					,m[12] - value, m[13] - value, m[14] - value, m[15] - value };
	return Matrix4x4(tmp);
}
inline Matrix4x4& Matrix4x4::operator-=(float value) {
	float tmp[16] = { m[0] -= value, m[1] -= value, m[2] -= value, m[3] -= value
					,m[4] -= value, m[5] -= value, m[6] -= value, m[7] -= value
					,m[8] -= value, m[9] -= value, m[10] -= value, m[11] -= value
					,m[12] -= value, m[13] -= value, m[14] -= value, m[15] -= value };
	return Matrix4x4(tmp);
}
inline Matrix4x4& Matrix4x4::operator*=(float value) {
	float tmp[16] = { m[0] *= value, m[1] *= value, m[2] *= value, m[3] *= value
					,m[4] *= value, m[5] *= value, m[6] *= value, m[7] *= value
					,m[8] *= value, m[9] *= value, m[10] *= value, m[11] *= value
					,m[12] *= value, m[13] *= value, m[14] *= value, m[15] *= value };
	return Matrix4x4(tmp);
}
inline Matrix4x4 Matrix4x4::operator*(float value) const {
	float tmp[16] = { m[0] * value, m[1] * value, m[2] * value, m[3] * value
					,m[4] * value, m[5] * value, m[6] * value, m[7] * value
					,m[8] * value, m[9] * value, m[10] * value, m[11] * value
					,m[12] * value, m[13] * value, m[14] * value, m[15] * value };
	return Matrix4x4(tmp);
}
inline Matrix4x4& Matrix4x4::operator/=(float value) {
	float tmp[16] = { m[0] /= value, m[1] /= value, m[2] /= value, m[3] /= value
					,m[4] /= value, m[5] /= value, m[6] /= value, m[7] /= value
					,m[8] /= value, m[9] /= value, m[10] /= value, m[11] /= value
					,m[12] /= value, m[13] /= value, m[14] /= value, m[15] /= value };
	return Matrix4x4(tmp);
}
inline Matrix4x4 Matrix4x4::operator/(float value) const {
	float valueInverse = 1 / value;
	float tmp[16] = { m[0] / value, m[1] / value, m[2] / value, m[3] / value
					,m[4] / value, m[5] / value, m[6] / value, m[7] / value
					,m[8] / value, m[9] / value, m[10] / value, m[11] / value
					,m[12] / value, m[13] / value, m[14] / value, m[15] / value };
	return Matrix4x4(tmp);
}
inline bool Matrix4x4::operator==(const Matrix4x4& other) {
	return(m[0] == other.m[0] && m[1] == other.m[1] && m[2] == other.m[2] && m[3] == other.m[3]
		&& m[4] == other.m[4] && m[5] == other.m[5] && m[6] == other.m[6] && m[7] == other.m[7]
		&& m[8] == other.m[8] && m[9] == other.m[9] && m[10] == other.m[10] && m[11] == other.m[11]
		&& m[12] == other.m[12] && m[13] == other.m[13] && m[14] == other.m[14] && m[15] == other.m[15]);
}
inline bool Matrix4x4::operator!=(const Matrix4x4& other) {
	return (m[0] == other.m[0] && m[1] == other.m[1] && m[2] == other.m[2] && m[3] == other.m[3]
		&& m[4] == other.m[4] && m[5] == other.m[5] && m[6] == other.m[6] && m[7] == other.m[7]
		&& m[8] == other.m[8] && m[9] == other.m[9] && m[10] == other.m[10] && m[11] == other.m[11]
		&& m[12] == other.m[12] && m[13] == other.m[13] && m[14] == other.m[14] && m[15] == other.m[15]);
}
inline void Matrix4x4::operator=(const Matrix4x4& other) {
	m[0] = other.m[0]; m[1] = other.m[1]; m[2] = other.m[2]; m[3] = other.m[3];
	m[4] = other.m[4]; m[5] = other.m[5]; m[6] = other.m[6]; m[7] = other.m[7];
	m[8] = other.m[8]; m[9] = other.m[9]; m[10] = other.m[10]; m[11] = other.m[11];
	m[12] = other.m[12]; m[13] = other.m[13]; m[14] = other.m[14]; m[15] = other.m[15];
}
#endif
