#ifndef SELECTEDPANEL_H
#define SELECTEDPANEL_H

#include "selected.h"
#include "subtagpanelbase.h"

class SelectedPanel : public SubTagPanelBase
{
public:
    explicit SelectedPanel(QWidget *parent = nullptr);

    void setSelectedFile(const int& file);
    void refreshTagList() override;
    void addTag() override;

private:
    int selectedFile;

    bool tagIsValid(const QString& tag);
    bool hasNonWhitespaceCharacter(const QString& tag);
    QString removeExcessWhitespace(QString tag);

signals:

public slots:
};

#endif // SELECTEDPANEL_H