#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QWidget>
#include <QHBoxLayout>

#include "src/gui/MainWindow.h"

#include "src/gui/SideBar.h"
#include "src/gui/LibraryView.h"
#include "src/gui/PlaylistView.h"
#include "src/gui/ImportView.h"
#include "src/gui/SearchView.h"

class MainWindow;
class SideBar;

class ViewManager : public QWidget
{
    public:
        ViewManager (MainWindow* parent_window);

        void setActiveView    (int idx);
        void resizeActiveView ();

    private:
        enum Views {Library, Playlist, Import, Search};

        MainWindow*  _window = nullptr;
        QHBoxLayout* _layout = nullptr;

        SideBar* sidebar     = nullptr;
        QWidget* active_view = nullptr;
        Views    view_idx    = Library;
};

#endif
