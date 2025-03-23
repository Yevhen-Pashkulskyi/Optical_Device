#include <iostream>
#include <string>

class OpticalDevice {
    char *modelName; // назва девайсу
    double focalLength; // фокусна відстань
    double aperture; // діаметр апертури
    double weight; // вага
    bool isPoweredOn; // стан ввімкнено/вімкнено
    double currentZoom; // поточний рівень збільшення

public:
    //Конструктор з параметрами
    OpticalDevice(char *model, double focal, double ap, double wt) : focalLength(focal), aperture(ap),
        weight(wt), isPoweredOn(false), currentZoom(0) {
        modelName = new char[strlen(model) + 1];
        strcpy(modelName, model);
    }

    // Конструкор копіювання
    OpticalDevice(OpticalDevice &other, const char *name): focalLength(other.focalLength), aperture(other.aperture),
                                                     weight(other.weight), isPoweredOn(other.isPoweredOn),
                                                     currentZoom(other.currentZoom) {
        modelName = new char[strlen(name) + 1];
        strcpy(modelName, name);
    }

    //Деструктор
    ~OpticalDevice() {
        std::cout << modelName << " Видалено" << std::endl;
        delete [] modelName;
    }

    //Увімкнення приладу
    std::string powerOn() {
        isPoweredOn = true;
        std::string info = modelName + std::string(" увімкнено.");
        return info;
    }

    //Вимкнення приладу
    std::string powerOff() {
        isPoweredOn = false;
        currentZoom = 0;
        std::string info = modelName + std::string(" вимкнено.");
        return info;
    }

    //Налаштування маштабу
    std::string adjustZoom(int level_zoom) {
        std::string info;
        if (isPoweredOn) {
            currentZoom = level_zoom;
            info = "Збільшення встановлено на рівень " + std::to_string(currentZoom);
        } else {
            info = "Неможливо змінити збільшиення прилад ввимкнений\n";
        }
        return info;
    }

    // Відображення зображення (симуляція)
    void displayImage(const std::string &info) {
        if (isPoweredOn) {
            std::cout << "Дісплей: " << info << std::endl;
        } else {
            std::cout << "Неможливо відобразити зображення: прилад вимкнений.\n" << std::endl;
        }
    }

    // Виведення стану об'єкта
    void printInfo() const {
        std::cout << "Модель: " << modelName << "\n"
                << "Фокусна відстань: " << focalLength << " мм\n"
                << "Апертура: " << aperture << " мм\n"
                << "Вага: " << weight << " г\n"
                << "Стан: " << (isPoweredOn ? "Увімкнено" : "Вимкнено") << "\n"
                << "Поточний рівень збільшення: " << currentZoom << "\n" << std::endl;
    }
};
