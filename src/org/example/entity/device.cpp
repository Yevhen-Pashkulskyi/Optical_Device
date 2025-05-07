/**
 * цей файл для реализацій конструкторів та функцій
 */

#include <iostream>
#include <string>
#include "device.h"

/**
 *  методи класу OpticalDevice
 */
double OpticalDevice::max_zoom_level = 5.0;

//Конструктор з параметрами
OpticalDevice::OpticalDevice(const char* model, double focal, double ap, double wt) : focalLength(focal), aperture(ap),
   weight(wt), isPoweredOn(false), currentZoom(0.0){
   modelName = new char[strlen(model) + 1];
   strcpy(modelName, model);
}

// Конструкор копіювання
OpticalDevice::OpticalDevice(const OpticalDevice& other, const char* name): focalLength(other.focalLength),
                                                                            aperture(other.aperture),
                                                                            weight(other.weight),
                                                                            isPoweredOn(other.isPoweredOn),
                                                                            currentZoom(other.currentZoom){
   modelName = new char[strlen(name) + 1];
   strcpy(modelName, name);
}

//Деструктор
OpticalDevice::~OpticalDevice(){
   std::cout << modelName << " видалено" << std::endl;
   delete [] modelName;
}

//Увімкнення приладу
std::string OpticalDevice::powerOn(){
   isPoweredOn = true;
   std::string info = std::string(modelName) + " увімкнено.";
   return info;
}

//Вимкнення приладу
std::string OpticalDevice::powerOff(){
   isPoweredOn = false;
   currentZoom = 0.0;
   std::string info = std::string(modelName) + " вимкнено.";
   return info;
}

void OpticalDevice::set_max_zoom_level(double level){ max_zoom_level = level; }

double OpticalDevice::get_max_zoom_level(){ return max_zoom_level; }

//Налаштування маштабу
void OpticalDevice::adjustZoom(double level_zoom){
   using namespace std;
   string info;
   if (isPoweredOn){
      if (level_zoom > max_zoom_level){
         currentZoom = max_zoom_level;
         cout << "МАКСИМАЛЬНЕ ЗНАЧЕННЯ ZOOM = " << max_zoom_level << "x" << endl;
      }
      else{ currentZoom = level_zoom; }
      cout << "Zоом встановлено " << currentZoom << "x" << endl;
   }
   else{ cout << "Неможливо змінити збільшиення: прилад ввимкнений\n" << endl; }
}

// Відображення зображення (симуляція)
void OpticalDevice::displayImage(const std::string& info) const{
   using namespace std;
   if (isPoweredOn){ cout << "Дісплей: " << info << endl; }
   else{ cout << "Неможливо відобразити зображення: прилад вимкнений.\n" << endl; }
}

// Виведення стану об'єкта
void OpticalDevice::printInfo() const{
   std::cout << "Модель: " << modelName << "\n"
      << "Фокусна відстань: " << focalLength << " мм\n"
      << "Апертура: " << aperture << " мм\n"
      << "Вага: " << weight << " г\n"
      << "Стан: " << (isPoweredOn ? "Увімкнено" : "Вимкнено") << "\n"
      << "Поточний рівень збільшення: " << currentZoom << "x" << "\n" << std::endl;
}

/**
 * методи класу  Camera
*/

// конструктор з параметрами
Camera::Camera(const char* model, double focalLength,
               double aperture, double wt, double megapixels,
               const char* mode)
   : OpticalDevice(model, focalLength, aperture, wt), megapixels(megapixels){
   shootingMode = new char[strlen(mode) + 1];
   strcpy(shootingMode, mode);
}

// конструткор копіювання
Camera::Camera(const Camera& other, const char* name)
   : OpticalDevice(other, name), megapixels(other.megapixels){
   shootingMode = new char[strlen(other.shootingMode) + 1];
   strcpy(shootingMode, other.shootingMode);
}

// деструктор
Camera::~Camera(){
   delete[]shootingMode;
}

// метод для зйомки фото
void Camera::capturePhoto() const{
   if (isPoweredOn){
      std::cout << "Зняте фото" << shootingMode << "з роздільною здатністю" <<
         megapixels << "MP.\n";
   }
   else{ std::cout << "Неможливо зробитиі фото: камера вимкнена.\n"; }
}

// перевизначенний метод
void Camera::printInfo() const{
   OpticalDevice::printInfo();
   std::cout << "Мегапікселі: " << megapixels << " MP\n"
      << "Режим зйомки: " << shootingMode << "\n" << std::endl;
}
