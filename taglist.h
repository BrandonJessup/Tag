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
#include "prompt.h"

class TagList : public QWidget
{
    Q_OBJECT

public:
    explicit TagList(QSize size = QSize(), QWidget *parent = nullptr);

    void clear();
    void addTag(const TagTuple& tag);

private:
    QStackedLayout* layout;
    QListWidget* viewingArea;
    QString styleSheetGreen;
    QString styleSheetRed;
    QString styleSheetGrey;

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
    void removeSelectedTag();
    void tagClickedEmitter(QListWidgetItem* item);
};

#endif // TAGLIST_H
