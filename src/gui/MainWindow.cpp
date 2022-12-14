#include "MainWindow.h"

/**
 * @brief       Constructs the main window of the application.
 */
MainWindow::MainWindow ()
{
    Database db;
    if (!db.getInitState())
    {
        db.initializeDatabase();
        db.setInitState(true);
    }

    /** Central Widget **/

    __center  = new QWidget     {};
    __clayout = new QVBoxLayout {};

    __center  -> setLayout(__clayout);

    /* Remove all padding in the central widget. */
    __clayout -> setSpacing (0);
    __clayout -> setMargin  (0);

    /* Set default window properties. */
    setWindowTitle("Ensemble");
    setMinimumSize(850, 400);
    setCentralWidget(__center);

    /** Music Player **/

    __player = new MusicPlayer {};
    __clayout -> addWidget(__player);

    /** Main Widget **/

    // __main    = new QWidget     {};
    // __mlayout = new QHBoxLayout {};

    // __main    -> setLayout(__mlayout);

    // /* Remove all padding in the main widget. */
    // __mlayout -> setSpacing (0);
    // __mlayout -> setMargin  (0);

    /* Add the main widget to the central widget. */
    // __clayout -> addWidget(__main);

    /** Sidebar **/

    view_manager = new ViewManager {this};
    __clayout -> addWidget(view_manager);

    // __sidebar         = new SideBar     {};
    // __sidebar_layout  = new QVBoxLayout {};
    // __library_button  = new QPushButton {" Library"};
    // __playlist_button = new QPushButton {" Playlists"};
    // __import_button   = new QPushButton {" Import"};
    // __search_button   = new QPushButton {" Search"};

    // __sidebar -> setLayout(__sidebar_layout);

    // /* Load sidebar button icons. */
    // QIcon library_icon    {"assets/icons/library.png"};
    // QIcon playlist_icon   {"assets/icons/playlist.png"};
    // QIcon statistics_icon {"assets/icons/import.png"};
    // QIcon search_icon     {"assets/icons/search.png"};

    // /* Set the icon for each sidebar button. */
    // __library_button  -> setIcon(library_icon);
    // __playlist_button -> setIcon(playlist_icon);
    // __import_button   -> setIcon(statistics_icon);
    // __search_button   -> setIcon(search_icon);

    // /* Define CSS stylesheets for each button. */
    // __library_button  -> setStyleSheet(SB_ENABLED_BUTTON_CSS);
    // __playlist_button -> setStyleSheet(SB_DISABLED_BUTTON_CSS);
    // __import_button   -> setStyleSheet(SB_DISABLED_BUTTON_CSS);
    // __search_button   -> setStyleSheet(SB_DISABLED_BUTTON_CSS);

    // /* Connect buttons to corresponding actions. */
    // connect(__library_button , &QPushButton::pressed,
    //         this, &MainWindow::setActiveView);
    // connect(__playlist_button, &QPushButton::pressed,
    //         this, &MainWindow::setActiveView);
    // connect(__import_button  , &QPushButton::pressed,
    //         this, &MainWindow::setActiveView);
    // connect(__search_button  , &QPushButton::pressed,
    //         this, &MainWindow::setActiveView);

    // /* Add buttons to sidebar. */
    // __sidebar_layout -> addWidget(__library_button);
    // __sidebar_layout -> addWidget(__playlist_button);
    // __sidebar_layout -> addWidget(__import_button);
    // __sidebar_layout -> addWidget(__search_button);

    // __sidebar -> setFixedWidth(150);

    // /* Align buttons to the top of the sidebar. */
    // __sidebar_layout -> setAlignment(Qt::AlignTop);

    // /* Background gradient for the sidebar. */
    // QLinearGradient sidebar_gradient {0, 0, (double) width(),
    //                                         (double) height()};

    // sidebar_gradient.setColorAt(0, QColor {"#DFE9F3"});
    // sidebar_gradient.setColorAt(1, QColor {"#FFFFFF"});

    // /* Set sidebar background color. */
    // QPalette sidebar_color = QPalette();
    // sidebar_color.setBrush(QPalette::Window, sidebar_gradient);

    // __sidebar -> setAutoFillBackground(true);
    // __sidebar -> setPalette(sidebar_color);

    // /* Consider Library Button as enabled by default. */
    // __active_button = __library_button;

    /* Add complete sidebar to the main widget. */
    // __mlayout -> addWidget(__sidebar);

    /** Active View **/

    /* Set the Library View as active by default. */
    //__active_view   = new LibraryView {20};
    // _album_list = db.getAlbumList();
    // __active_view   = new LibraryView {_album_list, __player};
    // __active_scroll = new QScrollArea {};

    // _active_idx = 0;

    // /* Parameters for scrollable area. */
    // __active_scroll -> setWidget(__active_view);
    // __active_scroll -> setWidgetResizable(true);
    // __active_scroll -> horizontalScrollBar() -> setEnabled(false);
    // __active_scroll -> horizontalScrollBar() -> setVisible(false);


    // __mlayout -> addWidget(__active_scroll);




    // /* SideBar Buttons */
    // library_button    = new QPushButton {" Library"};
    // playlist_button   = new QPushButton {" Playlists"};
    // statistics_button = new QPushButton {" Statistics"};
    // search_button     = new QPushButton {" Search"};

    // /* Allocate memory for the main window components. */
    // _main    = new QFrame      {};
    // _center  = new QWidget     {};
    // _mlayout = new QVBoxLayout {};
    // _clayout = new QHBoxLayout {};
    // _player  = new MusicPlayer {};
    // SideBar*     _sidebar = new SideBar     {library_button, playlist_button,
    //                             statistics_button, search_button};

    // _lview   = new LibraryView {38};
    // _lscroll = new QScrollArea {};

    // _pview = new PlaylistView {};

    // /* Remove padding and spacing between components. */
    // _mlayout -> setSpacing(0);
    // _clayout -> setSpacing(0);
    // _mlayout -> setMargin(0);
    // _clayout -> setMargin(0);

    // _main   -> setLayout(_mlayout);
    // _center -> setLayout(_clayout);

    // // Debug to see frames.
    // // _main -> setStyleSheet(
    // //     "QFrame {"
    // //     "    border: 1px solid #22E1FF; }"
    // // );



    // /* Build the Music Player. */
    // _mlayout -> addWidget(_player);

    // /* Build the Side Bar. */
    // _clayout -> addWidget(_sidebar);
    // _mlayout -> addWidget(_center);

    // /* Build the default Album View. */
    // _lscroll -> setWidget(_lview);
    // _lscroll -> setWidgetResizable(true);
    // _lscroll -> horizontalScrollBar() -> setEnabled(false);
    // _lscroll -> horizontalScrollBar() -> setVisible(false);
    // _clayout -> addWidget(_lscroll);

    // /* Set currently active view. */

    // /* SideBar Button Functionality */
    // connect(library_button, &QPushButton::pressed,
    //         this, &MainWindow::setActiveView);
    // connect(playlist_button, &QPushButton::pressed,
    //         this, &MainWindow::setActiveView);
    // connect(statistics_button, &QPushButton::pressed,
    //         this, &MainWindow::setActiveView);
    // connect(search_button, &QPushButton::pressed,
    //         this, &MainWindow::setActiveView);
}

