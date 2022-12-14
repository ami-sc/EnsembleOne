#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
    using std::string;
#include <utility>
    using std::pair;

#include "src/gui/Album.h"
#include "src/structures/AlbumList.h"
#include "src/gui/Song.h"
#include "src/structures/SongList.h"
#include "src/gui/Playlist.h"
#include "src/structures/PlaylistList.h"

#include "sqlite3.h"

const string DB_TABLES
{
    "CREATE TABLE IF NOT EXISTS Albums ("
        "title    TEXT,"
        "artist   TEXT,"
        "imageB64 TEXT,"
        "PRIMARY KEY (title, artist)"
    ");"

    "CREATE TABLE IF NOT EXISTS Songs ("
        "filePath  TEXT,"
        "songIndex INTEGER,"
        "title     TEXT DEFAULT 'Unknown Song',"
        "artist    TEXT DEFAULT 'Unknown Artist',"
        "length    TEXT DEFAULT '0:00',"
        "PRIMARY KEY (filePath)"
    ");"

    "CREATE TABLE IF NOT EXISTS Playlists ("
        "playlistName TEXT,"
        "PRIMARY KEY (playlistName)"
    ");"

    "CREATE TABLE IF NOT EXISTS Preferences ("
        "libPath TEXT,"
        "init    INTEGER"
    ");"

    "CREATE TABLE IF NOT EXISTS SongOnPlaylist ("
        "songIndex    INTEGER,"
        "filePath     TEXT,"
        "playlistName TEXT,"
        "FOREIGN KEY (filePath) "
        "    REFERENCES Songs (filePath) "
        "    ON DELETE CASCADE "
        "    ON UPDATE CASCADE,"
        "FOREIGN KEY (playlistName) "
        "    REFERENCES Playlists (playlistName) "
        "    ON DELETE CASCADE "
        "    ON UPDATE CASCADE"
    ");"

    "CREATE TABLE IF NOT EXISTS SongOnAlbum ("
        "song   TEXT,"
        "album  TEXT,"
        "artist INTEGER,"
        "FOREIGN KEY (song) "
        "    REFERENCES Songs (filePath) "
        "    ON DELETE CASCADE "
        "    ON UPDATE CASCADE,"
        "FOREIGN KEY (album, artist) "
        "    REFERENCES Albums (title, artist) "
        "    ON DELETE CASCADE "
        "    ON UPDATE CASCADE"
    ");"
};

class Song;
class SongList;

class Database
{
    public:
        Database  ();
        ~Database ();

        void initializeDatabase ();

        void insertSong        (string file_path, int song_idx, string title,
                                string artist, string length);
        void insertAlbum       (string title, string artist, string img_b64);
        void insertSongOnAlbum (string song, string album, string artist);

        void insertPlaylist       (string playlist_name);
        void insertSongOnPlaylist (int idx, string file_path, string playlist);

        SongList*     getSong          (string file_path);
        AlbumList*    getAlbumList     ();
        SongList*     getSongList      (string album);
        SongList*     getPlayList      (string playlist);
        PlaylistList* getPlaylistList  ();
        string        getB64Artwork    (string album);
        int           getSongCount     ();
        int           getAlbumCount    ();
        int           getArtistCount   ();
        int           getPlaylistCount ();
        int           getListSongCount (string playlist);

        void deletePlaylist (string playlist);

        SongList* searchDatabase (string query);

        void   setLibraryPath (string library_path);
        string getLibraryPath ();

        void setInitState (bool state);
        bool getInitState ();

    private:
        sqlite3* _db;
        char*    _emsg = nullptr;

        static int albumCallback      (void* album_list, int count,
                                       char** data, char** columns);
        static int songCallback       (void* song_list, int count,
                                       char** data, char** columns);
        static int playlistCallback   (void* song_list, int count,
                                       char** data, char** columns);
        static int queryCallback      (void* song_list, int count,
                                       char** data, char** columns);
        static int prefCallback       (void* result_pair, int count,
                                       char** data, char** columns);
        static int countCallback      (void* table_count, int count,
                                       char** data, char** columns);
        static int artworkCallback    (void* artwork, int count,
                                       char** data, char** columns);
        static int singleSongCallback (void* song, int count,
                                       char** data, char** columns);
};

#endif
