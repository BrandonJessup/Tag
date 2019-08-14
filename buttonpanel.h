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

class ButtonPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonPanel(QWidget *parent = nullptr);

private:
    QBoxLayout* layout;
    QPushButton* addImageButton;
    QPushButton* addFileButton;
    QPushButton* addFolderButton;
    QString lastDirectory;

    void setSize();
    void createLayout();
    void createAddImageButton();
    void createAddFileButton();
    void createAddFolderButton();
    void relaySignals();

    QString directoryToOpen();
    QString getParentFolder(const QString& filePath);
    QString extractNameFromPath(const QString& path);
    bool fileAlreadyInDatabase(QString path);
    void tagAndAddToDatabase(const QString& path);
    void addTagsToFile(int fileId, QStringList tags);

signals:
    void filesChanged();
    void fileDialogClosed(QString filePath);
    void databaseTagsChanged();

public slots:
    void addImage();
    void addFile();
    void addFolder();
    void updateLastDirectory(QString pathToFile);
};

#endif // ButtonPanel_H
