#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include "Controller.h"
#include <cctype>

#include "../view/View.h"
using namespace std;

Controller::Controller(PhotoCamera& camera, DeviceBase* basePtr):
   camera(camera), basePtr(basePtr){
}

int safeInputInt(){
   int value;
   while (!(std::cin >> value)){
      cout << "Введіть коректне число: ";
      cin.clear();
      cin.ignore(10000, '\n');
   }
   return value;
}

double safeInputDouble(){
   double value;
   while (!(std::cin >> value)){
      cout << "Введіть коректне число: ";
      cin.clear();
      cin.ignore(10000, '\n');
   }
   return value;
}

int Controller::run(){
   bool running = true;

   while (running){
      view.showMenuAddedDevice();
      int choice = safeInputInt();
      switch (choice){
      case 1: addDeviceFront();
         break;
      case 2: addDeviceBack();
         break;
      case 3: addDeviceAtPosition();
         break;
      case 4: findDeviceByCriteria();
         break;
      case 5: sortDeviceByAttribute();
         break;
      case 6: handleDisplayDevices();
         break;
      case 0:
         running = false;
         break;
      }
   }
   return 0;
}

void Controller::handlePowerOn(){
   string result = basePtr->powerOn();
   basePtr->displayImage(result);
}

void Controller::handlePowerOff(){
   string result = basePtr->powerOff();
   basePtr->displayImage(result);
}

void Controller::handleAdjustZoom(){
   double zoomLevel;
   cout << "Введіть рівень збільшення: ";
   zoomLevel = safeInputDouble();
   camera.adjustZoom(zoomLevel);
}

void Controller::handlePrintInfo(){ camera.printInfo(); }

void Controller::handleCopyCamera(){
   PhotoCamera* copyCamera = new PhotoCamera(camera, "CopiedCamera");
   cout << "Копія камери створена:\n";
   copyCamera->printInfo();
   delete copyCamera;
}

void Controller::handleSetMaxZoom(){
   double zoomLevel;
   cout << "Введіть число: ";
   zoomLevel = safeInputDouble();
   PhotoCamera::set_max_zoom_level(zoomLevel);
   cout << "Max zoom level: " << PhotoCamera::get_max_zoom_level() << "x" << endl;
}

void Controller::handleGetMaxZoom(){
   cout << "Max zoom level: " << PhotoCamera::get_max_zoom_level() << "x" << endl;
}

void Controller::handleCapturePhoto(){ camera.capturePhoto(); }

void Controller::handleSetShootingMode(){
   view.showMenuCameraShootingMode();
   int modeChoice = safeInputInt();
   switch (modeChoice){
   case 1: camera.setShootingMode("Auto");
      break;
   case 2: camera.setShootingMode("Portrait");
      break;
   case 3: camera.setShootingMode("Night");
      break;
   default: cout << "Невірний вибір режиму. Залишено поточний режим.\n";
      break;
   }
}

void Controller::handleDisplayDevices(){ displayDevices(); }

void Controller::addDeviceFront(){
   view.showTypeMenu();
   int typeChoice = safeInputInt();

   if (typeChoice == 1){
      auto input = inputDataPhotoCamera();
      devices.insert(devices.begin(), make_unique<PhotoCamera>(
                        get<string>(input[0]).c_str(), get<double>(input[1]),
                        get<double>(input[2]), get<double>(input[3]), get<double>(input[4]), "Auto"));
   }
   else if (typeChoice == 2){
      auto input = inputDataOpticalDevice();
      devices.insert(devices.begin(), make_unique<OpticalDevice>(
                        get<string>(input[0]).c_str(), get<double>(input[1]),
                        get<double>(input[2]), get<double>(input[3])));
   }
   else{ cout << "Невирный тып прыстрою"; }
}

