#include "SearchView.h"

SearchView::SearchView (MainWindow* window)
{
    _window = window;
    _layout = new QVBoxLayout {};
    _layout -> setAlignment(Qt::AlignTop);

    setLayout(_layout);

    /** Search Box **/

    _search_box    = new QWidget     {};
    _search_layout = new QHBoxLayout {};
    _search_input  = new QLineEdit   {};
    _search_button = new QPushButton {" Search"};

    QIcon search_icon {"assets/icons/search_b.png"};
    _search_button  -> setIcon(search_icon);

    connect(_search_button, &QPushButton::pressed,
            this, &SearchView::search);

    connect(_search_input, &QLineEdit::returnPressed,
            this, &SearchView::search);

    _search_input -> setPlaceholderText("Search by album, song, or artist...");

    _search_box -> setLayout(_search_layout);

    _search_layout -> addWidget(_search_input);
    _search_layout -> addWidget(_search_button);

    _layout -> addWidget(_search_box);
}

void SearchView::search ()
{
    QString query = _search_input -> text();

    if (_results)
    {
        delete _results;
        _results = nullptr;
    }

    if (!(query.isEmpty()))
    {
        Database db;

        if (result_list)
        {
            clearResultList();
        }

        result_list = db.searchDatabase(query.toStdString());

        _results = new QTableWidget {result_list -> getSize(), 5};
        QStringList col_headers {"#", "Title", "Artist", "Album", "Duration"};

        _results -> setHorizontalHeaderLabels(col_headers);
        _results -> horizontalHeader() -> setSectionResizeMode(
            QHeaderView::Stretch);
        _results -> setEditTriggers(QAbstractItemView::NoEditTriggers);

        _results -> horizontalHeader() -> setSectionResizeMode(
            0, QHeaderView::ResizeToContents);

        Song* current = result_list -> getHead();
        TableButton* play_button = nullptr;

        for (int i = 0; i < result_list -> getSize(); i++)
        {
            play_button = new TableButton {true};
            play_button -> setButtonIndex(i);

            connect(play_button, &QPushButton::released,
                    this, &SearchView::playSong);

            _results -> setIndexWidget(_results -> model() -> index(i, 0),
                                        play_button);

            play_button = nullptr;

            QTableWidgetItem* song   = new QTableWidgetItem {
                QString::fromStdString(current -> getTitle())};
            QTableWidgetItem* artist = new QTableWidgetItem {
                QString::fromStdString(current -> getArtist())};
            QTableWidgetItem* album  = new QTableWidgetItem {
                QString::fromStdString(current -> getAlbum())};
            QTableWidgetItem* length = new QTableWidgetItem {
                QString::fromStdString(current -> getLength())};

            _results -> setItem(i, 1, song);
            _results -> setItem(i, 2, artist);
            _results -> setItem(i, 3, album);
            _results -> setItem(i, 4, length);

            current = current -> getNext();
        }

        _layout -> addWidget(_results);
    }
}

void SearchView::clearResultList ()
{
    Song* current_song  = result_list -> getHead();
    Song* previous_song = nullptr;

    while (current_song)
    {
        previous_song = current_song;
        current_song  = current_song -> getNext();

        delete previous_song;
    }

    delete result_list;
}

void SearchView::playSong ()
{
    TableButton* calling_button = static_cast<TableButton*> (sender());
    int add_idx = calling_button -> getButtonIndex();

    Song* current = result_list -> getHead();

    /* Traverse result list to find the song to play. */
    for (int i = 0; i < add_idx; i++)
    {
        current = current -> getNext();
    }

    Database db;
    current -> setArtworkB64(db.getB64Artwork(current -> getAlbum()));

    _window -> getMusicPlayer() -> playSong(
        QString::fromStdString(current -> getFile()),
        QString::fromStdString(current -> getTitle()),
        QString::fromStdString(current -> getArtist()),
        QString::fromStdString(current -> getLength()),
        current -> getArtB64()
    );

    _window -> getMusicPlayer() -> resetSongList();
    _window -> getMusicPlayer() -> setSongList(result_list, add_idx);
}
