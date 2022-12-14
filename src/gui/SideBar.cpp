#include "SideBar.h"

/**
 * @brief       Constructs the sidebar.
 */
SideBar::SideBar (ViewManager* view_manager)
{
    _viewmg = view_manager;
    _layout = new QVBoxLayout {};
    _layout -> setAlignment(Qt::AlignTop);

    setFixedWidth(150);

    /* Define the background gradient. */
    QLinearGradient bg_gradient (0, 0, width(), height());

    bg_gradient.setColorAt(0, QColor {"#DFE9F3"});
    bg_gradient.setColorAt(1, QColor {"#FFFFFF"});

    /* Set sidebar background gradient. */
    QPalette sb_gradient = QPalette();
    sb_gradient.setBrush(QPalette::Window, bg_gradient);

    setAutoFillBackground(true);
    setPalette(sb_gradient);

    /* Create sidebar buttons. */
    library_button  = new SidebarButton
    {
        " Library",
        "assets/icons/library_b.png",
        "assets/icons/library_w.png"
    };

    playlist_button  = new SidebarButton
    {
        " Playlists",
        "assets/icons/playlist_b.png",
        "assets/icons/playlist_w.png"
    };

    import_button  = new SidebarButton
    {
        " Import",
        "assets/icons/import_b.png",
        "assets/icons/import_w.png"
    };

    search_button  = new SidebarButton
    {
        " Search",
        "assets/icons/search_b.png",
        "assets/icons/search_w.png"
    };

    /* Set Libary Button as enabled by default. */
    library_button -> setEnabledStyle();
    enabled_button = library_button;

    /* Set button actions. */
    connect(library_button, &QPushButton::pressed,
            this, &SideBar::changeView);
    connect(playlist_button, &QPushButton::pressed,
            this, &SideBar::changeView);
    connect(import_button, &QPushButton::pressed,
            this, &SideBar::changeView);
    connect(search_button, &QPushButton::pressed,
            this, &SideBar::changeView);

    /* Add buttons to sidebar layout. */
    _layout -> addWidget(library_button);
    _layout -> addWidget(playlist_button);
    _layout -> addWidget(import_button);
    _layout -> addWidget(search_button);

    /* Set finalized layout for sidebar. */
    setLayout(_layout);
}

void SideBar::changeView ()
{
    SidebarButton* sender_button = static_cast<SidebarButton*> (sender());

    /* Check that pressed button is not the one enabled. */
    if (sender_button != enabled_button)
    {
        /* Request target view from view manager. */
        _viewmg -> setActiveView(_layout -> indexOf(sender_button));

        enabled_button -> setDisabledStyle();
        sender_button  -> setEnabledStyle();
        enabled_button = sender_button;

    }
}
