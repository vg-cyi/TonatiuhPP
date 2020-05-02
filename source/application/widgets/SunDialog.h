#pragma once

#include <QDialog>
#include <QMap>


#include "ui_sundialog.h"

class QComboBox;
class QFrame;
class QGroupBox;
class QItemSelectionModel;
class QTabWidget;
class SceneModel;
class TLightKit;
class ShapeAbstract;
class ShapeFactory;
class SunAbstract;
class SunFactory;

//!  LightDialog class is the dialog to define the light parameters.
/*!
   LightDialog sets light parameters. The parameters that user can define are light suunshape, light input aperture shape and light position.
 */
class SunDialog: public QDialog, private Ui::SunDialog
{
    Q_OBJECT

public:
    SunDialog(SceneModel& sceneModel, TLightKit* currentLightKit, QMap<QString, SunFactory*> sunShapeMap, QWidget* parent = 0);

    TLightKit* getLightKit();

public slots:
    void SetValue(SoNode* node, QString parameter, QString value);

protected slots:
    void ChangeSunshape(int index);
    void AddNodeToDisabledNodeList();
    void RemoveNodeFromDisabledNodeList();

private:
    void makeSunShapeTab();
    void makeSunPositionTab();
    void makeSunApertureTab();

    SceneModel* m_sceneModel;
    QItemSelectionModel* m_selectionModel;
    TLightKit* m_lightKitOld;
    SunAbstract* m_sunNew;
    QMap<QString, SunFactory*> m_sunShapeMap;
    int m_currentSunShapeIndex;
};
