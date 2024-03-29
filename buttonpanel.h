#ifndef ButtonPanel_H
#define ButtonPanel_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QRegularExpression>

#include "database.h"
#include "prompt.h"
#include "imagetagadderdialog.h"
#include "settings.h"
#include "progressdialog.h"
#include "thumbnailmanager.h"

class ButtonPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonPanel(ThumbnailManager* thumbnailManager, QWidget *parent = nullptr);

private:
    ThumbnailManager* thumbnailManager;
    QBoxLayout* layout;
    QPushButton* addImageButton;
    QPushButton* addVideoButton;
    QPushButton* addFileButton;
    QPushButton* addFolderButton;

    void setSize();
    void createLayout();
    void createAddImageButton();
    void createAddVideoButton();
    void createAddFileButton();
    void createAddFolderButton();
    void relaySignals();

    QString getParentFolder(const QString& filePath);
    QString extractNameFromPath(const QString& path);
    bool fileAlreadyInDatabase(QString path);
    int addNewImages(QStringList paths);
    int addNewImagesWithoutTagging(QStringList paths);
    void addToDatabase(const QString& path, const QString& type);
    void tagAndAddToDatabase(const QString& path, const QString& type);
    void addTagsToFile(int fileId, QStringList tags);

signals:
    void filesChanged();
    void fileDialogClosed(QString filePath);
    void databaseTagsChanged();

public slots:
    void addImage();
    void addVideo();
    void addFile();
    void addFolder();
    void updateLastDirectory(QString pathToFile);
    void importFiles(QStringList paths);
};

#endif // ButtonPanel_H
