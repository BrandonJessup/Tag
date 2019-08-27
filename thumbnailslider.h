#ifndef THUMBNAILSLIDER_H
#define THUMBNAILSLIDER_H

#include <QSlider>
#include <QWheelEvent>

#include "settings.h"

class ThumbnailSlider : public QSlider
{
public:
    ThumbnailSlider();

private:
    void wheelEvent(QWheelEvent* event) override;
};

#endif // THUMBNAILSLIDER_H
