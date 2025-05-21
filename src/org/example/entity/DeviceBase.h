/**
 * Цей файл для оголошення абстрактного класу OpticalBase
 */

#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class OpticalBase {
protected:
    char *modelName; // назва девайсу
    double focalLength; // фокусна відстань
    double aperture; // діаметр апертури
    double weight; // вага
    bool isPoweredOn; // стан ввімкнено/вимкнено

public:
    OpticalBase(const char *model, double focalLength, double aperture, double wt);
    OpticalBase(const OpticalBase &other, const char *name);
    // віртуальні методи
    virtual ~OpticalBase(); // деструткор
    virtual std::string powerOn(); // метод включення
    virtual std::string powerOff(); // метод виключення
    virtual void displayImage(const std::string &info) const; // метод відображення емітація екрану
    virtual void printInfo() const = 0; // інформація девайсу
    virtual void configureDevice() = 0; // конфігурація девайсу
    std::string getModelName()const;
};

#endif