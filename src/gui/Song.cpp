#include "Song.h"

Song::Song (string file_path, int index, string title, string length)
{
    _file = file_path;

    _song = title;
    _slength = length;

    _layout = new QHBoxLayout {};
    _index  = new QLabel      {QString::number(index)};
    _title  = new QLabel      {QString::fromStdString(title)};
    _length = new QLabel      {QString::fromStdString(length)};

    setStyleSheet(SONG_CSS);

    _layout -> setMargin(5);
    _layout -> setSpacing(20);

    /* Align buttons to the top. */
    _layout -> setAlignment(Qt::AlignLeft);

    /* Set bold font for index number. */
    QFont _font = _index -> font();
    _font.setBold(true);
    _index -> setFont(_font);

    _layout -> addWidget(_index);
    _layout -> addWidget(_title);
    _layout -> addWidget(_length);

    // connect(this, &QPushButton::pressed,
    //         this, &Song::playSong);

    setLayout(_layout);
}

Song::Song (string title, string artist, string album, string length,
            string file_path)
{
    _song    = title;
    _artist  = artist;
    _album   = album;
    _slength = length;
    _file    = file_path;
}

Song::Song (string title, string artist, string length, string art_b64)
{
    _song    = title;
    _artist  = artist;
    _slength = length;
    _artwork = art_b64;
}

void Song::setIndex (int index)
{
    _index -> setText(QString(index));
}

void Song::setTitle (QString title)
{
    _title -> setText(title);
}

void Song::setTitle (string title)
{
    _title -> setText(QString::fromStdString(title));
}

void Song::setLength (QString length)
{
    _length -> setText(length);
}

void Song::setLength (string length)
{
    _length -> setText(QString::fromStdString(length));
}


void Song::playSong ()
{
    _player -> playSong(QString::fromStdString(_file),
                        QString::fromStdString(_song),
                        QString::fromStdString(_artist),
                        QString::fromStdString(_slength),
                        _artwork);
}
