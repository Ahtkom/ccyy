#ifndef CCYY_MATH_GEOMETRY_COORDINATESEQUENCE_H_
#define CCYY_MATH_GEOMETRY_COORDINATESEQUENCE_H_

#include <math/geometry/Coordinate3D.h>
#include <math/geometry/CoordinateSystem.h>

#include <vector>
#include <string>
#include <sstream>

// forward declaration
namespace ccyy {
namespace math {
namespace geometry {

class CoordinateSequence;
std::ostream &operator<<(std::ostream &os, const CoordinateSequence &coordinates);

} // namespace geometry
} // namespace math
} // namespace ccyy


namespace ccyy {
namespace math {
namespace geometry {

class CoordinateSequence
{
public:
    CoordinateSequence() = default;

    ~CoordinateSequence() = default;

    TO_STRING_METHOD

    std::size_t size() const { return coordinates_.size(); }

    Coordinate &operator[](std::size_t index) {
        return coordinates_[index];
    }

    const Coordinate &operator[](std::size_t index) const {
        return coordinates_[index];
    }

    CoordinateSequence &convertTo(CoordinateSystem new_cs);

private:
    std::vector<Coordinate> coordinates_;

    CoordinateSystem cs_;
};



} // namespace geometry
} // namespace math
} // namespace ccyy

#endif