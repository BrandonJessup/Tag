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

public slots:
    void selectionChanged(int selectedFile);
};

#endif // TAGPANEL_H
