#include "DataObject.h"

#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QScriptEngine>
#include <QString>
#include <QStringList>

DataObject::DataObject(QObject* parent):
    QObject(parent)
{

}

QScriptValue DataObject::read(const QString& fileName)
{
    m_data.clear();

    QFileInfo info = QString("project:") + fileName;
    if (!info.exists()) {
        QMessageBox::warning(0, "Warning", QString("File not found:\n") + fileName);
        return false;
    }

    QFile file(info.absoluteFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
          QMessageBox::warning(0, "Warning", QString("File cannot be opened:\n") + fileName);
        return false;
    }

    QTextStream in(&file);
    QString line;
    while (in.readLineInto(&line)) {
        m_data << line;
    }
    return true;
}

QScriptValue DataObject::write(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
          QMessageBox::warning(0, "Warning", QString("File cannot be opened:\n") + fileName);
        return false;
    }

    QTextStream out(&file);
    for (QString& line : m_data) {
        out << line << Qt::endl;
    }
    return true;
}

void DataObject::clear()
{
    m_data.clear();
}

QScriptValue DataObject::rows()
{
    return m_data.size();
}

QScriptValue DataObject::row(int n)
{
    if (n < 0 || n >= m_data.size()) return "";
    return m_data[n];
}

void DataObject::setRow(int n, const QString& line)
{
    if (n < 0 || n >= m_data.size()) return;
    m_data[n] = line;
}

void DataObject::addRow(const QString& line)
{
    m_data << line;
}

QScriptValue DataObject::array(int n)
{
    if (n < 0 || n >= m_data.size()) return "";
    QStringList list = m_data[n].split(',');
    return qScriptValueFromSequence(engine(), list);
}

void DataObject::setArray(int n, QScriptValue value)
{
    if (n < 0 || n >= m_data.size()) return;
    QStringList list;
    qScriptValueToSequence(value, list);
    m_data[n] = list.join(',');
}

void DataObject::addArray(QScriptValue value)
{
    QStringList list;
    qScriptValueToSequence(value, list);
    m_data << list.join(',');
}

//QScriptValue DataCSV::part(int n, int m)
//{
//    if (n < 0 || n >= m_data.size()) return "";
//    QVector<QStringRef> refs = m_data[n].splitRef(',');
//    if (m < 0 || m >= refs.size()) return "";
//    return refs[m].toString();
//}
