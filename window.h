#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QBoxLayout>

#include "buttonbar.h"
#include "tagpanel.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);

private:
    QBoxLayout* topLevelLayout;
    ButtonBar* buttonBar;
    QBoxLayout* lowerLayout;
    TagPanel* tagPanel;

    void createTopLevelLayout();
    void createButtonBar();
    void createLowerLayout();
    void createTagPanel();

signals:

public slots:
};

#endif // WINDOW_H
