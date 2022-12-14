#ifndef SONGTABLE_H
#define SONGTABLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QStringList>
#include <QHeaderView>

#include "src/database/Database.h"
#include "src/gui/ConfirmDialog.h"
#include "src/gui/SongsDialog.h"
#include "src/gui/PlaylistView.h"
#include "src/gui/Song.h"
#include "src/gui/TableButton.h"
#include "src/structures/SongList.h"
#include "src/structures/PlaylistList.h"

class PlaylistView;

class SongTable : public QWidget
{
    public:
        SongTable (QString playlist, PlaylistView* view);

        void addSongs       ();
        void deletePlaylist ();

        void playSong ();

    private:
        void buildSongTable ();
        void clearSongList  ();

        PlaylistView* _view   = nullptr;;
        QVBoxLayout*  _layout = nullptr;

        /* Playlist Header */

        QWidget*     playlist_header = nullptr;
        QHBoxLayout* header_layout   = nullptr;
        QLabel*      playlist_title  = nullptr;
        QPushButton* add_button      = nullptr;
        QPushButton* delete_button   = nullptr;

        QIcon add_icon    {"assets/icons/songs.png"};
        QIcon delete_icon {"assets/icons/delete.png"};

        /* Song Table */

        SongList*     song_list  = nullptr;
        QTableWidget* song_table = nullptr;
};

#endif
