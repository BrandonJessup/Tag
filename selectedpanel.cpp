#include "selectedpanel.h"

SelectedPanel::SelectedPanel(QWidget *parent) : SubTagPanelBase(parent)
{
    setGroupLabel("Selected");
    setTextFieldPlaceholder("Enter tag");
}
