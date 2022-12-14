#include "Database.h"

Database::Database ()
{
    int status = 0;
    status = sqlite3_open("ensemble.db", &_db);

    if (status)
    {
        std::cout << "Database::Database() - Error connecting to database."
                  << std::endl;
    }
    else
    {
        std::cout << "Database::Database() - Connected to database."
                  << std::endl;
    }
}

Database::~Database ()
{
    sqlite3_close(_db);
}

void Database::initializeDatabase ()
{
    sqlite3_exec(_db, DB_TABLES.c_str(), nullptr, 0, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::initializeDatabase() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::initializeDatabase() - Created database tables."
                  << std::endl;
    }
}

void Database::insertSong (string file_path, int song_idx, string title,
                           string artist, string length)
{
    int status = 0;
    sqlite3_stmt* stmt;

    string sql
    {
        "INSERT INTO Songs (filePath, songIndex, title, artist, length) "
            "VALUES (?, ?, ?, ?, ?);"
    };

    sqlite3_prepare_v2(_db, sql.c_str(), sql.length(), &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, file_path.c_str(), file_path.length(),
                      SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, song_idx);
    sqlite3_bind_text(stmt, 3, title.c_str(), title.length(),
                      SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, artist.c_str(), artist.length(),
                      SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, length.c_str(), length.length(),
                      SQLITE_STATIC);

    status = sqlite3_step(stmt);

    if (status != SQLITE_DONE)
    {
        std::cout << "Database::insertSong() - Error inserting values ("
                  << title  << ", " << song_idx << ", "
                  << artist << ", " << length   << ") to database."
                  << std::endl;

        std::cout << "SQL Status = " << status << std::endl;
    }
    else
    {
        std::cout << "Database::insertSong() - Added ("
                  << title  << ", " << song_idx << ", "
                  << artist << ", " << length   << ") to database."
                  << std::endl;
    }
}

void Database::insertAlbum (string title, string artist, string img_b64)
{
    int status;
    sqlite3_stmt* stmt;

    string sql
    {
        "INSERT OR IGNORE INTO Albums (title, artist, imageB64) "
            "VALUES(?, ?, ?);"
    };

    sqlite3_prepare_v2(_db, sql.c_str(), sql.length(), &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, title.c_str(), title.length(),
                      SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, artist.c_str(), artist.length(),
                      SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, img_b64.c_str(), img_b64.length(),
                      SQLITE_STATIC);

    status = sqlite3_step(stmt);

    if (status != SQLITE_DONE)
    {
        std::cout << "Database::insertAlbum() - Error inserting values ("
                  << title << ", " << artist
                  << ") to database."
                  << std::endl;

        std::cout << "SQL Status = " << status << std::endl;
    }
    else
    {
        std::cout << "Database::insertAlbum() - Added ("
                  << title << ", " << artist
                  << ") to database."
                  << std::endl;
    }
}

void Database::insertSongOnAlbum (string song, string album, string artist)
{
    int status;
    sqlite3_stmt* stmt;

    string sql
    {
        "INSERT INTO SongOnAlbum (song, album, artist) "
            "VALUES(?, ?, ?);"
    };

    sqlite3_prepare_v2(_db, sql.c_str(), sql.length(), &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, song.c_str(), song.length(),
                      SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, album.c_str(), album.length(),
                      SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, artist.c_str(), artist.length(),
                      SQLITE_STATIC);

    status = sqlite3_step(stmt);

    if (status != SQLITE_DONE)
    {
        std::cout << "Database::insertSongOnAlbum() - Error inserting values ("
                  << song   << ", " << album << ", "
                  << artist << ") to database."
                  << std::endl;

        std::cout << "SQL Status = " << status << std::endl;
    }
    else
    {
        std::cout << "Database::insertSongOnAlbum() - Added ("
                  << song   << ", " << album << ", "
                  << artist << ") to database."
                  << std::endl;
    }
}

