#pragma once

#include "kernel/profiles/ProfileRT.h"
#include "libraries/geometry/Vector2D.h"
#include "libraries/fields/MFVec2.h"


class TONATIUH_KERNEL ProfilePolygon: public ProfileRT
{
    SO_NODE_HEADER(ProfilePolygon);

public:
    static void initClass();
    ProfilePolygon();

    MFVec2 points;
    const QPolygonF& getPolygon() const {return m_polygon;}

    Box3D getBox() const;
    bool isInside(double u, double v) const;
    QVector<Vector2D> makeMesh(const QSize& dims) const;

    NAME_ICON_FUNCTIONS("Polygon", ":/images/ProfilePolygon.png")

protected:
    ~ProfilePolygon();

    QPolygonF m_polygon;

    SoNodeSensor* m_sensor;
    static void onSensor(void* data, SoSensor*);
};
