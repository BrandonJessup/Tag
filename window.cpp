#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    createTopLevelLayout();
    createButtonBar();
    createLowerLayout();
    createTagPanel();
}

// topLevelLayout contains the button bar at the very top with the
// bottom portion filled by the contents of lowerLayout.
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

void Window::createLowerLayout()
{
    lowerLayout = new QHBoxLayout;
    topLevelLayout->addLayout(lowerLayout);
}

void Window::createTagPanel()
{
    tagPanel = new TagPanel;
    lowerLayout->addWidget(tagPanel);
}
