#include "ProfileCircular.h"

#include "libraries/geometry/gcf.h"


SO_NODE_SOURCE(ProfileCircular)

void ProfileCircular::initClass()
{
     SO_NODE_INIT_CLASS(ProfileCircular, ProfileRT, "Profile");
}

ProfileCircular::ProfileCircular()
{
    SO_NODE_CONSTRUCTOR(ProfileCircular);
    SO_NODE_ADD_FIELD( rMin, (0.) );
    SO_NODE_ADD_FIELD( rMax, (1.) );
    SO_NODE_ADD_FIELD( phiMin, (-gcf::pi) );
    SO_NODE_ADD_FIELD( phiMax, (gcf::pi) );
}

Box3D ProfileCircular::getBox() const
{
    double rMinV = rMin.getValue();
    double rMaxV = rMax.getValue();
    double phiMinV = phiMin.getValue();
    double phiMaxV = phiMax.getValue();

    double xMin = cos(phiMinV);
    double xMax = cos(phiMaxV);
    double yMin = sin(phiMinV);
    double yMax = sin(phiMaxV);
    if (xMin > xMax) std::swap(xMin, xMax);
    if (yMin > yMax) std::swap(yMin, yMax);

    if (phiMinV <= 0. && 0. <= phiMaxV)
        xMax = 1.;
    if (phiMinV <= -gcf::pi || phiMaxV >= gcf::pi)
        xMin = -1.;
    if (phiMinV <= 0.5*gcf::pi && 0.5*gcf::pi <= phiMaxV)
        yMax = 1.;
    if (phiMinV <= -0.5*gcf::pi && -0.5*gcf::pi <= phiMaxV)
        yMin = -1.;

    xMax *= xMax > 0. ? rMaxV : rMinV;
    xMin *= xMin > 0. ? rMinV : rMaxV;

    yMax *= yMax > 0. ? rMaxV : rMinV;
    yMin *= yMin > 0. ? rMinV : rMaxV;

    return Box3D(
        Vector3D(xMin, yMin, 0.),
        Vector3D(xMax, yMax, 0.)
    );
}

bool ProfileCircular::isInside(double u, double v) const
{
    double r2 = u*u + v*v;
    if (r2 < pow(rMin.getValue(), 2)) return false;
    if (r2 > pow(rMax.getValue(), 2)) return false;
    double phi = atan2(v, u);
    if (phi < phiMin.getValue()) return false;
    if (phi > phiMax.getValue()) return false;
    return true;
}

QVector<Vector2D> ProfileCircular::makeMesh(const QSize& dims) const
{
    const int iMax = dims.width();
    const int jMax = dims.height();
    QVector<Vector2D> ans;

    for (int i = 0; i < iMax; ++i) {
        double un = i/double(iMax - 1);
        double u = (1. - un)*phiMin.getValue() + un*phiMax.getValue();
        for (int j = 0; j < jMax; ++j) {
            double vn = j/double(jMax - 1);
            double v = (1. - vn)*rMin.getValue() + vn*rMax.getValue();
            ans << v*Vector2D(cos(u), sin(u));
        }
    }
    return ans;
}