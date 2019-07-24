#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QWidget>
#include <QListWidget>
#include <QStackedLayout>

#include "database.h"

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

signals:

public slots:
    void reloadContents();
};

#endif // FILEBROWSER_H
