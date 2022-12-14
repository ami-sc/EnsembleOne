#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
// #include <QFrame>
#include <QIcon>
#include <QColor>
#include <QPalette>
#include <QLinearGradient>
#include <QMediaPlayer>

#include <iostream>

#include "src/gui/MusicPlayer.h"

#include "src/gui/ViewManager.h"

// #include "src/gui/SideBar.h"
// // #include "src/gui/LibraryView.h"
// #include "src/gui/PlaylistView.h"
// #include "src/gui/ImportView.h"
// #include "src/gui/SearchView.h"
// #include "src/structures/AlbumList.h"

#include "src/database/Database.h"

class ViewManager;

class MainWindow : public QMainWindow
{
    public:
        MainWindow ();

        inline MusicPlayer* getMusicPlayer () { return __player; };

        // void setActiveView ();
        void resizeEvent   (QResizeEvent* event);

    private:
        /* Central Widget of Main Window */
        QWidget*     __center  = nullptr;
        QVBoxLayout* __clayout = nullptr;

        ViewManager* view_manager = nullptr;

        /* Main Widget of Main Window */
        // QWidget*     __main    = nullptr;
        // QHBoxLayout* __mlayout = nullptr;

        /* Music Player */
        MusicPlayer* __player = nullptr;

        /* Sidebar Elements */
        // SideBar*     __sidebar         = nullptr;
        // QVBoxLayout* __sidebar_layout  = nullptr;
        // QPushButton* __library_button  = nullptr;
        // QPushButton* __playlist_button = nullptr;
        // QPushButton* __import_button   = nullptr;
        // QPushButton* __search_button   = nullptr;

        // /* Active View */
        // QWidget*     __active_view   = nullptr;
        // QScrollArea* __active_scroll = nullptr;
        // QPushButton* __active_button = nullptr;

        // AlbumList* _album_list = nullptr;

        // int _active_idx = 0;

        // QFrame*      _main    = nullptr;
        // QWidget*     _center  = nullptr;
        // QVBoxLayout* _mlayout = nullptr;
        // QHBoxLayout* _clayout = nullptr;
        // MusicPlayer* _player  = nullptr;

        // LibraryView* _lview   = nullptr;
        // QScrollArea* _lscroll = nullptr;

        // PlaylistView* _pview  = nullptr;
};

#endif
