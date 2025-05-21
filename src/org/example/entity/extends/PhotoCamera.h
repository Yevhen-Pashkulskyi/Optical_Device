#ifndef PHOTOCAMERA_H
#define PHOTOCAMERA_H
#include "OpticalDevice.h"
#include <string>


class PhotoCamera : public OpticalDevice {
   double megapixels; // кількість мегапікселів
   char *shootingMode; // режим зйомки

public:
   PhotoCamera(const char *model, double focalLength, double aperture, double wt, double mp, const char *mode);
   PhotoCamera(const PhotoCamera &other, const char *name);
   ~PhotoCamera() override;
   std::string powerOn() override;
   std::string powerOff() override;
   void displayImage(const std::string &info) const override;
   void printInfo() const override;
   void configureDevice() override;
   void capturePhoto() const;
   void setShootingMode(const char *mode);
   double getMegapixels() const;
};


#endif //PHOTOCAMERA_H
