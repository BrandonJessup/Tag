#include "filebrowser.h"

FileBrowser::FileBrowser(QWidget *parent) : QWidget(parent)
{
    createLayout();
    createViewingArea();

    reloadContents();
}

void FileBrowser::createLayout()
{
    layout = new QStackedLayout;
    this->setLayout(layout);
}

void FileBrowser::createViewingArea()
{
    viewingArea = new QListWidget;
    viewingArea->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(viewingArea, SIGNAL (customContextMenuRequested(QPoint)), this, SLOT (showContextMenu(QPoint)));
    layout->addWidget(viewingArea);
}

void FileBrowser::reloadContents()
{
    Database* database = Database::getInstance();
    QList<FileTuple> files = database->getAllFiles();

    for (FileTuple file : files) {
        addFileToViewingArea(file);
    }
}

void FileBrowser::addFileToViewingArea(const FileTuple& file)
{
    int id = file.getId();
    QString name = file.getName();
    QString path = file.getPath();
    QString type = file.getType();

    if (type == "image") {
        QListWidgetItem* item = new QListWidgetItem(QIcon(path), name);

        FileTuple tuple(id, name, path, type);
        item->setData(UserRole::ID, id);
        item->setData(UserRole::NAME, name);
        item->setData(UserRole::PATH, path);
        item->setData(UserRole::TYPE, type);

        viewingArea->addItem(item);
    }
}

void FileBrowser::showContextMenu(const QPoint& point)
{
    if (somethingIsSelected()) {
        QPoint position = viewingArea->mapToGlobal(point);

        QMenu contextMenu;
        contextMenu.addAction("Remove", this, SLOT (removeFiles()));
        contextMenu.exec(position);
    }
}

bool FileBrowser::somethingIsSelected()
{
    return viewingArea->currentRow() != -1;
}

void FileBrowser::removeFiles()
{
    for (int i = 0; i < viewingArea->selectedItems().size(); ++i) {
        QListWidgetItem* file = viewingArea->takeItem(viewingArea->currentRow());

        Database* database = Database::getInstance();
        int id = file->data(UserRole::ID).toInt();
        database->removeFile(id);

        // Removing the item from the list widget stop's Qt's management of it
        // and it must then be deleted manually.
        delete file;
    }
}
