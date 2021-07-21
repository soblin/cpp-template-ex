#include <algorithm>
#include <cmath>
#include <iostream>

#include <boost/utility/enable_if.hpp>

#include "geo.h"

namespace official {
struct point_category {};

template <class T, class Enable = void>
struct get_geometry_category;

template <class T, class Enable = void>
struct point_traits {
  static double x(const T& p) {
    return p.x();
  }
  static double y(const T& p) {
    return p.y();
  }

  static T subtract(const T& a, const T& b) {
    return T(x(a) - x(b), y(a) - y(b));
  }
};

class Point {
  double x_ = 0.0;
  double y_ = 0.0;

public:
  Point() = default;
  Point(double x, double y) : x_(x), y_(y) {}
  double x() const {
    return x_;
  }
  double y() const {
    return y_;
  }
};

template <>
struct get_geometry_category<Point> {
  typedef point_category type;
};

template <class T>
struct get_geometry_category<
    T,
    typename boost::enable_if<geo::is_point_category<T>>::type> {
  typedef point_category type;
};

template <class T>
struct point_traits<
    T,
    typename boost::enable_if<geo::is_point_category<T>>::type> {
  static double x(const T& p) {
    return geo::point_traits<T>::getX(p);
  }
  static double y(const T& p) {
    return geo::point_traits<T>::getY(p);
  }
  static T subtract(const T& a, const T& b) {
    return geo::point_traits<T>::subtract(a, b);
  }
};

template <class Point>
double distance_impl(Point a, Point b, point_category, point_category) {
  typedef point_traits<Point> traits;
  const Point d = traits::subtract(a, b);
  return std::hypot(traits::x(d), traits::y(d));
}

template <class Geometry1, class Geometry2>
double distance(Geometry1 a, Geometry2 b) {
  return distance_impl(a,
                       b,
                       typename get_geometry_category<Geometry1>::type(),
                       typename get_geometry_category<Geometry2>::type());
}
} // namespace official

int main() {
  {
    official::Point p1(0.0, 0.0);
    official::Point p2(3.0, 3.0);
    double d = official::distance(p1, p2);
    std::cout << d << std::endl;
  }
  {
    geo::Point p1(0.0, 0.0);
    geo::Point p2(3.0, 3.0);
    std::cout << official::distance(p1, p2) << std::endl;
  }
}
