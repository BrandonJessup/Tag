#include "selectedpanel.h"

SelectedPanel::SelectedPanel(QWidget *parent) : SubTagPanelBase(parent)
{
    selectedFile = Selected::NONE;
    setGroupLabel("Selected");
    setTextFieldPlaceholder("Enter tag");
}
