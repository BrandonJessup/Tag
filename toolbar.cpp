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
    thumbnailSlider = new QSlider(Qt::Horizontal);
    thumbnailSlider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    thumbnailSlider->setMinimum(50);
    thumbnailSlider->setMaximum(200);
    thumbnailSlider->setValue(100);
    layout->addWidget(thumbnailSlider);
}

void ToolBar::relaySignals()
{
    connect(buttonPanel, SIGNAL (filesChanged()), this, SIGNAL (filesChanged()));
    connect(thumbnailSlider, SIGNAL (valueChanged(int)), this, SLOT (sliderValueChangedReceiver(int)));
}

void ToolBar::sliderValueChangedReceiver(int newValue)
{
    updateSliderLabel(newValue);
    snapSliderToDefault(newValue);

    // newValue is not passed because the value of the slider may have
    // been changed by snapSliderToDefault.
    emit thumbnailSliderMoved(thumbnailSlider->value());
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
