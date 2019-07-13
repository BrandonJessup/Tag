#include "buttonbar.h"

ButtonBar::ButtonBar(QWidget *parent) : QWidget(parent)
{
    createLayout();
}

void ButtonBar::createLayout()
{
    layout = new QHBoxLayout;
    this->setLayout(layout);
}
