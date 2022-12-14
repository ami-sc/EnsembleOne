#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H

#include <QWidget>
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

#include "src/database/Database.h"
#include "src/gui/Song.h"
#include "src/gui/TableButton.h"
#include "src/structures/SongList.h"
#include "src/gui/MainWindow.h"

class MainWindow;

class SearchView : public QWidget
{
    public:
        SearchView (MainWindow* window);

        void search   ();
        void playSong ();

    private:
        void clearResultList ();

        MainWindow*  _window = nullptr;
        QVBoxLayout* _layout = nullptr;

        QWidget*     _search_box    = nullptr;
        QHBoxLayout* _search_layout = nullptr;
        QLineEdit*   _search_input  = nullptr;
        QPushButton* _search_button = nullptr;

        QTableWidget* _results = nullptr;

        SongList* result_list = nullptr;
};

#endif