void MainWindow::resizeEvent (QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    view_manager -> resizeActiveView();
}

// void MainWindow::setActiveView ()
// {
//     QPushButton* sender_button = static_cast<QPushButton*> (sender());

//     /* Check that the requested view is not currently the active one. */
//     if (sender_button != __active_button)
//     {
//         /* De-allocate current view. */
//         if (__active_scroll)
//         {
//             __mlayout -> removeWidget(__active_scroll);
//             delete __active_scroll;
//             __active_scroll = nullptr;
//         }
//         else
//         {
//             __mlayout -> removeWidget(__active_view);
//             delete __active_view;
//         }

//         /* Allocate new view. */
//         if (sender_button -> text() == " Library")
//         {
//             Database db;
//             _album_list = db.getAlbumList();
//             __active_view   = new LibraryView {_album_list, __player};
//             __active_scroll = new QScrollArea {};

//             /* Parameters for scrollable area. */
//             __active_scroll -> setWidget(__active_view);
//             __active_scroll -> setWidgetResizable(true);
//             __active_scroll -> horizontalScrollBar() -> setEnabled(false);
//             __active_scroll -> horizontalScrollBar() -> setVisible(false);

//             __mlayout -> addWidget(__active_scroll);
//             layout() -> update();

//             __active_button -> setStyleSheet(SB_DISABLED_BUTTON_CSS);
//             __active_button = sender_button;
//             __active_button -> setStyleSheet(SB_ENABLED_BUTTON_CSS);

//             _active_idx = 0;
//         }
//         else if (sender_button -> text() == " Playlists")
//         {
//             __active_view = new PlaylistView {7};
//             __mlayout -> addWidget(__active_view);

//             layout() -> update();

//             __active_button -> setStyleSheet(SB_DISABLED_BUTTON_CSS);
//             __active_button = sender_button;
//             __active_button -> setStyleSheet(SB_ENABLED_BUTTON_CSS);

//             _active_idx = 1;
//         }
//         else if (sender_button -> text() == " Import")
//         {
//             __active_view = new ImportView {};
//             __mlayout -> addWidget(__active_view);

//             layout() -> update();

//             __active_button -> setStyleSheet(SB_DISABLED_BUTTON_CSS);
//             __active_button = sender_button;
//             __active_button -> setStyleSheet(SB_ENABLED_BUTTON_CSS);

//             _active_idx = 2;
//         }
//         else if (sender_button -> text() == " Search")
//         {
//             __active_view = new SearchView {};
//             __mlayout -> addWidget(__active_view);

//             layout() -> update();

//             __active_button -> setStyleSheet(SB_DISABLED_BUTTON_CSS);
//             __active_button = sender_button;
//             __active_button -> setStyleSheet(SB_ENABLED_BUTTON_CSS);

//             _active_idx = 3;
//         }
//     }
// }
