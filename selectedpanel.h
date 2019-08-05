#ifndef SELECTEDPANEL_H
#define SELECTEDPANEL_H

#include "selected.h"
#include "subtagpanelbase.h"

class SelectedPanel : public SubTagPanelBase
{
public:
    explicit SelectedPanel(QWidget *parent = nullptr);

    void setSelectedFile(const int& file);
    void addTag() override;

private:
    int selectedFile;

    bool tagIsValid(const QString& tag);

signals:

public slots:
};

#endif // SELECTEDPANEL_H
