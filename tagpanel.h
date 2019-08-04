#ifndef TAGPANEL_H
#define TAGPANEL_H

#include <QWidget>
#include <QBoxLayout>

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

signals:

public slots:
    void selectionChanged(bool isSelection);
};

#endif // TAGPANEL_H
