#ifndef MISSINGFILEDIALOG_H
#define MISSINGFILEDIALOG_H

#include <QDialog>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "filetuple.h"

class MissingFileDialog : public QDialog
{
public:
    MissingFileDialog(const FileTuple& file);

private:
    QBoxLayout* layout;
    QBoxLayout* buttonLayout;
    QLabel* message;
    QPushButton* removeButton;
    QPushButton* locateButton;

    void createLayout();
    void createThumbnail(const FileTuple& file);
    void createMessage(const FileTuple& file);
    void createButtonLayout();
    void createButtons();
};

#endif // MISSINGFILEDIALOG_H
