#include "../include/opticaldevice.h"
// Конструктор класу OpticalDevice
OpticalDevice::OpticalDevice(QString model, double focal, double aperture, double weight)
    : modelName(model), focalLength(focal), aperture(aperture), weight(weight) {}
// Метод увімкнення пристрою
QString OpticalDevice::powerOn() {
    isPowerStatus = true;
    return modelName + "🟢 увімкнено.";
}
// Метод вимкнення пристрою
QString OpticalDevice::powerOff() {
    isPowerStatus = false;
    return modelName + "🔴 вимкнено.";
}
// Метод регулювання збільшення пристрою
QString OpticalDevice::adjustZoom(double level) {
    if (!isPowerStatus) {
        return "❗️ Неможливо змінити збільшення: пристрій вимкнений.";
    }

    if (level > max_zoom_level) {
        currentZoom = max_zoom_level;
        return QString("⚠️ Введене збільшення перевищує максимум. Встановлено максимальне значення: %1x").arg(currentZoom);
    }
    if (level < 1.0) {
        currentZoom = 1.0;
        return "⚠️ Мінімальне допустиме збільшення — 1.0x. Встановлено 1.0x.";
    } else {
        currentZoom = level;
        return QString("✅ Збільшення змінено на %1x").arg(currentZoom);
    }
}
// Метод отримання повної інформації про пристрій
QString OpticalDevice::getInfo() const {
    return QString("\nМодель: %1\nФокус: %2\nАпертура: %3\nВага: %4 г\nСтан: %5\nЗбільшення: %6x")
        .arg(modelName)
        .arg(focalLength)
        .arg(aperture)
        .arg(weight)
        .arg(isPowerStatus ? "🟢 Увімкнено" : "🔴 Вимкнено")
        .arg(currentZoom);
}
// Метод отримання назви моделі
QString OpticalDevice::getModelName() const{
    return modelName;
}
// Метод отримання поточного статусу живлення
bool OpticalDevice::getPowerStatus() const{
    return isPowerStatus;
}
// Статичний метод для встановлення нового значення максимального збільшення
void OpticalDevice::setMaxZoomLevel(double level) {
    max_zoom_level = level;
}
// Статичний метод для отримання значення максимального збільшення
double OpticalDevice::getMaxZoomLevel() {
    return max_zoom_level;
}
