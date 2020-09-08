#pragma once

#include "kernel/profiles/ProfileRT.h"


class TONATIUH_KERNEL ProfileRegular: public ProfileRT
{
    SO_NODE_HEADER(ProfileRegular);

public:
    static void initClass();
    ProfileRegular();

    SoSFInt32 n;
    SoSFDouble r;

    Box2D getBox() const;
    bool isInside(double u, double v) const;
    QVector<vec2d> makeMesh(QSize& dims) const;

    NAME_ICON_FUNCTIONS("Regular", ":/profiles/ProfileRegular.png")

protected:
    ~ProfileRegular() {}
};
