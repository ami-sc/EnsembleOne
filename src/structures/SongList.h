#ifndef SONGLIST_H
#define SONGLIST_H

#include "src/gui/Song.h"

class Song;

class SongList
{
    public:
        void addSong (Song* new_song);

        inline Song* getHead () { return _head; }
        inline int   getSize () { return _size; }

    private:
        Song* _head = nullptr;
        Song* _tail = nullptr;
        int   _size = 0;
};

#endif
