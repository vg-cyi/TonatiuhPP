#pragma once

#include <QDateTime>
#include <QPair>
#include <QVector>

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodekits/SoLightKit.h>


#include "trt.h"
#include "TSunShape.h"

struct BBox;
class Transform;
class TShapeKit;

/*!
  \class TLightKit TLightKit.h TLightKit.h
  \brief The TLightKit class provides a kit with a transform, a light, a shape and a sunshape to represents the sun light.


  The TLightKit structure:
  \verbatim
  CLASS TLightKit
  -->"this"
        "callbackList"
  -->   "transformGroup"
  -->      "transform"
  -->      "light"
  -->      "iconSeparator"
  -->         "icon"
  -->      "tsunshape"
  \endverbatim

  Detailed information on catalog parts:
  \verbatim
  CLASS TLightKit
  PVT   "this",  TLightKit  ---
        "callbackList",  SoNodeKitListPart [ SoCallback, SoEventCallback ]
  PVT   "transformGroup",  SoTransformSeparator  ---
        "transform",  SoTransform  ---
        "light",  SoLight  --- , (default type = SoDirectionalLight)
  PVT   "iconSeparator",  SoSeparator  ---
        "icon",  SoNode  --- , (default type = SoCube)
        "tsunshape",  TSunShape  --- , (default type = TDefaultSunShape)
  \endverbatim

*/

class TLightKit : public SoLightKit
{
    SO_KIT_HEADER(TLightKit);
     SO_KIT_CATALOG_ENTRY_HEADER(iconMaterial);
     SO_KIT_CATALOG_ENTRY_HEADER(iconTexture);
     SO_KIT_CATALOG_ENTRY_HEADER(tsunshape);



public:
    TLightKit();
    static void initClass();

    void ChangePosition( double newAzimuth, double newZenith );

    void Update( BBox box );
    void ComputeLightSourceArea( int widthDivisions,int heightDivisions,QVector< QPair< TShapeKit*, Transform > > surfacesList );

    trt::TONATIUH_REAL azimuth;
    trt::TONATIUH_REAL zenith;
    SoSFString disabledNodes;

private:
    virtual ~TLightKit();
    void UpdateSunPosition();


};
