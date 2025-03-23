#include "entity/device.cpp"

int main() {
    OpticalDevice telescope("SkyWatcher", 900, 100, 3000); // надав критерії
    telescope.printInfo(); // вивів всі данні що є зараз у об'єкта

    telescope.displayImage(telescope.powerOn()); // увімкнув та вивів на екран
    telescope.displayImage(telescope.adjustZoom(10)); //змінив зум та вивів на екран
    telescope.printInfo(); // данні о приладі
    telescope.displayImage(telescope.powerOff()); // вимкнув та вивів на екран


    OpticalDevice *copyTelescope = new OpticalDevice(telescope, "WatcherSky");
    copyTelescope->printInfo(); // данні о приладі
    //всі подалі дії такі ж самі як у першого телескопу
    copyTelescope->displayImage(copyTelescope->powerOn());
    copyTelescope->displayImage(copyTelescope->adjustZoom(30));
    copyTelescope->printInfo();
    copyTelescope->displayImage(copyTelescope->powerOff());
    delete copyTelescope;
    return 0;
}
