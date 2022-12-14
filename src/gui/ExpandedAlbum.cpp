#include "ExpandedAlbum.h"

ExpandedAlbum::ExpandedAlbum (QString title, QString artist, string art_b64,
                              MusicPlayer* music_player)
{
    _layout  = new QVBoxLayout {};
    _player  = music_player;
    _artwork = art_b64;
    _artist_txt = artist.toStdString();

    _tracklist        = new QWidget     {};
    _tracklist_layout = new QHBoxLayout {};

    _column_a = new QWidget     {};
    _column_b = new QWidget     {};
    _layout_a = new QVBoxLayout {};
    _layout_b = new QVBoxLayout {};

    _tracklist -> setLayout(_tracklist_layout);
    _column_a  -> setLayout(_layout_a);
    _column_b  -> setLayout(_layout_b);

    _layout_a -> setAlignment(Qt::AlignTop);
    _layout_b -> setAlignment(Qt::AlignTop);

    /* Set background color. */
    QLinearGradient background_gradient {0, 0, (double) width(),
                                               (double) height()};

    background_gradient.setColorAt(0, QColor {"#cfd9df"});
    background_gradient.setColorAt(1, QColor {"#e2ebf0"});

    QPalette background_color = QPalette();

    background_color.setBrush(QPalette::Window, background_gradient);
    setAutoFillBackground(true);
    setPalette(background_color);

    _title  = new QLabel {title};
    _artist = new QLabel {artist};

    /* Set bold font for album title. */
    QFont _font = _title -> font();
    _font.setBold(true);
    _title -> setFont(_font);

    _layout -> addWidget(_title);
    _layout -> addWidget(_artist);

    Database db {};

    song_list = db.getSongList(title.toStdString());

    _nsongs = song_list -> getSize();

    Song* current = song_list -> getHead();

    if (_nsongs > 6)
    {
        int mid_point = _nsongs / 2;

        if (_nsongs % 2)
        {
            mid_point++;
        }

        for (int i = 0; i < mid_point; i++)
        {
            _layout_a -> addWidget(current);
            current -> setMusicPlayer(_player);
            current -> setArtist(_artist_txt);
            current -> setArtworkB64(_artwork);

            connect(current, &QPushButton::pressed,
                    this, &ExpandedAlbum::playSong);

            current = current -> getNext();
        }

        for (int i = mid_point; i < _nsongs; i++)
        {
            _layout_b -> addWidget(current);
            current -> setMusicPlayer(_player);
            current -> setArtist(_artist_txt);
            current -> setArtworkB64(_artwork);

            connect(current, &QPushButton::pressed,
                    this, &ExpandedAlbum::playSong);

            current = current -> getNext();
        }

        _tracklist_layout -> addWidget(_column_a);
        _tracklist_layout -> addWidget(_column_b);
    }
    else
    {
        for (int i = 0; i < _nsongs; i++)
        {
            _layout_a -> addWidget(current);
            current -> setMusicPlayer(_player);
            current -> setArtist(_artist_txt);
            current -> setArtworkB64(_artwork);

            connect(current, &QPushButton::pressed,
                    this, &ExpandedAlbum::playSong);

            current = current -> getNext();
        }

        _tracklist_layout -> addWidget(_column_a);
    }

    _layout -> addWidget(_tracklist);

    setLayout(_layout);
}

void ExpandedAlbum::playSong ()
{
    Song* calling_button = static_cast<Song*> (sender());
    int add_idx = calling_button -> getIndex();

    _player -> playSong(
        QString::fromStdString(calling_button -> getFile()),
        QString::fromStdString(calling_button -> getTitle()),
        QString::fromStdString(calling_button -> getArtist()),
        QString::fromStdString(calling_button -> getLength()),
        calling_button -> getArtB64()
    );

    _player -> resetSongList();
    _player -> setSongList(song_list, (add_idx - 1) % _nsongs);
}
