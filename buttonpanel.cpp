#include "buttonpanel.h"

ButtonPanel::ButtonPanel(ThumbnailManager* thumbnailManager, QWidget *parent) : QWidget(parent)
{
    this->thumbnailManager = thumbnailManager;

    setSize();
    createLayout();
    createAddImageButton();
    createAddVideoButton();
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

void ButtonPanel::createAddVideoButton()
{
    addVideoButton = new QPushButton("Add Video");
    layout->addWidget(addVideoButton);

    connect(addVideoButton, SIGNAL (clicked()), this, SLOT (addVideo()));
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
    QString filter = "Images (*.png *.jpg)";
    QStringList paths = QFileDialog::getOpenFileNames(this, tr("Add Image(s)"), directoryToOpen, filter);

    if (paths.size() == 1) {
        QString path = paths.first();
        if (!fileAlreadyInDatabase(path)) {
            tagAndAddToDatabase(path, "image");
            emit filesChanged();
        }
        else {
            Prompt::show("File already exists!");
        }
    }
    else {
        if (!paths.isEmpty()) {
            // Prompt user for if they want to tag all the selected files
            // now, or if they wish to do that later.
            QPushButton* laterButton = new QPushButton("Later");
            QPushButton* nowButton = new QPushButton("Now");

            QMessageBox prompt;
            prompt.setText("Tag files now, or later?");
            prompt.addButton(nowButton, QMessageBox::AcceptRole);
            prompt.addButton(laterButton, QMessageBox::RejectRole);
            prompt.setDefaultButton(laterButton);

            int chosen = prompt.exec();
            int duplicateFiles = 0;
            switch (chosen) {
            case QMessageBox::AcceptRole:
                duplicateFiles = addNewImages(paths);
                break;
            case QMessageBox::RejectRole:
                duplicateFiles = addNewImagesWithoutTagging(paths);
                break;
            }

            emit filesChanged();
            emit databaseTagsChanged();

            if (duplicateFiles > 0) {
                Prompt::show(QString::number(duplicateFiles) + " files already exist!");
            }
        }
    }

    if (!paths.isEmpty()) {
        emit fileDialogClosed(paths.first());
    }
}

int ButtonPanel::addNewImages(QStringList paths)
{
    int existingCount = 0;
    for (QString path : paths) {
        if (!fileAlreadyInDatabase(path)) {
            tagAndAddToDatabase(path, "image");
        }
        else {
            ++existingCount;
        }
    }

    return existingCount;
}

int ButtonPanel::addNewImagesWithoutTagging(QStringList paths)
{
    ProgressDialog popup(this, "Generating thumbnails...", paths.size());

    int existingCount = 0;
    for (int i = 0; i < paths.size(); ++i) {
        popup.setValue(i);
        if (!fileAlreadyInDatabase(paths[i])) {
            addToDatabase(paths[i], "image");
        }
        else {
            ++existingCount;
        }
    }

    popup.setValueToMaximum();

    return existingCount;
}

void ButtonPanel::addToDatabase(const QString& path, const QString& type)
{
    Database* database = Database::getInstance();

    QString name = extractNameFromPath(path);

    int id = database->addFile(name, path, type);
    if (type == "image") {
        thumbnailManager->generateAndSaveThumbnail(path, id);
    }
}

void ButtonPanel::tagAndAddToDatabase(const QString& path, const QString& type)
{
    Database* database = Database::getInstance();

    QString name = extractNameFromPath(path);

    int fileId = database->addFile(name, path, type);

    if (type == "image") {
        thumbnailManager->generateAndSaveThumbnail(path, fileId);

        ImageTagAdderDialog popup(name, path);
        int result = popup.exec();

        if (result == QDialog::Accepted) {
            addTagsToFile(fileId, popup.getTagsToAdd());
        }
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

void ButtonPanel::addVideo()
{
    QString directoryToOpen = Settings::loadLastUsedDirectory();
    QString filter = "Videos (*.mp4 *.mkv *.avi *.webm *.m4v)";
    QStringList paths = QFileDialog::getOpenFileNames(this, tr("Add Video(s)"), directoryToOpen, filter);

    if (paths.size() == 1) {
        QString path = paths.first();
        if (!fileAlreadyInDatabase(path)) {
            addToDatabase(path, "video");
            emit filesChanged();
        }
        else {
            Prompt::show("File already exists!");
        }
    }
    else {
        if (!paths.isEmpty()) {
            int duplicateFiles = 0;
            for (int i = 0; i < paths.size(); ++i) {
                if (!fileAlreadyInDatabase(paths[i])) {
                    addToDatabase(paths[i], "video");
                }
                else {
                    ++duplicateFiles;
                }
            }

            emit filesChanged();
            emit databaseTagsChanged();

            if (duplicateFiles > 0) {
                Prompt::show(QString::number(duplicateFiles) + " files already exist!");
            }
        }
    }

    if (!paths.isEmpty()) {
        emit fileDialogClosed(paths.first());
    }
}



void ButtonPanel::addFile()
{
    QString directoryToOpen = Settings::loadLastUsedDirectory();
    QString filter = "All Files (*)";
    QStringList paths = QFileDialog::getOpenFileNames(this, tr("Add File(s)"), directoryToOpen, filter);

    if (paths.size() == 1) {
        QString path = paths.first();
        if (!fileAlreadyInDatabase(path)) {
            addToDatabase(path, "file");
            emit filesChanged();
        }
        else {
            Prompt::show("File already exists!");
        }
    }
    else {
        if (!paths.isEmpty()) {
            int duplicateFiles = 0;
            for (int i = 0; i < paths.size(); ++i) {
                if (!fileAlreadyInDatabase(paths[i])) {
                    addToDatabase(paths[i], "file");
                }
                else {
                    ++duplicateFiles;
                }
            }

            emit filesChanged();
            emit databaseTagsChanged();

            if (duplicateFiles > 0) {
                Prompt::show(QString::number(duplicateFiles) + " files already exist!");
            }
        }
    }

    if (!paths.isEmpty()) {
        emit fileDialogClosed(paths.first());
    }
}

void ButtonPanel::addFolder()
{
    QString directoryToOpen = Settings::loadLastUsedDirectory();
    QString path = QFileDialog::getExistingDirectory(this, tr("Add Folder"), directoryToOpen, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!path.isEmpty()) {
        if (!fileAlreadyInDatabase(path)) {
            addToDatabase(path, "folder");
            emit filesChanged();
        }
        else {
            Prompt::show("File already exists!");
        }

        emit fileDialogClosed(path);
    }
}
