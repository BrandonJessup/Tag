#include "tagpanel.h"

TagPanel::TagPanel(QWidget *parent) : QWidget(parent)
{
    setSize();
    createLayout();
    createSearchPanel();
    createSelectedPanel();
    relaySignals();
}

void TagPanel::setSize()
{
    this->setFixedWidth(280);
}

void TagPanel::createLayout()
{
    layout = new QVBoxLayout;
    this->setLayout(layout);
}

void TagPanel::createSearchPanel()
{
    searchPanel = new SearchPanel;
    layout->addWidget(searchPanel);
}

void TagPanel::createSelectedPanel()
{
    selectedPanel = new SelectedPanel;
    selectedPanel->setEnabled(false);
    layout->addWidget(selectedPanel);
}

void TagPanel::relaySignals()
{
    connect(selectedPanel, SIGNAL (tagClicked(int)), searchPanel, SLOT (toggleTagInSearch(int)));
    connect(searchPanel, SIGNAL (activeSearchTagsChanged(QList<int>, QList<int>)), this, SIGNAL (activeSearchTagsChanged(QList<int>, QList<int>)));
    connect(selectedPanel, SIGNAL (tagAddedToSelectedFile(int)), searchPanel, SLOT (updateTagDictionary()));
    connect(selectedPanel, SIGNAL (tagRemovedFromSelectedFile(int)), searchPanel, SLOT (updateTagDictionary()));
    connect(selectedPanel, SIGNAL (tagAddedToSelectedFile(int)), this, SIGNAL (tagAddedToSelectedFile(int)));
    connect(selectedPanel, SIGNAL (tagRemovedFromSelectedFile(int)), this, SIGNAL (tagRemovedFromSelectedFile(int)));
}

void TagPanel::selectionChanged(int selectedFile)
{
    bool fileIsSelected = selectedFile != Selected::NONE;
    selectedPanel->setEnabled(fileIsSelected);
    selectedPanel->setSelectedFile(selectedFile);
    selectedPanel->refreshTagList();
}

void TagPanel::updateTagDictionaries()
{
    searchPanel->updateTagDictionary();
    selectedPanel->updateTagDictionary();
}
