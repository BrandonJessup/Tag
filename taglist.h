#ifndef TAGLIST_H
#define TAGLIST_H

#include <QWidget>
#include <QStackedLayout>
#include <QListWidget>
#include <QMenu>
#include <QString>
#include <QLabel>

#include "tagtuple.h"
#include "userrole.h"
#include "database.h"
#include "tagcolor.h"

class TagList : public QWidget
{
    Q_OBJECT

public:
    explicit TagList(QWidget *parent = nullptr);

    void clear();
    void addTag(const TagTuple& tag, TagColor color);

private:
    QStackedLayout* layout;
    QListWidget* viewingArea;
    QString styleSheetGreen;
    QString styleSheetRed;

    void createLayout();
    void createStyleSheets();
    void createViewingArea();
    void relaySignals();

    bool somethingIsSelected();
    void removeTag(QListWidgetItem* tag);

signals:
    void tagToBeRemovedFromSelectedFile(int id);
    void tagToBeRemovedFromSearch(int id);
    void tagToBeRemoved(QString tagName);
    void tagClicked(int tagId);
    void tagClicked(QString tagName);

public slots:
    void showContextMenu(const QPoint& point);
    void removeSelectedTags();
    void tagClickedEmitter(QListWidgetItem* item);
};

#endif // TAGLIST_H
