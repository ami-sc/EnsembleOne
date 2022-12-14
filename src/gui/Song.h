#ifndef SONG_H
#define SONG_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QMediaPlayer>

#include <iostream>
#include <string>
    using std::string;

#include "src/gui/MusicPlayer.h"

const QString SONG_CSS
{
    "QPushButton {"
    "    padding: 6px;"
    "    border-radius: 6px; }"
    "QPushButton::hover {"
    "    background-color: #8FD3F4;"
    "    padding: 6px;"
    "    border-radius: 6px; }"
    "QPushButton::pressed {"
    "    background-color: #4FACFE;"
    "    padding: 6px;"
    "    border-radius: 6px; }"
};

class MusicPlayer;

class Song : public QPushButton
{
    public:
        Song ();
        Song (string file_path, int index, string title, string length);
        Song (string title, string artist, string album, string length,
              string file_path);
        Song (string title, string artist, string length, string art_b64);

        void setIndex  (int index);
        void setTitle  (QString title);
        void setTitle  (string title);
        void setLength (QString length);
        void setLength (string length);

        void setMusicPlayer (MusicPlayer* music_player) { _player = music_player; }

        void playSong ();

        /** SongList Methods **/
        inline Song* getNext ()               { return _next;     }
        inline void  setNext (Song* new_next) { _next = new_next; }
        inline Song* getPrev ()               { return _prev;     }
        inline void  setPrev (Song* new_prev) { _prev = new_prev; }

        inline void setArtist     (string artist)  { _artist  = artist;  }
        inline void setArtworkB64 (string art_b64) { _artwork = art_b64; }

        inline string getFile   () { return _file;    }
        inline string getTitle  () { return _song;    }
        inline string getAlbum  () { return _album;   }
        inline string getArtist () { return _artist;  }
        inline string getLength () { return _slength; }
        inline string getArtB64 () { return _artwork; }
        inline int    getIndex  () { return (_index -> text()).toInt(); }

    private:
        QHBoxLayout* _layout = nullptr;
        QLabel*      _index  = nullptr;
        QLabel*      _title  = nullptr;
        QLabel*      _length = nullptr;

        string _file    = "";
        string _song    = "";
        string _album   = "";
        string _artist  = "";
        string _slength = "";
        string _artwork = "";

        MusicPlayer* _player = nullptr;

        /** SongList Attributes **/
        Song* _next = nullptr;
        Song* _prev = nullptr;
};

#endif
