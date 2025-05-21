#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../entity/DeviceBase.h"
#include "../entity/extends/PhotoCamera.h"
#include "view/View.h"
#include <vector>
#include <memory>
#include <string>

class CameraController{
   PhotoCamera& camera;
   OpticalBase* basePtr;
   View view;
   std::vector<std::unique_ptr<OpticalBase>> devices; // контейнер для зберігання об'єктів

public:
   CameraController(PhotoCamera& camera, OpticalBase* basePtr);
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
};

#endif //CONTROLLER_H
