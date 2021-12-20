#include "searchpanel.h"

SearchPanel::SearchPanel(QWidget *parent) : QWidget(parent)
{
    createOuterLayout();
    createGroupBox("Search");
    createGroupBoxLayout();
    createSearchFieldLayout();
    createTextField();
    createCompleter();
    createExcludeDropDown();
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

void SearchPanel::createCompleter()
{
    completer = new QCompleter(tagDictionary);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    textField->setCompleter(completer);
    updateTagDictionary();
}

void SearchPanel::createExcludeDropDown()
{
    excludeDropDown = new QComboBox;
    excludeDropDown->addItem("Include");
    excludeDropDown->addItem("Exclude");
    excludeDropDown->setCurrentIndex(DropDownIndex::INCLUDE);
    searchFieldLayout->addWidget(excludeDropDown);
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

void SearchPanel::updateTagDictionary()
{
    Database* database = Database::getInstance();

    tagDictionary = database->getAllTagNames();
    QStringListModel* model = new QStringListModel(tagDictionary);
    completer->setModel(model);
}

void SearchPanel::removeTagFromSearch(int tagId)
{
    if (activeSearchTags.contains(tagId)) {
        activeSearchTags.removeOne(tagId);
    }
    else {
        activeExcludeTags.removeOne(tagId);
    }

    emit activeSearchTagsChanged(activeSearchTags, activeExcludeTags);
    refreshTagList();
}

void SearchPanel::refreshTagList()
{
    Database* database = Database::getInstance();
    QList<TagTuple> tags = database->getTuplesOfTags(activeSearchTags);
    QList<TagTuple> excludeTags = database->getTuplesOfTags(activeExcludeTags);
    colorTagsRed(excludeTags);
    populateTagList(tags, excludeTags);
}

void SearchPanel::colorTagsRed(QList<TagTuple>& tags)
{
    for (TagTuple& tag : tags) {
        tag.setColor(TagColor::RED);
    }
}

void SearchPanel::populateTagList(QList<TagTuple> tags, QList<TagTuple> excludeTags)
{
    tagList->clear();
    QList<TagTuple> allTags = tags + excludeTags;
    std::sort(allTags.begin(), allTags.end(), TagTuple::alphabeticalSort);
    for (TagTuple tag : allTags) {
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
            if (!activeSearchTags.contains(id) && !activeExcludeTags.contains(id)) {
                switch (excludeDropDown->currentIndex()) {
                case DropDownIndex::INCLUDE:
                    activeSearchTags.append(id);
                    break;
                case DropDownIndex::EXCLUDE:
                    activeExcludeTags.append(id);
                    break;
                }

                refreshTagList();
                emit activeSearchTagsChanged(activeSearchTags, activeExcludeTags);
            }
            else {
                Prompt::show("The tag '" + tag + "' is already in the search!");
            }
        }
        catch (TagNameNotFoundException e) {
            Prompt::show("The tag '" + tag + "' does not exist!");
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

bool SearchPanel::searchIsEmpty()
{
    return activeSearchTags.isEmpty() && activeExcludeTags.isEmpty();
}

void SearchPanel::toggleTagInSearch(int tagId)
{
    if (!activeSearchTags.contains(tagId)) {
        activeSearchTags.append(tagId);
        refreshTagList();
        emit activeSearchTagsChanged(activeSearchTags, activeExcludeTags);
    }
    else {
        removeTagFromSearch(tagId);
    }
}
