#include "ImportView.h"

ImportView::ImportView ()
{
    Database db;

    _layout = new QVBoxLayout {};

    /** Directory Box **/

    dir_box       = new QGroupBox   {"Multimedia Directory"};
    dir_layout    = new QHBoxLayout {};
    directory     = new QLineEdit   {};
    import_button = new QPushButton {" Select Directory"};

    string lib_path = db.getLibraryPath();

    if (lib_path.empty())
    {
        directory -> setPlaceholderText("No directory imported...");
    }
    else
    {
        directory -> setPlaceholderText(QString::fromStdString(lib_path));
    }

    directory -> setEnabled(false);

    import_button -> setIcon(dir_icon);
    connect(import_button, &QPushButton::released,
            this, &ImportView::selectDirectory);

    dir_layout -> addWidget(directory);
    dir_layout -> addWidget(import_button);

    dir_box -> setLayout(dir_layout);
    _layout -> addWidget(dir_box);

    /** Information Box **/

    info_box     = new QGroupBox   {"Directory Statistics"  };
    info_layout  = new QVBoxLayout {};
    song_count   = new QLabel      {" ♪ Number of Songs: 0"  };
    album_count  = new QLabel      {" ♪ Number of Albums: 0" };
    artist_count = new QLabel      {" ♪ Number of Artists: 0"};

    string util_s;

    util_s = " ♪ Number of Songs: " + std::to_string(db.getSongCount());
    song_count -> setText(QString::fromStdString(util_s));

    util_s = " ♪ Number of Albums: " + std::to_string(db.getAlbumCount());
    album_count -> setText(QString::fromStdString(util_s));

    util_s = " ♪ Number of Artists: " + std::to_string(db.getArtistCount());
    artist_count -> setText(QString::fromStdString(util_s));

    info_layout -> addWidget(song_count);
    info_layout -> addWidget(album_count);
    info_layout -> addWidget(artist_count);

    info_box -> setLayout(info_layout);
    _layout -> addWidget(info_box);

    setLayout(_layout);
}

QString ImportView::selectDirectory ()
{
    _importdlg = new QFileDialog {this};

    /* Get the target directory. */
    QString import_dir = _importdlg -> getExistingDirectory();

    std::cout << "ImportView::selectDirectory() - Target Directory: "
              << import_dir.toStdString() << std::endl;

    getDirectoryMediaFiles(import_dir);

    return import_dir;
}

void ImportView::getDirectoryMediaFiles (QString dir_path)
{
    Database db;

    string title;
    string album;
    string artist;
    string artwork;
    int idx;

    int minutes;
    int seconds;

    string length;

    stringstream length_ss;
    stringstream artwork_ss;

    string util_s;

    /** M4A & AAC File Extractor **/

    QDirIterator dir_it (dir_path, {"*.m4a", "*.aac"},
                         QDir::Files, QDirIterator::Subdirectories);

    db.setLibraryPath(dir_path.toStdString());

    /* Iterate over possible .m4a files. */
    while (dir_it.hasNext())
    {
        QString current_file = dir_it.next();

        /* Get media file tags. */
        TagLib::MP4::File m4a_file (current_file.toStdString().c_str());
        TagLib::MP4::Tag* m4a_tags = m4a_file.tag();
        TagLib::MP4::Properties* m4a_prop = m4a_file.audioProperties();

        if (!(m4a_tags -> isEmpty()))
        {
            title  = m4a_tags -> title().to8Bit(true);
            album  = m4a_tags -> album().to8Bit(true);
            artist = m4a_tags -> artist().to8Bit(true);
            idx = m4a_tags -> track();

            minutes = (m4a_prop -> lengthInSeconds()) / 60;
            seconds = (m4a_prop -> lengthInSeconds()) % 60;

            if (seconds <= 10)
            {
                length_ss << minutes << ":0" << seconds;
            }

            else
            {
                length_ss << minutes << ':' << seconds;
            }

            length_ss >> length;

            TagLib::MP4::Item art_item = m4a_tags -> item("covr");
            TagLib::MP4::CoverArtList cover_arts = art_item.toCoverArtList();

            std::cout << idx << ':' << album << " - " << artist << std::endl;

            if (!cover_arts.isEmpty())
            {
                TagLib::MP4::CoverArt cover_art = cover_arts.front();
                artwork_ss << cover_art.data().toBase64();
                artwork_ss >> artwork;
            }

            db.insertAlbum(album, artist, artwork);
            db.insertSong(current_file.toStdString(), idx,
                          title, artist, length);
            db.insertSongOnAlbum(current_file.toStdString(), album, artist);
        }

        length_ss.clear();
        artwork_ss.clear();
    }

    directory -> setPlaceholderText(
        QString::fromStdString(db.getLibraryPath())
    );

    util_s = " ♪ Number of Songs: " + std::to_string(db.getSongCount());
    song_count -> setText(QString::fromStdString(util_s));

    util_s = " ♪ Number of Albums: " + std::to_string(db.getAlbumCount());
    album_count -> setText(QString::fromStdString(util_s));

    util_s = " ♪ Number of Artists: " + std::to_string(db.getArtistCount());
    artist_count -> setText(QString::fromStdString(util_s));
}
