/**
 * Головний файл де запускається сама програма
 */

#include "entity/DeviceBase.h"
#include  "control/Controller.h"
#include "entity/extends/PhotoCamera.h"

int main() {
   PhotoCamera camera("Canon", 50, 35, 800, 24.1, "Auto");
   DeviceBase* basePtr = &camera;
   Controller controller(camera, basePtr);
   controller.run();
   return 0;
}