/**
 * Головний файл де запускається сама програма
 */
#include "entity/device.h"
#include <string>

int main() {
   Camera camera("Canon", 50, 35, 800, 24.1, "Auto");
   OpticalBase* basePtr = &camera;

   int choice;
   bool running = true;
   while (running) {
      std::cout << "\n=== Меню управління камерою ===\n"
                << "1. Увімкнути камеру\n"
                << "2. Вимкнути камеру\n"
                << "3. Змінити збільшення\n"
                << "4. Відобразити інформацію\n"
                << "5. Копіювати камеру\n"
                << "6. Назначити максимальне значення zoom\n"
                << "7. Максимальне значення zoom\n"
                << "8. Зробити фото\n"
                << "9. Змінити режим зйомки\n"
                << "0. Вийти\n"
                << "Оберіть дію: ";
      std::cin >> choice;

      switch (choice) {
      case 1: {
         std::string result = basePtr->powerOn();
         basePtr->displayImage(result);
         break;
      }
      case 2: {
         std::string result = basePtr->powerOff();
         basePtr->displayImage(result);
         break;
      }
      case 3: {
         double zoomLevel;
         std::cout << "Введіть рівень збільшення: ";
         std::cin >> zoomLevel;
         camera.adjustZoom(zoomLevel);
         break;
      }
      case 4: {
         camera.printInfo();
         break;
      }
      case 5: {
         Camera* copyCamera = new Camera(camera, "CopiedCamera");
         std::cout << "Копія камери створена:\n";
         copyCamera->printInfo();
         delete copyCamera; // Видаляємо копію одразу
         break;
      }
      case 6: {
         double zoomLevel;
         std::cout << "Введіть число: ";
         std::cin >> zoomLevel;
         Camera::set_max_zoom_level(zoomLevel);
         std::cout << "Max zoom level: " << Camera::get_max_zoom_level() << "x" << std::endl;
         break;
      }
      case 7: {
         std::cout << "Max zoom level: " << Camera::get_max_zoom_level() << "x" << std::endl;
         break;
      }
      case 8: {
         camera.capturePhoto();
         break;
      }
      case 9: {
         std::cout << "Оберіть режим зйомки:\n"
                   << "  1 - Auto\n"
                   << "  2 - Portrait\n"
                   << "  3 - Night\n"
                   << "Введіть номер: ";
         int modeChoice;
         std::cin >> modeChoice;
         switch (modeChoice) {
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
               std::cout << "Невірний вибір режиму. Залишено поточний режим.\n";
               break;
         }
         break;
      }
      case 0:
         running = false;
         break;
      default:
         std::cout << "Невірний вибір. Спробуйте ще раз.\n";
         break;
      }
   }

   return 0;
}