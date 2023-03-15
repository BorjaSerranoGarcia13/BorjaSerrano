#ifndef __VECTOR2_H__
#define __VECTOR2_H__ 1

#include <cmath>
#include <math_utils.h>
#include <math.h>

class Vector2 {
 public:

  Vector2();
  Vector2(float x, float y);
  Vector2(const Vector2& copy);
  ~Vector2();

  Vector2 operator+(const Vector2& other) const;
  Vector2 operator+(float value);
  Vector2& operator+=(const Vector2& other);
  Vector2& operator+=(float value);
  Vector2 operator-(const Vector2& other) const;
  Vector2 operator-(float value) const;
  Vector2& operator-();
  Vector2& operator-=(const Vector2& other);
  Vector2& operator-=(float value);
  bool operator==(const Vector2& other) const;
  bool operator!=(const Vector2& other) const;
  void operator=(const Vector2& other);
  void operator=(float value);
  Vector2 operator*(float value) const;
  Vector2& operator*=(float value);
  Vector2 operator/(float value) const;
  Vector2& operator/=(float value);

  float Magnitude() const;
  void Normalize();
  Vector2 Normalized() const;

  void Scale(const Vector2 scale);

  float SqrMagnitude() const;
  static float Distance(const Vector2 a, const Vector2 b);

  static float DotProduct(Vector2 a, Vector2 b);

  static Vector2 Lerp(const Vector2 a, const Vector2 b, float t);
  static Vector2 LerpUnclamped(const Vector2 a, const Vector2 b, float t);

  static const Vector2 up;
  static const Vector2 down;
  static const Vector2 right;
  static const Vector2 left;
  static const Vector2 zero;
  static const Vector2 one;

  float x;
  float y;
};

inline Vector2::Vector2() {
	this->x = 0.0f;
	this->y = 0.0f;
}

inline Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

inline Vector2::Vector2(const Vector2& other) {
	this->x = other.x;
	this->y = other.y;
}

inline Vector2::~Vector2() {
}

inline Vector2 Vector2::operator+(const Vector2& other) const {
	
	return Vector2(x + other.x,y + other.y);
}

inline Vector2 Vector2::operator+(float value) {
  
	return Vector2(x + value, y + value);
}

inline Vector2& Vector2::operator+=(const Vector2& other){
	x += other.x;
	y += other.y;
	return *this;
}

inline Vector2& Vector2::operator+=(float value){
	y += value;
	x += value;
	return *this;
}

inline Vector2 Vector2::operator-(const Vector2& other) const {
  
	return Vector2 (x - other.x, x - other.y);
}

inline Vector2 Vector2::operator-(float value) const {
  return Vector2(x - value, x - value);
}

inline Vector2& Vector2::operator-() {
	x *= -1.0f;
	y *= -1.0f;
	return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

inline Vector2& Vector2::operator-=(float value){
	x -= value;
	y -= value;
	return *this;
}

inline bool Vector2::operator==(const Vector2& other) const {
	if (x == other.x && y == other.y) {
		return true;
	}
	else return false;
}

inline bool Vector2::operator!=(const Vector2& other) const {
	if (x != other.x && y != other.y) {
		return true;
	}
	else return false;
	return true;
}


inline void Vector2::operator=(const Vector2& other) {
	 x = other.x;
	 y = other.y;
	
}

inline void Vector2::operator=(float value) {
	x = value;
	y = value;
}

inline Vector2 Vector2::operator*(float value) const {
	return Vector2(x * value, y * value);
}

inline Vector2& Vector2::operator*=(float value) {  
	x *= value;
	y *= value;
	return *this;
}

inline Vector2 Vector2::operator/(float value) const {
	return Vector2(x / value, y / value);
}

inline Vector2& Vector2::operator/=(float value) {
	x /= value;
	y /= value;
	return *this;
}

inline float Vector2::Magnitude() const {
  
	return sqrt(SqrMagnitude());
}

inline void Vector2::Normalize() {
	float num = Magnitude();
	x /= num;
	y /= num;
}

inline Vector2 Vector2::Normalized() const {
	float num = Magnitude();
	return Vector2(x / num, y / num);
}

inline void Vector2::Scale(const Vector2 scale){
	x *= scale.x;
	y *= scale.y;
}

inline float Vector2::SqrMagnitude() const {
  
	return x * x + y * y;
}


inline float Vector2::Distance(const Vector2 a, const Vector2 b) {
	Vector2 tmp;
	tmp.x = a.x - b.x;
	tmp.y = a.y - b.y;

  return tmp.Magnitude();
}

inline Vector2 Vector2::Lerp(const Vector2 a, const Vector2 b, float t) {	
	float clampedT = MathUtils::Clamp(t, 0, 1);
	return Vector2::LerpUnclamped(a, b, clampedT);
}

inline Vector2 Vector2::LerpUnclamped(const Vector2 a, const Vector2 b, float t) {
	return Vector2((b.x - a.x) * t + a.x, (b.y - a.y) * t + a.y);
}


inline float Vector2::DotProduct(Vector2 a, Vector2 b) {
	return a.x * b.x + a.y * b.y;
}

#endif 
