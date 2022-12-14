#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>

#include <QString>
#include <QStringList>
#include <QHeaderView>

#include "src/database/Database.h"
#include "src/gui/MainWindow.h"
#include "src/gui/AddDialog.h"
#include "src/gui/Playlist.h"
#include "src/gui/SongTable.h"
#include "src/gui/Song.h"
#include "src/structures/PlaylistList.h"

class MainWindow;
class SongTable;

class PlaylistView : public QWidget
{
    public:
        PlaylistView  (MainWindow* window);
        ~PlaylistView ();

        void addPlaylist    ();
        void deletePlaylist (QString playlist);
        void showSongTable  ();

        void playSong (Song* song, SongList* play_list, int idx);

        void updateSongCount ();

    private:
        void setDefaultText      ();
        void removeDefaultText   ();
        void buildPlaylistColumn ();
        void clearPlaylistColumn ();

        MainWindow*  _window = nullptr;
        QHBoxLayout* _layout = nullptr;

        /* Playlist Sidebar */

        QWidget*     sidebar         = nullptr;
        QVBoxLayout* sidebar_layout  = nullptr;
        QScrollArea* scroll_area     = nullptr;
        QWidget*     playlist_column = nullptr;
        QVBoxLayout* playlist_layout = nullptr;
        QPushButton* add_button      = nullptr;

        PlaylistList* playlist_list   = nullptr;
        Playlist*     active_playlist = nullptr;

        QLabel* no_playlists = nullptr;

        int n_playlists = 0;

        /* Song Table */

        QWidget*     default_label  = nullptr;
        QHBoxLayout* default_layout = nullptr;
        QLabel*      default_text   = nullptr;
        SongTable*   song_table     = nullptr;
};

#endif
