#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    createTopLevelLayout();
    createToolBar();
    createLowerLayout();
    createTagPanel();
    createFileBrowser();

    relaySignals();
}

// topLevelLayout contains the button bar at the very top with the
// bottom portion filled by the contents of lowerLayout.
void Window::createTopLevelLayout()
{
    topLevelLayout = new QVBoxLayout;
    this->setLayout(topLevelLayout);
}

void Window::createToolBar()
{
    toolBar = new ToolBar;
    topLevelLayout->addWidget(toolBar);
}

// lowerLayout contains the tagPanel on the left side and the
// fileBrowser on the right.
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

void Window::createFileBrowser()
{
    fileBrowser = new FileBrowser;
    lowerLayout->addWidget(fileBrowser);
}

void Window::relaySignals()
{
    connect(toolBar, SIGNAL (filesChanged()), fileBrowser, SLOT (reloadContents()));
    connect(fileBrowser, SIGNAL (selectionChanged(int)), tagPanel, SLOT (selectionChanged(int)));
    connect(fileBrowser, SIGNAL (databaseTagsChanged()), tagPanel, SLOT (updateTagDictionaries()));
    connect(toolBar, SIGNAL (databaseTagsChanged()), tagPanel, SLOT (updateTagDictionaries()));
    connect(tagPanel, SIGNAL (activeSearchTagsChanged(QList<int>, QList<int>)), fileBrowser, SLOT (updateSearchList(QList<int>, QList<int>)));
    connect(tagPanel, SIGNAL (databaseTagsChanged()), fileBrowser, SLOT (reloadContents()));
    connect(toolBar, SIGNAL (thumbnailSliderMoved(int)), fileBrowser, SLOT (updateThumbnailScale(int)));
}
