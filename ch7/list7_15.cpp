#include <cmath>
#include <iostream>

namespace official {

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

template <class Point>
class line_segment {
  Point p1_, p2_;

public:
  typedef Point point_type;

  line_segment() = default;
  line_segment(const Point& p1, const Point& p2) : p1_(p1), p2_(p2) {}
  const Point& p1() const {
    return p1_;
  }
  const Point& p2() const {
    return p2_;
  }
};

template <class T>
struct line_segment_traits {
  typedef typename T::point_type point_type;

  static const point_type& p1(const T& line) {
    return line.p1();
  }
  static const point_type& p2(const T& line) {
    return line.p2();
  }
};

struct point_category {};
struct line_segment_category {};

template <class T>
struct get_geometry_category;

template <>
struct get_geometry_category<Point> {
  typedef point_category type;
};

template <class Point>
struct get_geometry_category<line_segment<Point>> {
  typedef line_segment_category type;
};

template <class Geometry1, class Geometry2>
double distance(Geometry1 a, Geometry2 b) {
  return distance_impl(a,
                       b,
                       typename get_geometry_category<Geometry1>::type(),
                       typename get_geometry_category<Geometry2>::type());
}

template <class Point>
double distance_impl(Point a, Point b, point_category, point_category) {
  typedef point_traits<Point> traits;
  const Point d = traits::subtract(a, b);
  return std::hypot(traits::x(d), traits::y(d));
}

template <class Point, class LineSegment>
double
distance_impl(Point a, LineSegment b, point_category, line_segment_category) {
  typedef line_segment_traits<LineSegment> traits;
  return std::min(distance(a, traits::p1(b)), distance(a, traits::p2(b)));
}

template <class LineSegment, class Point>
double
distance_impl(LineSegment a, Point b, line_segment_category, point_category) {
  typedef line_segment_traits<LineSegment> traits;
  return std::min(b, a);
}

} // namespace official

// user
// need to adapt this class for `official`
namespace mine {

class MyPoint {
  double x_ = 0.0;
  double y_ = 0.0;

public:
  MyPoint() = default;
  MyPoint(double x, double y) : x_(x), y_(y) {}
  double x() const {
    return x_;
  }
  double y() const {
    return y_;
  }
};
} // namespace mine

// to use your custom class, you have to specialize `get_geometry_caterogry`,
// `point_traits`, `line_segment_traits` for your class
namespace official {

using namespace mine;

template <>
struct get_geometry_category<MyPoint> {
  typedef point_category type;
};

template <>
struct point_traits<MyPoint> {
  static double x(const MyPoint& p) {
    return p.x();
  }
  static double y(const MyPoint& p) {
    return p.y();
  }

  static MyPoint subtract(const MyPoint& a, const MyPoint& b) {
    return MyPoint(x(a) - x(b), y(a) - y(b));
  }
};
} // namespace official

int main() {
  using namespace official;

  {
    Point p1(0.0, 0.0);
    Point p2(3.0, 3.0);

    line_segment<Point> line(Point(2.0, 2.0), Point(3.0, 3.0));

    double d1 = distance(p1, p2);
    std::cout << d1 << std::endl;

    double d2 = distance(p1, line);
    std::cout << d2 << std::endl;
  }
  {
    mine::MyPoint p1(0.0, 0.0);
    mine::MyPoint p2(3.0, 3.0);

    line_segment<mine::MyPoint> line(mine::MyPoint(2.0, 2.0),
                                     mine::MyPoint(3.0, 3.0));

    double d1 = distance(p1, p2);
    std::cout << d1 << std::endl;

    double d2 = distance(p1, line);
    std::cout << d2 << std::endl;
  }
}
