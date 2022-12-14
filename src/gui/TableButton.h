#ifndef TABLEBUTTON_H
#define TABLEBUTTON_H

#include <QPushButton>
#include <QIcon>

class TableButton : public QPushButton
{
    public:
        TableButton (bool play);

        inline void setButtonIndex (int idx) { button_idx = idx; }
        inline int  getButtonIndex ()        { return button_idx; }

    private:
        int button_idx = 0;

        QIcon add_icon  {"assets/icons/add.png"};
        QIcon play_icon {"assets/icons/play_c.png"};
};

#endif
