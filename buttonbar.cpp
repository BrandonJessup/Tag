#include "buttonbar.h"

ButtonBar::ButtonBar(QWidget *parent) : QWidget(parent)
{
    createLayout();
    createAddImageButton();
    createAddFileButton();
    createAddFolderButton();
}

void ButtonBar::createLayout()
{
    layout = new QHBoxLayout;
    this->setLayout(layout);
}

void ButtonBar::createAddImageButton()
{
    addImageButton = new QPushButton("Add Image");
    layout->addWidget(addImageButton);

    connect(addImageButton, SIGNAL (clicked()), this, SLOT (addImage()));
}

void ButtonBar::createAddFileButton()
{
    addFileButton = new QPushButton("Add File");
    layout->addWidget(addFileButton);

    connect(addFileButton, SIGNAL (clicked()), this, SLOT (addFile()));
}

void ButtonBar::createAddFolderButton()
{
    addFolderButton = new QPushButton("Add Folder");
    layout->addWidget(addFolderButton);

    connect(addFolderButton, SIGNAL (clicked()), this, SLOT (addFolder()));
}

void ButtonBar::addImage()
{
    // TODO
}

void ButtonBar::addFile()
{
    // TODO
}

void ButtonBar::addFolder()
{
    // TODO
}
