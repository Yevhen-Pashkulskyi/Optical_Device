#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow> // Підключення базового класу для головного вікна

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow; // Оголошення класу UI, який генерується Qt
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT // Макрос, необхідний для використання сигналів і слотів Qt

public:
    // Конструктор: ініціалізує головне вікно
    MainWindow(QWidget *parent = nullptr);
    // Деструктор: очищає ресурси, пов'язані з вікном
    ~MainWindow();

private:
    // Вказівник на об'єкт UI, що містить елементи інтерфейсу
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
