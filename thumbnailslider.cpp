#include "thumbnailslider.h"

ThumbnailSlider::ThumbnailSlider() : QSlider(Qt::Horizontal)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setMinimum(50);
    setMaximum(200);

    int value = Settings::loadThumbnailSliderPosition();
    setValue(value);
}

void ThumbnailSlider::wheelEvent(QWheelEvent* event)
{
    setValue(value() + event->angleDelta().y() / 8);
}
