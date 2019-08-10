#include "selectedpanel.h"

SelectedPanel::SelectedPanel(QWidget *parent) : QWidget(parent)
{
    createOuterLayout();
    createGroupBox("Selected");
    createGroupBoxLayout();
    createTextField();
    createTagList();
    setSelectedFile(Selected::NONE);
    relaySignals();
}

void SelectedPanel::createOuterLayout()
{
    outerLayout = new QStackedLayout;
    this->setLayout(outerLayout);
}

void SelectedPanel::createGroupBox(const QString& title)
{
    groupBox = new QGroupBox(title);
    outerLayout->addWidget(groupBox);
}

void SelectedPanel::createGroupBoxLayout()
{
    groupBoxLayout = new QVBoxLayout();
    groupBox->setLayout(groupBoxLayout);
}

void SelectedPanel::createTextField()
{
    textField = new QLineEdit;
    textField->setPlaceholderText("Enter tag");
    groupBoxLayout->addWidget(textField);
}

void SelectedPanel::createTagList()
{
    tagList = new TagList;
    groupBoxLayout->addWidget(tagList);
}

void SelectedPanel::relaySignals()
{
    connect(textField, SIGNAL (returnPressed()), this, SLOT (addTag()));
    connect(tagList, SIGNAL (tagToBeRemovedFromSelectedFile(int)), this, SLOT (removeTagFromSelectedFile(int)));
    connect(tagList, SIGNAL (tagClicked(int)), this, SIGNAL (tagClicked(int)));
}

void SelectedPanel::setSelectedFile(const int& file)
{
    selectedFile = file;
}

void SelectedPanel::addTag()
{
    QString tag = textField->text();
    textField->clear();
    if (tagIsValid(tag)) {
        tag = cleanUp(tag);
        Database* database = Database::getInstance();
        database->addTagToFile(tag, selectedFile);
        refreshTagList();
    }
}

bool SelectedPanel::tagIsValid(const QString& tag)
{
    bool isValid = true;
    isValid &= !tag.isEmpty();
    isValid &= hasNonWhitespaceCharacter(tag);

    return isValid;
}

bool SelectedPanel::hasNonWhitespaceCharacter(const QString& tag)
{
    for (int i = 0; i < tag.length(); ++i) {
        if (!tag[i].isSpace()) {
            return true;
        }
    }
    return false;
}

QString SelectedPanel::cleanUp(QString tag)
{
    tag = tag.simplified();
    tag = tag.toLower();
    return tag;
}

void SelectedPanel::refreshTagList()
{
    Database* database = Database::getInstance();
    QList<TagTuple> tags = database->getTagsOfFile(selectedFile);
    populateTagList(tags);
}

void SelectedPanel::populateTagList(QList<TagTuple> tags)
{
    tagList->clear();
    for (TagTuple tag : tags) {
        tagList->addTag(tag);
    }
}

void SelectedPanel::removeTagFromSelectedFile(int id)
{
    Database* database = Database::getInstance();
    database->removeTagFromFile(id, selectedFile);
}
