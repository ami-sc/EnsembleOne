#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <QPalette>

class SideBar : public QWidget
{
    public:
        SideBar ();

    private:
        QVBoxLayout* _layout = nullptr;

        QPushButton* library_button    = nullptr;
        QPushButton* playlist_button   = nullptr;
        QPushButton* statistics_button = nullptr;
        QPushButton* search_button     = nullptr;
};

#endif
