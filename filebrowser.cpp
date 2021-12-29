#include "filebrowser.h"

FileBrowser::FileBrowser(ThumbnailManager* thumbnailManager, QWidget *parent) : QWidget(parent)
{
    this->thumbnailManager = thumbnailManager;
    revisionCount = 0;

    createLayout();
    createViewingArea();
    relaySignals();

    updateThumbnailScale(Settings::loadThumbnailSliderPosition());
    reloadContents();
}

void FileBrowser::createLayout()
{
    layout = new QStackedLayout;
    this->setLayout(layout);
}

void FileBrowser::createViewingArea()
{
    QSize defaultThumbnailSize = thumbnailManager->getDefaultSize();

    viewingArea = new QListWidget;
    viewingArea->setResizeMode(QListView::Adjust);
    viewingArea->setViewMode(QListView::IconMode);
    viewingArea->setGridSize(QSize(defaultThumbnailSize.width() + 2, defaultThumbnailSize.height() + 20));
    viewingArea->setIconSize(defaultThumbnailSize);
    viewingArea->setMovement(QListView::Static);
    viewingArea->setSelectionMode(QAbstractItemView::ExtendedSelection);
    viewingArea->setWordWrap(true);
    viewingArea->verticalScrollBar()->setSingleStep(40);

    viewingArea->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(viewingArea, SIGNAL (customContextMenuRequested(QPoint)), this, SLOT (showContextMenu(QPoint)));

    layout->addWidget(viewingArea);
}

void FileBrowser::relaySignals()
{
    connect(viewingArea, SIGNAL (itemSelectionChanged()), this, SLOT (selectionChangedEmitter()));
    connect(viewingArea, SIGNAL (itemDoubleClicked(QListWidgetItem*)), this, SLOT (openFile(QListWidgetItem*)));
}

void FileBrowser::selectionChangedEmitter()
{
    // The SelectedPanel is only enabled if only one file is
    // selected, so we only emit a valid fileId if there is a single
    // selection.
    int selectedFile;
    QList<QListWidgetItem*> selectedFiles = viewingArea->selectedItems();
    if (selectedFiles.size() == 1) {
        selectedFile = selectedFiles[0]->data(UserRole::ID).toInt();
    }
    else {
        selectedFile = Selected::NONE;
    }
    emit selectionChanged(selectedFile);
}

