/**
 * цей файл для реалізацій конструкторів та функцій
 */

#include <iostream>
#include <string>
#include "device.h"

double OpticalDevice::max_zoom_level = 5.0;

// Конструктор з параметрами
OpticalDevice::OpticalDevice(const char* model, double focal, double ap, double wt) : focalLength(focal), aperture(ap),
    weight(wt), isPoweredOn(false), currentZoom(0.0)
{
    modelName = new char[strlen(model) + 1];
    strcpy(modelName, model);
}

// Конструктор копіювання
OpticalDevice::OpticalDevice(const OpticalDevice& other, const char* name): focalLength(other.focalLength),
       aperture(other.aperture),
      weight(other.weight),
       isPoweredOn(other.isPoweredOn),
      currentZoom(other.currentZoom)
{
    modelName = new char[strlen(name) + 1];
    strcpy(modelName, name);
}

// Деструктор
OpticalDevice::~OpticalDevice()
{
    std::cout << modelName << " Видалено" << std::endl;
    delete [] modelName;
}

// Увімкнення приладу
std::string OpticalDevice::powerOn()
{
    isPoweredOn = true;
    currentZoom = 1.0; // Ініціалізація мінімального зуму
    std::string info = std::string(modelName) + " увімкнено. Зум ініціалізовано на 1.0x.";
    return info;
}

// Вимкнення приладу
std::string OpticalDevice::powerOff()
{
    isPoweredOn = false;
    currentZoom = 0.0; // Скидання зуму
    std::string info = std::string(modelName) + " вимкнено. Зум скинуто.";
    return info;
}

void OpticalDevice::set_max_zoom_level(double level)
{
    max_zoom_level = level;
}

double OpticalDevice::get_max_zoom_level()
{
    return max_zoom_level;
}

// Налаштування масштабу
void OpticalDevice::adjustZoom(double level_zoom)
{
    using namespace std;
    if (isPoweredOn) {
        if (level_zoom > max_zoom_level) {
            currentZoom = max_zoom_level;
            cout << "Досягнуто максимальне значення ZOOM = " << max_zoom_level << "x" << endl;
        } else if (level_zoom < 1.0) {
            currentZoom = 1.0; // Мінімальний зум
            cout << "Досягнуто мінімальне значення ZOOM = 1.0x" << endl;
        } else {
            currentZoom = level_zoom;
        }
        // Розрахунок поля зору (у градусах, приблизно)
        double baseFieldOfView = 20.0; // Базове поле зору для прикладу
        double fieldOfView = baseFieldOfView / currentZoom;
        cout << "Зум встановлено на " << currentZoom << "x. Поле зору: " << fieldOfView << " градусів." << endl;
    } else {
        cout << "Неможливо змінити збільшення: прилад вимкнений." << endl;
    }
}

// Відображення зображення (симуляція)
void OpticalDevice::displayImage(const std::string& info) const
{
    using namespace std;
    if (isPoweredOn) {
        // Симуляція відображення з урахуванням параметрів
        double baseFieldOfView = 20.0;
        double fieldOfView = baseFieldOfView / currentZoom;
        cout << "Відображення на дисплеї: " << info << endl;
        cout << "Параметри зображення: Зум = " << currentZoom << "x, Поле зору = " << fieldOfView << " градусів." << endl;
    } else {
        cout << "Неможливо відобразити зображення: прилад вимкнений." << endl;
    }
}

// Виведення стану об'єкта
void OpticalDevice::printInfo() const
{
    std::cout << "Модель: " << modelName << "\n"
              << "Фокусна відстань: " << focalLength << " мм\n"
              << "Апертура: " << aperture << " мм\n"
              << "Вага: " << weight << " г\n"
              << "Стан: " << (isPoweredOn ? "Увімкнено" : "Вимкнено") << "\n"
              << "Поточний рівень збільшення: " << currentZoom << "x\n";
    // Розрахунок світлосили (f-number)
    double fNumber = focalLength / aperture;
    std::cout << "Світлосила (f-number): f/" << fNumber << "\n" << std::endl;
}

// Реалізація методів класу Camera

// Конструктор з параметрами
PhotoCamera::PhotoCamera(const char* model, double focal, double ap, double wt, double mp, const char* mode)
    : OpticalDevice(model, focal, ap, wt), megapixels(mp)
{
    shootingMode = new char[strlen(mode) + 1];
    strcpy(shootingMode, mode);
}

// Конструктор копіювання
PhotoCamera::PhotoCamera(const PhotoCamera& other, const char* name)
    : OpticalDevice(other, name), megapixels(other.megapixels)
{
    shootingMode = new char[strlen(other.shootingMode) + 1];
    strcpy(shootingMode, other.shootingMode);
}

// Деструктор
PhotoCamera::~PhotoCamera()
{
    delete [] shootingMode;
}

// Метод для зйомки фотографії
void PhotoCamera::capturePhoto() const
{
    if (isPoweredOn) {
        // Симуляція зйомки з урахуванням shootingMode і megapixels
        std::string quality;
        double photoSizeMB = megapixels * 0.3; // Приблизний розмір фото в МБ (0.3 МБ на мегапіксель)
        if (std::strcmp(shootingMode, "Auto") == 0) {
            quality = "стандартна";
            photoSizeMB *= 1.0; // Без змін
        } else if (std::strcmp(shootingMode, "Portrait") == 0) {
            quality = "висока";
            photoSizeMB *= 1.5; // Вища якість, більший розмір
        } else if (std::strcmp(shootingMode, "Night") == 0) {
            quality = "низька";
            photoSizeMB *= 0.7; // Нижча якість для нічного режиму
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

// Метод для зміни режиму зйомки
void PhotoCamera::setShootingMode(const char *mode)
{
    // Звільняємо попередній режим
    delete [] shootingMode;
    // Виділяємо пам’ять для нового режиму
    shootingMode = new char[strlen(mode) + 1];
    strcpy(shootingMode, mode);
    std::cout << "Режим зйомки змінено на: " << shootingMode << std::endl;
}

// Перевизначений метод printInfo
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