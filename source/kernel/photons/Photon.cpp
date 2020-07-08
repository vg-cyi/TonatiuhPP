#include "Photon.h"


Photon::Photon():
    id(-1),
    pos(vec3d()),
    intersectedSurface(0),
    isFront(-1),
    isAbsorbed(-1)
{

}

Photon::Photon(double id, const vec3d& pos, InstanceNode* surface, int isFront, int isAbsorbed):
    id(id),
    pos(pos),
    isFront(isFront),
    intersectedSurface(surface),
    isAbsorbed(isAbsorbed)
{

}

