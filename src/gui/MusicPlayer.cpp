#include "MusicPlayer.h"

/**
 * @brief       Constructs a Music Player interface and its controls.
 */
MusicPlayer::MusicPlayer ()
{
    setFixedHeight(60);

    _player = new QMediaPlayer {};

    /* Update Position Label */
    connect(_player, &QMediaPlayer::positionChanged,
            this, &MusicPlayer::updatePositionLabel);

    /* For updating duration in slider. */
    connect(_player, &QMediaPlayer::durationChanged,
            this, &MusicPlayer::updateDuration);

    /** Set background color. **/
    QPalette background_color = QPalette();
    background_color.setColor(QPalette::Window, "#DFE9F3");
    setAutoFillBackground(true);
    setPalette(background_color);

    _layout = new QHBoxLayout {};

    /*** Player Buttons ***/

    /** Allocate memory for button objects. **/
    back_button = new QPushButton {};
    play_button = new QPushButton {};
    next_button = new QPushButton {};

    /** Set the icon for each button. **/
    back_button -> setIcon(back_icon);
    play_button -> setIcon(play_icon);
    next_button -> setIcon(next_icon);

    /** Define CSS stylesheets for each button. **/
    back_button -> setStyleSheet(_buttoncss);
    play_button -> setStyleSheet(_buttoncss);
    next_button -> setStyleSheet(_buttoncss);

    /* Set signals and slots. */
    connect(back_button, &QPushButton::pressed,
            this, &MusicPlayer::previousSong);
    connect(play_button, &QPushButton::pressed,
            this, &MusicPlayer::playback);
    connect(next_button, &QPushButton::pressed,
            this, &MusicPlayer::nextSong);

    /** Add finalized buttons to the layout. **/
    _layout -> addWidget(back_button);
    _layout -> addWidget(play_button);
    _layout -> addWidget(next_button);

    /*** Song Information ***/

    /** Allocate memory for each object. **/
    album_box   = new QLabel      {};
    album_art   = new QIcon       {"assets/default_artwork.jpg"};
    info_box    = new QWidget     {};
    info_layout = new QVBoxLayout {};
    song_name   = new QLabel      {"Unknown Song"};
    artist_name = new QLabel      {"Unknown Artist"};

    song_name   -> setFixedWidth(120);
    artist_name -> setFixedWidth(120);

    /** Create box with song information. **/
    info_layout -> addWidget(song_name);
    info_layout -> addWidget(artist_name);

    info_layout -> setSpacing(0);
    info_layout -> setMargin(2);

    album_box -> setPixmap(album_art -> pixmap(QSize(45, 45)));
    info_box -> setLayout(info_layout);

    /** Add finalized widgets to layout. **/
    _layout -> addWidget(album_box);
    _layout -> addWidget(info_box);

    /** Progress Bar **/

    /** Allocate memory for progress bar components. **/
    current_pos  = new QLabel  {"0:00"};
    progress_bar = new QSlider {Qt::Horizontal};
    duration     = new QLabel  {"9:99"};

    /** Define stylings for the progress bar. **/
    progress_bar -> setFixedHeight(20);
    progress_bar -> setValue(42);
    progress_bar -> setStyleSheet(
        "QSlider::groove:horizontal {"
        "    border: 1px solid #000000;"
        "    height: 15px;"
        "    margin: 2px 0;"
        "    background: QLinearGradient(x1: 0, y1: 0, x2: 1, y2: 0,"
        "                                stop: 0 #625EB1,"
        "                                stop: 0.5 #1D8FE1,"
        "                                stop: 1 #22E1FF); }"
        "QSlider::handle:horizontal {"
        "    border: 1px solid #5c5c5c;"
        "    width: 10px;"
        "    background: #b4b4b4;"
        "    margin: -2px 0; }"
        "QSlider::add-page:horizontal {"
        "    border: 1px solid #000000;"
        "    height: 15px;"
        "    margin: 2px 0;"
        "    background: white; }");

    /* Update duration when slider is moved. */
    connect(progress_bar, &QSlider::sliderReleased,
            this, &MusicPlayer::updatePosition);

    /** Add finalized widgets to layout. **/
    _layout -> addWidget(current_pos);
    _layout -> addWidget(progress_bar);
    _layout -> addWidget(duration);

    /*** Additional Control Buttons ***/

    /** Allocate memory for button objects. **/
    loop_button    = new QPushButton {};
    shuffle_button = new QPushButton {};

    /** Load button icons. **/
    QIcon loop_icon    {"assets/icons/loop.png"};
    QIcon shuffle_icon {"assets/icons/shuffle.png"};

    /** Set the icon for each button. **/
    loop_button    -> setIcon(loop_icon);
    shuffle_button -> setIcon(shuffle_icon);

    /** Define CSS stylesheets for each button. **/
    loop_button -> setStyleSheet(_buttoncss);
    shuffle_button -> setStyleSheet(_buttoncss);

    en_logo  = new QIcon  {"assets/ensemble.png"};
    logo_box = new QLabel {};
    logo_box -> setPixmap(en_logo -> pixmap(QSize(45, 45)));

    _layout -> addWidget(logo_box);

    /** Set layout for the complete Music Player. **/
    setLayout(_layout);
}

