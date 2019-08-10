#ifndef ButtonPanel_H
#define ButtonPanel_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QFileDialog>

#include "database.h"

class ButtonPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonPanel(QWidget *parent = nullptr);

private:
    QBoxLayout* layout;
    QPushButton* addImageButton;
    QPushButton* addFileButton;
    QPushButton* addFolderButton;

    void setSize();
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

#endif // ButtonPanel_H
