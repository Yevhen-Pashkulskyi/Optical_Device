/**
 * Головний файл де запускається сама програма
 */
#include "entity/device.h"
#include <string>

int main(){
   OpticalDevice device("SkyWatcher", 900, 100, 3000);
   Camera camera("Canon", 50, 35, 800, 24.1, "Auto");

   int choice;
   bool running = true;
   while (running){
      std::cout << "\n=== Меню управління ===\n"
         << "1. Увімкнути прилад\n"
         << "2. Вимкнути прилад\n"
         << "3. Змінити збільшення\n"
         << "4. Відобразити інформацію\n"
         << "5. Копіювати прилад\n"
         << "6. Назначити максимальне значення zoom\n"
         << "7. Максимальне значення zoom\n"
         << "8. Зробити фото (тільки для камери)\n"
         << "0. Вийти\n"
         << "Оберіть дію: ";
      std::cin >> choice;

      OpticalDevice* selectedDevice = &device;
      int deviceChoice;
      if (choice != 0 && choice != 6 && choice != 7){
         std::cout << "Оберіть прилад:\n"
            << "  1 - OpticalDevice\n"
            << "  2 - Camera\n"
            << "Введіть номер: ";
         std::cin >> deviceChoice;
         if (deviceChoice == 2){ selectedDevice = &camera; }
         else if (deviceChoice != 1){
            std::cout << "Невірний вибір приладу. Використано OpticalDevice за замовчуванням.\n";
         }
      }
      else if (choice == 0){
         running = false;
         continue;
      }
      switch (choice){
      case 1: {
         std::string result = selectedDevice->powerOn();
         selectedDevice->displayImage(result);
         break;
      }
      case 2: {
         std::string result = selectedDevice->powerOff();
         selectedDevice->displayImage(result);
         break;
      }
      case 3: {
         double zoomLevel;
         std::cout << "Введіть рівень збільшення: ";
         std::cin >> zoomLevel;
         selectedDevice->adjustZoom(zoomLevel);
         break;
      }
      case 4: {
         selectedDevice->printInfo();
         break;
      }
      case 5: {
         if (selectedDevice == &camera){
            Camera* copyCamera = new Camera(static_cast<const Camera&>(*selectedDevice), "CopiedCamera");
            std::cout << "Копія камери створена:\n";
            copyCamera->printInfo();
            delete copyCamera;
         }
         else{
            OpticalDevice* copyDevice = new OpticalDevice(*selectedDevice, "CopiedSkyWatcher");
            std::cout << "Копія створена:\n";
            copyDevice->printInfo();
            delete copyDevice;
         }
         break;
      }
      case 6: {
         double zoomLevel;
         std::cout << "Введіть число: ";
         std::cin >> zoomLevel;
         OpticalDevice::set_max_zoom_level(zoomLevel);
         std::cout << "Max zoom level: " << OpticalDevice::get_max_zoom_level() << "x" << std::endl;
         break;
      }
      case 7: {
         std::cout << "Max zoom level: " << OpticalDevice::get_max_zoom_level() << "x" << std::endl;
         break;
      }
      case 8: {
         if (selectedDevice == &camera){ static_cast<Camera*>(selectedDevice)->capturePhoto(); }
         else{ std::cout << "Ця дія доступна тільки для камери.\n"; }
         break;
      }
      default:
         std::cout << "Невірний вибір. Спробуйте ще раз.\n";
         break;
      }
   }
   return 0;
}
