#include "TableButton.h"

TableButton::TableButton (bool play)
{
    if (play)
    {
        setIcon(play_icon);
    }
    else
    {
        setIcon(add_icon);
    }

    setFixedWidth(45);
}
