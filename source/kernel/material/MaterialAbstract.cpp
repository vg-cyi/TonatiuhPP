#include "MaterialAbstract.h"

SO_NODE_ABSTRACT_SOURCE(MaterialAbstract)


void MaterialAbstract::initClass()
{
    SO_NODE_INIT_ABSTRACT_CLASS(MaterialAbstract, SoMaterial, "Material");

}

MaterialAbstract::MaterialAbstract()
{
    //SO_NODE_CONSTRUCTOR( TMaterial );

}

MaterialAbstract::~MaterialAbstract()
{
}