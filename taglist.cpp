#include "taglist.h"

TagList::TagList(QSize size, QWidget *parent) : QWidget(parent)
{
    if (size.isValid()) {
        this->setFixedSize(size);
    }

    createLayout();
    createStyleSheets();
    createViewingArea();
    relaySignals();
}

void TagList::createLayout()
{
    layout = new QStackedLayout;
    this->setLayout(layout);
}

void TagList::createStyleSheets()
{
    styleSheetGreen = "background-color: #A9DFBF;"
                      "padding: 4px 2px 4px 3px;"
                      "border-radius: 3px;";
    styleSheetRed = "background-color: #F5B7B1;"
                    "padding: 4px 2px 4px 3px;"
                    "border-radius: 3px;";
}

void TagList::createViewingArea()
{
    viewingArea = new QListWidget;

    viewingArea->setContextMenuPolicy(Qt::CustomContextMenu);
    viewingArea->setViewMode(QListView::IconMode);
    viewingArea->setMovement(QListView::Static);
    viewingArea->setResizeMode(QListView::Adjust);
    viewingArea->setSpacing(4);
    viewingArea->setFocusPolicy(Qt::NoFocus);
    connect(viewingArea, SIGNAL (customContextMenuRequested(QPoint)), this, SLOT (showContextMenu(QPoint)));

    layout->addWidget(viewingArea);
}

void TagList::relaySignals()
{
    connect(viewingArea, SIGNAL (itemClicked(QListWidgetItem*)), this, SLOT (tagClickedEmitter(QListWidgetItem*)));
}

void TagList::tagClickedEmitter(QListWidgetItem* item)
{
    int tagId = item->data(UserRole::ID).toInt();
    QString tagName = item->data(UserRole::NAME).toString();

    emit tagClicked(tagId);
    emit tagClicked(tagName);
}

void TagList::clear()
{
    viewingArea->clear();
}

void TagList::addTag(const TagTuple& tag)
{
    int id = tag.getId();
    QString name = tag.getName();

    QListWidgetItem* item = new QListWidgetItem;

    item->setData(UserRole::ID, id);
    item->setData(UserRole::NAME, name);

    QLabel* label = new QLabel(name);

    switch (tag.getColor()) {
    case TagColor::GREEN:
        label->setStyleSheet(styleSheetGreen);
        break;
    case TagColor::RED:
        label->setStyleSheet(styleSheetRed);
        break;
    }

    item->setSizeHint(label->sizeHint());
    viewingArea->addItem(item);
    viewingArea->setItemWidget(item, label);
}

bool TagList::somethingIsSelected()
{
    return !viewingArea->selectedItems().isEmpty();
}

void TagList::showContextMenu(const QPoint& point)
{
    if (somethingIsSelected()) {
        QPoint position = viewingArea->mapToGlobal(point);

        QMenu contextMenu;
        contextMenu.addAction("Remove", this, SLOT (removeSelectedTags()));
        contextMenu.exec(position);
    }
}

void TagList::removeSelectedTags()
{
    for (int i = 0; i < viewingArea->selectedItems().size(); ++i) {
        removeTag(viewingArea->takeItem(viewingArea->currentRow()));
    }
}

void TagList::removeTag(QListWidgetItem* tag)
{
    int id = tag->data(UserRole::ID).toInt();
    QString name = tag->data(UserRole::NAME).toString();
    emit tagToBeRemovedFromSelectedFile(id);
    emit tagToBeRemovedFromSearch(id);
    emit tagToBeRemoved(name);

    // Removing the item from the list widget stops Qt's management of it
    // and it must then be deleted manually.
    delete tag;
}
