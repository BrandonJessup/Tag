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
    QString directoryToOpen = Settings::loadLastUsedDirectory();
    QStringList paths = QFileDialog::getOpenFileNames(this, tr("Open File"), directoryToOpen, tr("Images (*.png *.jpg)"));

    if (paths.size() == 1) {
        QString path = paths.first();
        if (!fileAlreadyInDatabase(path)) {
            tagAndAddToDatabase(path);
            emit filesChanged();
        }
        else {
            Prompt::show("File already exists!");
        }
    }
    else {
        int existingCount = 0;
        for (QString path : paths) {
            if (!fileAlreadyInDatabase(path)) {
                tagAndAddToDatabase(path);
            }
            else {
                ++existingCount;
            }
        }
        if (existingCount > 0) {
            Prompt::show(QString::number(existingCount) + " files already exist!");
        }
        if (!paths.isEmpty()) {
            emit filesChanged();
            emit databaseTagsChanged();
        }
    }

    if (!paths.isEmpty()) {
        emit fileDialogClosed(paths.first());
    }
}

void ButtonPanel::tagAndAddToDatabase(const QString& path)
{
    Database* database = Database::getInstance();

    QString name = extractNameFromPath(path);
    QString type = "image";

    int fileId = database->addFile(name, path, type);

    ImageTagAdderDialog popup(name, path);
    int result = popup.exec();

    if (result == QDialog::Accepted) {
        addTagsToFile(fileId, popup.getTagsToAdd());
    }
}

void ButtonPanel::addTagsToFile(int fileId, QStringList tags)
{
    Database* database = Database::getInstance();

    for (QString tag : tags) {
        database->addTagToFile(tag, fileId);
    }
}

bool ButtonPanel::fileAlreadyInDatabase(QString path)
{
    Database* database = Database::getInstance();
    return database->filePathExists(path);
}

void ButtonPanel::updateLastDirectory(QString pathToFile)
{
    QString pathToDirectory = getParentFolder(pathToFile);
    Settings::saveLastUsedDirectory(pathToDirectory);
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
