#pragma once

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFDouble.h>
#include "kernel/air/AirAbstract.h"

class SoFieldSensor;
class SoSensor;


class TONATIUH_KERNEL AirPolynomial: public AirAbstract
{
    SO_NODE_HEADER(AirPolynomial);

public:
    static void initClass();
    AirPolynomial();
    ~AirPolynomial();

    double transmission(double distance) const;

    enum Coefficients {
        Vacuum,
        VittitoeBiggsClear,
        VittitoeBiggsHazy,
        BallestrinClear,
        BallestrinHazy,
        Custom
    };

    SoSFEnum coefficients;

    SoSFDouble a0;
    SoSFDouble a1;
    SoSFDouble a2;
    SoSFDouble a3;

    NAME_ICON_FUNCTIONS("Polynomial", ":/images/AirPolynomial.png")

protected:
    static void update_coefficients(void* data, SoSensor*);

private:
    SoFieldSensor* m_sensor_coefficients;
};
