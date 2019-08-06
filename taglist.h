#ifndef TAGLIST_H
#define TAGLIST_H

#include <QWidget>
#include <QStackedLayout>
#include <QListWidget>
#include <QMenu>

#include "tagtuple.h"
#include "userrole.h"
#include "database.h"

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
    void relaySignals();

    bool somethingIsSelected();

signals:
    void tagToBeRemovedFromSelectedFile(int id);

public slots:
    void showContextMenu(const QPoint& point);
    void removeTags();
};

#endif // TAGLIST_H
