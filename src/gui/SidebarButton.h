#ifndef SIDEBARBUTTON_H
#define SIDEBARBUTTON_H

#include <QPushButton>
#include <QIcon>
#include <QString>

const QString SB_ENABLED_BUTTON_CSS
{
    "QPushButton {"
    "    color: #FFFFFF;"
    "    border: 1px hidden;"
    "    padding: 10px;"
    "    border-radius: 6px;"
    "    background: QLinearGradient(x1: 0, y1: 0, x2: 1, y2: 0,"
    "                                stop: 0 #6a11cb,"
    "                                stop: 1 #2575fc); }"
    "QPushButton::hover {"
    "    color: #FFFFFF;"
    "    background-color: #1e3c72;"
    "    border: 1px hidden;"
    "    padding: 10px;"
    "    border-radius: 6px; }"
    "QPushButton::pressed {"
    "    border: 1px hidden;"
    "    padding: 10px;"
    "    border-radius: 6px;"
    "    background: QLinearGradient(x1: 0, y1: 0, x2: 1, y2: 0,"
    "                                stop: 0 #6a11cb,"
    "                                stop: 1 #2575fc); }"
};

const QString SB_DISABLED_BUTTON_CSS
{
    "QPushButton {"
    "    border: 1px hidden;"
    "    padding: 10px;"
    "    border-radius: 6px; }"
    "QPushButton::hover {"
    "    background-color: #8FD3F4;"
    "    border: 1px hidden;"
    "    padding: 10px;"
    "    border-radius: 6px; }"
    "QPushButton::pressed {"
    "    border: 1px hidden;"
    "    padding: 10px;"
    "    border-radius: 6px;"
    "    background: QLinearGradient(x1: 0, y1: 0, x2: 1, y2: 0,"
    "                                stop: 0 #6a11cb,"
    "                                stop: 1 #2575fc); }"
};

class SidebarButton : public QPushButton
{
    public:
        SidebarButton (QString text, QString icon_b_path, QString icon_w_path);

        void setEnabledStyle  ();
        void setDisabledStyle ();

    private:
        QIcon icon_b;
        QIcon icon_w;
};

#endif
