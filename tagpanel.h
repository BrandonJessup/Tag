#ifndef TAGPANEL_H
#define TAGPANEL_H

#include <QWidget>
#include <QBoxLayout>

#include "selected.h"
#include "searchpanel.h"
#include "selectedpanel.h"

class TagPanel : public QWidget
{
    Q_OBJECT

public:
    explicit TagPanel(QWidget *parent = nullptr);

private:
    QBoxLayout* layout;
    SearchPanel* searchPanel;
    SelectedPanel* selectedPanel;

    void setSize();
    void createLayout();
    void createSearchPanel();
    void createSelectedPanel();
    void relaySignals();

signals:
    void activeSearchTagsChanged(QList<int> tags, QList<int> excludeTags);
    void tagAddedToSelectedFile(int tagId);
    void tagRemovedFromSelectedFile(int tagId);

public slots:
    void selectionChanged(int selectedFile);
    void updateTagDictionaries();
};

#endif // TAGPANEL_H