void Database::insertPlaylist (string playlist_name)
{
    int status;
    sqlite3_stmt* stmt;

    string sql
    {
        "INSERT INTO Playlists (playlistName) "
            "VALUES(?);"
    };

    sqlite3_prepare_v2(_db, sql.c_str(), sql.length(), &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, playlist_name.c_str(), playlist_name.length(),
                      SQLITE_STATIC);

    status = sqlite3_step(stmt);

    if (status != SQLITE_DONE)
    {
        std::cout << "Database::insertPlaylist() - Error inserting values ("
                  << playlist_name << ") to database."
                  << std::endl;

        std::cout << "SQL Status = " << status << std::endl;
    }
    else
    {
        std::cout << "Database::insertPlaylist() - Added ("
                  << playlist_name << ") to database."
                  << std::endl;
    }
}

void Database::insertSongOnPlaylist (int idx, string file_path, string playlist)
{
    int status;
    sqlite3_stmt* stmt;

    string sql
    {
        "INSERT INTO SongOnPlaylist (songIndex, filePath, playlistName) "
            "VALUES(?, ?, ?);"
    };

    sqlite3_prepare_v2(_db, sql.c_str(), sql.length(), &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, idx);
    sqlite3_bind_text(stmt, 2, file_path.c_str(), file_path.length(),
                      SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, playlist.c_str(), playlist.length(),
                      SQLITE_STATIC);

    status = sqlite3_step(stmt);

    if (status != SQLITE_DONE)
    {
        std::cout << "Database::insertSongOnPlaylist() - Error inserting values"
                  << " (" << idx      << ", " << file_path << ", "
                  << playlist << ") to database."
                  << std::endl;

        std::cout << "SQL Status = " << status << std::endl;
    }
    else
    {
        std::cout << "Database::insertSongOnPlaylist() - Added ("
                  << idx      << ", " << file_path << ", "
                  << playlist << ") to database."
                  << std::endl;
    }
}

SongList* Database::getSong (string file_path)
{
    SongList* song_obj = new SongList {};

    string sql
    {
        "SELECT Songs.title, Songs.artist, Songs.length, Albums.imageB64 "
        "FROM Songs, SongOnAlbum, Albums "
        "WHERE Songs.filePath = SongOnAlbum.song AND "
        "      SongOnAlbum.album = Albums.title AND "
        "      SongOnAlbum.artist = Albums.artist AND "
        "      Songs.filePath = '" + file_path + "';"
    };

    sqlite3_exec(_db, sql.c_str(), singleSongCallback, song_obj, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getSong() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getSong() - Retrieved song."
                  << std::endl;
    }

    return song_obj;
}

AlbumList* Database::getAlbumList ()
{
    AlbumList* album_list = new AlbumList {};

    string sql
    {
        "SELECT * "
        "FROM Albums "
        "ORDER BY artist, title;"
    };

    sqlite3_exec(_db, sql.c_str(), albumCallback, album_list, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getAlbumList() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getAlbumList() - Retrieved album list."
                  << std::endl;
    }

    return album_list;
}

SongList* Database::getSongList (string album)
{
    SongList* song_list = new SongList {};

    string sql
    {
        "SELECT filePath, songIndex, title, Songs.artist, length "
        "FROM SongOnAlbum, Songs "
        "WHERE album = '" + album + "' AND "
        "      song = filePath "
        "ORDER BY songIndex;"
    };

    sqlite3_exec(_db, sql.c_str(), songCallback, song_list, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getSongList() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getSongList() - Retrieved song list for "
                  << album << std::endl;
    }

    return song_list;
}

SongList* Database::getPlayList (string playlist)
{
    SongList* play_list = new SongList {};

    string sql
    {
        "SELECT Songs.title, Songs.artist, SongOnAlbum.album, "
        "       Songs.length, SongOnPlaylist.filePath "
        "FROM SongOnPlaylist, Songs, SongOnAlbum "
        "WHERE SongOnPlaylist.playlistName = '" + playlist + "' AND "
        "      SongOnAlbum.song = SongOnPlaylist.filePath AND "
        "      SongOnPlaylist.filePath = Songs.filePath "
        "ORDER BY SongOnPlaylist.songIndex;"
    };

    sqlite3_exec(_db, sql.c_str(), queryCallback, play_list, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getPlayList() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getPlayList() - Retrieved song list for "
                  << playlist << std::endl;
    }

    return play_list;
}

