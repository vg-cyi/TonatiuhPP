#pragma once

#include <QTreeView>

#include "SceneDelegate.h"

class SceneView: public QTreeView
{
    Q_OBJECT

public:
    SceneView(QWidget* parent = 0);
    ~SceneView();

signals:
    void dragAndDrop(const QModelIndex& newParent, const QModelIndex& item);
    void dragAndDropCopy(const QModelIndex& newParent, const QModelIndex& item);
    void nodeNameModificated(const QModelIndex& index, const QString& newName);
    void showMenu(const QModelIndex& index);

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dropEvent(QDropEvent* event);

protected slots:
    void currentChanged(const QModelIndex& current, const QModelIndex& previous);
    void closeEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint);

private:
    void startDrag(QMouseEvent* event);

    QModelIndex m_currentIndex;
    QPoint m_startPos;
};
