#include "SongsDialog.h"

SongsDialog::SongsDialog (QString playlist)
{
    _layout = new QVBoxLayout {};
    _layout -> setAlignment(Qt::AlignTop);

    _playlist = playlist;

    _layout -> setSpacing(0);

    setWindowTitle("Add Songs to Playlist");
    setFixedSize(700, 300);

    /** Search Box **/

    search_box    = new QWidget     {};
    box_layout    = new QHBoxLayout {};
    search_input  = new QLineEdit   {};
    search_button = new QPushButton {" Search"};
    done_button   = new QPushButton {" Go Back"};

    search_button -> setIcon(search_icon);
    connect(search_button, &QPushButton::pressed,
            this, &SongsDialog::findSongs);
    connect(search_input, &QLineEdit::returnPressed,
            this, &SongsDialog::findSongs);

    done_button -> setIcon(go_back_icon);
    connect(done_button, &QPushButton::released,
            this, &SongsDialog::closeDialog);

    search_input -> setPlaceholderText("Search songs to add...");

    box_layout -> addWidget(search_input);
    box_layout -> addWidget(search_button);
    box_layout -> addWidget(done_button);

    search_box -> setLayout(box_layout);

    _layout -> addWidget(search_box);

    /** Status Label **/

    status_widget = new QWidget     {};
    status_layout = new QHBoxLayout {};
    status_label  = new QLabel      {"(...)"};

    status_label -> setAlignment(Qt::AlignCenter);

    status_layout -> addWidget(status_label);
    status_widget -> setLayout(status_layout);

    _layout -> addWidget(status_widget);

    setLayout(_layout);
}

void SongsDialog::addSong ()
{
    TableButton* calling_button = static_cast<TableButton*> (sender());
    int add_idx = calling_button -> getButtonIndex();

    Song* current = result_list -> getHead();

    /* Traverse results list to find the song to add. */
    for (int i = 0; i < add_idx; i++)
    {
        current = current -> getNext();
    }

    Database db;
    db.insertSongOnPlaylist(1, current -> getFile(), _playlist.toStdString());

    QString status_text
    {
        "Added " + QString::fromStdString(current -> getTitle())
                 + " to " + _playlist + "."
    };

    status_label -> setText(status_text);
}

void SongsDialog::findSongs ()
{
    QString query = search_input -> text();

    if (results_table)
    {
        delete results_table;
        results_table = nullptr;
    }

    if (!(query.isEmpty()))
    {
        Database db;

        if (result_list)
        {
            clearResultList();
        }

        result_list = db.searchDatabase(query.toStdString());

        results_table = new QTableWidget {result_list -> getSize(), 4};
        QStringList col_headers {"Add", "Title", "Artist", "Album"};

        results_table -> setHorizontalHeaderLabels(col_headers);
        results_table -> horizontalHeader() -> setSectionResizeMode(
            QHeaderView::Stretch);
        results_table -> setEditTriggers(QAbstractItemView::NoEditTriggers);

        results_table -> horizontalHeader() -> setSectionResizeMode(
            0, QHeaderView::ResizeToContents);

        Song* current = result_list -> getHead();

        TableButton* add_button = nullptr;

        for (int i = 0; i < result_list -> getSize(); i++)
        {
            /* Add Button */
            add_button = new TableButton {false};
            add_button -> setButtonIndex(i);

            connect(add_button, &QPushButton::released,
                    this, &SongsDialog::addSong);

            /* Table widget assumes ownership of add button. */
            results_table -> setIndexWidget(
                results_table -> model() -> index(i, 0), add_button);

            add_button = nullptr;

            QTableWidgetItem* song   = new QTableWidgetItem {
                QString::fromStdString(current -> getTitle())};
            QTableWidgetItem* artist = new QTableWidgetItem {
                QString::fromStdString(current -> getArtist())};
            QTableWidgetItem* album  = new QTableWidgetItem {
                QString::fromStdString(current -> getAlbum())};

            results_table -> setItem(i, 1, song);
            results_table -> setItem(i, 2, artist);
            results_table -> setItem(i, 3, album);

            current = current -> getNext();
        }

        _layout -> addWidget(results_table);
    }
}

void SongsDialog::closeDialog ()
{
    close();
}

void SongsDialog::clearResultList ()
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
