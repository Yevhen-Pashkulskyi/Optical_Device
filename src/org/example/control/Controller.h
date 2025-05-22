#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../entity/DeviceBase.h"
#include "../entity/extends/PhotoCamera.h"
#include "view/View.h"
#include <vector>
#include <memory>
#include <string>
using namespace std;

class Controller{
   PhotoCamera& camera;
   DeviceBase* basePtr;
   View view;
   vector<unique_ptr<DeviceBase>> devices; // контейнер для зберігання об'єктів

public:
   Controller(PhotoCamera& camera, DeviceBase* basePtr);
   int run();

private:
   void handlePowerOn();
   void handlePowerOff();
   void handleAdjustZoom();
   void handlePrintInfo();
   void handleCopyCamera();
   void handleSetMaxZoom();
   void handleGetMaxZoom();
   void handleCapturePhoto();
   void handleSetShootingMode();
   void handleDisplayDevices();

   // операции с контейнером
   void addDeviceFront(); //додати в початок
   void addDeviceBack();// додати в кінець
   void addDeviceAtPosition(); // додати в конкретну позицію
   void findDeviceByCriteria(); // пошук за певними критеріями
   void sortDeviceByAttribute(); // сортує за кокретинм атрібутом
   void displayDevices(); // вивід девайсів
   vector<variant<string,double>> inputDataPhotoCamera();
   vector<variant<std::string,double>> inputDataOpticalDevice();
};

#endif //CONTROLLER_H
