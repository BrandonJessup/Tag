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
    connect(tagList, SIGNAL (tagClicked(int)), this, SLOT (tagClickedEmitter(int)));
}

void SelectedPanel::tagClickedEmitter(int tagId)
{
    emit tagClicked(tagId);
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
        tag = format(tag);
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

void SelectedPanel::removeTagFromSelectedFile(int id)
{
    Database* database = Database::getInstance();
    database->removeTagFromFile(id, selectedFile);
}
