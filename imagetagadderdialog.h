#ifndef IMAGETAGADDERDIALOG_H
#define IMAGETAGADDERDIALOG_H

#include <QPushButton>
#include <QIcon>
#include <QPixmap>
#include <QDesktopServices>

#include "tagadderdialog.h"

class ImageTagAdderDialog : public TagAdderDialog
{
    Q_OBJECT

public:
    ImageTagAdderDialog(const QString& name, const QString& path);

private:
    QPushButton* thumbnail;
    QLabel* fileName;
    QString filePath;

    void createThumbnailView(const QString& path);
    void createFileNameLabel(const QString& name);
    void relaySignals();

public slots:
    void openImageInDefaultApplication();
};

#endif // IMAGETAGADDERDIALOG_H
