#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QBoxLayout>
#include <QSlider>
#include <QLabel>

#include "buttonpanel.h"

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = nullptr);

private:
    QBoxLayout* layout;
    QLabel* sliderLabel;
    QSlider* thumbnailSlider;
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
};

#endif // TOOLBAR_H
