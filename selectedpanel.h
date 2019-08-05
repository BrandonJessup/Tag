#ifndef SELECTEDPANEL_H
#define SELECTEDPANEL_H

#include "selected.h"
#include "subtagpanelbase.h"

class SelectedPanel : public SubTagPanelBase
{
public:
    explicit SelectedPanel(QWidget *parent = nullptr);

private:
    int selectedFile;

signals:

public slots:
};

#endif // SELECTEDPANEL_H
