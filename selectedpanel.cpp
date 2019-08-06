#include "selectedpanel.h"

SelectedPanel::SelectedPanel(QWidget *parent) : SubTagPanelBase(parent)
{
    selectedFile = Selected::NONE;
    setGroupLabel("Selected");
    setTextFieldPlaceholder("Enter tag");
    relaySignals();
}

void SelectedPanel::relaySignals()
{
    connect(tagList, SIGNAL (tagToBeRemovedFromSelectedFile(int)), this, SLOT (removeTagFromSelectedFile(int)));
}

void SelectedPanel::setSelectedFile(const int& file)
{
    selectedFile = file;
}

void SelectedPanel::addTag()
{
    QString tag = getTextFieldContent();
    clearTextField();
    if (tagIsValid(tag)) {
        tag = removeExcessWhitespace(tag);
        Database* database = Database::getInstance();
        database->addTagToFile(tag, selectedFile);
        refreshTagList();
    }
}

void SelectedPanel::refreshTagList()
{
    Database* database = Database::getInstance();
    QList<TagTuple> tags = database->getTagsOfFile(selectedFile);
    populateTagList(tags);
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

QString SelectedPanel::removeExcessWhitespace(QString tag)
{
    return tag.simplified();
}

void SelectedPanel::removeTagFromSelectedFile(int id)
{
    Database* database = Database::getInstance();
    database->removeTagFromFile(id, selectedFile);
}
