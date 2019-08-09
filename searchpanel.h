#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include <QList>
#include <QMessageBox>

#include "subtagpanelbase.h"
#include "tagnamenotfoundexception.h"

class SearchPanel : public SubTagPanelBase
{
    Q_OBJECT

public:
    explicit SearchPanel(QWidget *parent = nullptr);

    void refreshTagList() override;
    void addTag() override;

private:
    QList<int> activeSearchTags;

    void showPrompt(const QString& message);

signals:
    void activeSearchTagsChanged(QList<int> tagIds);

public slots:
};

#endif // SEARCHPANEL_H
