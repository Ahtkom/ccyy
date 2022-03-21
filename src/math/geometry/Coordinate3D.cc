#include <math/geometry/Coordinate3D.h>

namespace ccyy {
namespace math {
namespace geometry {

Coordinate3D::Coordinate3D(double x, double y, double z, CoordinateSystem cs)
    : Coordinate(x, y, cs)
    , z_(z)
{}

Coordinate3D::Coordinate3D(const Coordinate &coordinate, double z)
    : Coordinate(coordinate)
    , z_(z)
{}

std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate)
{
    os << "Coordinate[" << coordinate.getX() << ", " << coordinate.getY();
    if (coordinate.is3D()) {
        os << ", " << static_cast<const Coordinate3D &>(coordinate).getZ();
    }
    os << "]";
    return os;
}


} // namespace geometry
} // namespace math
} // namespace ccyy