/**
 * @brief       De-allocates memory of elements not directly loaded into the
 *              layout of the Music Player object.
 */
MusicPlayer::~MusicPlayer ()
{
    delete album_art;
    album_art = nullptr;

    delete _player;
}

void MusicPlayer::pauseSong ()
{
    _player -> pause();
    play_button -> setIcon(play_icon);
    is_paused = true;
}

void MusicPlayer::resumeSong ()
{
    _player -> play();
    play_button -> setIcon(pause_icon);
    is_paused = false;
}

void MusicPlayer::previousSong ()
{
    if (_playlist && (_current - 1 >= 0))
    {
        _current--;

        Database db;

        SongList* song_obj = db.getSong(_playlist[_current]);
        Song* song = song_obj -> getHead();

        playSong(
            QString::fromStdString(_playlist[_current]),
            QString::fromStdString(song -> getTitle()),
            QString::fromStdString(song -> getArtist()),
            QString::fromStdString(song -> getLength()),
            song -> getArtB64()
        );

        delete song;
        delete song_obj;
    }
}

void MusicPlayer::nextSong ()
{
    if (_playlist && (_current + 1 < _psize))
    {
        _current++;

        Database db;

        SongList* song_obj = db.getSong(_playlist[_current]);
        Song* song = song_obj -> getHead();

        playSong(
            QString::fromStdString(_playlist[_current]),
            QString::fromStdString(song -> getTitle()),
            QString::fromStdString(song -> getArtist()),
            QString::fromStdString(song -> getLength()),
            song -> getArtB64()
        );

        delete song;
        delete song_obj;
    }
}

void MusicPlayer::playSong (QString file_path, QString song, QString artist,
                            QString length, string artwork_b64)
{
    _player -> setMedia(QUrl::fromLocalFile(file_path));

    /* Update album art. */
    delete _artwork;

    _artwork = new QPixmap {};
    _artwork -> loadFromData(QByteArray::fromBase64(artwork_b64.c_str()));
    album_box -> setPixmap(_artwork -> scaled(45, 45));
    album_box -> setScaledContents(true);

    QFontMetrics song_metrics {song_name -> font()};
    QFontMetrics art_metrics {artist_name -> font()};

    QString elided_song = song_metrics.elidedText(song, Qt::ElideRight, 120);
    QString elided_art = art_metrics.elidedText(artist, Qt::ElideRight, 120);

    song_name -> setText(elided_song);
    artist_name -> setText(elided_art);

    _player -> setVolume(100);
    _player -> play();

    play_button -> setIcon(pause_icon);
    is_paused = false;

    duration -> setText(length);
}

void MusicPlayer::resetSongList ()
{
    _playlist = nullptr;
    _psize = 0;
    _current = 0;
}

void MusicPlayer::setSongList (SongList* song_list, int song_idx)
{
    _psize = song_list -> getSize();
    _playlist = new string[_psize];

    Song* current = song_list -> getHead();

    /* Traverse list to get all songs. */
    for (int i = 0; i < _psize; i++)
    {
        /* Add file to playlist. */
        _playlist[i] = current -> getFile();

        current = current -> getNext();
    }

    _current = song_idx;
}

void MusicPlayer::playback ()
{
    if (is_paused)
    {
        resumeSong();
    }
    else
    {
        pauseSong();
    }
}

void MusicPlayer::updatePositionLabel ()
{
    int minutes = (_player -> position()) / 60000;
    int seconds = ((_player -> position()) - (minutes * 60000)) / 1000;

    string new_label = "";

    if (seconds < 10)
    {
        new_label = std::to_string(minutes) + ":0"+ std::to_string(seconds);
    }
    else
    {
        new_label = std::to_string(minutes) + ':' + std::to_string(seconds);
    }

    current_pos -> setText(QString::fromStdString(new_label));

    /* Update Slider */
    progress_bar -> setSliderPosition(_player -> position());
}

void MusicPlayer::updateDuration ()
{
    /* Update Slider */
    progress_bar -> setMinimum(0);
    progress_bar -> setMaximum(_player -> duration());

    std::cout << _player -> duration() << std::endl;
}

void MusicPlayer::updatePosition ()
{
    _player -> setPosition(progress_bar -> value());
}
