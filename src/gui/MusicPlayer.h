#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QSize>
#include <QPalette>
#include <QSlider>
#include <QString>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QApplication>
#include <QFontMetrics>

#include <string>
    using std::string;
#include <iostream>

#include "src/gui/Song.h"
#include "src/structures/SongList.h"
#include "src/database/Database.h"

const QString _buttoncss
{
    "QPushButton {"
    "    padding: 6px;"
    "    border-radius: 0px; }"
    "QPushButton::hover {"
    "    background-color: #8FD3F4;"
    "    border: 1px solid rgba(0, 0, 0, 1);"
    "    padding: 6px;"
    "    border-radius: 0px; }"
    "QPushButton::pressed {"
    "    background-color: #4FACFE;"
    "    border: 1px solid #4FACFE;"
    "    padding: 6px;"
    "    border-radius: 0px; }"
};

class SongList;
class Song;

class MusicPlayer : public QWidget
{
    public:
        MusicPlayer  ();
        ~MusicPlayer ();

        void playSong      (QString file_path, QString song, QString artist,
                            QString length, string artwork_b64);
        void setSongList   (SongList* song_list, int song_idx);
        void resetSongList ();
        void pauseSong     ();
        void resumeSong    ();
        void previousSong  ();
        void nextSong      ();

    private:
        QHBoxLayout* _layout = nullptr;

        QPushButton* back_button = nullptr;
        QPushButton* play_button = nullptr;
        QPushButton* next_button = nullptr;

        QLabel*      album_box   = nullptr;
        QIcon*       album_art   = nullptr;
        QWidget*     info_box    = nullptr;
        QVBoxLayout* info_layout = nullptr;
        QLabel*      song_name   = nullptr;
        QLabel*      artist_name = nullptr;

        QPixmap* _artwork = nullptr;

        QLabel*  current_pos  = nullptr;
        QSlider* progress_bar = nullptr;
        QLabel*  duration     = nullptr;

        QPushButton* loop_button    = nullptr;
        QPushButton* shuffle_button = nullptr;

        QMediaPlayer* _player   = nullptr;
        string*       _playlist = nullptr;
        int           _current  = 0;
        int           _psize    = 0;

        bool is_paused = false;

        /* Button Icons */
        QIcon back_icon  {"assets/icons/back.png"};
        QIcon play_icon  {"assets/icons/play.png"};
        QIcon next_icon  {"assets/icons/next.png"};
        QIcon pause_icon {"assets/icons/pause.png"};

        QLabel* logo_box = nullptr;
        QIcon* en_logo = nullptr;

        /* Private Methods */
        void playback ();
        void updatePositionLabel ();
        void updateDuration ();
        void updatePosition ();
        void clearPlaylist  ();
};

#endif
