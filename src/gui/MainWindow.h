#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "src/gui/MusicPlayer.h"
#include "src/gui/SideBar.h"

class MainWindow : public QMainWindow
{
    public:
        MainWindow ();

    private:
        QWidget*     _main     = nullptr;
        QWidget*     _center   = nullptr;
        QVBoxLayout* _mlayout  = nullptr;
        QHBoxLayout* _clayout  = nullptr;
        MusicPlayer* _player   = nullptr;
        SideBar*     _sidebar  = nullptr;
};

#endif
