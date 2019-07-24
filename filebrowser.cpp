#include "filebrowser.h"

FileBrowser::FileBrowser(QWidget *parent) : QWidget(parent)
{
    createLayout();
    createViewingArea();
}

void FileBrowser::createLayout()
{
    layout = new QStackedLayout;
    this->setLayout(layout);
}

void FileBrowser::createViewingArea()
{
    viewingArea = new QListWidget;
    layout->addWidget(viewingArea);
}

void FileBrowser::reloadContents()
{
    // TODO: Pull file data from database to populate viewing area.
}
