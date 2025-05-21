#include "OpticalDevice.h"
#include <iostream>
#include <string>

// --- OpticalDevice ---

double OpticalDevice::max_zoom_level = 5.0;

OpticalDevice::OpticalDevice(const char* model, double focal, double ap, double wt)
    : OpticalBase(model, focal, ap, wt), currentZoom(0.0)
{
}

OpticalDevice::OpticalDevice(const OpticalDevice& other, const char* name)
    : OpticalBase(other, name), currentZoom(other.currentZoom)
{
}

OpticalDevice::~OpticalDevice()
{
    std::cout << modelName << " Видалено (OpticalDevice)" << std::endl;
}

std::string OpticalDevice::powerOn()
{
    isPoweredOn = true;
    currentZoom = 1.0; // Ініціалізація зуму
    return std::string(modelName) + " увімкнено. Зум ініціалізовано на 1.0x.";
}

std::string OpticalDevice::powerOff()
{
    isPoweredOn = false;
    currentZoom = 0.0; // Скидання зуму
    return std::string(modelName) + " вимкнено. Зум скинуто.";
}

void OpticalDevice::displayImage(const std::string& info) const
{
    using namespace std;
    if (isPoweredOn) {
        double baseFieldOfView = 20.0;
        double fieldOfView = baseFieldOfView / currentZoom;
        cout << "Відображення на дисплеї: " << info << endl;
        cout << "Параметри зображення: Зум = " << currentZoom << "x, Поле зору = " << fieldOfView << " градусів." << endl;
    } else {
        cout << "Неможливо відобразити зображення: прилад вимкнений." << endl;
    }
}

void OpticalDevice::printInfo() const
{
    std::cout << "\nМодель: " << modelName << "\n"
              << "Фокусна відстань: " << focalLength << " мм\n"
              << "Апертура: " << aperture << " мм\n"
              << "Вага: " << weight << " г\n"
              << "Стан: " << (isPoweredOn ? "Увімкнено" : "Вимкнено") << "\n"
              << "Поточний рівень збільшення: " << currentZoom << "x\n";
    double fNumber = focalLength / aperture;
    std::cout << "Світлосила (f-number): f/" << fNumber << std::endl;
}

void OpticalDevice::configureDevice()
{
    currentZoom = 1.0;
    std::cout << modelName << ": Конфігурація завершена. Зум встановлено на 1.0x." << std::endl;
}

void OpticalDevice::set_max_zoom_level(double level)
{
    max_zoom_level = level;
}

double OpticalDevice::get_max_zoom_level()
{
    return max_zoom_level;
}

void OpticalDevice::adjustZoom(double level_zoom)
{
    using namespace std;
    if (isPoweredOn) {
        if (level_zoom > max_zoom_level) {
            currentZoom = max_zoom_level;
            cout << "Досягнуто максимальне значення ZOOM = " << max_zoom_level << "x" << endl;
        } else if (level_zoom < 1.0) {
            currentZoom = 1.0;
            cout << "Досягнуто мінімальне значення ZOOM = 1.0x" << endl;
        } else {
            currentZoom = level_zoom;
        }
        double baseFieldOfView = 20.0;
        double fieldOfView = baseFieldOfView / currentZoom;
        cout << "Зум встановлено на " << currentZoom << "x. Поле зору: " << fieldOfView << " градусів." << endl;
    } else {
        cout << "Неможливо змінити збільшення: прилад вимкнений." << endl;
    }
}
