#ifndef SONGSDIALOG_H
#define SONGSDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QString>
#include <QStringList>
#include <QModelIndexList>

#include <iostream>

#include "src/database/Database.h"
#include "src/gui/Song.h"
#include "src/gui/TableButton.h"
#include "src/structures/SongList.h"

class SongsDialog : public QDialog
{
    public:
        SongsDialog (QString playlist);

        void addSong     ();
        void findSongs   ();
        void closeDialog ();

    private:
        void clearResultList ();

        QString      _playlist = nullptr;
        QVBoxLayout* _layout   = nullptr;

        QWidget*     search_box    = nullptr;
        QHBoxLayout* box_layout    = nullptr;
        QLineEdit*   search_input  = nullptr;
        QPushButton* search_button = nullptr;
        QPushButton* done_button   = nullptr;

        QTableWidget* results_table = nullptr;

        QWidget*     status_widget = nullptr;
        QHBoxLayout* status_layout = nullptr;
        QLabel*      status_label  = nullptr;

        QIcon search_icon  {"assets/icons/search_b.png"};
        QIcon go_back_icon {"assets/icons/go_back.png"};

        SongList* result_list = nullptr;
};

#endif
