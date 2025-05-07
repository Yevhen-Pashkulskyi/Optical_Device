/**
* Цей файл для об'явлення класу OpticalDevice з його атрибутами, конструкторами та функціями
 */

#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <string>

class OpticalDevice {
   char *modelName; // назва девайсу
   double focalLength; // фокусна відстань
   double aperture; // діаметр апертури
   double weight; // вага
   double currentZoom; // поточний рівень збільшення
   static double max_zoom_level; // максимальне збільшення статична змінна
protected:
   bool isPoweredOn; // стан ввімкнено/вимкнено

public:
   OpticalDevice(const char *model, double focalLength, double aperture, double wt);
   OpticalDevice(const OpticalDevice &other, const char *name);
   ~OpticalDevice();
   std::string powerOn();
   std::string powerOff();
   // статичний метод для всіх об'єктів
   static void set_max_zoom_level(double level);
   static double get_max_zoom_level();
   void adjustZoom(double level_zoom);
   void displayImage(const std::string &info) const;
   void printInfo() const;
};

class Camera : public OpticalDevice {
   double megapixels; // кількість мегапікселів
   char *shootingMode; // режим зйомки (наприклад, авто, портрет, нічний)

public:
   Camera(const char *model, double focalLength, double aperture, double wt, double mp, const char *mode);
   Camera(const Camera &other, const char *name);
   ~Camera();
   void capturePhoto() const; // новий метод для зйомки фотографії
   void setShootingMode(const char *mode); // метод для зміни режиму зйомки
   void printInfo() const; // перевизначений метод для відображення додаткової інформації
};

#endif