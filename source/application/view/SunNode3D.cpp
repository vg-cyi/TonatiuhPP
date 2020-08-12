#include "SunNode3D.h"

#include "kernel/sun/SunPosition.h"

#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoNormal.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTextureCoordinate2.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoTransparencyType.h>

#include "libraries/math/gcf.h"

SunNode3D::SunNode3D()
{    
    create();
    m_sensor = new SoNodeSensor(update, this);
}

SunNode3D::~SunNode3D()
{
    delete m_sensor;
}

void SunNode3D::attach(SunPosition* sp)
{
    m_sensor->detach();
    m_sensor->attach(sp);
    update(this, 0);
}

void SunNode3D::create()
{
    m_transform = new SoTransform;
    addChild(m_transform);

    // from {0, 0, -1}
    SoTransform* sTransform = new SoTransform;
    sTransform->translation = SbVec3f(0., 0., -1.);
    addChild(sTransform);

//    SoShapeHints* hints = new SoShapeHints;
//    hints->shapeType = SoShapeHints::SOLID;
//    addChild(hints);

    // transparent textures do not check depth buffer
//    SoMaterial* material = new SoMaterial;
//    material->diffuseColor = SbVec3f(1, 1, 1);
//    material->transparency = 0.5;
//    addChild(material);

    SoTexture2* texture = new SoTexture2;
    texture->filename.setValue("../images/sun.png"); // relative to exe file
    texture->model = SoTexture2::REPLACE;
    addChild(texture);

    SoTextureCoordinate2* tCoords = new SoTextureCoordinate2;
    tCoords->point.set1Value(0, SbVec2f(0, 0));
    tCoords->point.set1Value(1, SbVec2f(1, 0));
    tCoords->point.set1Value(2, SbVec2f(1, 1));
    tCoords->point.set1Value(3, SbVec2f(0, 1));
    addChild(tCoords);

    SoTextureCoordinateBinding* tBind = new SoTextureCoordinateBinding;
    tBind->value.setValue(SoTextureCoordinateBinding::PER_VERTEX);
    addChild(tBind);

    SoCoordinate3* sCoords = new SoCoordinate3;
    double s = 0.05;
    sCoords->point.set1Value(0, SbVec3f(-s, -s, 0.));
    sCoords->point.set1Value(1, SbVec3f( s, -s, 0.));
    sCoords->point.set1Value(2, SbVec3f( s, s, 0.));
    sCoords->point.set1Value(3, SbVec3f(-s, s, 0.));
    addChild(sCoords);

//    SoNormal* normal = new SoNormal;
//    normal->vector.set1Value(0, SbVec3f(0, 0, 1));
//    addChild(normal);

//    SoNormalBinding* nBind = new SoNormalBinding;
//    nBind->value.setValue(SoNormalBinding::OVERALL);
//    addChild(nBind);

    SoFaceSet* shape = new SoFaceSet;
    shape->numVertices.set1Value(0, 4);
    addChild(shape);
}

void SunNode3D::update(void* data, SoSensor*)
{
    SunNode3D* node = (SunNode3D*) data;
    SunPosition* sp = (SunPosition*) node->m_sensor->getAttachedNode();
    // Rz(-gamma) Rx(alpha)
    node->m_transform->rotation =
        SbRotation(SbVec3f(1., 0., 0.), (90. + sp->elevation.getValue())*gcf::degree) *
        SbRotation(SbVec3f(0., 0., 1.),  -sp->azimuth.getValue()*gcf::degree);
}