#ifndef CCYY_MATH_GEOMETRY_COORDINATE3D_H_
#define CCYY_MATH_GEOMETRY_COORDINATE3D_H_

#include <math/geometry/CoordinateSystem.h>
#include <math/geometry/Coordinate.h>

namespace ccyy {
namespace math {
namespace geometry {

class Coordinate3D : public Coordinate
{
public:
    Coordinate3D(double x, double y, double z, CoordinateSystem cs = CoordinateSystem::RECTANGULAR);

    Coordinate3D(const Coordinate &coordinate, double z);

    ~Coordinate3D() = default;

    double getZ() const { return z_; }

    void setZ(double z) { z_ = z; }

    virtual bool is3D() const override { return true; }

private:
    double z_;
};

} // namespace geometry
} // namespace math
} // namespace ccyy

#endif