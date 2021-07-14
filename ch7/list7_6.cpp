#include <cmath>
#include <iostream>

namespace official {

template <class T>
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

template <class Point>
double distance(Point a, Point b) {
  typedef point_traits<Point> traits;
  const Point d = traits::subtract(a, b);
  return std::hypot(traits::x(d), traits::y(d));
}
} // namespace official

// This class `happens` to have required interface
class Point {
  double x_ = 0;
  double y_ = 0;

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

namespace mine {

class Point {
  double x_ = 0;
  double y_ = 0;

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
} // namespace mine

// adapt for mine::Point
namespace official {
template <>
struct point_traits<mine::Point> {
  static double x(const mine::Point& p) {
    return p.getX();
  }
  static double y(const mine::Point& p) {
    return p.getY();
  }
  static mine::Point subtract(const mine::Point& a, const mine::Point& b) {
    return mine::Point(x(a) - x(b), y(a) - y(b));
  }
};
} // namespace official

int main() {
  Point p1(1.0, 2.0), p2(2.0, 1.0);

  std::cout << official::distance(p1, p2) << std::endl;

  mine::Point p3(1.0, 2.0), p4(2.0, 1.0);

  std::cout << official::distance(p3, p4) << std::endl;
}