PlaylistList* Database::getPlaylistList ()
{
    PlaylistList* playlist_list = new PlaylistList {};

    string sql
    {
        "SELECT playlistName "
        "FROM Playlists;"
    };

    sqlite3_exec(_db, sql.c_str(), playlistCallback, playlist_list, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getPlaylistList() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getPlaylistList() - Retrieved playlist list."
                  << std::endl;
    }

    return playlist_list;
}

string Database::getB64Artwork (string album)
{
    string art_b64 = "";

    string sql
    {
        "SELECT imageB64 "
        "FROM Albums "
        "WHERE title = '" + album + "';"
    };

    sqlite3_exec(_db, sql.c_str(), artworkCallback, &art_b64, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getB64Artwork() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getB64Artwork() - Retrieved artwork."
                  << std::endl;
    }

    return art_b64;
}

int Database::getSongCount ()
{
    int song_count = 0;
    string sql
    {
        "SELECT COUNT(filePath) "
        "FROM Songs;"
    };

    sqlite3_exec(_db, sql.c_str(), countCallback, &song_count, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getSongCount() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getSongCount() - Retrieved song count of "
                  << song_count << std::endl;
    }

    return song_count;
}

int Database::getAlbumCount ()
{
    int album_count = 0;
    string sql
    {
        "SELECT COUNT(title) "
        "FROM Albums;"
    };

    sqlite3_exec(_db, sql.c_str(), countCallback, &album_count, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getAlbumCount() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getAlbumCount() - Retrieved album count of "
                  << album_count << std::endl;
    }

    return album_count;
}

int Database::getArtistCount ()
{
    int artist_count = 0;
    string sql
    {
        "SELECT COUNT(DISTINCT artist) "
        "FROM Songs;"
    };

    sqlite3_exec(_db, sql.c_str(), countCallback, &artist_count, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getArtistCount() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getArtistCount() - Retrieved artist count of "
                  << artist_count << std::endl;
    }

    return artist_count;
}

int Database::getPlaylistCount ()
{
    int playlist_count = 0;
    string sql
    {
        "SELECT COUNT(DISTINCT playlistName) "
        "FROM Playlists;"
    };

    sqlite3_exec(_db, sql.c_str(), countCallback, &playlist_count, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getPlaylistCount() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getPlaylistCount() - Retrieved count of "
                  << playlist_count << std::endl;
    }

    return playlist_count;
}

int Database::getListSongCount (string playlist)
{
    int song_count = 0;
    string sql
    {
        "SELECT COUNT(filePath) "
        "FROM SongOnPlaylist "
        "WHERE playlistName = '" + playlist + "';"
    };

    sqlite3_exec(_db, sql.c_str(), countCallback, &song_count, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getListSongCount() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getListSongCount() - Retrieved count of "
                  << song_count << std::endl;
    }

    return song_count;
}

void Database::deletePlaylist (string playlist)
{
    string sql
    {
        "DELETE "
        "FROM Playlists "
        "WHERE playlistName = '" + playlist + "';"
    };

    sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::deletePlaylist() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::deletePlaylist() - Deleted playlist "
                  << playlist << " from database."
                  << std::endl;
    }
}

SongList* Database::searchDatabase (string query)
{
    SongList* song_list = new SongList {};

    string sql
    {
        "SELECT Songs.title, SongOnAlbum.artist, "
        "       SongOnAlbum.album, Songs.length, Songs.filePath "
        "FROM SongOnAlbum, Songs "
        "WHERE SongOnAlbum.song = Songs.filePath AND "
        "      (Songs.title        LIKE '%" + query + "%' OR "
        "       SongOnAlbum.album  LIKE '%" + query + "%' OR "
        "       SongOnAlbum.artist LIKE '%" + query + "%');"
    };

    sqlite3_exec(_db, sql.c_str(), queryCallback, song_list, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::searchDatabase() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::searchDatabase() - Retrieved results for query "
                  << query << std::endl;
    }

    return song_list;
}