void FileBrowser::openFile(QListWidgetItem* item)
{
    QString path = item->data(UserRole::PATH).toString();
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void FileBrowser::reloadContents()
{
    int selectedFileId = getIdOfSelected();

    viewingArea->clear();

    Database* database = Database::getInstance();
    QList<FileTuple> files;
    if (searchList.isEmpty() && excludeList.isEmpty()) {
        files = database->getAllFiles();
    }
    else {
        files = database->getFilesThatMatchTags(searchList, excludeList);
    }

    for (FileTuple file : files) {
        addFileToViewingArea(file);
    }

    if (selectedFileId != Selected::NONE) {
        selectFileWithId(selectedFileId);
    }
}

int FileBrowser::getIdOfSelected()
{
    QList<QListWidgetItem*> items = viewingArea->selectedItems();
    if (!items.isEmpty()) {
        return items.first()->data(UserRole::ID).toInt();
    }
    else {
        return Selected::NONE;
    }
}

void FileBrowser::selectFileWithId(int id)
{
    for (int i = 0; i < viewingArea->count(); ++i) {
        if (viewingArea->item(i)->data(UserRole::ID).toInt() == id) {
            viewingArea->setCurrentItem(viewingArea->item(i));
            return;
        }
    }
}

void FileBrowser::addFileToViewingArea(const FileTuple& file)
{
    int id = file.getId();
    QString name = file.getName();
    QString path = file.getPath();
    QString type = file.getType();
    QString thumbnail = file.getThumbnail();

    QListWidgetItem* item = new QListWidgetItem;
    item->setText(name);

    item->setIcon(thumbnailManager->getThumbnail(file));

    item->setData(UserRole::ID, id);
    item->setData(UserRole::NAME, name);
    item->setData(UserRole::PATH, path);
    item->setData(UserRole::TYPE, type);
    item->setData(UserRole::THUMBNAIL, thumbnail);

    viewingArea->addItem(item);
}

void FileBrowser::showContextMenu(const QPoint& point)
{
    int numberOfSelectedItems = viewingArea->selectedItems().size();
    if (numberOfSelectedItems == 1) {
        QPoint position = viewingArea->mapToGlobal(point);

        QMenu contextMenu;
        contextMenu.addAction("Show in Explorer", this, SLOT (showSelectedInExplorer()));
        contextMenu.addAction("Tag Selected File", this, SLOT (tagSelectedDialog()));

        QString selectedItemType = viewingArea->selectedItems().first()->data(UserRole::TYPE).toString();
        if (selectedItemType != "image") {
            contextMenu.addAction("Change Thumbnail", this, SLOT (changeThumbnailOfSelectedFile()));
        }

        contextMenu.addAction("Remove Selected File", this, SLOT (fileRemovePrompt()));
        contextMenu.exec(position);
    }
    else if (numberOfSelectedItems > 1) {
        QPoint position = viewingArea->mapToGlobal(point);

        QMenu contextMenu;
        contextMenu.addAction("Tag Selected Files", this, SLOT (tagSelectedDialog()));
        contextMenu.addAction("Remove Selected Files", this, SLOT (fileRemovePrompt()));
        contextMenu.exec(position);
    }
}

void FileBrowser::changeThumbnailOfSelectedFile()
{    
    QString directoryToOpen = Settings::loadLastUsedDirectory();
    QString filter = "Images (*.png *.jpg)";
    QString sourcePath = QFileDialog::getOpenFileName(this, tr("Select New Thumbnail"), directoryToOpen, filter);

    if (!sourcePath.isEmpty()) {
        updateLastDirectory(sourcePath);

        QListWidgetItem* item = viewingArea->selectedItems().first();
        FileTuple file;
        file.setId(item->data(UserRole::ID).toInt());
        file.setName(item->data(UserRole::NAME).toString());
        file.setPath(item->data(UserRole::PATH).toString());
        file.setType(item->data(UserRole::TYPE).toString());
        file.setThumbnail(item->data(UserRole::THUMBNAIL).toString());

        thumbnailManager->changeThumbnail(file, sourcePath);

        reloadContents();
    }
}

void FileBrowser::showSelectedInExplorer()
{
    QListWidgetItem* item = viewingArea->selectedItems().first();
    QString path = item->data(UserRole::PATH).toString();

    QProcess::startDetached("explorer.exe", {"/select,", QDir::toNativeSeparators(path)});
}

void FileBrowser::updateLastDirectory(QString pathToFile)
{
    QString pathToDirectory = getParentFolder(pathToFile);
    Settings::saveLastUsedDirectory(pathToDirectory);
}

QString FileBrowser::getParentFolder(const QString& filePath)
{
    QRegularExpression expression("\\b.*/");
    QRegularExpressionMatch match = expression.match(filePath);
    if (match.hasMatch()) {
        return match.captured(0);
    }
    else {
        return "";
    }
}

void FileBrowser::fileRemovePrompt()
{
    QPushButton* removeButton = new QPushButton("Remove");

    QMessageBox prompt;
    prompt.setText("Remove selected files?");
    prompt.setStandardButtons(QMessageBox::Cancel);
    prompt.addButton(removeButton, QMessageBox::AcceptRole);
    prompt.setDefaultButton(removeButton);

    int chosen = prompt.exec();
    switch (chosen) {
    case QMessageBox::AcceptRole:
        removeFiles();
        break;
    default:
        // Do nothing.
        break;
    }
}

void FileBrowser::tagSelectedDialog()
{
    TagAdderDialog popup;
    int result = popup.exec();

    if (result == QDialog::Accepted) {
        addTagsToSelected(popup.getTagsToAdd());
        emit databaseTagsChanged();
    }
}

void FileBrowser::addTagsToSelected(QStringList tags)
{
    Database* database = Database::getInstance();

    QList<QListWidgetItem*> selectedFiles = viewingArea->selectedItems();
    if (selectedFiles.size() == 1) {
        for (QString tag : tags) {
            int fileId = selectedFiles.first()->data(UserRole::ID).toInt();
            database->addTagToFile(tag, fileId);
        }
    }
    else {
        ProgressDialog popup(this, "Applying tags...", selectedFiles.size());

        for (int i = 0; i < selectedFiles.size(); ++i) {
            popup.setValue(i);
            for (QString tag : tags) {
                int fileId = selectedFiles[i]->data(UserRole::ID).toInt();
                database->addTagToFile(tag, fileId);
            }
        }

        popup.setValueToMaximum();
    }

    reloadContents();
}

void FileBrowser::removeFiles()
{
    QList<QListWidgetItem*> selectedFiles = viewingArea->selectedItems();

    if (selectedFiles.size() == 1) {
        QListWidgetItem* file = viewingArea->takeItem(viewingArea->row(selectedFiles.first()));

        Database* database = Database::getInstance();
        int id = file->data(UserRole::ID).toInt();
        QString thumbnailPath = file->data(UserRole::THUMBNAIL).toString();
        database->removeFile(id);

        // Removing the item from the list widget stop's Qt's management of it
        // and it must then be deleted manually.
        revisionCount++;
        delete file;

        thumbnailManager->deleteThumbnail(thumbnailPath, id);
    }
    else {
        ProgressDialog popup(this, "Removing files...", selectedFiles.size());

        for (int i = 0; i < selectedFiles.size(); ++i) {
            popup.setValue(i);

            QListWidgetItem* file = viewingArea->takeItem(viewingArea->row(selectedFiles[i]));

            Database* database = Database::getInstance();
            int id = file->data(UserRole::ID).toInt();
            QString thumbnailPath = file->data(UserRole::THUMBNAIL).toString();
            database->removeFile(id);

            // Removing the item from the list widget stop's Qt's management of it
            // and it must then be deleted manually.
            revisionCount++;
            delete file;

            thumbnailManager->deleteThumbnail(thumbnailPath, id);
        }

        popup.setValueToMaximum();
    }
}

void FileBrowser::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Delete:
        fileRemovePrompt();
        break;
    default:
        // Do nothing.
        break;
    }
}

void FileBrowser::updateSearchList(QList<int> tagIds, QList<int> excludeTagIds)
{
    searchList = tagIds;
    excludeList = excludeTagIds;
    reloadContents();
}

void FileBrowser::updateThumbnailScale(int percentage)
{
    QSize defaultThumbnailSize = thumbnailManager->getDefaultSize();

    QSize newSize;
    newSize.setWidth(defaultThumbnailSize.width() * percentage / 100);
    newSize.setHeight(defaultThumbnailSize.height() * percentage / 100);

    viewingArea->setIconSize(newSize);
    viewingArea->setGridSize(QSize(newSize.width() + 2, newSize.height() + 20));
}

void FileBrowser::reloadIfTagAddedImpactsSearch(int tagId)
{
    if (excludeList.contains(tagId)) {
        reloadContents();
    }
}

void FileBrowser::reloadIfTagRemovedImpactsSearch(int tagId)
{
    if (searchList.contains(tagId)) {
        reloadContents();
    }
}

void FileBrowser::showNewestItem()
{
    searchList.clear();
    excludeList.clear();
    reloadContents();

    viewingArea->setCurrentRow(viewingArea->count()-1);
    viewingArea->scrollTo(viewingArea->currentIndex());
    viewingArea->setFocus();
}
