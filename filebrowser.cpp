#include "filebrowser.h"

FileBrowser::FileBrowser(QWidget *parent) : QWidget(parent)
{
    revisionCount = 0;

    createLayout();
    createViewingArea();
    createDefaultIcons();
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
    viewingArea = new QListWidget;
    baseThumbnailSize = QSize(250, 340);

    viewingArea->setResizeMode(QListView::Adjust);
    viewingArea->setViewMode(QListView::IconMode);
    viewingArea->setIconSize(baseThumbnailSize);
    viewingArea->setMovement(QListView::Static);
    viewingArea->setSelectionMode(QAbstractItemView::ExtendedSelection);
    viewingArea->setWordWrap(true);

    viewingArea->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(viewingArea, SIGNAL (customContextMenuRequested(QPoint)), this, SLOT (showContextMenu(QPoint)));

    layout->addWidget(viewingArea);
}

void FileBrowser::createDefaultIcons()
{
    // Icons made by Nysttren.
    defaultImageIcon = QIcon("default icons/image.png");
    defaultVideoIcon = QIcon("default icons/video.png");
    defaultFileIcon = QIcon("default icons/file.png");
    defaultFolderIcon = QIcon("default icons/folder.png");
}

void FileBrowser::relaySignals()
{
    connect(viewingArea, SIGNAL (itemSelectionChanged()), this, SLOT (selectionChangedEmitter()));
    connect(viewingArea, SIGNAL (itemDoubleClicked(QListWidgetItem*)), this, SLOT (openFileAtIndex(QListWidgetItem*)));
    connect(this, SIGNAL (thumbnailReady(const QIcon&, QListWidgetItem*, int)), this, SLOT (applyThumbnail(const QIcon&, QListWidgetItem*, int)));
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

void FileBrowser::openFileAtIndex(QListWidgetItem* item)
{
    QString path = item->data(UserRole::PATH).toString();
    QDesktopServices::openUrl(QUrl("file:///" + path));
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

    QStringList thumbnailPaths;
    QList<QListWidgetItem*> items;
    for (int i = 0; i < viewingArea->count(); ++i) {
        QListWidgetItem* item = viewingArea->item(i);
        QString thumbnailPath = item->data(UserRole::THUMBNAIL).toString();
        if (!thumbnailPath.isEmpty()) {
            items.append(item);
            thumbnailPaths.append(thumbnailPath);
        }
    }
    revisionCount++;
    QtConcurrent::run(this, &FileBrowser::loadThumbnails, thumbnailPaths, items, revisionCount);
}

void FileBrowser::loadThumbnails(QStringList thumbnailPaths, QList<QListWidgetItem*> items, int revision)
{
    int numberOfFiles = thumbnailPaths.size();
    for (int i = 0; i < numberOfFiles; ++i) {
        if (revision == revisionCount) {
            if (items[i] != nullptr) {
                QIcon icon(thumbnailPaths[i]);
                emit thumbnailReady(icon, items[i], revision);
            }
        }
    }
}

void FileBrowser::applyThumbnail(const QIcon& icon, QListWidgetItem* item, int revision)
{
    if (revision == revisionCount) {
        item->setIcon(icon);

        // Refreshes the layout after an item is added to remove
        // unsightly side effects of changing an icon. This is
        // normally not done until mouse over of the viewing area.
        viewingArea->doItemsLayout();
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
    if (type == "image") {
        item->setIcon(defaultImageIcon);
    }
    else if (type == "video") {
        item->setIcon(defaultVideoIcon);
    }
    else if (type == "file") {
        item->setIcon(defaultFileIcon);
    }
    else if (type == "folder") {
        item->setIcon(defaultFolderIcon);
    }

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

    QListWidgetItem* item = viewingArea->selectedItems().first();
    int fileId = item->data(UserRole::ID).toInt();
    QString oldThumbnailPath = item->data(UserRole::THUMBNAIL).toString();

    if (!sourcePath.isEmpty()) {
        deleteThumbnail(oldThumbnailPath);

        QString newThumbnailPath = generateAndStoreThumbnail(sourcePath, fileId);

        Database* database = Database::getInstance();
        database->setThumbnail(newThumbnailPath, fileId);

        reloadContents();
    }
}

QString FileBrowser::generateAndStoreThumbnail(const QString& path, const int& fileId)
{
    QDir dir;
    dir.mkdir("thumbnails");

    QString thumbnailPath = "thumbnails/" + QString::number(fileId) + ".jpg";

    QImage image;
    image.load(path);
    image = image.scaled(500, 680, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    image.save(thumbnailPath);

    return thumbnailPath;
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
    for (QListWidgetItem* item : selectedFiles) {
        for (QString tag : tags) {
            int fileId = item->data(UserRole::ID).toInt();
            database->addTagToFile(tag, fileId);
        }
    }

    reloadContents();
}

void FileBrowser::removeFiles()
{
    QList<QListWidgetItem*> selectedFiles = viewingArea->selectedItems();

    for (int i = 0; i < selectedFiles.size(); ++i) {
        QListWidgetItem* file = viewingArea->takeItem(viewingArea->row(selectedFiles[i]));

        Database* database = Database::getInstance();
        int id = file->data(UserRole::ID).toInt();
        QString thumbnailPath = file->data(UserRole::THUMBNAIL).toString();
        database->removeFile(id);

        // Removing the item from the list widget stop's Qt's management of it
        // and it must then be deleted manually.
        revisionCount++;
        delete file;

        deleteThumbnail(thumbnailPath);
    }
}

void FileBrowser::deleteThumbnail(const QString& path)
{
    QFile file(path);
    if (file.isOpen()) {
        file.remove();
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
    int baseWidth = baseThumbnailSize.width();
    int baseHeight = baseThumbnailSize.height();

    QSize newSize;
    newSize.setWidth(baseWidth * percentage / 100);
    newSize.setHeight(baseHeight * percentage / 100);

    viewingArea->setIconSize(newSize);
}