void Database::setLibraryPath (string library_path)
{
    string sql_a
    {
        "DELETE FROM Albums;"
        "DELETE FROM Songs;"
        "DELETE FROM SongOnAlbum;"
        "DELETE FROM Preferences;"
        "DELETE FROM Playlists;"
        "DELETE FROM SongOnPlaylist;"
    };

    sqlite3_exec(_db, sql_a.c_str(), nullptr, nullptr, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::setLibraryPath() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::setLibraryPath() - Cleared tables."
                  << std::endl;
    }

    int status;
    sqlite3_stmt* stmt;

    string sql_b
    {
        "INSERT INTO Preferences (libPath, init) "
            "VALUES(?, ?);"
    };

    sqlite3_prepare_v2(_db, sql_b.c_str(), sql_b.length(), &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, library_path.c_str(), library_path.length(),
                      SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, 1);

    status = sqlite3_step(stmt);

    if (status != SQLITE_DONE)
    {
        std::cout << "Database::setLibraryPath() - Error setting path ("
                  << library_path << ") to database."
                  << std::endl;

        std::cout << "SQL Status = " << status << std::endl;
    }
    else
    {
        std::cout << "Database::setLibraryPath() - Set path to ("
                  << library_path << ") to database."
                  << std::endl;
    }
}

string Database::getLibraryPath ()
{
    pair<string, int> result_pair;
    result_pair.first  = "";
    result_pair.second = 0;

    string sql
    {
        "SELECT * "
        "FROM Preferences;"
    };

    sqlite3_exec(_db, sql.c_str(), prefCallback, &result_pair, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getLibraryPath() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getLibraryPath() - Retrieved path "
                  << result_pair.first << ") from database."
                  << std::endl;
    }

    return result_pair.first;
}

void Database::setInitState (bool state)
{
    int status;
    sqlite3_stmt* stmt;

    string sql
    {
        "UPDATE Preferences "
        "SET init = ?;"
    };

    sqlite3_prepare_v2(_db, sql.c_str(), sql.length(), &stmt, nullptr);

    if (state)
    {
        sqlite3_bind_int(stmt, 1, 1);
    }
    else
    {
        sqlite3_bind_int(stmt, 1, 0);
    }

    status = sqlite3_step(stmt);

    if (status != SQLITE_DONE)
    {
        std::cout << "Database::setInitState() - Error setting init state."
                  << std::endl;

        std::cout << "SQL Status = " << status << std::endl;
    }
    else
    {
        std::cout << "Database::setInitState() - Set init state."
                  << std::endl;
    }
}

bool Database::getInitState ()
{
    pair<string, int> result_pair;

    string sql
    {
        "SELECT * "
        "FROM Preferences;"
    };

    sqlite3_exec(_db, sql.c_str(), prefCallback, &result_pair, &_emsg);

    if (_emsg)
    {
        std::cout << "Database::getInitState() - SQL Error: "
                  << _emsg << std::endl;
        sqlite3_free(_emsg);
    }
    else
    {
        std::cout << "Database::getInitState() - Retrieved init state ("
                  << result_pair.second << ") from database."
                  << std::endl;
    }

    return result_pair.second;
}

int Database::albumCallback (void* album_list, int count,
                             char** data, char** columns)
{
    string title = data[0];
    string artist = data[1];
    string img_b64 = data[2];

    std::cout << "Database::albumCallback() - Retrieved " << count
              << " columns." << std::endl;

    for (int i = 0; i < count; i++)
    {
        std::cout << columns[i] << ' ';
    }
    std::cout << std::endl;

    std::cout << "Database::albumCallback() - Retrieved values ("
              << title << ", " << artist
              << ") from database."
              << std::endl;

    /* Build Album object. */
    Album* new_album = new Album {title, artist, img_b64};

    /* Add Album to AlbumList, which assumes ownership. */
    static_cast<AlbumList*> (album_list) -> addAlbum(new_album);

    new_album = nullptr;

    return 0;
}

int Database::songCallback (void* song_list, int count,
                            char** data, char** columns)
{
    string file   = data[0];
    int    idx    = atoi(data[1]);
    string song   = data[2];
    string artist = data[3];
    string length = data[4];

    std::cout << "Database::songCallback() - Retrieved " << count
              << " columns." << std::endl;

    for (int i = 0; i < count; i++)
    {
        std::cout << columns[i] << ' ';
    }
    std::cout << std::endl;

    std::cout << "Database::songCallback() - Retrieved values ("
              << idx << ", " << song << ", " << artist << ", " << length
              << ") from database."
              << std::endl;

    /* Build Song object. */
    Song* new_song = new Song {file, idx, song, length};

    /* Add Song to SongList, which assumes ownership. */
    static_cast<SongList*> (song_list) -> addSong(new_song);

    new_song = nullptr;

    return 0;
}

