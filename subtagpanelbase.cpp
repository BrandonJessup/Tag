#include "subtagpanelbase.h"

SubTagPanelBase::SubTagPanelBase(QWidget *parent) : QWidget(parent)
{
    createOuterLayout();
    createGroupBox();
    createInnerLayout();
    createTextField();
    createTagList();

    relaySignals();
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

void SubTagPanelBase::relaySignals()
{
    connect(textField, SIGNAL (returnPressed()), this, SLOT (addTag()));
}

QString SubTagPanelBase::getTextFieldContent()
{
    return textField->text();
}

void SubTagPanelBase::clearTextField()
{
    textField->clear();
}

void SubTagPanelBase::populateTagList(QList<TagTuple> tags)
{
    tagList->clear();
    for (TagTuple tag : tags) {
        tagList->addTag(tag);
    }
}
