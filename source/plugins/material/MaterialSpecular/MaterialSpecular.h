#pragma once

#include "kernel/material/MaterialRT.h"


class MaterialSpecular: public MaterialRT
{
    SO_NODE_HEADER(MaterialSpecular);

public:
    enum Distribution {
        pillbox = 0,
        Gaussian = 1
    };

    static void initClass();
    MaterialSpecular();

    bool OutputRay(const Ray& rayIn, const DifferentialGeometry& dg, Random& rand, Ray& rayOut) const;

    SoSFDouble reflectivity;
    SoSFDouble slope;
    SoSFEnum distribution;

    NAME_ICON_FUNCTIONS("Specular", ":/MaterialSpecular.png")

protected:
    ~MaterialSpecular();

    double m_sigmaOpt;

    static void updateReflectivity(void* data, SoSensor*);

private:
    SoFieldSensor* m_reflectivitySensor;
};


class MaterialSpecularFactory:
    public QObject, public MaterialFactoryT<MaterialSpecular>
{
    Q_OBJECT
    Q_INTERFACES(MaterialFactory)
    Q_PLUGIN_METADATA(IID "tonatiuh.MaterialFactory")
};
