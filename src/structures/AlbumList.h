#ifndef ALBUMLIST_H
#define ALBUMLIST_H

#include "src/gui/Album.h"

class AlbumList
{
    public:
        // AlbumList ();

        void addAlbum (Album* new_album);

        inline Album* getHead () { return _head; }
        inline int    getSize () { return _size; }

    private:
        Album* _head = nullptr;
        Album* _tail = nullptr;
        int    _size = 0;
};

#endif
