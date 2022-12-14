#ifndef IMPORTVIEW_H
#define IMPORTVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QDirIterator>
#include <QGroupBox>
#include <QLabel>

/* TagLib Source Files */
#include <tag.h>
    using TagLib::Tag;
#include <fileref.h>
    using TagLib::FileRef;

/* M4A, AAC File Tag Support */
#include <mp4tag.h>
#include <mp4file.h>
#include <mp4item.h>
#include <mp4coverart.h>
#include <mp4properties.h>

#include <iostream>
#include <QString>
#include <string>
    using std::string;
#include <sstream>
    using std::stringstream;

#include "src/database/Database.h"

class ImportView : public QWidget
{
    public:
        ImportView ();

        QString selectDirectory        ();
        void    getDirectoryMediaFiles (QString dir_path);

    private:
        QVBoxLayout* _layout    = nullptr;
        QFileDialog* _importdlg = nullptr;

        /* Directory Box */
        QGroupBox*   dir_box       = nullptr;
        QHBoxLayout* dir_layout    = nullptr;
        QLineEdit*   directory     = nullptr;
        QPushButton* import_button = nullptr;

        /* Information Box */
        QGroupBox*   info_box     = nullptr;
        QVBoxLayout* info_layout  = nullptr;
        QLabel*      song_count   = nullptr;
        QLabel*      album_count  = nullptr;
        QLabel*      artist_count = nullptr;

        /* Icons */
        QIcon dir_icon {"assets/icons/folder.png"};
};

#endif
