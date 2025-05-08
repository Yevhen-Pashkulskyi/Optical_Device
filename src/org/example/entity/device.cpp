/**
 * Цей файл для реалізації конструкторів та функцій
 */

#include <iostream>
#include <string>
#include "device.h"

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
    std::cout << "Модель: " << modelName << "\n"
              << "Фокусна відстань: " << focalLength << " мм\n"
              << "Апертура: " << aperture << " мм\n"
              << "Вага: " << weight << " г\n"
              << "Стан: " << (isPoweredOn ? "Увімкнено" : "Вимкнено") << "\n"
              << "Поточний рівень збільшення: " << currentZoom << "x\n";
    double fNumber = focalLength / aperture;
    std::cout << "Світлосила (f-number): f/" << fNumber << "\n" << std::endl;
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

// --- Camera ---

PhotoCamera::PhotoCamera(const char* model, double focal, double ap, double wt, double mp, const char* mode)
    : OpticalDevice(model, focal, ap, wt), megapixels(mp)
{
    shootingMode = new char[strlen(mode) + 1];
    strcpy(shootingMode, mode);
}

PhotoCamera::PhotoCamera(const PhotoCamera& other, const char* name)
    : OpticalDevice(other, name), megapixels(other.megapixels)
{
    shootingMode = new char[strlen(other.shootingMode) + 1];
    strcpy(shootingMode, other.shootingMode);
}

PhotoCamera::~PhotoCamera()
{
    std::cout << "Режим зйомки " << shootingMode << " видалено" << std::endl;
    delete [] shootingMode;
}

std::string PhotoCamera::powerOn()
{
    isPoweredOn = true;
    currentZoom = 1.0;
    setShootingMode("Auto"); // Ініціалізація режиму зйомки
    return std::string(modelName) + " увімкнено. Зум і режим зйомки ініціалізовано.";
}

std::string PhotoCamera::powerOff()
{
    isPoweredOn = false;
    currentZoom = 0.0;
    return std::string(modelName) + " вимкнено. Зум скинуто.";
}

void PhotoCamera::displayImage(const std::string& info) const
{
    using namespace std;
    if (isPoweredOn) {
        double baseFieldOfView = 20.0;
        double fieldOfView = baseFieldOfView / currentZoom;
        cout << "Відображення на екрані камери: " << info << endl;
        cout << "Параметри зображення: Зум = " << currentZoom << "x, Поле зору = " << fieldOfView << " градусів, "
             << "Режим зйомки = " << shootingMode << endl;
    } else {
        cout << "Неможливо відобразити зображення: камера вимкнена." << endl;
    }
}

void PhotoCamera::printInfo() const
{
    OpticalDevice::printInfo();
    std::string quality;
    if (std::strcmp(shootingMode, "Auto") == 0) {
        quality = "стандартна";
    } else if (std::strcmp(shootingMode, "Portrait") == 0) {
        quality = "висока";
    } else if (std::strcmp(shootingMode, "Night") == 0) {
        quality = "низька";
    } else {
        quality = "невідома";
    }
    std::cout << "Мегапікселі: " << megapixels << " MP\n"
              << "Режим зйомки: " << shootingMode << " (якість: " << quality << ")\n" << std::endl;
}

void PhotoCamera::configureDevice()
{
    currentZoom = 1.0;
    setShootingMode("Auto");
    std::cout << modelName << ": Конфігурація завершена. Зум = 1.0x, Режим зйомки = Auto." << std::endl;
}

void PhotoCamera::capturePhoto() const
{
    if (isPoweredOn) {
        std::string quality;
        double photoSizeMB = megapixels * 0.3;
        if (std::strcmp(shootingMode, "Auto") == 0) {
            quality = "стандартна";
            photoSizeMB *= 1.0;
        } else if (std::strcmp(shootingMode, "Portrait") == 0) {
            quality = "висока";
            photoSizeMB *= 1.5;
        } else if (std::strcmp(shootingMode, "Night") == 0) {
            quality = "низька";
            photoSizeMB *= 0.7;
        } else {
            quality = "невідома";
        }
        std::cout << "Фото знято в режимі " << shootingMode << ".\n"
                  << "Якість: " << quality << ", Роздільна здатність: " << megapixels << " MP, "
                  << "Розмір фото: " << photoSizeMB << " МБ.\n";
    } else {
        std::cout << "Неможливо зробити фото: камера вимкнена.\n";
    }
}

void PhotoCamera::setShootingMode(const char *mode)
{
    delete [] shootingMode;
    shootingMode = new char[strlen(mode) + 1];
    strcpy(shootingMode, mode);
    std::cout << "Режим зйомки змінено на: " << shootingMode << std::endl;
}