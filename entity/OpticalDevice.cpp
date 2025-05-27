#include "../include/opticaldevice.h"
#include <QString>

OpticalDevice::OpticalDevice(QString model, double focal, double aperture, double weight)
    : modelName(model), focalLength(focal), aperture(aperture), weight(weight) {}

QString OpticalDevice::powerOn() {
    isPoweredOn = true;
    return modelName + " увімкнено.";
}

QString OpticalDevice::powerOff() {
    isPoweredOn = false;
    return modelName + " вимкнено.";
}

void OpticalDevice::adjustZoom(double level) {
    if (isPoweredOn) {
        currentZoom = std::clamp(level, 1.0, max_zoom_level);
    }
}

QString OpticalDevice::getInfo() const {
    return QString("Модель: %1\nФокус: %2\nАпертура: %3\nВага: %4 г\nСтан: %5\nЗбільшення: %6x")
        .arg(modelName)
        .arg(focalLength)
        .arg(aperture)
        .arg(weight)
        .arg(isPoweredOn ? "Увімкнено" : "Вимкнено")
        .arg(currentZoom);
}

void OpticalDevice::setMaxZoomLevel(double level) {
    max_zoom_level = level;
}

double OpticalDevice::getMaxZoomLevel() {
    return max_zoom_level;
}
