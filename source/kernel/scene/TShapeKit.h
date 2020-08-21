#pragma once

#include "kernel/TonatiuhKernel.h"

#include <Inventor/nodekits/SoShapeKit.h>

class ShapeRT;
class MaterialRT;

class SoFieldSensor;
class SoSensor;


class TONATIUH_KERNEL TShapeKit: public SoBaseKit
{
    SO_KIT_HEADER(TShapeKit);

    SO_KIT_CATALOG_ENTRY_HEADER(topSeparator);

public:
    static void initClass();
    TShapeKit();

    SoSFNode shapeRT;
    SoSFNode profileRT;
    SoSFNode materialRT;
    SoSFNode material;

    SoShapeKit* m_shapeKit;
protected:
     ~TShapeKit();

    SoFieldSensor* m_sensorShape;
    SoFieldSensor* m_sensorProfile;
    static void onSensor(void* data, SoSensor*);

    void setDefaultOnNonWritingFields();
};
