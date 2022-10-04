#include "MusicPlayer.h"

/**
 * @brief       Constructs a Music Player interface and its controls.
 */
MusicPlayer::MusicPlayer ()
{
    _layout = new QHBoxLayout();

    /** Set background color. **/
    QPalette background_color = QPalette();
    background_color.setColor(QPalette::Window, "#C0C0C0");
    setAutoFillBackground(true);
    setPalette(background_color);

    setFixedHeight(60);

    /*** Player Buttons ***/

    /** Allocate memory for button objects. **/
    back_button = new QPushButton {};
    play_button = new QPushButton {};
    next_button = new QPushButton {};

    /** Load button icons. **/
    QIcon back_icon {"assets/icons/back.png"};
    QIcon play_icon {"assets/icons/play.png"};
    QIcon next_icon {"assets/icons/next.png"};

    /** Set the icon for each button. **/
    back_button -> setIcon(back_icon);
    play_button -> setIcon(play_icon);
    next_button -> setIcon(next_icon);

    /** Define CSS stylesheets for each button. **/
    back_button -> setStyleSheet(
        "QPushButton {"
        "    border: 8px solid rgba(255, 255, 255, 0);"
        "    border-radius: 3px; }"
        "QPushButton::hover { background-color : #BDC3C7; }"
        "QPushButton::pressed { background-color : #6495ED; }");
    play_button -> setStyleSheet(
        "QPushButton {"
        "    border: 8px solid rgba(255, 255, 255, 0);"
        "    border-radius: 3px; }"
        "QPushButton::hover { background-color : #BDC3C7; }"
        "QPushButton::pressed { background-color : #6495ED; }");
    next_button -> setStyleSheet(
        "QPushButton {"
        "    border: 8px solid rgba(255, 255, 255, 0);"
        "    border-radius: 3px; }"
        "QPushButton::hover { background-color : #BDC3C7; }"
        "QPushButton::pressed { background-color : #6495ED; }");

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

    /** Create box with song information. **/
    info_layout -> addWidget(song_name);
    info_layout -> addWidget(artist_name);

    album_box -> setPixmap(album_art -> pixmap(QSize(45, 45)));
    info_box -> setLayout(info_layout);

    /** Add finalized widgets to layout. **/
    _layout -> addWidget(album_box);
    _layout -> addWidget(info_box);

    /** Progress Bar **/

    /** Allocate memory for progress bar components. **/
    current_pos  = new QLabel       {"0:00"};
    progress_bar = new QProgressBar {};
    duration     = new QLabel       {"9:99"};

    /** Define stylings for the progress bar. **/
    progress_bar -> setValue(42);
    progress_bar -> setTextVisible(false);
    progress_bar -> setStyleSheet(
        "QProgressBar {"
        "    border: 1.5px solid #000000;"
        "    border-radius: 6px; }"
        "QProgressBar::chunk {"
        "    background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,"
        "                                  stop: 0 #1A2980,"
        "                                  stop: 1 #26D0CE );"
        "    border-radius: 3px;}");

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
    loop_button -> setStyleSheet(
        "QPushButton {"
        "    border: 8px solid rgba(255, 255, 255, 0);"
        "    border-radius: 3px; }"
        "QPushButton::hover { background-color : #BDC3C7; }"
        "QPushButton::pressed { background-color : #6495ED; }");
    shuffle_button -> setStyleSheet(
        "QPushButton {"
        "    border: 8px solid rgba(255, 255, 255, 0);"
        "    border-radius: 3px; }"
        "QPushButton::hover { background-color : #BDC3C7; }"
        "QPushButton::pressed { background-color : #6495ED; }");

    /** Add finalized buttons to the layout. **/
    _layout -> addWidget(loop_button);
    _layout -> addWidget(shuffle_button);

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
    album_art   = nullptr;
}
