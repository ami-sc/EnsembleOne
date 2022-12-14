#ifndef EXPANDEDALBUM_H
#define EXPANDEDALBUM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QMediaPlayer>

#include <string>
    using std::string;

#include "src/database/Database.h"
#include "Song.h"
#include "MusicPlayer.h"
#include "src/structures/SongList.h"

class ExpandedAlbum : public QWidget
{
    public:
        ExpandedAlbum (QString title, QString artist, string art_b64,
                       MusicPlayer* music_player);

        void playSong ();

    private:
        QVBoxLayout* _layout     = nullptr;

        QWidget*     _tracklist        = nullptr;
        QHBoxLayout* _tracklist_layout = nullptr;

        QWidget*     _column_a = nullptr;
        QWidget*     _column_b = nullptr;
        QVBoxLayout* _layout_a = nullptr;
        QVBoxLayout* _layout_b = nullptr;

        int _nsongs = 0;

        QLabel*      _title  = nullptr;
        QLabel*      _artist = nullptr;

        string _artist_txt;
        string _artwork;

        MusicPlayer* _player = nullptr;

        SongList* song_list = nullptr;
};

#endif
