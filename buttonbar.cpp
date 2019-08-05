#include "buttonbar.h"

ButtonBar::ButtonBar(QWidget *parent) : QWidget(parent)
{
    setSize();
    createLayout();
    createAddImageButton();
    createAddFileButton();
    createAddFolderButton();
}

void ButtonBar::setSize()
{
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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
    Database* database = Database::getInstance();
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.jpg)"));
    QString name = extractNameFromPath(path);
    QString type = "image";
    database->addFile(name, path, type);
    emit filesChanged();
}

QString ButtonBar::extractNameFromPath(const QString& path)
{
    int lastSlash = path.lastIndexOf('/');
    int stringLength = path.length();
    return path.right(stringLength - lastSlash - 1);
}

void ButtonBar::addFile()
{
    // TODO
}

void ButtonBar::addFolder()
{
    // TODO
}
