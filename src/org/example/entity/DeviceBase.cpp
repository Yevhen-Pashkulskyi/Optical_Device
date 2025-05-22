/**
 * Цей файл для реалізації конструкторів та функцій
 */

#include <iostream>
#include <string>
#include "DeviceBase.h"

// --- OpticalBase ---

DeviceBase::DeviceBase(const char* model, double focal, double ap, double wt)
    : focalLength(focal), aperture(ap), weight(wt), isPoweredOn(false)
{
    modelName = new char[strlen(model) + 1];
    strcpy(modelName, model);
}

DeviceBase::DeviceBase(const DeviceBase& other, const char* name)
    : focalLength(other.focalLength), aperture(other.aperture), weight(other.weight), isPoweredOn(other.isPoweredOn)
{
    modelName = new char[strlen(name) + 1];
    strcpy(modelName, name);
}

DeviceBase::~DeviceBase()
{
    std::cout << modelName << " Видалено (OpticalBase)" << std::endl;
    delete [] modelName;
}

std::string DeviceBase::powerOn()
{
    isPoweredOn = true;
    return std::string(modelName) + " увімкнено.";
}

std::string DeviceBase::powerOff()
{
    isPoweredOn = false;
    return std::string(modelName) + " вимкнено.";
}

void DeviceBase::displayImage(const std::string& info) const
{
    if (isPoweredOn) {
        std::cout << "Відображення: " << info << std::endl;
    } else {
        std::cout << "Неможливо відобразити: пристрій вимкнений." << std::endl;
    }
}

std::string DeviceBase::getModelName() const{
    return std::string(modelName);
}
