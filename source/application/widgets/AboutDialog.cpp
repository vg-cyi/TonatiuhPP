#include "AboutDialog.h"
#include "ui_AboutDialog.h"

#include <QDate>

AboutDialog::AboutDialog(QWidget* parent):
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QString textVersion = qApp->applicationVersion();

    QString textDate = QString(__DATE__).simplified(); // "Jan  1 2020"
    QDate date = QDate::fromString(textDate, "MMM d yyyy");
    textDate = date.toString("d MMM yyyy");

    QString text = QString("Version: %1 (%2)").arg(textVersion).arg(textDate);

    ui->label_version->setText(text);

    setWindowFlag(Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint, true);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
