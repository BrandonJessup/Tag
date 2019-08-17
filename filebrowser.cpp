#include "filebrowser.h"

FileBrowser::FileBrowser(QWidget *parent) : QWidget(parent)
{
    revisionCount = 0;

    createLayout();
    createViewingArea();
    createDefaultIcons();
    relaySignals();

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
    // Temporary icon used with credit to flaticon.com/authors/smashicons
    defaultImageIcon = QIcon("default icons/image.png");
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
        items.append(item);
        thumbnailPaths.append(item->data(UserRole::PATH).toString());
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

    if (type == "image") {
        QListWidgetItem* item = new QListWidgetItem(defaultImageIcon, name);
//        QListWidgetItem* item = new QListWidgetItem(defaultImageIcon, name);


        FileTuple tuple(id, name, path, type);
        item->setData(UserRole::ID, id);
        item->setData(UserRole::NAME, name);
        item->setData(UserRole::PATH, path);
        item->setData(UserRole::TYPE, type);

        viewingArea->addItem(item);
    }
}

void FileBrowser::showContextMenu(const QPoint& point)
{
    if (somethingIsSelected()) {
        QPoint position = viewingArea->mapToGlobal(point);

        QMenu contextMenu;
        contextMenu.addAction("Tag Selected Files", this, SLOT (tagSelectedDialog()));
        contextMenu.addAction("Remove Selected Files", this, SLOT (fileRemovePrompt()));
        contextMenu.exec(position);
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
    for (QListWidgetItem* item : selectedFiles) {
        for (QString tag : tags) {
            int fileId = item->data(UserRole::ID).toInt();
            database->addTagToFile(tag, fileId);
        }
    }

    reloadContents();
}

bool FileBrowser::somethingIsSelected()
{
    return !viewingArea->selectedItems().isEmpty();
}

void FileBrowser::removeFiles()
{
    QList<QListWidgetItem*> selectedFiles = viewingArea->selectedItems();

    for (int i = 0; i < selectedFiles.size(); ++i) {
        QListWidgetItem* file = viewingArea->takeItem(viewingArea->row(selectedFiles[i]));

        Database* database = Database::getInstance();
        int id = file->data(UserRole::ID).toInt();
        database->removeFile(id);

        // Removing the item from the list widget stop's Qt's management of it
        // and it must then be deleted manually.
        delete file;
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
