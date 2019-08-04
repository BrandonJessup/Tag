#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include <QWidget>
#include <QStackedLayout>
#include <QBoxLayout>
#include <QGroupBox>
#include <QLineEdit>

#include "taglist.h"

class SearchPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPanel(QWidget *parent = nullptr);

private:
    QStackedLayout* outerLayout;
    QGroupBox* groupBox;
    QBoxLayout* innerLayout;
    QLineEdit* textField;
    TagList* tagList;

    void createOuterLayout();
    void createGroupBox();
    void createInnerLayout();
    void createTextField();
    void createTagList();

signals:

public slots:
};

#endif // SEARCHPANEL_H
