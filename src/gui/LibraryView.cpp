#include "LibraryView.h"

LibraryView::LibraryView (MainWindow* parent_window)
{
    /* Get the list of albums stored in the database. */
    Database db;
    albums = db.getAlbumList();

    n_albums = albums -> getSize();

    _window = parent_window;

    /* Create a scrollable layout for the album grid. */
    scroll_area   = new QScrollArea {};
    scroll_layout = new QHBoxLayout {};

    /* Disable the horizontal scrollbar. */
    scroll_area -> horizontalScrollBar() -> setEnabled(false);
    scroll_area -> horizontalScrollBar() -> setVisible(false);

    /* Remove padding for scroll area. */
    scroll_layout -> setSpacing(0);
    scroll_layout -> setMargin(0);

    scroll_layout -> addWidget(scroll_area);

    /* If currently there are no albums in the database, show a message.*/
    if (!n_albums)
    {
        default_msg = new QLabel{"No music found. Add some via Import."};

        scroll_area -> setWidget(default_msg);
        scroll_area -> setWidgetResizable(true);

        default_msg -> setAlignment(Qt::AlignCenter);
    }
    else
    {
        grid        = new QWidget{};
        grid_layout = new QGridLayout {};

        /*
        * Calculate the maximum number of columns we can fit in the current
        * window size.
        *
        * Consider that the sidebar has a fixed width of 150 pixels, and assume
        * each album has a fixed width of 160 pixels, with 10 pixels of padding
        * between each column.
        *
        * The maximum number of columns in the view is calculated as:
        *
        * n_cols = (w_width - 150) / 170
        */
        n_cols = (parent_window -> width() - 150) / 170;

        Album* current_album = albums -> getHead();

        while (current_album)
        {
            /* Set button funtionality. */
            connect(current_album, &QPushButton::released,
                    this, &LibraryView::expandAlbum);

            /* Move to the next album in the list. */
            current_album = current_album -> getNext();
        }

        buildGrid();

        grid -> setLayout(grid_layout);

        scroll_area -> setWidget(grid);
        scroll_area -> setWidgetResizable(true);
    }

    setLayout(scroll_layout);
}

LibraryView::~LibraryView ()
{
    delete albums;
}

void LibraryView::expandAlbum ()
{
    /* Check if an album is currently expanded. */
    if (expanded_view)
    {
        /*
         * Remove and de-allocate the current expanded view. This is expected
         * even if the pressed album is the one that is currently expanded.
         */
        grid_layout -> removeWidget(static_cast<QWidget*> (expanded_view));
        delete expanded_view;
        expanded_album -> setExpandedState(false);

        expanded_view  = nullptr;
    }

    /*
     * Check that the pressed album was not the one that was expanded so
     * that we do not allocate its expanded view again.
     */
    if (static_cast<Album*> (sender()) != expanded_album)
    {
        /* Set the pressed album as the new expanded album. */
        expanded_album = static_cast<Album*> (sender());
        expanded_album -> setExpandedState(true);

        /* Create the expanded album object for the pressed album. */
        expanded_view = new ExpandedAlbum
        {
            expanded_album -> getAlbumTitle(),
            expanded_album -> getAlbumArtist(),
            expanded_album -> getArtworkB64(),
            _window -> getMusicPlayer()
        };

        /*
         * Add the expanded view to the grid, in the row below the album
         * that was pressed.
         */
        grid_layout -> addWidget(expanded_view, expanded_album -> getRow() + 1,
                                 0, 1, n_cols);
    }
    /*
     * If the pressed album was the one that was expanded, update the pointer
     * to indicate that it is no longer expanded.
     */
    else
    {
        expanded_album = nullptr;
    }
}

void LibraryView::resizeView ()
{
    /*
     * Check if an additional column will fit in the new window width.
     *
     * Consider that the sidebar has a fixed width of 150 pixels, and assume
     * each album has a fixed width of 160 pixels, with 10 pixels of padding
     * between each column.
     *
     * An additional column occupies another 160 pixels, plus 10 pixels of
     * padding.
     *
     * The new (target) width should be at least:
     *
     * target_width = ((n_cols + 1) * 170) + 150
     */

    int target_width  = ((n_cols + 1) * 170) + 150;
    int current_width = ((n_cols) * 170) + 150;

    /*
     * Check if the target width is lower than the current width. If so, we
     * can add a new column to the grid.
     */
    if (target_width < _window -> width())
    {
        clearGrid();

        /* Reflect the addition of the new column. */
        n_cols++;

        buildGrid();
    }

    /*
     * Check if the current width is larger than the window width. If so, we
     * need to remove a column.
     */
    else if (current_width > _window -> width())
    {
        clearGrid();

        /* Reflect the removal of a column. */
        n_cols--;

        buildGrid();
    }
}

void LibraryView::buildGrid ()
{
    /*
     * Check if the number of albums to be inserted into the grid is not
     * perfectly divided by the number of columns. In this case, we will have an
     * additional, incompletely-filled row.
     *
     * We must have double the required rows to reserve the space for the
     * Expanded Album object.
     */
    if (n_albums % n_cols)
    {
        n_rows = ((n_albums / n_cols) + 1) * 2;
    }
    else
    {
        n_rows = (n_albums / n_cols) * 2;
    }

    std::cout << "LibraryView::buildGrid - Building album grid with "
              << n_albums << " albums. ("
              << n_cols << " columns, "
              << n_rows << " rows)"
              << std::endl;

    Album* current_album = albums -> getHead();

    /* Load the albums into the grid. */
    for (int row = 0; row < n_rows; row++)
    {
        /* Every other row needs to be empty for the Expanded View. */
        if (!(row % 2))
        {
            for (int col = 0; col < n_cols; col++)
            {
                /* Check if we still have albums to add. */
                if (current_album)
                {
                    /* Add the album to the target position in the grid. */
                    grid_layout -> addWidget(current_album, row, col);
                    current_album -> setRow(row);
                    current_album -> setCol(col);

                    /* Move to the next album in the list. */
                    current_album = current_album -> getNext();
                }
            }
        }
    }

    /* Re-add an expanded view, if there was one, to the grid. */
    if (expanded_view)
    {
        grid_layout -> addWidget(expanded_view, expanded_album -> getRow() + 1,
                                 0, 1, n_cols);
    }
}

void LibraryView::clearGrid ()
{
    /* Check if there is an expanded album, and if so, remove it. */
    if (expanded_view)
    {
        grid_layout -> takeAt(grid_layout -> indexOf(expanded_view));
    }

    /* Remove the albums from the layout. */
    for (int i = 0; i < n_albums; i++)
    {
        grid_layout -> takeAt(i);
    }
}
