#ifndef THUMBNAILMANAGER_H
#define THUMBNAILMANAGER_H

#include <QWidget>
#include <QSize>
#include <QMap>
#include <QIcon>
#include <QList>
#include <QDir>

#include "database.h"
#include "progressdialog.h"
#include "filetuple.h"

class ThumbnailManager
{
public:
    ThumbnailManager(QWidget* mainWidget);

    QSize getDefaultSize();
    QIcon getThumbnail(const FileTuple& file);
    void changeThumbnail(const FileTuple& file, const QString& sourcePath);
    void deleteThumbnail(const QString& path, const int& fileId);
    void generateAndSaveThumbnail(const QString& sourcePath, const int& fileId);

private:
    QWidget* mainWidget;
    QSize defaultSize;
    QSize maximumSize;
    QMap<int, QIcon> cached;
    QIcon defaultImage;
    QIcon defaultVideo;
    QIcon defaultFile;
    QIcon defaultFolder;

    void makeThumbnailDirectory();
    void loadStored();
    void loadDefault();
};

#endif // THUMBNAILMANAGER_H
