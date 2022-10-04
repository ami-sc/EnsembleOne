#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>

#include <QIcon>
#include <QSize>
#include <QPalette>

class MusicPlayer : public QWidget
{
    public:
        MusicPlayer  ();
        ~MusicPlayer ();

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

        QLabel*       current_pos  = nullptr;
        QProgressBar* progress_bar = nullptr;
        QLabel*       duration     = nullptr;

        QPushButton* loop_button    = nullptr;
        QPushButton* shuffle_button = nullptr;
};

#endif
