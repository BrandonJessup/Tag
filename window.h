#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QBoxLayout>
#include <QListWidget>

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
    QListWidget* fileBrowser;

    void createTopLevelLayout();
    void createButtonBar();
    void createLowerLayout();
    void createTagPanel();
    void createFileBrowser();

signals:

public slots:
};

#endif // WINDOW_H
