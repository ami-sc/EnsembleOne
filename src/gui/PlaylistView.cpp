#include "PlaylistView.h"

PlaylistView::PlaylistView (MainWindow* window)
{
    Database db;

    _window = window;
    _layout = new QHBoxLayout {};

    /* Disable spacing and padding of layout widgets. */
    _layout -> setSpacing(0);
    _layout -> setMargin(0);

    _layout -> setAlignment(Qt::AlignLeft);

    n_playlists = db.getPlaylistCount();

    /* Create a playlist sidebar widget. */
    sidebar        = new QWidget     {};
    sidebar_layout = new QVBoxLayout {};

    sidebar -> setFixedWidth(235);

    /* Disable spacing and padding of sidebar widgets. */
    sidebar_layout -> setSpacing(0);
    sidebar_layout -> setMargin(0);

    /* Build a scrollable playlist column. */
    scroll_area = new QScrollArea {};

    playlist_column = new QWidget     {};
    playlist_layout = new QVBoxLayout {};

    playlist_layout -> setAlignment(Qt::AlignTop);

    playlist_list = db.getPlaylistList();

    buildPlaylistColumn();

    playlist_column -> setLayout(playlist_layout);

    scroll_area -> setWidget(playlist_column);
    scroll_area -> setWidgetResizable(true);

    /* Add scrollable playlist sidebar to the sidebar widget. */
    sidebar_layout -> addWidget(scroll_area);

    add_button = new QPushButton {"New Playlist"};

    connect(add_button, &QPushButton::released,
            this, &PlaylistView::addPlaylist);

    sidebar_layout -> addWidget(add_button);

    sidebar -> setLayout(sidebar_layout);
    _layout -> addWidget(sidebar);

    setDefaultText();

    setLayout(_layout);
}

PlaylistView::~PlaylistView ()
{
    delete playlist_list;
}

void PlaylistView::addPlaylist ()
{
    AddDialog* add_dialog = new AddDialog {};
    add_dialog -> exec();

    /* Check if a name was given. */
    if (!(add_dialog -> getText()).isEmpty())
    {
        /* Add playlist to database. */
        Database db;
        db.insertPlaylist((add_dialog -> getText()).toStdString());

        clearPlaylistColumn();

        /* Get updated playlist list from database. */
        playlist_list = db.getPlaylistList();
        n_playlists = db.getPlaylistCount();

        buildPlaylistColumn();
    }

    delete add_dialog;
}

void PlaylistView::deletePlaylist (QString playlist)
{
    Database db;
    db.deletePlaylist(playlist.toStdString());

    clearPlaylistColumn();

    /* Get updated playlist list from database. */
    playlist_list = db.getPlaylistList();
    n_playlists = db.getPlaylistCount();

    buildPlaylistColumn();
}

void PlaylistView::showSongTable ()
{
    /* Check if there is a song list currently being shown. */
    if (active_playlist)
    {
        active_playlist -> setActiveCSS(false);

        /* Delete the current table. */
        delete song_table;

        setDefaultText();
    }

    /* Check that the pressed playlist is not the one that was active. */
    if (static_cast<Playlist*> (sender()) != active_playlist)
    {
        removeDefaultText();

        active_playlist = static_cast<Playlist*> (sender());
        active_playlist -> setActiveCSS(true);

        /* Create a new song table. */
        song_table = new SongTable {active_playlist -> getPlaylistTitle(),
                                    this};
        _layout -> addWidget(song_table);
    }
    else
    {
        active_playlist = nullptr;
    }
}

void PlaylistView::playSong (Song* song, SongList* play_list, int idx)
{
    _window -> getMusicPlayer() -> playSong(
        QString::fromStdString(song -> getFile()),
        QString::fromStdString(song -> getTitle()),
        QString::fromStdString(song -> getArtist()),
        QString::fromStdString(song -> getLength()),
        song -> getArtB64()
    );

    _window -> getMusicPlayer() -> resetSongList();
    _window -> getMusicPlayer() -> setSongList(play_list, idx);
}

void PlaylistView::updateSongCount ()
{
    Database db;
    int new_count = db.getListSongCount(
        (active_playlist -> getPlaylistTitle()).toStdString());

    active_playlist -> setSongNumber(new_count);
}

void PlaylistView::setDefaultText ()
{
    default_label  = new QWidget     {};
    default_layout = new QHBoxLayout {};

    default_text = new QLabel {"No playlist is selected."};

    default_layout -> setAlignment(Qt::AlignCenter);
    default_layout -> addWidget(default_text);

    default_label -> setLayout(default_layout);

    // _layout -> removeWidget(song_table);
    _layout -> addWidget(default_label);
}

void PlaylistView::removeDefaultText ()
{
    _layout -> removeWidget(default_label);
    delete default_label;
}

void PlaylistView::buildPlaylistColumn ()
{
    Database db;
    Playlist* current_playlist = playlist_list -> getHead();

    int song_count = 0;

    while (current_playlist)
    {
        connect(current_playlist, &QPushButton::released,
                this, &PlaylistView::showSongTable);

        song_count = db.getListSongCount(
            (current_playlist -> getPlaylistTitle()).toStdString());
        current_playlist -> setSongNumber(song_count);

        playlist_layout -> addWidget(current_playlist);
        current_playlist = current_playlist -> getNext();
    }
}

void PlaylistView::clearPlaylistColumn ()
{
    /* Check if there is a song list currently being shown. */
    if (active_playlist)
    {
        active_playlist -> setActiveCSS(false);
        delete song_table;

        active_playlist = nullptr;

        setDefaultText();
    }

    /* Clear playlist column and de-allocate object memory. */
    Playlist* current_playlist  = playlist_list -> getHead();
    Playlist* previous_playlist = nullptr;

    while (current_playlist)
    {
        playlist_layout -> removeWidget(current_playlist);

        previous_playlist = current_playlist;
        current_playlist = current_playlist -> getNext();

        delete previous_playlist;
    }

    /* Delete the previous playlist list. */
    delete playlist_list;
}
