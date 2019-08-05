#ifndef TAGLIST_H
#define TAGLIST_H

#include <QWidget>
#include <QStackedLayout>
#include <QListWidget>

#include "tagtuple.h"
#include "userrole.h"

class TagList : public QWidget
{
    Q_OBJECT

public:
    explicit TagList(QWidget *parent = nullptr);

    void clear();
    void addTag(const TagTuple& tag);

private:
    QStackedLayout* layout;
    QListWidget* viewingArea;

    void createLayout();
    void createViewingArea();

signals:

public slots:
};

#endif // TAGLIST_H
