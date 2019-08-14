#include "imagetagadderdialog.h"

ImageTagAdderDialog::ImageTagAdderDialog(const QString& name, const QString& path) : TagAdderDialog()
{
    filePath = path;
    createFileNameLabel(name);
    createThumbnailView(path);
    setTagListSize(QSize(400, 120));
    setCancelButtonText("Don't Tag");
    updateAndLockSize();
    relaySignals();
}

void ImageTagAdderDialog::createFileNameLabel(const QString& name)
{
    fileName = new QLabel(name);
    insertWidgetInLayout(0, fileName);
}

void ImageTagAdderDialog::createThumbnailView(const QString& path)
{
    QPixmap pixmap(path);
    QSize sourceSize = pixmap.size();

    thumbnail = new QPushButton;
    thumbnail->setFlat(true);
    thumbnail->setIcon(QIcon(pixmap));
    thumbnail->setFixedWidth(400);
    thumbnail->setAutoDefault(false);

    int width = 400;
    int heightToScale = sourceSize.height() * width / sourceSize.width();
    thumbnail->setIconSize(QSize(width, heightToScale));
    insertWidgetInLayout(1, thumbnail);
}

void ImageTagAdderDialog::relaySignals()
{
    connect(thumbnail, SIGNAL (clicked()), this, SLOT (openImageInDefaultApplication()));
}

void ImageTagAdderDialog::openImageInDefaultApplication()
{
    QDesktopServices::openUrl(QUrl("file:///" + filePath));
}
