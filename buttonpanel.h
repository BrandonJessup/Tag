#ifndef ButtonPanel_H
#define ButtonPanel_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QRegularExpression>
#include <QProgressDialog>

#include "database.h"
#include "prompt.h"
#include "imagetagadderdialog.h"
#include "settings.h"

class ButtonPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonPanel(QWidget *parent = nullptr);

private:
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
    QString generateAndStoreThumbnail(const QString& path, const int& fileId);
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
};

#endif // ButtonPanel_H
