#include "subtagpanelbase.h"

SubTagPanelBase::SubTagPanelBase(QWidget *parent) : QWidget(parent)
{
    createOuterLayout();
    createGroupBox();
    createInnerLayout();
    createTextField();
    createTagList();
}

void SubTagPanelBase::createOuterLayout()
{
    outerLayout = new QStackedLayout;
    this->setLayout(outerLayout);
}

void SubTagPanelBase::createGroupBox()
{
    groupBox = new QGroupBox;
    outerLayout->addWidget(groupBox);
}

void SubTagPanelBase::createInnerLayout()
{
    innerLayout = new QVBoxLayout;
    groupBox->setLayout(innerLayout);
}

void SubTagPanelBase::createTextField()
{
    textField = new QLineEdit;
    innerLayout->addWidget(textField);
}

void SubTagPanelBase::createTagList()
{
    tagList = new TagList;
    innerLayout->addWidget(tagList);
}

void SubTagPanelBase::setGroupLabel(const QString& label)
{
    groupBox->setTitle(label);
}

void SubTagPanelBase::setTextFieldPlaceholder(const QString& placeHolder)
{
    textField->setPlaceholderText(placeHolder);
}
