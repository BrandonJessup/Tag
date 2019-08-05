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
    layout->addWidget(viewingArea);
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
