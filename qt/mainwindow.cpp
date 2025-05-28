#include "../qt/mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include "../include/opticaldevice.h"

OpticalDevice* device = nullptr;

MainWindow::MainWindow(QWidget* parent)
   : QMainWindow(parent), ui(new Ui::MainWindow){
   ui->setupUi(this);

   connect(ui->btnCreate, &QPushButton::clicked, this, [=]{
      device = new OpticalDevice("SkyWatcher", 900, 100, 3000);
      ui->textOutput->append("✅" + device->getModelName() + " створено.");
   });

   connect(ui->btnPowerOn, &QPushButton::clicked, this, [=]{
      if (device){
         if (device->getPowerStatus()){ ui->textOutput->append(device->getModelName() + " вже увімкнено"); }
         else{ ui->textOutput->append("\n" + device->powerOn()); }
      }
      else{ ui->textOutput->append("❗️ Пристрій не створено.\n"); }
   });

   connect(ui->btnPowerOff, &QPushButton::clicked, this, [=]{
      if (device){
         if (!device->getPowerStatus()){ ui->textOutput->append(device->getModelName() + " вже вимкнено\n"); }
         else{ ui->textOutput->append(device->powerOff()); }
      }
   });

   connect(ui->btnInfo, &QPushButton::clicked, this, [=]{
      if (device)
         ui->textOutput->append(device->getInfo());
   });

   connect(ui->btnDelete, &QPushButton::clicked, this, [=]{
      if (device){
         ui->textOutput->append(device->getModelName() + "❌ видалено.\n");
         delete device;
         device = nullptr;
      }
   });

   connect(ui->btnChangeZoom, &QPushButton::clicked, this, [=]{
      if (device){
         bool ok;
         double zoomLevel = ui->lineEdit->text().toDouble(&ok);
         if (ok){
            QString message = device->adjustZoom(zoomLevel);
            ui->textOutput->append(message);
         }
         else{ ui->textOutput->append("\n❗️ Помилка: введіть коректне число для збільшення."); }
      }
      else{ ui->textOutput->append("❗️ Пристрій не створено."); }
   });
}

MainWindow::~MainWindow(){
   delete ui;
   delete device;
}
