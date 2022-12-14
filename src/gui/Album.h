#ifndef ALBUM_H
#define ALBUM_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QPixmap>
#include <QFontMetrics>

#include <string>
    using std::string;

const QString INACTIVE_ALBUM_CSS
{
    "QPushButton {"
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

const QString ACTIVE_ALBUM_CSS
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

class Album : public QPushButton
{
    public:
        // Album  (QString title, QString artist, QString artpath);
        Album  (string title, string artist, string art_b64);
        ~Album ();

        inline void setRow (int row) { _row = row; }
        inline void setCol (int col) { _col = col; }

        inline int getRow () { return _row; }
        inline int getCol () { return _col; }

        inline QString getAlbumTitle  () { return *_full_title;      }
        inline QString getAlbumArtist () { return _artist -> text(); }
        inline string  getArtworkB64  () { return artwork_b64;       }

        bool getExpandedState ();
        void setExpandedState (bool expanded);

        /** AlbumList Methods **/
        inline Album* getNext ()                { return _next;     }
        inline void   setNext (Album* new_next) { _next = new_next; }

    private:
        QVBoxLayout* _layout  = nullptr;
        QLabel*      _title   = nullptr;
        QLabel*      _artist  = nullptr;
        QLabel*      _artbox  = nullptr;
        QIcon*       _artwork = nullptr;

        QString* _full_title = nullptr;

        string artwork_b64 = "";
        QPixmap* _img = nullptr;

        bool _expandedstate = false;

        int _row = 0;
        int _col = 0;

        /** AlbumList Attributes **/
        Album* _next = nullptr;
};

#endif
