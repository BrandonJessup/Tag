#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    checkIntegrityOfFiles();

    createTopLevelLayout();
    createToolBar();
    createLowerLayout();
    createTagPanel();
    createFileBrowser();

    relaySignals();
}

void Window::checkIntegrityOfFiles()
{
    Database* database = Database::getInstance();
    QList<FileTuple> files = database->getAllFiles();

    for (FileTuple file : files) {
        if (!QFileInfo::exists(file.getPath())) {
            QString oldPath = file.getPath();
            QString oldName = file.getName();

            QPushButton* removeButton = new QPushButton("Remove");
            QPushButton* locateButton = new QPushButton("Locate");

            QMessageBox popup;
            popup.setText("The file '" + oldName + "' could not be found at the expected location: '" + oldPath + "'!");
            popup.setInformativeText("Would you like to locate the file, or remove it?");
            popup.addButton(removeButton, QMessageBox::RejectRole);
            popup.addButton(locateButton, QMessageBox::AcceptRole);
            popup.setDefaultButton(locateButton);

            int choice = popup.exec();
            if (choice == QDialog::Accepted) {
                QString searchContitions = "All Files (*)";
                if (file.getType() == "image") {
                    searchContitions = "Image Files (*.png *.jpg)";
                }

                QString newPath = QFileDialog::getOpenFileName(this, "Locate " + oldName, Settings::loadLastUsedDirectory(), searchContitions);

                if (newPath.isNull()) {
                    deleteThumbnail(file.getThumbnail());
                    database->removeFile(file.getId());
                    Prompt::show("The file was removed.");
                }
                else {
                    database->setPath(newPath, file.getId());
                    QString newName = extractNameFromPath(newPath);
                    if (newName != file.getName()) {
                        database->setFileName(newName, file.getId());
                    }
                }
            }
            else if (choice == QDialog::Rejected) {
                deleteThumbnail(file.getThumbnail());
                database->removeFile(file.getId());
            }
        }
    }
}

QString Window::extractNameFromPath(const QString& path)
{
    int lastSlash = path.lastIndexOf('/');
    int stringLength = path.length();
    return path.right(stringLength - lastSlash - 1);
}

void Window::deleteThumbnail(const QString& path)
{
    QFile file(path);
    file.remove();
}

// topLevelLayout contains the button bar at the very top with the
// bottom portion filled by the contents of lowerLayout.
void Window::createTopLevelLayout()
{
    topLevelLayout = new QVBoxLayout;
    this->setLayout(topLevelLayout);
}

void Window::createToolBar()
{
    toolBar = new ToolBar;
    topLevelLayout->addWidget(toolBar);
}

// lowerLayout contains the tagPanel on the left side and the
// fileBrowser on the right.
void Window::createLowerLayout()
{
    lowerLayout = new QHBoxLayout;
    topLevelLayout->addLayout(lowerLayout);
}

void Window::createTagPanel()
{
    tagPanel = new TagPanel;
    lowerLayout->addWidget(tagPanel);
}

void Window::createFileBrowser()
{
    fileBrowser = new FileBrowser;
    lowerLayout->addWidget(fileBrowser);
}

void Window::relaySignals()
{
    connect(toolBar, SIGNAL (filesChanged()), fileBrowser, SLOT (reloadContents()));
    connect(fileBrowser, SIGNAL (selectionChanged(int)), tagPanel, SLOT (selectionChanged(int)));
    connect(fileBrowser, SIGNAL (databaseTagsChanged()), tagPanel, SLOT (updateTagDictionaries()));
    connect(toolBar, SIGNAL (databaseTagsChanged()), tagPanel, SLOT (updateTagDictionaries()));
    connect(tagPanel, SIGNAL (activeSearchTagsChanged(QList<int>, QList<int>)), fileBrowser, SLOT (updateSearchList(QList<int>, QList<int>)));
    connect(tagPanel, SIGNAL (databaseTagsChanged()), fileBrowser, SLOT (reloadContents()));
    connect(toolBar, SIGNAL (thumbnailSliderMoved(int)), fileBrowser, SLOT (updateThumbnailScale(int)));
}