int Database::playlistCallback (void* playlist_list, int count,
                                char** data, char** columns)
{
    string name = data[0];

    std::cout << "Database::playlistCallback() - Retrieved " << count
              << " columns." << std::endl;

    for (int i = 0; i < count; i++)
    {
        std::cout << columns[i] << ' ';
    }
    std::cout << std::endl;

    std::cout << "Database::playlistCallback() - Retrieved values ("
              << name << ") from database."
              << std::endl;

    /* Build Playlist object. */
    Playlist* new_playlist = new Playlist {name};

    /* Add Playlist to PlaylistList, which assumes ownership. */
    static_cast<PlaylistList*> (playlist_list) -> addPlaylist(new_playlist);

    new_playlist = nullptr;

    return 0;
}

int Database::queryCallback (void* song_list, int count,
                             char** data, char** columns)
{
    string song      = data[0];
    string artist    = data[1];
    string album     = data[2];
    string length    = data[3];
    string file_path = data[4];

    std::cout << "Database::queryCallback() - Retrieved " << count
              << " columns." << std::endl;

    for (int i = 0; i < count; i++)
    {
        std::cout << columns[i] << ' ';
    }
    std::cout << std::endl;

    std::cout << "Database::queryCallback() - Retrieved values ("
              << song << ", " << artist << ", " << album << ", " << length
              << ", " << file_path << ") from database."
              << std::endl;

    /* Build Song object. */
    Song* new_song = new Song {song, artist, album, length, file_path};

    /* Add Album to AlbumList, which assumes ownership. */
    static_cast<SongList*> (song_list) -> addSong(new_song);

    new_song = nullptr;

    return 0;
}

int Database::prefCallback (void* result_pair, int count,
                            char** data, char** columns)
{
    string file_path = data[0];
    int    status    = atoi(data[1]);

    std::cout << "Database::prefCallback() - Retrieved " << count
              << " columns." << std::endl;

    for (int i = 0; i < count; i++)
    {
        std::cout << columns[i] << ' ';
    }
    std::cout << std::endl;

    static_cast<pair<string, int>*> (result_pair) -> first  = file_path;
    static_cast<pair<string, int>*> (result_pair) -> second = status;

    std::cout << "Database::prefCallback() - Retrieved values ("
              << file_path << ", " << status
              << ") from database."
              << std::endl;

    return 0;
}

int Database::countCallback (void* table_count, int count,
                             char** data, char** columns)
{
    int t_count = atoi(data[0]);

    *(static_cast<int*> (table_count)) = t_count;

    std::cout << "Database::countCallback() - Retrieved " << count
              << " columns." << std::endl;

    for (int i = 0; i < count; i++)
    {
        std::cout << columns[i] << ' ';
    }
    std::cout << std::endl;

    std::cout << "Database::countCallback() - Retrieved value ("
              << t_count << ") from database."
              << std::endl;

    return 0;
}

int Database::artworkCallback (void* artwork, int count,
                               char** data, char** columns)
{
    string art_b64 = data[0];

    *(static_cast<string*> (artwork)) = art_b64;

    std::cout << "Database::artworkCallback() - Retrieved " << count
              << " columns." << std::endl;

    for (int i = 0; i < count; i++)
    {
        std::cout << columns[i] << ' ';
    }
    std::cout << std::endl;

    std::cout << "Database::countCallback() - Retrieved artwork from database."
              << std::endl;

    return 0;
}

int Database::singleSongCallback (void* song_obj, int count,
                                  char** data, char** columns)
{
    string title   = data[0];
    string artist  = data[1];
    string length  = data[2];
    string art_b64 = data[3];

    std::cout << "Database::singleSongCallback() - Retrieved " << count
              << " columns." << std::endl;

    for (int i = 0; i < count; i++)
    {
        std::cout << columns[i] << ' ';
    }
    std::cout << std::endl;

    Song* new_song = new Song {title, artist, length, art_b64};

    static_cast<SongList*> (song_obj) -> addSong(new_song);

    std::cout << "Database::singleSongCallback() - Retrieved song."
              << std::endl;

    return 0;
}
