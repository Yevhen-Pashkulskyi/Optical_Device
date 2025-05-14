#include <iostream>
#include <string>
#include "CameraController.h"

#include "../view/View.h"
using namespace std;

CameraController::CameraController(PhotoCamera& camera, OpticalBase* basePtr):
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

int CameraController::run(){
   bool running = true;
   View view;

   while (running){
      view.show_menu_camera();
      int choice = safeInputInt();
      switch (choice){
      case 1: {
         string result = basePtr->powerOn();
         basePtr->displayImage(result);
         break;
      }
      case 2: {
         string result = basePtr->powerOff();
         basePtr->displayImage(result);
         break;
      }
      case 3: {
         double zoomLevel;
         cout << "Введіть рівень збільшення: ";
         zoomLevel = safeInputDouble();
         camera.adjustZoom(zoomLevel);
         break;
      }
      case 4: {
         camera.printInfo();
         break;
      }
      case 5: {
         PhotoCamera* copyCamera = new PhotoCamera(camera, "CopiedCamera");
         cout << "Копія камери створена:\n";
         copyCamera->printInfo();
         delete copyCamera;
         break;
      }
      case 6: {
         double zoomLevel;
         cout << "Введіть число: ";
         zoomLevel = safeInputDouble();
         PhotoCamera::set_max_zoom_level(zoomLevel);
         cout << "Max zoom level: " << PhotoCamera::get_max_zoom_level() << "x" << endl;
         break;
      }
      case 7: {
         cout << "Max zoom level: " << PhotoCamera::get_max_zoom_level() << "x" << endl;
         break;
      }
      case 8: {
         camera.capturePhoto();
         break;
      }
      case 9: {
         view.show_menu_camera_shoting_mode();
         int modeChoice;
         cin >> modeChoice;
         switch (modeChoice){
         case 1:
            camera.setShootingMode("Auto");
            break;
         case 2:
            camera.setShootingMode("Portrait");
            break;
         case 3:
            camera.setShootingMode("Night");
            break;
         default:
            cout << "Невірний вибір режиму. Залишено поточний режим.\n";
            break;
         }
         break;
      }
      case 0:
         running = false;
         break;
      }
   }
   return 0;
}
