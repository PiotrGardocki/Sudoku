#include "MainWindow.hpp"
#include <QApplication>

#define CATCH_CONFIG_RUNNER
#include "vendor/catch.hpp"

int main(int argc, char *argv[])
{
    //Catch::Session().run(argc, argv);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
