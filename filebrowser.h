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
#include <QtConcurrent/QtConcurrent>

#include "userrole.h"
#include "selected.h"
#include "database.h"
#include "filetuple.h"
#include "taglist.h"
#include "tagadderdialog.h"

class FileBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit FileBrowser(QWidget *parent = nullptr);

private:
    int revisionCount;
    QStackedLayout* layout;
    QListWidget* viewingArea;
    QList<int> searchList;
    QList<int> excludeList;
    QSize baseThumbnailSize;
    QIcon defaultImageIcon;

    void createLayout();
    void createViewingArea();
    void createDefaultIcons();
    void relaySignals();

    void addFileToViewingArea(const FileTuple& file);
    void addTagsToSelected(QStringList tags);
    bool somethingIsSelected();
    void removeFiles();
    int getIdOfSelected();
    void selectFileWithId(int id);

    void loadThumbnails(QStringList thumbnailPaths, QList<QListWidgetItem*> items, int revision);

protected:
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void selectionChanged(int selectedFile);
    void databaseTagsChanged();

    void thumbnailReady(const QIcon& icon, QListWidgetItem* item, int revision);

public slots:
    void selectionChangedEmitter();
    void reloadContents();
    void showContextMenu(const QPoint& point);
    void fileRemovePrompt();
    void tagSelectedDialog();
    void updateSearchList(QList<int> tagIds, QList<int> excludeTagIds);
    void openFileAtIndex(QListWidgetItem* item);
    void updateThumbnailScale(int percentage);

    void applyThumbnail(const QIcon& icon, QListWidgetItem* item, int revision);
};

#endif // FILEBROWSER_H
