#pragma once

#include <QAction>

class TFactory;
class ShapeFactory;
class ProfileFactory;
class MaterialFactory;
class TrackerFactory;
class ComponentFactory;


//!  ActionInsertShape class is the action to insert a shape in the scene.
/*!
   ActionInsertShape is the action added to menu and toolbar for each shape plugin.
 */
class ActionInsert: public QAction
{
    Q_OBJECT

public:
    ActionInsert(TFactory* factory, QObject* parent);

public slots:
    void onTriggered();

signals:
    void InsertSurface(ShapeFactory* factory);
    void InsertProfile(ProfileFactory* factory);
    void InsertMaterial(MaterialFactory* factory);
    void InsertTracker(TrackerFactory* factory);
    void InsertComponent(ComponentFactory* factory);

private:
    TFactory* m_factory;
};
