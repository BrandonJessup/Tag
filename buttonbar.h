#ifndef BUTTONBAR_H
#define BUTTONBAR_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>

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

signals:

public slots:
};

#endif // BUTTONBAR_H
