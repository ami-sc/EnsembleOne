#include <QApplication>

#include "src/gui/MainWindow.h"

int main (int argc, char *argv[])
{
    /** Ignore the color schemes and styles of the operating system. **/
    QApplication::setStyle("fusion");
    QApplication::setDesktopSettingsAware(false);

    QApplication Ensemble(argc, argv);

    /** Build the Main Window of the application. **/
    MainWindow main_window;
    main_window.show();

    return Ensemble.exec();
}
