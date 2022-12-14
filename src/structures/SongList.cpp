#include "SongList.h"

void SongList::addSong (Song* new_song)
{
    /* Check if the list is not empty. */
    if (_head)
    {
        _tail -> setNext(new_song);
        new_song -> setPrev(_tail);
        _tail = new_song;
    }
    /* If the list is empty, the new Song becomes the head. */
    else
    {
        _head = new_song;
        _tail = _head;
    }

    _size++;
}

