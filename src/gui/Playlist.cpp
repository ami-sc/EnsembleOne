#include "Playlist.h"

Playlist::Playlist (string name)
{
    setFixedSize(200, 100);
    setStyleSheet(INACTIVE_PLAYLIST_CSS);

    _layout  = new QHBoxLayout {};
    _descr   = new QWidget     {};
    _dlayout = new QVBoxLayout {};
    _name    = new QLabel      {QString::fromStdString(name)};
    _songs   = new QLabel      {};
    _artwork = new QIcon       {"assets/default_playlist.jpg"};
    _artbox  = new QLabel      {};

    _artbox -> setPixmap(_artwork -> pixmap(QSize(80, 80)));

    _descr -> setLayout(_dlayout);
    _dlayout -> addWidget(_name);
    _dlayout -> addWidget(_songs);
    _dlayout -> setSpacing (0);
    _dlayout -> setMargin  (0);
    _dlayout -> setAlignment(Qt::AlignLeft);

    QFont _font = _name -> font();
    _font.setBold(true);
    _name -> setFont(_font);

    _layout -> addWidget(_artbox);
    _layout -> addWidget(_descr);

    setLayout(_layout);
}

void Playlist::setActiveCSS (bool active)
{
    if (active)
    {
        setStyleSheet(ACTIVE_PLAYLIST_CSS);
    }
    else
    {
        setStyleSheet(INACTIVE_PLAYLIST_CSS);
    }
}

QString Playlist::getPlaylistTitle ()
{
    return _name -> text();
}
