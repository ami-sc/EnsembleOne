#include "SongTable.h"

SongTable::SongTable (QString playlist, PlaylistView* view)
{
    _view = view;
    _layout = new QVBoxLayout {};

    /* Remove space and padding between widgets. */
    _layout -> setSpacing(0);
    _layout -> setMargin(0);

    /** Playlist Header **/

    playlist_header = new QWidget     {};
    header_layout   = new QHBoxLayout {};

    playlist_title  = new QLabel      {playlist};
    add_button      = new QPushButton {"  Add Songs"};
    delete_button   = new QPushButton {"  Delete Playlist"};

    add_button -> setIcon(add_icon);
    add_button -> setMaximumWidth(150);

    connect(add_button, &QPushButton::released,
            this, &SongTable::addSongs);

    delete_button -> setIcon(delete_icon);
    delete_button -> setMaximumWidth(150);

    connect(delete_button, &QPushButton::released,
            this, &SongTable::deletePlaylist);

    header_layout -> addWidget(playlist_title, Qt::AlignLeft);
    header_layout -> addWidget(add_button, Qt::AlignRight);
    header_layout -> addWidget(delete_button, Qt::AlignRight);

    playlist_header -> setLayout(header_layout);

    _layout -> addWidget(playlist_header);

    /** Song Table **/

    buildSongTable();

    setLayout(_layout);
}

void SongTable::addSongs ()
{
    SongsDialog* songs_dlg = new SongsDialog {playlist_title -> text()};
    songs_dlg -> exec();

    delete songs_dlg;

    buildSongTable();
    _view -> updateSongCount();
}

void SongTable::deletePlaylist ()
{
    ConfirmDialog* confirm_dlg = new ConfirmDialog {};
    confirm_dlg -> exec();

    /* Check if user confirmed deletion. */
    if (confirm_dlg -> getDeleteStatus())
    {
        delete confirm_dlg;
        _view -> deletePlaylist(playlist_title -> text());
    }
    else
    {
        delete confirm_dlg;
    }
}

void SongTable::playSong ()
{
    TableButton* calling_button = static_cast<TableButton*> (sender());
    int add_idx = calling_button -> getButtonIndex();

    Song* current = song_list -> getHead();

    /* Traverse playlist to find the song to play. */
    for (int i = 0; i < add_idx; i++)
    {
        current = current -> getNext();
    }

    Database db;
    current -> setArtworkB64(db.getB64Artwork(current -> getAlbum()));
    _view -> playSong(current, song_list, add_idx);
}

void SongTable::buildSongTable ()
{
    Database db;

    if (song_list)
    {
        clearSongList();
    }

    if (song_table)
    {
        _layout -> removeWidget(song_table);
        delete song_table;
    }

    song_list = db.getPlayList((playlist_title -> text()).toStdString());

    /* Allocate a new table. */
    song_table = new QTableWidget {song_list -> getSize(), 5};

    /* Set column headers. */
    QStringList col_headers {"#", "Title", "Artist", "Album", "Duration"};
    song_table -> setHorizontalHeaderLabels(col_headers);
    song_table -> horizontalHeader() -> setSectionResizeMode(
                                            QHeaderView::Stretch);

    song_table -> horizontalHeader() -> setSectionResizeMode(0, QHeaderView::ResizeToContents);

    /* Populate table. */
    Song* current = song_list -> getHead();
    TableButton* play_button = nullptr;

    for (int i = 0; i < song_list -> getSize(); i++)
    {
        play_button = new TableButton {true};
        play_button -> setButtonIndex(i);

        connect(play_button, &QPushButton::released,
                this, &SongTable::playSong);

        song_table -> setIndexWidget(song_table -> model() -> index(i, 0),
                                     play_button);

        play_button = nullptr;

        QTableWidgetItem* song   = new QTableWidgetItem {QString::fromStdString(current -> getTitle())};
        QTableWidgetItem* artist = new QTableWidgetItem {QString::fromStdString(current -> getArtist())};
        QTableWidgetItem* album  = new QTableWidgetItem {QString::fromStdString(current -> getAlbum())};
        QTableWidgetItem* length = new QTableWidgetItem {QString::fromStdString(current -> getLength())};

        song_table -> setItem(i, 1, song);
        song_table -> setItem(i, 2, artist);
        song_table -> setItem(i, 3, album);
        song_table -> setItem(i, 4, length);

        current = current -> getNext();
    }

    /* Prevent users from directly editing the table. */
    song_table -> setEditTriggers(QAbstractItemView::NoEditTriggers);

    /* Add table to layout. */
    _layout -> addWidget(song_table);
}

void SongTable::clearSongList ()
{
    Song* current_song  = song_list -> getHead();
    Song* previous_song = nullptr;

    while (current_song)
    {
        previous_song = current_song;
        current_song  = current_song -> getNext();

        delete previous_song;
    }

    delete song_list;
}
