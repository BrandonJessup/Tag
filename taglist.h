#ifndef TAGLIST_H
#define TAGLIST_H

#include <QWidget>
#include <QStackedLayout>
#include <QListWidget>

class TagList : public QWidget
{
    Q_OBJECT

public:
    explicit TagList(QWidget *parent = nullptr);

private:
    QStackedLayout* layout;
    QListWidget* viewingArea;

    void createLayout();
    void createViewingArea();

signals:

public slots:
};

#endif // TAGLIST_H
