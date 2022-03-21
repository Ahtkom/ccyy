#ifndef CCYY_MATH_GEOMETRY_COORDINATE3DSEQUENCE_H_
#define CCYY_MATH_GEOMETRY_COORDINATE3DSEQUENCE_H_

#include <math/geometry/Coordinate3D.h>
#include <math/geometry/CoordinateSystem.h>

#include <vector>

namespace ccyy {
namespace math {
namespace geometry {

class Coordinate3DSequence
{
public:
    Coordinate3DSequence();

    ~Coordinate3DSequence();

    Coordinate3DSequence &convertTo(CoordinateSystem new_cs);

private:
    std::vector<Coordinate3D> coordinates_;

    CoordinateSystem cs_;
};

} // namespace geometry
} // namespace math
} // namespace ccyy

#endif