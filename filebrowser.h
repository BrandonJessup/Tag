#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedLayout>
#include <QList>
#include <QMenu>
#include <QVariant>
#include <QMessageBox>
#include <QPushButton>
#include <QDesktopServices>
#include <QLineEdit>
#include <QFileDialog>
#include <QScrollBar>
#include <QProcess>

#include "userrole.h"
#include "selected.h"
#include "database.h"
#include "filetuple.h"
#include "taglist.h"
#include "tagadderdialog.h"
#include "settings.h"
#include "progressdialog.h"
#include "thumbnailmanager.h"

class FileBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit FileBrowser(ThumbnailManager* manager, QWidget *parent = nullptr);

private:
    ThumbnailManager* thumbnailManager;
    int revisionCount;
    QStackedLayout* layout;
    QListWidget* viewingArea;
    QList<int> searchList;
    QList<int> excludeList;

    void createLayout();
    void createViewingArea();
    void relaySignals();

    void addFileToViewingArea(const FileTuple& file);
    void addTagsToSelected(QStringList tags);
    void removeFiles();
    int getIdOfSelected();
    void selectFileWithId(int id);
    QString generateAndStoreThumbnail(const QString& path, const int& fileId);
    void updateLastDirectory(QString pathToFile);
    QString getParentFolder(const QString& filePath);

    void loadThumbnails(QStringList thumbnailPaths, QList<QListWidgetItem*> items, int revision);

protected:
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void selectionChanged(int selectedFile);
    void databaseTagsChanged();

public slots:
    void selectionChangedEmitter();
    void reloadContents();
    void showContextMenu(const QPoint& point);
    void fileRemovePrompt();
    void tagSelectedDialog();
    void updateSearchList(QList<int> tagIds, QList<int> excludeTagIds);
    void openFile(QListWidgetItem* item);
    void updateThumbnailScale(int percentage);
    void changeThumbnailOfSelectedFile();
    void showSelectedInExplorer();
    void reloadIfTagAddedImpactsSearch(int tagId);
    void reloadIfTagRemovedImpactsSearch(int tagId);
    void showNewestItem();
};

#endif // FILEBROWSER_H
