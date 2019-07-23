#ifndef BUTTONBAR_H
#define BUTTONBAR_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QFileDialog>

#include "database.h"

class ButtonBar : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonBar(QWidget *parent = nullptr);

private:
    QBoxLayout* layout;
    QPushButton* addImageButton;
    QPushButton* addFileButton;
    QPushButton* addFolderButton;

    void createLayout();
    void createAddImageButton();
    void createAddFileButton();
    void createAddFolderButton();

    QString extractNameFromPath(const QString& path);

signals:
    void filesChanged();

public slots:
    void addImage();
    void addFile();
    void addFolder();
};

#endif // BUTTONBAR_H
