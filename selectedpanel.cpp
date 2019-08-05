#include "selectedpanel.h"

SelectedPanel::SelectedPanel(QWidget *parent) : SubTagPanelBase(parent)
{
    selectedFile = Selected::NONE;
    setGroupLabel("Selected");
    setTextFieldPlaceholder("Enter tag");
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
    // TODO: Perform some basic checks like whether it's empty,
    // whether it is entirely spaces, etc.

    // TEMP
    return true;
}
