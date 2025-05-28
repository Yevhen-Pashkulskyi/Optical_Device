#ifndef OPTICALDEVICE_H
#define OPTICALDEVICE_H

#include <QString>

class OpticalDevice {
    QString modelName; // Назва моделі оптичного пристрою
    double focalLength; // Фокусна відстань пристрою
    double aperture; // Значення апертури пристрою
    double weight; // Вага пристрою
    bool isPowerStatus = false; // Статус живлення (увімкнено/вимкнено)
    double currentZoom = 1.0; // Поточний рівень збільшення
    inline static double max_zoom_level = 5.0; // Максимально допустимий рівень збільшення (статичний)

public:
    // Конструктор: ініціалізує новий оптичний пристрій
    OpticalDevice(QString model, double focal, double aperture, double weight);
    // Увімкнення пристрою
    QString powerOn();
    // Вимкнення пристрою
    QString powerOff();
    // Регулювання рівня збільшення
    QString adjustZoom(double level);
    // Отримання повної інформації про пристрій
    QString getInfo() const;
    // Отримання назви моделі
    QString getModelName() const;
    // Отримання поточного статусу живлення
    bool getPowerStatus() const;
    // Статичний метод: встановлення максимального рівня збільшення
    static void setMaxZoomLevel(double level);
    // Статичний метод: отримання максимального рівня збільшення
    static double getMaxZoomLevel();
};

#endif // OPTICALDEVICE_H
