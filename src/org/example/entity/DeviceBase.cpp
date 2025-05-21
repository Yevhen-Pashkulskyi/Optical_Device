/**
 * Цей файл для реалізації конструкторів та функцій
 */

#include <iostream>
#include <string>
#include "DeviceBase.h"

// --- OpticalBase ---

OpticalBase::OpticalBase(const char* model, double focal, double ap, double wt)
    : focalLength(focal), aperture(ap), weight(wt), isPoweredOn(false)
{
    modelName = new char[strlen(model) + 1];
    strcpy(modelName, model);
}

OpticalBase::OpticalBase(const OpticalBase& other, const char* name)
    : focalLength(other.focalLength), aperture(other.aperture), weight(other.weight), isPoweredOn(other.isPoweredOn)
{
    modelName = new char[strlen(name) + 1];
    strcpy(modelName, name);
}

OpticalBase::~OpticalBase()
{
    std::cout << modelName << " Видалено (OpticalBase)" << std::endl;
    delete [] modelName;
}

std::string OpticalBase::powerOn()
{
    isPoweredOn = true;
    return std::string(modelName) + " увімкнено.";
}

std::string OpticalBase::powerOff()
{
    isPoweredOn = false;
    return std::string(modelName) + " вимкнено.";
}

void OpticalBase::displayImage(const std::string& info) const
{
    if (isPoweredOn) {
        std::cout << "Відображення: " << info << std::endl;
    } else {
        std::cout << "Неможливо відобразити: пристрій вимкнений." << std::endl;
    }
}

std::string OpticalBase::getModelName() const{
    return std::string(modelName);
}
