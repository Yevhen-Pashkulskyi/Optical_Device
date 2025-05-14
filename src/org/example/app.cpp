/**
 * Головний файл де запускається сама програма
 */

#include "entity/DeviceBase.h"
#include  "control/CameraController.h"
#include "entity/PhotoCamera.h"

int main() {
   PhotoCamera camera("Canon", 50, 35, 800, 24.1, "Auto");
   OpticalBase* basePtr = &camera;
   CameraController controller(camera, basePtr);
   controller.run();
   return 0;
}