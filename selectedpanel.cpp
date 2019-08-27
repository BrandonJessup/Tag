#include "selectedpanel.h"

SelectedPanel::SelectedPanel(QWidget *parent) : QWidget(parent)
{
    createOuterLayout();
    createGroupBox("Selected");
    createGroupBoxLayout();
    createTextField();
    createCompleter();
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

void SelectedPanel::createCompleter()
{
    completer = new QCompleter(tagDictionary);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    textField->setCompleter(completer);
    updateTagDictionary();
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
    connect(this, SIGNAL (tagAddedToSelectedFile(int)), this, SLOT (updateTagDictionary()));
    connect(this, SIGNAL (tagRemovedFromSelectedFile(int)), this, SLOT (updateTagDictionary()));
}

void SelectedPanel::updateTagDictionary() {
    Database* database = Database::getInstance();

    tagDictionary = database->getAllTagNamesExcludingSpecial();
    QStringListModel* model = new QStringListModel(tagDictionary);
    completer->setModel(model);
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
        if (database->isSpecialTag(tag)) {
            Prompt::show(tag + " is a reserved name!");
        }
        else if (database->fileHasTag(selectedFile, tag)) {
            Prompt::show("Selected file already has that tag!");
        }
        else {
            database->addTagToFile(tag, selectedFile);
            refreshTagList();
            int tagId = database->getIdOfTag(tag);
            emit tagAddedToSelectedFile(tagId);
            textField->setFocus();
        }
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
    Database* database = Database::getInstance();

    tagList->clear();
    std::sort(tags.begin(), tags.end(), TagTuple::alphabeticalSort);
    for (TagTuple tag : tags) {
        if (database->isSpecialTag(tag.getName())) {
            tag.setColor(TagColor::GREY);
        }
        tagList->addTag(tag);
    }
}

void SelectedPanel::removeTagFromSelectedFile(int id)
{
    Database* database = Database::getInstance();
    database->removeTagFromFile(id, selectedFile);
    emit tagRemovedFromSelectedFile(id);
}
