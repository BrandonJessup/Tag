#include "searchpanel.h"

SearchPanel::SearchPanel(QWidget *parent) : QWidget(parent)
{
    createOuterLayout();
    createGroupBox();
    createInnerLayout();
    createTextField();
    createTagList();
}

void SearchPanel::createOuterLayout()
{
    outerLayout = new QStackedLayout;
    this->setLayout(outerLayout);
}

void SearchPanel::createGroupBox()
{
    groupBox = new QGroupBox;
    groupBox->setTitle("Search");
    outerLayout->addWidget(groupBox);
}

void SearchPanel::createInnerLayout()
{
    innerLayout = new QVBoxLayout;
    groupBox->setLayout(innerLayout);
}

void SearchPanel::createTextField()
{
    textField = new QLineEdit;
    textField->setPlaceholderText("Enter tag");

    innerLayout->addWidget(textField);
}

void SearchPanel::createTagList()
{
    tagList = new TagList;

    innerLayout->addWidget(tagList);
}
