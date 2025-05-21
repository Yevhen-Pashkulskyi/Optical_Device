#include "PhotoCamera.h"
#include <iostream>
#include <string>


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
              << "Режим зйомки: " << shootingMode << " (якість: " << quality << ")" << std::endl;
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

double PhotoCamera::getMegapixels() const{
    return megapixels;
}
