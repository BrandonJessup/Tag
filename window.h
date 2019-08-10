#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QBoxLayout>

#include "toolbar.h"
#include "tagpanel.h"
#include "filebrowser.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);

private:
    QBoxLayout* topLevelLayout;
    ToolBar* toolBar;
    QBoxLayout* lowerLayout;
    TagPanel* tagPanel;
    FileBrowser* fileBrowser;

    void createTopLevelLayout();
    void createToolBar();
    void createLowerLayout();
    void createTagPanel();
    void createFileBrowser();
    void relaySignals();

signals:

public slots:
};

#endif // WINDOW_H
