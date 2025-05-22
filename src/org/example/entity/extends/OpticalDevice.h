#ifndef OPTICALDEVICE_H
#define OPTICALDEVICE_H

#include "../DeviceBase.h"

class OpticalDevice : public DeviceBase {
protected:
   double currentZoom; // поточний рівень збільшення
   static double max_zoom_level; // максимальне збільшення

public:
   OpticalDevice(const char *model, double focalLength, double aperture, double wt);
   OpticalDevice(const OpticalDevice &other, const char *name);
   ~OpticalDevice() override;
   std::string powerOn() override;
   std::string powerOff() override;
   void displayImage(const std::string &info) const override;
   void printInfo() const override;
   void configureDevice() override;
   static void set_max_zoom_level(double level);
   static double get_max_zoom_level();
   void adjustZoom(double level_zoom);
   double getFocusLength() const;
};


#endif //OPTICALDEVICE_H
