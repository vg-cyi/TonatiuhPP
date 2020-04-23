#include <QFileDialog>
#include <QMessageBox>

#include "ExportDialog.h"
#include "kernel/gui/InstanceNode.h"
#include "kernel/raytracing/TShapeKit.h"

/**
 * Creates a dialog to define export parameters.
 * The dialog need \a sceneModel to allow user to select a surface to export.
 * Sets export mode to export all photos if \a previousSurfaceUrl is empty. Otherwise, sets to surface export mode.
 * Sets global coordinate system if \a previusInGlobal is \a true. Otherwise, sets to local coordinate system.
 * The current export file value takes the \a previousFile name. The file \a previousFile is the last file uses to export a photon map.
 */
ExportDialog::ExportDialog(SceneModel& sceneModel, QString previousSurfaceUrl, bool previusInGlobal, QString previousFile, QWidget* parent)
    : QDialog(parent),
      m_exportSceneModel(&sceneModel),
      m_exportSelectionModel(0)
{
    setupUi(this);
    connect(allMapRadio, SIGNAL(toggled(bool)), this, SLOT(SetExportAllPhotons(bool)) );
    connect(surfaceMapRadio, SIGNAL(toggled(bool)), this, SLOT(SetExportSurfacePhotons(bool)) );
    connect(selectFile, SIGNAL(clicked()), this, SLOT(SelectFile()) );


    m_exportSelectionModel = new QItemSelectionModel(m_exportSceneModel);

    modelView->setModel(m_exportSceneModel);
    modelView->setSelectionModel(m_exportSelectionModel);
    modelView->setSelectionMode(QAbstractItemView::SingleSelection);
    modelView->setSelectionBehavior(QAbstractItemView::SelectRows);
    modelView->setRootIsDecorated(true);

    if (!previousSurfaceUrl.isEmpty() )
    {
        SetExportSurfacePhotons(true);
        QModelIndex selectedNodeIndex = m_exportSceneModel->IndexFromNodeUrl(previousSurfaceUrl);
        m_exportSelectionModel->select(selectedNodeIndex, QItemSelectionModel::ClearAndSelect);

        QModelIndex parentIndex = selectedNodeIndex.parent();
        while (parentIndex != QModelIndex() )
        {
            modelView->expand(parentIndex);
            parentIndex = parentIndex.parent();
        }
    }

    if (previusInGlobal) globalCoordinatesRadio->setChecked(true);
    else localCoordinates->setChecked(true);

    if (!previousFile.isEmpty() ) fileNameEdit->setText(previousFile);
}

ExportDialog::ExportDialog(SceneModel& sceneModel, QWidget* parent)
    : QDialog(parent),
      m_exportSceneModel(&sceneModel),
      m_exportSelectionModel(0)
{
    setupUi(this);
    //connect( allMapRadio, SIGNAL( toggled( bool ) ), this, SLOT( SetExportAllPhotons( bool ) ) );
    connect(surfaceMapRadio, SIGNAL(toggled(bool)), this, SLOT(SetExportSurfacePhotons(bool)) );
    connect(selectFile, SIGNAL(clicked()), this, SLOT(SelectFile()) );

    m_exportSelectionModel = new QItemSelectionModel(m_exportSceneModel);

    modelView->setModel(m_exportSceneModel);
    modelView->setSelectionModel(m_exportSelectionModel);
    modelView->setSelectionMode(QAbstractItemView::SingleSelection);
    modelView->setSelectionBehavior(QAbstractItemView::SelectRows);
    modelView->setRootIsDecorated(true);

    allMapRadio->setVisible(false);
    surfaceMapRadio->setChecked(true);
    fileWidget->setVisible(false);
}
/*!
 * Destroys the file dialog.
 */
ExportDialog::~ExportDialog()
{
    delete m_exportSelectionModel;
}

/*!
 * Returns \a true if the option export all photon map option is selected. Otherwise, returns \a false.
 */
