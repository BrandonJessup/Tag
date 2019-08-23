#include "missingfiledialog.h"

MissingFileDialog::MissingFileDialog(const FileTuple& file)
{
    createLayout();
    createThumbnail(file);
    createMessage(file);
    createButtonLayout();
    createButtons();
}

void MissingFileDialog::createLayout()
{
    layout = new QVBoxLayout;
    this->setLayout(layout);
}

void MissingFileDialog::createThumbnail(const FileTuple& file)
{
    if (!file.getThumbnail().isEmpty()) {
        QLabel* thumbnail = new QLabel;
        thumbnail->setPixmap(QPixmap(file.getThumbnail()));
        layout->addWidget(thumbnail);
    }
}

void MissingFileDialog::createMessage(const FileTuple& file)
{
    message = new QLabel;
    if (!file.getThumbnail().isEmpty()) {
        message->setText("The file '" + file.getName() + "' could not be found at the expected location: '" + file.getPath() + "'!\n\nWould you like to locate the file, or remove it?");
    }
    else {
        message->setText("The file with the above thumbnail could not be found at the expected location: '" + file.getPath() + "'!\n\nWould you like to locate the file, or remove it?");
    }
    message->setWordWrap(true);
    layout->addWidget(message);
}

void MissingFileDialog::createButtonLayout()
{
    buttonLayout = new QHBoxLayout;
    layout->addLayout(buttonLayout);
}

void MissingFileDialog::createButtons()
{
    removeButton = new QPushButton("Remove");
    buttonLayout->addWidget(removeButton);
    connect(removeButton, SIGNAL (clicked()), this, SLOT (reject()));

    buttonLayout->addStretch();

    locateButton = new QPushButton("Locate");
    buttonLayout->addWidget(locateButton);
    connect(locateButton, SIGNAL (clicked()), this, SLOT (accept()));
}
