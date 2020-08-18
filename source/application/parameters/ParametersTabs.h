#pragma once

#include <QTabWidget>

class SoBaseKit;
class SoNode;


class ParametersTabs: public QTabWidget
{
    Q_OBJECT

public:
    ParametersTabs(QWidget* parent = 0);

    void SelectionChanged(SoNode* node);
    void UpdateView();

signals:
    void valueModified(SoNode* node, QString field, QString value);

public slots:
    void setValue(SoNode* node, QString field, QString value);

private:
    void addTabNode(SoNode* node, QString partName);
    QStringList ContainerNodeParts(SoBaseKit* kit);

    SoNode* m_node;
};
