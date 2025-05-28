#include "../qt/mainwindow.h"
#include "../ui/ui_mainwindow.h" // Підключення згенерованого UI файлу
#include "../include/opticaldevice.h"

// Глобальний вказівник на об'єкт OpticalDevice
OpticalDevice* device = nullptr;
// Конструктор головного вікна
MainWindow::MainWindow(QWidget* parent)
   : QMainWindow(parent), ui(new Ui::MainWindow){
   ui->setupUi(this); // Налаштування UI елементів вікна

   // Підключення слоту до сигналу кліку кнопки "Створити"
   connect(ui->btnCreate, &QPushButton::clicked, this, [=]{
      device = new OpticalDevice("SkyWatcher", 900, 100, 3000);
      ui->textOutput->append("✅" + device->getModelName() + " створено.");
   });
   // Підключення слоту до сигналу кліку кнопки "Увімкнути"
   connect(ui->btnPowerOn, &QPushButton::clicked, this, [=]{
      if (device){
         if (device->getPowerStatus()){ ui->textOutput->append(device->getModelName() + " вже увімкнено"); }
         else{ ui->textOutput->append("\n" + device->powerOn()); }
      }
      else{ ui->textOutput->append("❗️ Пристрій не створено.\n"); }
   });
   // Підключення слоту до сигналу кліку кнопки "Вимкнути"
   connect(ui->btnPowerOff, &QPushButton::clicked, this, [=]{
      if (device){
         if (!device->getPowerStatus()){ ui->textOutput->append(device->getModelName() + " вже вимкнено\n"); }
         else{ ui->textOutput->append(device->powerOff()); }
      }
   });
   // Підключення слоту до сигналу кліку кнопки "Інфо"
   connect(ui->btnInfo, &QPushButton::clicked, this, [=]{
      if (device)
         ui->textOutput->append(device->getInfo());
   });
   // Підключення слоту до сигналу кліку кнопки "Видалити"
   connect(ui->btnDelete, &QPushButton::clicked, this, [=]{
      if (device){
         ui->textOutput->append(device->getModelName() + "❌ видалено.\n");
         delete device;
         device = nullptr;
      }
   });
   // Підключення слоту до сигналу кліку кнопки "Змінити збільшення"
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
// Деструктор вікна
MainWindow::~MainWindow(){
   delete ui;
   delete device;
}
