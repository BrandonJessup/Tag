#include "buttonpanel.h"

ButtonPanel::ButtonPanel(QWidget *parent) : QWidget(parent)
{
    setSize();
    createLayout();
    createAddImageButton();
    createAddFileButton();
    createAddFolderButton();
    relaySignals();
}

void ButtonPanel::setSize()
{
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void ButtonPanel::createLayout()
{
    layout = new QHBoxLayout;
    this->setLayout(layout);
}

void ButtonPanel::createAddImageButton()
{
    addImageButton = new QPushButton("Add Image");
    layout->addWidget(addImageButton);

    connect(addImageButton, SIGNAL (clicked()), this, SLOT (addImage()));
}

void ButtonPanel::createAddFileButton()
{
    addFileButton = new QPushButton("Add File");
    layout->addWidget(addFileButton);

    connect(addFileButton, SIGNAL (clicked()), this, SLOT (addFile()));
}

void ButtonPanel::createAddFolderButton()
{
    addFolderButton = new QPushButton("Add Folder");
    layout->addWidget(addFolderButton);

    connect(addFolderButton, SIGNAL (clicked()), this, SLOT (addFolder()));
}

void ButtonPanel::relaySignals()
{
    connect(this, SIGNAL (fileDialogClosed(QString)), this, SLOT (updateLastDirectory(QString)));
}

void ButtonPanel::addImage()
{
    Database* database = Database::getInstance();
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), directoryToOpen(), tr("Images (*.png *.jpg)"));

    if (!fileAlreadyInDatabase(path)) {
        QString name = extractNameFromPath(path);
        QString type = "image";
        database->addFile(name, path, type);
        emit filesChanged();
    }
    else {
        Prompt::show("File already exists!");
    }

    emit fileDialogClosed(path);
}

bool ButtonPanel::fileAlreadyInDatabase(QString path)
{
    Database* database = Database::getInstance();
    return database->filePathExists(path);
}

void ButtonPanel::updateLastDirectory(QString pathToFile)
{
    QString pathToDirectory = getParentFolder(pathToFile);
    lastDirectory = pathToDirectory;
}

QString ButtonPanel::directoryToOpen()
{
    if (lastDirectory.isEmpty()) {
        return "/home";
    }
    else {
        return lastDirectory;
    }
}

QString ButtonPanel::getParentFolder(const QString& filePath)
{
    QRegularExpression expression("\\b.*/");
    QRegularExpressionMatch match = expression.match(filePath);
    if (match.hasMatch()) {
        return match.captured(0);
    }
    else {
        return "";
    }
}

QString ButtonPanel::extractNameFromPath(const QString& path)
{
    int lastSlash = path.lastIndexOf('/');
    int stringLength = path.length();
    return path.right(stringLength - lastSlash - 1);
}

void ButtonPanel::addFile()
{
    // TODO
}

void ButtonPanel::addFolder()
{
    // TODO
}
