#include "searchpanel.h"

SearchPanel::SearchPanel(QWidget *parent) : SubTagPanelBase(parent)
{
    setGroupLabel("Search");
    setTextFieldPlaceholder("Enter tag");
    relaySignals();
}

void SearchPanel::relaySignals()
{
    connect(tagList, SIGNAL (tagClicked(int)), this, SLOT (removeTagFromSearch(int)));
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

void SearchPanel::addTag()
{
    QString tag = getTextFieldContent();
    clearTextField();
    if (tagIsValid(tag)) {
        tag = format(tag);

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
