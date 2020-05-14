#include "Vector3D.h"

#include "gcf.h"

const Vector3D Vector3D::Zero(0., 0., 0.);
const Vector3D Vector3D::UnitX(1., 0., 0.);
const Vector3D Vector3D::UnitY(0., 1., 0.);
const Vector3D Vector3D::UnitZ(0., 0., 1.);


bool Vector3D::operator==(const Vector3D& v) const
{
    if (this == &v) return true;

    return gcf::equals(x, v.x) &&
           gcf::equals(y, v.y) &&
           gcf::equals(z, v.z);
}

bool Vector3D::operator!=(const Vector3D& v) const
{
    return !(*this == v);
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v)
{
    os << v.x << ", " << v.y << ", " << v.z;
    return os;
}
