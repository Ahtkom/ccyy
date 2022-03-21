#include <math/geometry/CoordinateSequence.h>

namespace ccyy {
namespace math {
namespace geometry {

CoordinateSequence &CoordinateSequence::convertTo(CoordinateSystem new_cs)
{
    for (std::size_t i = 0; i != size(); ++i) {
        // operator[](i).convertTo(new_cs);
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const CoordinateSequence &coordinates)
{
    os << "CoordinateSequence[";
    for (std::size_t i = 0; i != coordinates.size() - 1; ++i) {
        os << coordinates[i] << ",";
    }
    os << coordinates[coordinates.size() - 1] << "]";
    return os;
}

} // namespace geometry
} // namespace math
} // namespace ccyy