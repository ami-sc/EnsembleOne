#ifndef PLAYLISTLIST_H
#define PLAYLISTLIST_H

#include "src/gui/Playlist.h"

class PlaylistList
{
    public:
        void addPlaylist (Playlist* new_song);

        inline Playlist* getHead () { return _head; }
        inline int       getSize () { return _size; }

    private:
        Playlist* _head = nullptr;
        Playlist* _tail = nullptr;
        int       _size = 0;
};

#endif
