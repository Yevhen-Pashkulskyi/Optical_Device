/**
 * Цей файл для оголошення абстрактного класу DeviceBase
 */

#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class DeviceBase {
protected:
    char *modelName; // назва девайсу
    double focalLength; // фокусна відстань
    double aperture; // діаметр апертури
    double weight; // вага
    bool isPoweredOn; // стан ввімкнено/вимкнено

public:
    DeviceBase(const char *model, double focalLength, double aperture, double wt);
    DeviceBase(const DeviceBase &other, const char *name);
    // віртуальні методи
    virtual ~DeviceBase(); // деструткор
    virtual std::string powerOn(); // метод включення
    virtual std::string powerOff(); // метод виключення
    virtual void displayImage(const std::string &info) const; // метод відображення емітація екрану
    virtual void printInfo() const = 0; // інформація девайсу
    virtual void configureDevice() = 0; // конфігурація девайсу
    std::string getModelName()const;
};

#endif