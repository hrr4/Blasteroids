#ifndef VECTOR
#define VECTOR
 
#include <iosfwd>
#include <cmath>
 
template <class T>
class Vector {
 public:
  Vector() { set(T(), T(), T()); }
  Vector(T new_x, T new_y, T new_z) { set(new_x, new_y, new_z); }
  explicit Vector(T value) { set(value, value, value); }
 
  void set(T new_x, T new_y, T new_z) {
    x() = new_x;
    y() = new_y;
    z() = new_z;
  }
 
  T& x(){return _c[0];}
  T& y(){return _c[1];}
  T& z(){return _c[2];}
  T x() const{return _c[0];}
  T y() const{return _c[1];}
  T z() const{return _c[2];}
 
  void operator=(T value) {
    set(value, value, value);
  }
 
  void operator+=(const Vector& other) {
    set(x() + other.x(), y() + other.y(), z() + other.z());
  }
  void operator-=(const Vector& other) {
    set(x() - other.x(), y() - other.y(), z() - other.z());
  }
  void operator*=(T factor) {
    set(x() * factor, y() * factor, z() * factor);
  }
  void operator/=(T factor) {
    set(x() / factor, y() / factor, z() / factor);
  }
 
  T lengthSquared() const {
    return x()*x() + y()*y() + z()*z();
  }
  T length() const {
    return std::sqrt(lengthSquared());
  }
  void normalize() {
    operator/=(length());
  }
  void invert() {
    x() = -x();
    y() = -y();
    z() = -z();
  }
 
  operator const T*() const {
    return _c;
  }
 
  template <class U>
  Vector<U> convert() const {
    return Vector<U>(static_cast<U>(x()), static_cast<U>(y()), static_cast<U>(z()));
  }
 
 private:
  T _c[3];
};
 
template <class T>
inline const Vector<T> operator+(const Vector<T>& one, const Vector<T>& two) {
  return Vector<T>(one.x() + two.x(), one.y() + two.y(), one.z() + two.z());
}
template <class T>
inline const Vector<T> operator-(const Vector<T>& one, const Vector<T>& two) {
  return Vector<T>(one.x() - two.x(), one.y() - two.y(), one.z() - two.z());
}
template <class T>
inline const Vector<T> operator-(const Vector<T>& one) {
  return Vector<T>(-one.x(), -one.y(), -one.z());
}
template <class T>
inline const Vector<T> operator*(const Vector<T>& one, T factor) {
  return Vector<T>(one.x() * factor, one.y() * factor, one.z() * factor);
}
template <class T>
inline const Vector<T> operator*(T factor, const Vector<T>& one) {
  return Vector<T>(one.x() * factor, one.y() * factor, one.z() * factor);
}
template <class T>
inline const Vector<T> operator/(const Vector<T>& one, T factor) {
  return Vector<T>(one.x() / factor, one.y() / factor, one.z() / factor);
}
 
template <class T>
inline T operator*(const Vector<T>& one, const Vector<T>& two) { //Dotproduct
  return one.x()*two.x() + one.y()*two.y() + one.z()*two.z();
}
template <class T>
inline T boundedDot(const Vector<T>& one, const Vector<T>& two) {
  T dot = one * two;
  if (dot < 0)
    return 0;
  if (dot > 1)
    return 1;
  return dot;
}
template <class T>
inline Vector<T> operator%(const Vector<T>& one, const Vector<T> two){ //crossproduct
  return Vector<T>(one.y()*two.z() - one.z()*two.y(), one.z()*two.x() - one.x()*two.z(), 
		    one.x()*two.y() - one.y()*two.x());
}
 
template <class T>
inline Vector<T> normalize(const Vector<T>& vec){return vec / vec.length();}
 
template <class T>
inline bool operator==(const Vector<T>& one, const Vector<T>& two) {
  return one.x() == two.x() and one.y() == two.y() and one.z() == two.z();
}
template <class T>
inline bool operator!=(const Vector<T>& one, const Vector<T>& two) {
  return !(one == two);
}
 
/*
template<class T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
  os << '(' << vec.x() << ',' << ' ' << vec.y() << ',' << ' ' << vec.z() << ')';
  return os;
}
*/
 
typedef Vector<float> Vectorf;
typedef Vector<int> Vectori;
typedef Vector<size_t> Vectoru;
 
#endif