void Controller::addDeviceBack(){
   view.showTypeMenu();
   int typeChoice = safeInputInt();
   if (typeChoice == 1){
      auto input = inputDataPhotoCamera();
      devices.push_back(make_unique<PhotoCamera>(
         get<string>(input[0]).c_str(), get<double>(input[1]),
         get<double>(input[2]), get<double>(input[3]), get<double>(input[4]), "Auto"));
   }
   else if (typeChoice == 2){
      auto input = inputDataOpticalDevice();
      devices.push_back(make_unique<OpticalDevice>(
         get<string>(input[0]).c_str(), get<double>(input[1]),
         get<double>(input[2]), get<double>(input[3])));
   }
   else{ cout << "Невирный тып прыстрою"; }
}

void Controller::addDeviceAtPosition(){
   cout << "Введіть позицію (0-" << devices.size() << "): ";
   int pos = safeInputInt();
   if (pos < 0 || pos > devices.size()){
      cout << "Невірна позиція.\n";
      return;
   }
   view.showTypeMenu();
   int typeChoice = safeInputInt();
   if (typeChoice == 1){
      auto input = inputDataPhotoCamera();
      devices.insert(devices.begin() + pos, make_unique<PhotoCamera>(
                        get<string>(input[0]).c_str(), get<double>(input[1]),
                        get<double>(input[2]), get<double>(input[3]), get<double>(input[4]), "Auto"));
   }
   else if (typeChoice == 2){
      auto input = inputDataOpticalDevice();
      devices.insert(devices.begin() + pos, make_unique<OpticalDevice>(
                        get<string>(input[0]).c_str(), get<double>(input[1]),
                        get<double>(input[2]), get<double>(input[3])));
   }
   else{ cout << "Невірний тип пристрою"; }
}

// // Допоміжна функція для порівняння рядків нечутливо до регістру
// bool caseInsensitiveCompare(const string& a, const string& b){
//    string lowerA, lowerB;
//    lowerA.resize(a.size());
//    lowerB.resize(b.size());
//    transform(a.begin(), a.end(), lowerA.begin(), ::tolower);
//    transform(b.begin(), b.end(), lowerB.begin(), ::tolower);
//    return lowerA < lowerB;
// }

void Controller::findDeviceByCriteria(){
   if (devices.empty()){
      cout << "\nКонтейнер пуст\n";
      return;
   }
   std::cout << "Введіть назву модели для пошуку: ";
   cin.ignore(10000, '\n');
   string modelName;
   getline(cin, modelName);

   bool found = false;

   for (const auto& device : devices){
      if (device->getModelName().c_str() == modelName){
         device->printInfo();
         found = true;
         break;
      }
   }
   if (!found){ cout << "Пристрої " << modelName << " не знайдено!"; }
}

void Controller::sortDeviceByAttribute(){
   std::sort(devices.begin(), devices.end(), [](const auto& a, const auto& b){
      return a->getModelName() < b->getModelName();
   });
   std::cout << "\nПристрої відсортовано за назвою.\n";
   displayDevices();
}

void Controller::displayDevices(){
   if (devices.empty()){
      cout << "\n-Контейнер порожній-\n";
      return;
   }
   for (const auto& device : devices){
      device->printInfo();
   }
}

vector<variant<string, double>> Controller::inputDataPhotoCamera(){
   vector<variant<string, double>> data = inputDataOpticalDevice();
   double megapixeles;
   cout << "Введіть мегапікселі: ";
   megapixeles = safeInputDouble();
   data.push_back(megapixeles);
   return data;
}

vector<variant<string, double>> Controller::inputDataOpticalDevice(){
   vector<variant<string, double>> data;
   string modelName;
   double focal, aperture, weight;
   cout << "Введіть модель: ";
   cin >> modelName;
   data.push_back(modelName);
   cout << "Введіть фокусну відстань: ";
   focal = safeInputDouble();
   data.push_back(focal);
   cout << "Введіть апертуру: ";
   aperture = safeInputDouble();
   data.push_back(aperture);
   cout << "Введіть вагу: ";
   weight = safeInputDouble();
   data.push_back(weight);
   return data;
}
