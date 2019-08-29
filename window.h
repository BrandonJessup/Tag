#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QBoxLayout>
#include <QFileInfo>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QStringList>
#include <QMimeData>

#include "toolbar.h"
#include "tagpanel.h"
#include "filebrowser.h"
#include "settings.h"
#include "database.h"
#include "filetuple.h"
#include "missingfiledialog.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);

private:
    ThumbnailManager* thumbnailManager;
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
    void checkIntegrityOfFiles();
    void createThumbnailManager();
    void relaySignals();

    void deleteThumbnail(const QString& path);
    QString extractNameFromPath(const QString& path);
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

signals:
    void filesDropped(QStringList paths);

public slots:
};

#endif // WINDOW_H
