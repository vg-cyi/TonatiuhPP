#pragma once

#include "kernel/TonatiuhKernel.h"
#include "kernel/raytracing/TAbstract.h"
#include <Inventor/nodes/SoSubNode.h>


class TONATIUH_KERNEL AirAbstract: public SoNode
{
    SO_NODE_ABSTRACT_HEADER(AirAbstract);

public:
    static void initClass();

    virtual double transmission(double /*distance*/) const {return 1.;}

    NAME_ICON_FUNCTIONS("X", ":/AirX.png")

protected:
    AirAbstract() {}
    ~AirAbstract() {}
};
