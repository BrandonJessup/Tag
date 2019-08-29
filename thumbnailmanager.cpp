#include "thumbnailmanager.h"

ThumbnailManager::ThumbnailManager(QWidget* mainWidget)
{
    makeThumbnailDirectory();

    this->mainWidget = mainWidget;

    const int DEFAULT_WIDTH = 250;
    const int DEFAULT_HEIGHT = 250;
    defaultSize = QSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    maximumSize = QSize(DEFAULT_WIDTH * 2, DEFAULT_HEIGHT * 2);

    loadStored();
    loadDefault();
}

void ThumbnailManager::makeThumbnailDirectory()
{
    QDir dir;
    dir.mkdir("thumbnails");
}

void ThumbnailManager::loadStored()
{
    Database* database = Database::getInstance();
    QList<FileTuple> files = database->getAllFiles();

    ProgressDialog popup(mainWidget, "Loading thumbnails...", files.size());

    // If file has a thumbnail, cache it.
    for (int i = 0; i < files.size(); ++i) {
        FileTuple file = files[i];
        popup.setValue(i);
        QString thumbnailPath = file.getThumbnail();
        if (!thumbnailPath.isEmpty()) {
            QIcon thumbnail(thumbnailPath);
            cached.insert(file.getId(), thumbnail);
        }
    }

    popup.setValueToMaximum();
}

void ThumbnailManager::loadDefault()
{
    // Icons made by Nysttren.
    defaultImage = QIcon("default icons/image.png");
    defaultVideo = QIcon("default icons/video.png");
    defaultFile = QIcon("default icons/file.png");
    defaultFolder = QIcon("default icons/folder.png");
}

QSize ThumbnailManager::getDefaultSize()
{
    return defaultSize;
}

QIcon ThumbnailManager::getThumbnail(const FileTuple& file)
{
    bool hasThumbnail = !file.getThumbnail().isEmpty();
    if (hasThumbnail) {
        return cached.value(file.getId());
    }
    else {
        QString type = file.getType();
        if (type == "image") {
            return defaultImage;
        }
        else if (type == "video") {
            return defaultVideo;
        }
        else if (type == "folder") {
            return defaultFolder;
        }
        else {
            return defaultFile;
        }
    }
}

void ThumbnailManager::changeThumbnail(const FileTuple& file, const QString& sourcePath)
{
    QString oldPath = file.getThumbnail();
    deleteThumbnail(oldPath, file.getId());

    generateAndSaveThumbnail(sourcePath, file.getId());
}

void ThumbnailManager::deleteThumbnail(const QString& path, const int& fileId)
{
    QFile file(path);
    if (file.exists()) {
        file.remove();
    }

    cached.remove(fileId);
}

void ThumbnailManager::generateAndSaveThumbnail(const QString& sourcePath, const int& fileId)
{
    QString newPath = "thumbnails/" + QString::number(fileId) + ".jpg";

    QImage image;
    image.load(sourcePath);
    image = image.scaled(maximumSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    image.save(newPath);

    cached.insert(fileId, QIcon(QPixmap::fromImage(image)));

    Database* database = Database::getInstance();
    database->setThumbnail(newPath, fileId);
}
