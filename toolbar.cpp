#include "toolbar.h"

ToolBar::ToolBar(QWidget *parent) : QWidget(parent)
{
    createLayout();
    createButtonPanel();
    createSpacer();
    createSliderLabel();
    createThumbnailSlider();
    relaySignals();
}

void ToolBar::createLayout()
{
    layout = new QHBoxLayout;
    this->setLayout(layout);
}

void ToolBar::createButtonPanel()
{
    buttonPanel = new ButtonPanel;
    layout->addWidget(buttonPanel);
}

void ToolBar::createSpacer()
{
    layout->addStretch();
}

void ToolBar::createSliderLabel()
{
    sliderLabel = new QLabel("100%");
    layout->addWidget(sliderLabel);
}

void ToolBar::createThumbnailSlider()
{
    thumbnailSlider = new ThumbnailSlider;
    updateSliderLabel(thumbnailSlider->value());
    layout->addWidget(thumbnailSlider);
}

void ToolBar::relaySignals()
{
    connect(buttonPanel, SIGNAL (filesChanged()), this, SIGNAL (filesChanged()));
    connect(thumbnailSlider, SIGNAL (valueChanged(int)), this, SLOT (sliderValueChangedReceiver(int)));
    connect(buttonPanel, SIGNAL (databaseTagsChanged()), this, SIGNAL (databaseTagsChanged()));
}

void ToolBar::sliderValueChangedReceiver(int newValue)
{
    updateSliderLabel(newValue);
    snapSliderToDefault(newValue);

    // The current value is passed instread of newValue because the
    // slider may have been changed by snapSliderToDefault.
    emit thumbnailSliderMoved(thumbnailSlider->value());
    Settings::saveThumbnailSliderPosition(thumbnailSlider->value());
}

void ToolBar::updateSliderLabel(int newValue)
{
    sliderLabel->setText(QString::number(newValue) + "%");
}

void ToolBar::snapSliderToDefault(int value)
{
    if (value < 110 && value > 90) {
        thumbnailSlider->setValue(100);
    }
}
