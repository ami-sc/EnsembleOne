#include "SideBar.h"

/**
 * @brief       Constructs a Side Bar and its corresponding buttons.
 */
SideBar::SideBar ()
{
    /** Allocate memory for button objects. **/
    _layout           = new QVBoxLayout {};
    library_button    = new QPushButton {" Library"};
    playlist_button   = new QPushButton {" Playlists"};
    statistics_button = new QPushButton {" Statistics"};
    search_button     = new QPushButton {" Search"};

    /** Load button icons. **/
    QIcon library_icon    {"assets/icons/library.png"};
    QIcon playlist_icon   {"assets/icons/playlist.png"};
    QIcon statistics_icon {"assets/icons/statistics.png"};
    QIcon search_icon     {"assets/icons/search.png"};

    /** Set the icon for each button. **/
    library_button    -> setIcon(library_icon);
    playlist_button   -> setIcon(playlist_icon);
    statistics_button -> setIcon(statistics_icon);
    search_button     -> setIcon(search_icon);

    /** Define CSS stylesheets for each button. **/
    library_button -> setStyleSheet(
        "QPushButton {"
        "    border: 1px hidden;"
        "    padding: 10px;"
        "    border-radius: 6px;"
        "    background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,"
        "                                  stop: 0 #99FFFF,"
        "                                  stop: 1 #99FFCC ); }"
        "QPushButton::hover { background-color : #73BFBF; }"
        "QPushButton::pressed { background-color : #67AB89; }");

    playlist_button -> setStyleSheet(
        "QPushButton {"
        "    border: 1px hidden;"
        "    padding: 10px;"
        "    border-radius: 6px;"
        "    background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,"
        "                                  stop: 0 #FFE6CC,"
        "                                  stop: 1 #FFCCE6 ); }"
        "QPushButton::hover { background-color : #73BFBF; }"
        "QPushButton::pressed { background-color : #67AB89; }");

    statistics_button -> setStyleSheet(
        "QPushButton {"
        "    border: 1px hidden;"
        "    padding: 10px;"
        "    border-radius: 6px;"
        "    background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,"
        "                                  stop: 0 #CCFFE6,"
        "                                  stop: 1 #E6FFCC ); }"
        "QPushButton::hover { background-color : #73BFBF; }"
        "QPushButton::pressed { background-color : #67AB89; }");

    search_button -> setStyleSheet(
        "QPushButton {"
        "    border: 1px hidden;"
        "    padding: 10px;"
        "    border-radius: 6px;"
        "    background: #CCCCCC; }"
        "QPushButton::hover { background-color : #73BFBF; }"
        "QPushButton::pressed { background-color : #67AB89; }");

    /** Add finalized buttons to the layout. **/
    _layout -> addWidget(library_button);
    _layout -> addWidget(playlist_button);
    _layout -> addWidget(statistics_button);
    _layout -> addWidget(search_button);

    /** Set layout for the complete Side Bar. **/
    setLayout(_layout);
}
