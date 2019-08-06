#include "taglist.h"

TagList::TagList(QWidget *parent) : QWidget(parent)
{
    createLayout();
    createViewingArea();
}

void TagList::createLayout()
{
    layout = new QStackedLayout;
    this->setLayout(layout);
}

void TagList::createViewingArea()
{
    viewingArea = new QListWidget;

    viewingArea->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(viewingArea, SIGNAL (customContextMenuRequested(QPoint)), this, SLOT (showContextMenu(QPoint)));

    layout->addWidget(viewingArea);
}

void TagList::relaySignals()
{
    connect(viewingArea->selectionModel(), SIGNAL (selectionChanged(QItemSelection, QItemSelection)), this, SLOT (showContextMenu()));
}

void TagList::clear()
{
    viewingArea->clear();
}

void TagList::addTag(const TagTuple& tag)
{
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
        contextMenu.addAction("Remove", this, SLOT (removeTags()));
        contextMenu.exec(position);
    }
}

void TagList::removeTags()
{
    for (int i = 0; i < viewingArea->selectedItems().size(); ++i) {
        QListWidgetItem* tag = viewingArea->takeItem(viewingArea->currentRow());

        int id = tag->data(UserRole::ID).toInt();
        emit tagToBeRemovedFromSelectedFile(id);

        // Removing the item from the list widget stop's Qt's management of it
        // and it must then be deleted manually.
        delete tag;
    }
}
