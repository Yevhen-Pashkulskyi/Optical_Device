#include "qt/mainwindow.h" // Підключення заголовного файлу головного вікна

#include <QApplication> // Клас для керування GUI додатком
#include <QLocale> // Клас для локалізації
#include <QTranslator> // Клас для перекладів

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Створення об'єкта додатку

    QTranslator translator; // Створення об'єкта для перекладів
    const QStringList uiLanguages = QLocale::system().uiLanguages(); // Отримання системних мов інтерфейсу
    for (const QString &locale : uiLanguages) { // Перебір доступних мов
        const QString baseName = "OpticalProject_" + QLocale(locale).name(); // Формування базового імені файлу перекладу
        if (translator.load(":/i18n/" + baseName)) { // Спроба завантажити переклад
            a.installTranslator(&translator);// Встановлення перекладу для додатку
            break;
        }
    }
    MainWindow w; // Створення об'єкта головного вікна
    w.show(); // Відображення головного вікна
    return a.exec(); // Запуск циклу обробки подій додатку
}
