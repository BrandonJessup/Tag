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
}

void ButtonBar::createAddFileButton()
{
    addFileButton = new QPushButton("Add File");
    layout->addWidget(addFileButton);
}

void ButtonBar::createAddFolderButton()
{
    addFolderButton = new QPushButton("Add Folder");
    layout->addWidget(addFolderButton);
}
