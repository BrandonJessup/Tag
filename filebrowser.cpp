#include "filebrowser.h"

FileBrowser::FileBrowser(QWidget *parent) : QWidget(parent)
{
    createLayout();
    createViewingArea();
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

    viewingArea->setResizeMode(QListView::Adjust);
    viewingArea->setViewMode(QListView::IconMode);
    viewingArea->setIconSize(QSize(250, 340));
    viewingArea->setMovement(QListView::Static);
    viewingArea->setWordWrap(true);

    viewingArea->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(viewingArea, SIGNAL (customContextMenuRequested(QPoint)), this, SLOT (showContextMenu(QPoint)));

    layout->addWidget(viewingArea);
}

void FileBrowser::relaySignals()
{
    connect(viewingArea->selectionModel(), SIGNAL (selectionChanged(QItemSelection, QItemSelection)), this, SLOT (selectionChangedEmitter(QItemSelection)));
}

void FileBrowser::selectionChangedEmitter(const QItemSelection& selected)
{
    int selectedFile = Selected::NONE;

    // Selections are returned as a list even though we only allow
    // for one file to be selected at a time.
    QModelIndexList selectedFileList = selected.indexes();
    if (!selectedFileList.isEmpty()) {
        selectedFile = selectedFileList.first().data(UserRole::ID).toInt();
    }

    emit selectionChanged(selectedFile);
}

void FileBrowser::reloadContents()
{
    viewingArea->clear();

    Database* database = Database::getInstance();
    QList<FileTuple> files;
    if (searchList.isEmpty()) {
        files = database->getAllFiles();
    }
    else {
        files = database->getFilesThatMatchTags(searchList);
    }

    for (FileTuple file : files) {
        addFileToViewingArea(file);
    }
}

void FileBrowser::addFileToViewingArea(const FileTuple& file)
{
    int id = file.getId();
    QString name = file.getName();
    QString path = file.getPath();
    QString type = file.getType();

    if (type == "image") {
        QListWidgetItem* item = new QListWidgetItem(QIcon(path), name);

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
        contextMenu.addAction("Remove", this, SLOT (fileRemovePrompt()));
        contextMenu.exec(position);
    }
}

void FileBrowser::fileRemovePrompt()
{
    QPushButton* removeButton = new QPushButton("Remove");

    QMessageBox prompt;
    prompt.setText("Remove selected file?");
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

bool FileBrowser::somethingIsSelected()
{
    return !viewingArea->selectedItems().isEmpty();
}

void FileBrowser::removeFiles()
{
    for (int i = 0; i < viewingArea->selectedItems().size(); ++i) {
        QListWidgetItem* file = viewingArea->takeItem(viewingArea->currentRow());

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

void FileBrowser::updateSearchList(QList<int> tagIds)
{
    searchList = tagIds;
    reloadContents();
}
