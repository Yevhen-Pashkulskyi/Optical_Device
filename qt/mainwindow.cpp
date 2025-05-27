#include "../qt/mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include "../include/opticaldevice.h"

OpticalDevice *device = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->btnCreate, &QPushButton::clicked, this, [=] {
        device = new OpticalDevice("SkyWatcher", 900, 100, 3000);
        ui->textOutput->append("Об’єкт створено.");
    });

    connect(ui->btnPowerOn, &QPushButton::clicked, this, [=] {
        if (device)
            ui->textOutput->append(device->powerOn());
    });

    connect(ui->btnPowerOff, &QPushButton::clicked, this, [=] {
        if (device)
            ui->textOutput->append(device->powerOff());
    });

    connect(ui->btnInfo, &QPushButton::clicked, this, [=] {
        if (device)
            ui->textOutput->append(device->getInfo());
    });

    connect(ui->btnDelete, &QPushButton::clicked, this, [=] {
        if (device) {
            delete device;
            device = nullptr;
            ui->textOutput->append("Об’єкт видалено.");
        }
    });
}

MainWindow::~MainWindow() {
    delete ui;
    delete device;
}
