#include "settings.h"

const QString Settings::ORGANIZATION = "Brandon Jessup";
const QString Settings::APPLICATION = "Tag";

void Settings::saveThumbnailSliderPosition(const int& value)
{
    QSettings settings(ORGANIZATION, APPLICATION);
    settings.setValue("thumbnailSlider", value);
}

int Settings::loadThumbnailSliderPosition()
{
    QSettings settings(ORGANIZATION, APPLICATION);
    const int DEFAULT_VALUE = 100;
    return settings.value("thumbnailSlider", DEFAULT_VALUE).toInt();
}

void Settings::saveLastUsedDirectory(const QString& path)
{
    QSettings settings(ORGANIZATION, APPLICATION);
    settings.setValue("lastUsedDirectory", path);
}

QString Settings::loadLastUsedDirectory()
{
    QSettings settings(ORGANIZATION, APPLICATION);
    const QString DEFAULT_VALUE = "/home";
    return settings.value("lastUsedDirectory", DEFAULT_VALUE).toString();
}
