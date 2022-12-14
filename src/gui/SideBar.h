#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QColor>
#include <QPalette>
#include <QLinearGradient>

#include "src/gui/ViewManager.h"
#include "src/gui/SidebarButton.h"

class ViewManager;

class SideBar : public QWidget
{
    public:
        SideBar (ViewManager* view_manager);

        void changeView ();

    private:
        enum Views {Library, Playlist, Import, Search};

        ViewManager* _viewmg = nullptr;
        QVBoxLayout* _layout = nullptr;

        SidebarButton* library_button  = nullptr;
        SidebarButton* playlist_button = nullptr;
        SidebarButton* import_button   = nullptr;
        SidebarButton* search_button   = nullptr;

        SidebarButton* enabled_button = nullptr;
};

#endif
