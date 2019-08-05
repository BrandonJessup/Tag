#include "tagpanel.h"

TagPanel::TagPanel(QWidget *parent) : QWidget(parent)
{
    setSize();
    createLayout();
    createSearchPanel();
    createSelectedPanel();
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

void TagPanel::selectionChanged(int selectedFile)
{
    bool fileIsSelected = selectedFile != Selected::NONE;
    selectedPanel->setEnabled(fileIsSelected);
}
