#include "ParametersModel.h"

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/lists/SoFieldList.h>
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/nodes/SoGroup.h>

#include "ParametersItemField.h"
#include "ParametersItemNode.h"


ParametersModel::ParametersModel(QObject* parent):
    QStandardItemModel(parent)
{

}

void ParametersModel::setNode(SoNode* node)
{
    if (!node) return;
    beginResetModel();
    clear();
    setHorizontalHeaderLabels({"Parameter", "Value"});
    QStandardItem* parent = invisibleRootItem();

//    SoBaseKit* kit = dynamic_cast<SoBaseKit*>(node);
//    if (!kit) {
        QString name = node->getName().getString();
        QString nameType = node->getTypeId().getName().getString();
        QStandardItem* item = new QStandardItem(nameType);
        item->setEditable(false);
        parent->appendRow({new ParametersItemNode(name, node), item});
//    } else {
//        QString type = kit->getTypeId().getName().getString();
//        QStringList parts;
//        if (type == "TSeparatorKit")
//            parts << "transform";
//        else if (type == "TShapeKit")
//            parts << "shapeRT" << "profileRT" << "materialRT" << "material";
//        else if (type == "WorldKit")
//            parts;
//        else {
//            SoFieldList fields;
//            kit->getFields(fields);
//            for (int n = 0; n < fields.getLength(); ++n)
//            {
//                SoField* field = fields.get(n);
//                SbName name;
//                kit->getFieldName(field, name);
//                parts << name.getString();
//            }
//        }

//        for (QString part : parts)
//        {
//            SoNode* nodeSub = kit->getPart(part.toStdString().c_str(), false);
//            if (!nodeSub)
//                if (SoField* field = kit->getField(part.toStdString().c_str()))
//                    if (SoSFNode* fn = dynamic_cast<SoSFNode*>(field))
//                        nodeSub = fn->getValue();

//            if (nodeSub) {
////                QString name = nodeSub->getName().getString();
////                if (name.isEmpty())
//                QString name = nodeSub->getTypeId().getName().getString();
//                QStandardItem* item = new QStandardItem(name);
//                item->setEditable(false);
//                parent->appendRow({new ParametersItemNode(part, nodeSub), item});

//            }

//        }
//    }

    endResetModel();
}

bool ParametersModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    ParametersItemField* item = dynamic_cast<ParametersItemField*>(itemFromIndex(index));
    if (!item)
        return QStandardItemModel::setData(index, value, role);
    else {
        item->setData(value, role);

        ParametersItemNode* itemNode = (ParametersItemNode*) itemFromIndex(index.parent());
        SoNode* node = itemNode->node();
        SbName name;
        node->getFieldName(item->field(), name);
        emit valueModified(node, name.getString(), value.toString());

        return true;
    }
}



//            else if (part[part.size() - 1] == '*')
//            {
//                QString partX = part.left(part.size() - 1);
//                SoGroup* group = static_cast<SoGroup*>(kit->getPart(partX.toStdString().c_str(), false));
//                if (!group) continue;
//                int nMax = std::min(group->getNumChildren(), 10);
//                for (int n = 0; n < nMax; n++)
//                {
//                    SoNode* node = (SoNode*) group->getChild(n);
//                    if (node)
//                        parent->appendRow(new ParametersItemNode(node));
//                }
//            }

//    if (item->isCheckable()) {
//        ParametersItem* pitem = (ParametersItem*) item;
//        SoSFBool* f = dynamic_cast<SoSFBool*>(pitem->getField());
//        if (!f) return;
//        bool on = item->checkState() == Qt::Checked;
//        if (f->getValue() == on) return;
//    }
