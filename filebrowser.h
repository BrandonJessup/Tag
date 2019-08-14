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
    QStackedLayout* layout;
    QListWidget* viewingArea;
    QList<int> searchList;
    QList<int> excludeList;
    QSize baseThumbnailSize;

    void createLayout();
    void createViewingArea();
    void relaySignals();

    void addFileToViewingArea(const FileTuple& file);
    void addTagsToSelected(QStringList tags);
    bool somethingIsSelected();
    void removeFiles();
    int getIdOfSelected();
    void selectFileWithId(int id);

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
    void openFileAtIndex(QListWidgetItem* item);
    void updateThumbnailScale(int percentage);
};

#endif // FILEBROWSER_H
