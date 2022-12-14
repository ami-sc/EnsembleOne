######################################################################
# Ensemble Project File
######################################################################

TEMPLATE = app
TARGET = Ensemble
INCLUDEPATH += . \
               "/usr/include/taglib"

# Input
HEADERS += src/database/Database.h \
           src/database/sqlite3.h \
           src/gui/Album.h \
           src/gui/ExpandedAlbum.h \
           src/gui/ImportView.h \
           src/gui/LibraryView.h \
           src/gui/MainWindow.h \
           src/gui/MusicPlayer.h \
           src/gui/Playlist.h \
           src/gui/PlaylistView.h \
           src/gui/SearchView.h \
           src/gui/SideBar.h \
           src/gui/Song.h \
           src/gui/ViewManager.h \
           src/gui/SidebarButton.h \
           src/gui/AddDialog.h \
           src/gui/SongTable.h \
           src/gui/ConfirmDialog.h \
           src/gui/SongsDialog.h \
           src/gui/TableButton.h \
           src/structures/AlbumList.h \
           src/structures/PlaylistList.h \
           src/structures/SongList.h
SOURCES += src/main.cpp \
           src/database/Database.cpp \
           src/database/sqlite3.c \
           src/gui/Album.cpp \
           src/gui/ExpandedAlbum.cpp \
           src/gui/ImportView.cpp \
           src/gui/LibraryView.cpp \
           src/gui/MainWindow.cpp \
           src/gui/MusicPlayer.cpp \
           src/gui/Playlist.cpp \
           src/gui/PlaylistView.cpp \
           src/gui/SearchView.cpp \
           src/gui/SideBar.cpp \
           src/gui/Song.cpp \
           src/gui/ViewManager.cpp \
           src/gui/SidebarButton.cpp \
           src/gui/AddDialog.cpp \
           src/gui/SongTable.cpp \
           src/gui/ConfirmDialog.cpp \
           src/gui/SongsDialog.cpp \
           src/gui/TableButton.cpp \
           src/structures/AlbumList.cpp \
           src/structures/PlaylistList.cpp \
           src/structures/SongList.cpp

LIBS += -ltag

QT += gui \
      widgets \
      core \
      multimedia
