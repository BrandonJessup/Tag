#include "searchpanel.h"

SearchPanel::SearchPanel(QWidget *parent) : SubTagPanelBase(parent)
{
    setGroupLabel("Search");
    setTextFieldPlaceholder("Enter tag");
}
