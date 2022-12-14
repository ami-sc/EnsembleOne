#include "AlbumList.h"

void AlbumList::addAlbum (Album* new_album)
{
    /* Check if the list is not empty. */
    if (_head)
    {
        _tail -> setNext(new_album);
        _tail = new_album;
    }
    /* If the list is empty, the new Album becomes the head. */
    else
    {
        _head = new_album;
        _tail = _head;
    }

    _size++;
}
