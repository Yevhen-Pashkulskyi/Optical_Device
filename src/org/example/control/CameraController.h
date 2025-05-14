#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../entity/DeviceBase.h"
#include "../entity/PhotoCamera.h"

class CameraController{
   PhotoCamera &camera;
   OpticalBase *basePtr;
public:
   CameraController(PhotoCamera &camera, OpticalBase *basePtr);
   int run();
};

#endif //CONTROLLER_H
