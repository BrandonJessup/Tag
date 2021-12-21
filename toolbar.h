#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>

#include "buttonpanel.h"
#include "settings.h"
#include "thumbnailslider.h"

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar(ThumbnailManager* thumbnailManager, QWidget *parent = nullptr);

private:
    ThumbnailManager* thumbnailManager;
    QBoxLayout* layout;
    QLabel* sliderLabel;
    ThumbnailSlider* thumbnailSlider;
    ButtonPanel* buttonPanel;

    void createLayout();
    void createButtonPanel();
    void createSpacer();
    void createSliderLabel();
    void createThumbnailSlider();
    void relaySignals();
    void updateSliderLabel(int newValue);
    void snapSliderToDefault(int value);

signals:
    void filesChanged();
    void thumbnailSliderMoved(int newValue);
    void databaseTagsChanged();

public slots:
    void sliderValueChangedReceiver(int newValue);
    void importFiles(QStringList paths);
};

#endif // TOOLBAR_H