bool ExportDialog::ExportAllPhotonMap() const
{
    if (allMapRadio->isChecked() ) return true;
    else return false;
}

/*!
 * Return \a true if the global coordinates system is selected. Otherwise, returns \a  false.
 */
bool ExportDialog::ExportPhotonsInGlobal() const
{
    if (globalCoordinatesRadio->isChecked() ) return true;
    else return false;
}

/*!
 * Returns id to indicate selected photon map photons.
 *
 * If all photon map is selected, returns \a 0. To surface photon map returns \a 1.
 *
 * \sa GetSelectedSurface
 */
QString ExportDialog::GetExportFileName() const
{
    return fileNameEdit->text();
}

/*!
 * Return selected surface node url.
 *
 * Returns an empty string if there is not selection or selected node is not surface node.
 */
QString ExportDialog::GetSelectedSurface() const
{
    if (!surfaceMapRadio->isChecked () ) return 0;
    if (!m_exportSelectionModel->hasSelection() ) return 0;

    InstanceNode* selectedNode = m_exportSceneModel->NodeFromIndex(m_exportSelectionModel->currentIndex() );
    if (!selectedNode->GetNode()->getTypeId().isDerivedFrom(TShapeKit::getClassTypeId() ) ) return 0;

    //return m_exportSceneModel->PathFromIndex( m_exportSelectionModel->currentIndex() );
    return selectedNode->GetNodeURL();
}

/*!
 * Hides the modal dialog and sets the result code to Accepted.
 */
void ExportDialog::accept()
{
    if (allMapRadio->isVisible()) {
        if (fileNameEdit->text().isEmpty() )
        {
            QMessageBox::information(this, "Tonatiuh ",  "No file defined to save photon map", 1);
            return;
        }
    }
    if (surfaceMapRadio->isChecked () )
    {
        if (m_exportSelectionModel->hasSelection() )
        {
            InstanceNode* selectedNode = m_exportSceneModel->NodeFromIndex(m_exportSelectionModel->currentIndex() );
            if (!selectedNode->GetNode()->getTypeId().isDerivedFrom(TShapeKit::getClassTypeId() ) )
            {
                QMessageBox::information(this, "Tonatiuh",    "Selected node is not surface node", 1);
                return;
            }

        }
    }
    QDialog::accept();

}

/*!
 * If \a allPhotos is true set export mode to export all photon map.
 * Otherwise \a sets to export all photons if surface photons is not checked.
 */
void ExportDialog::SetExportAllPhotons(bool allPhotos)
{
    if (allPhotos) allMapRadio->setChecked(true);
    else if ( (!allPhotos) && (!surfaceMapRadio->isChecked() ) )
        allMapRadio->setChecked(true);
}

/*!
 * If \a allPhotos is true set export mode to export surface photons.
 * Otherwise \a sets to export surface photons if all photons is not checked.
 */
void ExportDialog::SetExportSurfacePhotons(bool surfacePhotos)
{
    if (surfacePhotos) surfaceMapRadio->setChecked(true);
    else if ( (!surfacePhotos) && (!allMapRadio->isChecked() ) )
        surfaceMapRadio->setChecked(true);
}

/*!
 * Opens a dialog to select a file as the the file to save the export information.
 *
 * \a fileNameEdit line will show the selected file path.
 */
void ExportDialog::SelectFile()
{
    QString currentDir = ".";

    QFileInfo currentFile(fileNameEdit->text() );
    QDir fileDir = currentFile.absoluteDir();
    if (fileDir.exists() ) currentDir = fileDir.absolutePath();


    QString fileName = QFileDialog::getSaveFileName(this, tr("Export PhotonMap"),
                                                    currentDir,
                                                    tr("Binary data files (*.dat)") );

    if (!fileName.isEmpty() )    {
        QStringList list = fileName.split(".");
        if (list.size()<2) {
            fileName.append(".dat");
        }
        fileNameEdit->setText(fileName);

    }

}

