#ifndef OPTICALDEVICE_H
#define OPTICALDEVICE_H

#include <QString>

class OpticalDevice {
    QString modelName;
    double focalLength;
    double aperture;
    double weight;
    bool isPoweredOn = false;
    double currentZoom = 1.0;
    inline static double max_zoom_level = 5.0;

public:
    OpticalDevice(QString model, double focal, double aperture, double weight);
    QString powerOn();
    QString powerOff();
    QString adjustZoom(double level);
    QString getInfo() const;
    QString getModelName() const;

    static void setMaxZoomLevel(double level);
    static double getMaxZoomLevel();
};

#endif // OPTICALDEVICE_H
