#ifndef CCYY_MATH_GEOMETRY_COORDINATE_H_
#define CCYY_MATH_GEOMETRY_COORDINATE_H_

#include <math/geometry/CoordinateSystem.h>
#include <util/Macro.h>

#include <string>
#include <sstream>

// forward declaration
namespace ccyy {
namespace math {
namespace geometry {

class Coordinate;
std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate);

} // namespace geometry
} // namespace math
} // namespace ccyy


namespace ccyy {
namespace math {
namespace geometry {

class Coordinate
{
public:
    Coordinate(double x, double y, CoordinateSystem cs = CoordinateSystem::RECTANGULAR);

    virtual ~Coordinate() = default;

    TO_STRING_METHOD

    double getX() const { return x_; }
    double getY() const { return y_; }

    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }

    virtual bool is3D() const { return false; }

    CoordinateSystem getCoordinateSystem() const { return cs_; }

    double distanceTo(const Coordinate &other);

    Coordinate &convertTo(CoordinateSystem new_cs);

private:
    double x_, y_;

    CoordinateSystem cs_;
};


} // namespace geometry
} // namespace math
} // namespace ccyy

#endif