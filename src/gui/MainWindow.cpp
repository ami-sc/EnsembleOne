#include "MainWindow.h"

/**
 * @brief       Constructs the main window of the application.
 */
MainWindow::MainWindow ()
{
    /** Allocate memory for the main window components. **/
    _main    = new QWidget     {};
    _center  = new QWidget     {};
    _mlayout = new QVBoxLayout {};
    _clayout = new QHBoxLayout {};
    _player  = new MusicPlayer {};
    _sidebar = new SideBar     {};

    _main   -> setLayout(_mlayout);
    _center -> setLayout(_clayout);

    /** Set default window properties. **/
    setWindowTitle("Ensemble");
    setMinimumSize(800, 400);
    setCentralWidget(_main);

    /** Built the Music Player. **/
    _mlayout -> addWidget(_player);

    /** Build the Side Bar. **/
    _clayout -> addWidget(_sidebar);
    _mlayout -> addWidget(_center);
}
