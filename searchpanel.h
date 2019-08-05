#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include "subtagpanelbase.h"

class SearchPanel : public SubTagPanelBase
{
public:
    explicit SearchPanel(QWidget *parent = nullptr);

    void refreshTagList() override;
    void addTag() override;

signals:

public slots:
};

#endif // SEARCHPANEL_H
