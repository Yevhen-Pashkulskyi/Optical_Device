#include "entity/device.h"

int main() {
    // використання статичного методу для максимального значення для всіх обєєктів
    OpticalDevice::set_max_zoom_level(10.0);
    OpticalDevice telescope("SkyWatcher", 900, 100, 3000);

    int choice;
    bool running = true;

    while (running) {
        std::cout << "\n=== Меню управління OpticalDevice ===\n";
        std::cout << "1. Увімкнути прилад\n";
        std::cout << "2. Вимкнути прилад\n";
        std::cout << "3. Змінити збільшення\n";
        std::cout << "4. Відобразити інформацію\n";
        std::cout << "5. Копіювати прилад\n";
        std::cout << "0. Вийти\n";
        std::cout << "Оберіть дію: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string result = telescope.powerOn();
                telescope.displayImage(result);
                break;
            }
            case 2: {
                std::string result = telescope.powerOff();
                telescope.displayImage(result);
                break;
            }
            case 3: {
                double zoomLevel;
                std::cout << "Введіть рівень збільшення: ";
                std::cin >> zoomLevel;
                telescope.adjustZoom(zoomLevel);
                break;
            }
            case 4:
                telescope.printInfo();
                break;
            case 5: {
                OpticalDevice *copyTelescope = new OpticalDevice(telescope, "WatcherSky");
                std::cout << "Копія створена:\n";
                copyTelescope->printInfo();
                delete copyTelescope;
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
