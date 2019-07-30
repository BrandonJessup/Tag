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
        viewingArea->addItem(new QListWidgetItem(QIcon(path), name));
    }
}

void FileBrowser::showContextMenu(const QPoint& point)
{
    QPoint position = viewingArea->mapToGlobal(point);

    QMenu contextMenu;
    contextMenu.addAction("Remove", this, SLOT (removeFiles()));
    contextMenu.exec(position);
}

void FileBrowser::removeFiles()
{
    for (int i = 0; i < viewingArea->selectedItems().size(); ++i) {
        QListWidgetItem* file = viewingArea->takeItem(viewingArea->currentRow());

        // TODO: Remove file from database.

        // Removing the item from the list widget stop's Qt's management of it
        // and it must then be deleted manually.
        delete file;
    }
}
