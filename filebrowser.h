#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedLayout>
#include <QList>
#include <QMenu>

#include "database.h"
#include "filetuple.h"

class FileBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit FileBrowser(QWidget *parent = nullptr);

private:
    QStackedLayout* layout;
    QListWidget* viewingArea;

    void createLayout();
    void createViewingArea();

    void addFileToViewingArea(const FileTuple& file);

    bool somethingIsSelected();

signals:

public slots:
    void reloadContents();
    void showContextMenu(const QPoint& point);
    void removeFiles();
};

#endif // FILEBROWSER_H
