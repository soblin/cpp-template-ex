#ifndef GEO_H
#define GEO_H

#include <utility>

namespace geo {

// specify this for user's custom class and `true`
template <class T>
struct is_point_category {
  static const bool value = false;
};

// specify this for user's custom class (.getX() and .getY() are just nominal
// **interface**)
template <class T>
struct point_traits {
  static double getX(const T& p) {
    return p.getX();
  }
  static double getY(const T& p) {
    return p.getY();
  }

  static T subtract(const T& a, const T& b) {
    return T(a.getX() - b.getX(), a.getY() - b.getY());
  }
};

class Point {
  double x_ = 0.0;
  double y_ = 0.0;

public:
  Point() = default;
  Point(double x, double y) : x_(x), y_(y) {}
  double getX() const {
    return x_;
  }
  double getY() const {
    return y_;
  }
};

template <>
struct is_point_category<Point> {
  static const bool value = true;
};

template <>
struct point_traits<std::pair<double, double>> {
  typedef std::pair<double, double> point_type;

  static double getX(const point_type& p) {
    return p.first;
  }
  static double getY(const point_type& p) {
    return p.second;
  }

  static point_type subtract(const point_type& a, const point_type& b) {
    return std::make_pair(a.first - b.first, a.second - b.second);
  }
};

template <>
struct is_point_category<std::pair<double, double>> {
  static const bool value = true;
};

} // namespace geo

#endif
