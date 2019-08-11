#include "taglist.h"

TagList::TagList(QWidget *parent) : QWidget(parent)
{
    createLayout();
    createStyleSheet();
    createViewingArea();
    relaySignals();
}

void TagList::createLayout()
{
    layout = new QStackedLayout;
    this->setLayout(layout);
}

void TagList::createStyleSheet()
{
    styleSheet =
            "QListWidget::item { "
                "background-color: #A9DFBF;"
                "padding: 2px;"
                "border-radius: 2px;"
            "}";
}

void TagList::createViewingArea()
{
    viewingArea = new QListWidget;

    viewingArea->setContextMenuPolicy(Qt::CustomContextMenu);
    viewingArea->setViewMode(QListView::IconMode);
    viewingArea->setMovement(QListView::Static);
    viewingArea->setResizeMode(QListView::Adjust);
    viewingArea->setStyleSheet(styleSheet);
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
    emit tagClicked(item->data(UserRole::ID).toInt());
}

void TagList::clear()
{
    viewingArea->clear();
}

void TagList::addTag(const TagTuple& tag, TagColor color)
{
    // TODO: Make color actually change the color of the item. This
    // would likely also mean a change in the stylesheet for the
    // QListWidget.

    int id = tag.getId();
    QString name = tag.getName();

    QListWidgetItem* item = new QListWidgetItem(name);

    TagTuple tuple(id, name);
    item->setData(UserRole::ID, id);
    item->setData(UserRole::NAME, name);

    viewingArea->addItem(item);
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
    emit tagToBeRemovedFromSelectedFile(id);
    emit tagToBeRemovedFromSearch(id);

    // Removing the item from the list widget stop's Qt's management of it
    // and it must then be deleted manually.
    delete tag;
}
