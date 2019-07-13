#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QBoxLayout>

#include "buttonbar.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);

private:
    QBoxLayout* topLevelLayout;
    ButtonBar* buttonBar;

    void createTopLevelLayout();
    void createButtonBar();

signals:

public slots:
};

#endif // WINDOW_H
