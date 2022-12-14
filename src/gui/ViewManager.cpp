#include "ViewManager.h"

ViewManager::ViewManager (MainWindow* parent_window)
{
    _window = parent_window;
    _layout = new QHBoxLayout {};

    /* Remove spacing between widgets. */
    _layout -> setSpacing(0);
    _layout -> setMargin(0);

    /* Build the sidebar. */
    sidebar = new SideBar {this};
    _layout -> addWidget(sidebar);

    /* Build the default (Library) view. */
    active_view = new LibraryView {_window};

    _layout -> addWidget(active_view);

    setLayout(_layout);
}

void ViewManager::setActiveView (int idx)
{
    /* Check that the requested view is not the active one. */
    if (idx != view_idx)
    {
        /* De-allocate the current view. */
        _layout -> removeWidget(active_view);
        delete active_view;

        /* Create the requested view. */
        if (idx == Library)
        {
            active_view = new LibraryView {_window};
            view_idx = Library;
        }
        else if (idx == Playlist)
        {
            active_view = new PlaylistView {_window};
            view_idx = Playlist;
        }
        else if (idx == Import)
        {
            active_view = new ImportView {};
            view_idx = Import;
        }
        else if (idx == Search)
        {
            active_view = new SearchView {_window};
            view_idx = Search;
        }

        _layout -> addWidget(active_view);
    }
}

void ViewManager::resizeActiveView ()
{
    if (view_idx == Library)
    {
        static_cast<LibraryView*> (active_view) -> resizeView();
    }
}
