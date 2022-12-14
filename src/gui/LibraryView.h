#ifndef LIBRARYVIEW_H
#define LIBRARYVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include <iostream>

#include "src/database/Database.h"
#include "src/gui/MainWindow.h"
#include "src/gui/Album.h"
#include "src/gui/ExpandedAlbum.h"
#include "src/structures/AlbumList.h"

class MainWindow;

class LibraryView : public QWidget
{
    public:
        LibraryView  (MainWindow* parent_window);
        ~LibraryView ();

        void expandAlbum ();
        void resizeView  ();

    private:
        void buildGrid ();
        void clearGrid ();

        MainWindow*  _window = nullptr;

        QScrollArea* scroll_area   = nullptr;
        QHBoxLayout* scroll_layout = nullptr;

        QWidget*     grid        = nullptr;
        QGridLayout* grid_layout = nullptr;

        int n_albums = 0;
        int n_cols   = 0;
        int n_rows   = 0;

        AlbumList* albums = nullptr;

        Album*         expanded_album = nullptr;
        ExpandedAlbum* expanded_view  = nullptr;

        QLabel* default_msg = nullptr;
};

#endif
