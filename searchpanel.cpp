#include "searchpanel.h"

SearchPanel::SearchPanel(QWidget *parent) : QWidget(parent)
{
    createOuterLayout();
    createGroupBox("Search");
    createGroupBoxLayout();
    createSearchFieldLayout();
    createTextField();
    createTagList();
    relaySignals();
}

void SearchPanel::createOuterLayout()
{
    outerLayout = new QStackedLayout;
    this->setLayout(outerLayout);
}

void SearchPanel::createGroupBox(const QString& title)
{
    groupBox = new QGroupBox(title);
    outerLayout->addWidget(groupBox);
}

void SearchPanel::createGroupBoxLayout()
{
    groupBoxLayout = new QVBoxLayout;
    groupBox->setLayout(groupBoxLayout);
}

void SearchPanel::createSearchFieldLayout()
{
    searchFieldLayout = new QHBoxLayout;
    groupBoxLayout->addLayout(searchFieldLayout);
}

void SearchPanel::createTextField()
{
    textField = new QLineEdit;
    textField->setPlaceholderText("Enter tag");
    searchFieldLayout->addWidget(textField);
}

void SearchPanel::createTagList()
{
    tagList = new TagList;
    groupBoxLayout->addWidget(tagList);
}

void SearchPanel::relaySignals()
{
    connect(textField, SIGNAL (returnPressed()), this, SLOT (addTag()));
    connect(tagList, SIGNAL (tagClicked(int)), this, SLOT (removeTagFromSearch(int)));
    connect(tagList, SIGNAL (tagToBeRemovedFromSearch(int)), this, SLOT (removeTagFromSearch(int)));
}

void SearchPanel::removeTagFromSearch(int tagId)
{
    activeSearchTags.removeOne(tagId);
    emit activeSearchTagsChanged(activeSearchTags);
    refreshTagList();
}

void SearchPanel::refreshTagList()
{
    Database* database = Database::getInstance();
    QList<TagTuple> tags = database->getTuplesOfTags(activeSearchTags);
    populateTagList(tags);
}

void SearchPanel::populateTagList(QList<TagTuple> tags)
{
    tagList->clear();
    for (TagTuple tag : tags) {
        tagList->addTag(tag);
    }
}

void SearchPanel::addTag()
{
    QString tag = textField->text();
    textField->clear();
    if (tagIsValid(tag)) {
        tag = cleanUp(tag);

        Database* database = Database::getInstance();
        try {
            int id = database->getIdOfTag(tag);
            if (!activeSearchTags.contains(id)) {
                activeSearchTags.append(id);
                refreshTagList();
                emit activeSearchTagsChanged(activeSearchTags);
            }
            else {
                showPrompt("The tag " + tag + " is already in the search!");
            }
        }
        catch (TagNameNotFoundException e) {
            showPrompt("The tag " + tag + " does not exist!");
        }
    }
}

bool SearchPanel::tagIsValid(const QString& tag)
{
    bool isValid = true;
    isValid &= !tag.isEmpty();
    isValid &= hasNonWhitespaceCharacter(tag);

    return isValid;
}

bool SearchPanel::hasNonWhitespaceCharacter(const QString& tag)
{
    for (int i = 0; i < tag.length(); ++i) {
        if (!tag[i].isSpace()) {
            return true;
        }
    }
    return false;
}

QString SearchPanel::cleanUp(QString tag)
{
    tag = tag.simplified();
    tag = tag.toLower();
    return tag;
}

void SearchPanel::showPrompt(const QString& message)
{
    QMessageBox prompt;
    prompt.setText(message);
    prompt.setStandardButtons(QMessageBox::Ok);
    prompt.setDefaultButton(QMessageBox::Ok);
    prompt.exec();
}

void SearchPanel::toggleTagInSearch(int tagId)
{
    if (!activeSearchTags.contains(tagId)) {
        activeSearchTags.append(tagId);
        refreshTagList();
        emit activeSearchTagsChanged(activeSearchTags);
    }
    else {
        removeTagFromSearch(tagId);
    }
}
