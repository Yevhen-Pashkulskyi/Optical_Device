/**
 * цей файл для реализацій конструкторів та функцій
 */

#include <iostream>
#include <string>
#include "device.h"

double OpticalDevice::max_zoom_level = 5.0;

//Конструктор з параметрами
OpticalDevice::OpticalDevice(const char *model, double focal, double ap, double wt) : focalLength(focal), aperture(ap),
    weight(wt), isPoweredOn(false), currentZoom(0.0) {
    modelName = new char[strlen(model) + 1];
    strcpy(modelName, model);
}

// Конструкор копіювання

OpticalDevice::OpticalDevice(const OpticalDevice &other, const char *name): focalLength(other.focalLength),
                                                                            aperture(other.aperture),
                                                                            weight(other.weight),
                                                                            isPoweredOn(other.isPoweredOn),
                                                                            currentZoom(other.currentZoom) {
    modelName = new char[strlen(name) + 1];
    strcpy(modelName, name);
}

//Деструктор

OpticalDevice::~OpticalDevice() {
    std::cout << modelName << " Видалено" << std::endl;
    delete [] modelName;
}

//Увімкнення приладу

std::string OpticalDevice::powerOn() {
    isPoweredOn = true;
    std::string info = std::string(modelName) + " увімкнено.";
    return info;
}

//Вимкнення приладу

std::string OpticalDevice::powerOff() {
    isPoweredOn = false;
    currentZoom = 0.0;
    std::string info = std::string(modelName) + " вимкнено.";
    return info;
}

void OpticalDevice::set_max_zoom_level(double level) {
    max_zoom_level = level;
}

//Налаштування маштабу

void OpticalDevice::adjustZoom(double level_zoom) {
    using namespace std;
    string info;
    if (isPoweredOn) {
        if (level_zoom > max_zoom_level) {
            currentZoom = max_zoom_level;
            cout << "МАКСИМАЛЬНЕ ЗНАЧЕННЯ ZOOM = " << max_zoom_level << "x" << endl;
        } else {
            currentZoom = level_zoom;
        }
        cout << "Zоом встановлено " << currentZoom << "x" << endl;
    } else {
        cout << "Неможливо змінити збільшиення: прилад ввимкнений\n" << endl;
    }
}

// Відображення зображення (симуляція)

void OpticalDevice::displayImage(const std::string &info) const {
    using namespace std;
    if (isPoweredOn) {
        cout << "Дісплей: " << info << endl;
    } else {
        cout << "Неможливо відобразити зображення: прилад вимкнений.\n" << endl;
    }
}

// Виведення стану об'єкта

void OpticalDevice::printInfo() const {
    std::cout << "Модель: " << modelName << "\n"
            << "Фокусна відстань: " << focalLength << " мм\n"
            << "Апертура: " << aperture << " мм\n"
            << "Вага: " << weight << " г\n"
            << "Стан: " << (isPoweredOn ? "Увімкнено" : "Вимкнено") << "\n"
            << "Поточний рівень збільшення: " << currentZoom << "x" << "\n" << std::endl;
}
