#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    createTopLevelLayout();
    createButtonBar();
}

void Window::createTopLevelLayout()
{
    topLevelLayout = new QVBoxLayout;
    this->setLayout(topLevelLayout);
}

void Window::createButtonBar()
{
    buttonBar = new ButtonBar;
    topLevelLayout->addWidget(buttonBar);
}
