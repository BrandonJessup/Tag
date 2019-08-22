#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings
{
public:
    static void saveThumbnailSliderPosition(const int& value);
    static int loadThumbnailSliderPosition();

    static void saveLastUsedDirectory(const QString& path);
    static QString loadLastUsedDirectory();

protected:
    Settings();

private:
    static const QString ORGANIZATION;
    static const QString APPLICATION;
};

#endif // SETTINGS_H
