/**
 * Цей файл для оголошення абстрактного класу OpticalBase та похідних класів
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
};

class OpticalDevice : public OpticalBase {
protected:
    double currentZoom; // поточний рівень збільшення
    static double max_zoom_level; // максимальне збільшення

public:
    OpticalDevice(const char *model, double focalLength, double aperture, double wt);
    OpticalDevice(const OpticalDevice &other, const char *name);
    ~OpticalDevice() override;
    std::string powerOn() override;
    std::string powerOff() override;
    void displayImage(const std::string &info) const override;
    void printInfo() const override;
    void configureDevice() override;
    static void set_max_zoom_level(double level);
    static double get_max_zoom_level();
    void adjustZoom(double level_zoom);
};

class PhotoCamera : public OpticalDevice {
    double megapixels; // кількість мегапікселів
    char *shootingMode; // режим зйомки

public:
    PhotoCamera(const char *model, double focalLength, double aperture, double wt, double mp, const char *mode);
    PhotoCamera(const PhotoCamera &other, const char *name);
    ~PhotoCamera() override;
    std::string powerOn() override;
    std::string powerOff() override;
    void displayImage(const std::string &info) const override;
    void printInfo() const override;
    void configureDevice() override;
    void capturePhoto() const;
    void setShootingMode(const char *mode);
};

#endif