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

#include "userrole.h"
#include "selected.h"
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
    void relaySignals();

    void addFileToViewingArea(const FileTuple& file);
    bool somethingIsSelected();
    void removeFiles();

protected:
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void selectionChanged(int selectedFile);

public slots:
    void selectionChangedEmitter(const QItemSelection& selected);
    void reloadContents();
    void showContextMenu(const QPoint& point);
    void fileRemovePrompt();
};

#endif // FILEBROWSER_H
