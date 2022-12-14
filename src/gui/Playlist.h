#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QFont>
#include <QString>

#include <string>
    using std::string;

const QString INACTIVE_PLAYLIST_CSS
{
    "QPushButton {"
    "    padding: 6px;"
    "    border-radius: 6px; }"
    "QPushButton::hover {"
    "    background-color: #4481eb;"
    "    padding: 6px;"
    "    border-radius: 6px; }"
    "QPushButton::pressed {"
    "    background: QLinearGradient(x1: 0, y1: 0, x2: 1, y2: 0,"
    "                                stop: 0 #4481eb,"
    "                                stop: 1 #04befe);"
    "    padding: 6px;"
    "    border-radius: 6px; }"
};

const QString ACTIVE_PLAYLIST_CSS
{
    "QPushButton {"
    "    background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,"
    "                                  stop: 0 #4481eb,"
    "                                  stop: 1 #04befe );"
    "    padding: 6px;"
    "    border-radius: 6px; }"
    "QPushButton::hover {"
    "    background-color: #4481eb;"
    "    padding: 6px;"
    "    border-radius: 6px; }"
    "QPushButton::pressed {"
    "    background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,"
    "                                  stop: 0 #4481eb,"
    "                                  stop: 1 #04befe );"
    "    padding: 6px;"
    "    border-radius: 6px; }"
};

class Playlist : public QPushButton
{
    public:
        Playlist (string name);

        void setActiveCSS (bool active);

        void setSongNumber (int song_num)
        {
            _songs -> setText(QString::number(song_num) + " Songs");
        }

        QString getPlaylistTitle ();

        /** SongList Methods **/
        inline Playlist* getNext ()                   { return _next;     }
        inline void      setNext (Playlist* new_next) { _next = new_next; }

    private:
        QHBoxLayout* _layout  = nullptr;
        QWidget*     _descr   = nullptr;
        QVBoxLayout* _dlayout = nullptr;
        QLabel*      _name    = nullptr;
        QLabel*      _songs   = nullptr;
        QLabel*      _artbox  = nullptr;
        QIcon*       _artwork = nullptr;

        /** PlaylistList Attributes **/
        Playlist* _next = nullptr;
};

#endif
