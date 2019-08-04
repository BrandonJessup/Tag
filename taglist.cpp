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
