#include "SidebarButton.h"

SidebarButton::SidebarButton (QString text, QString icon_b_path,
                              QString icon_w_path)
{
    icon_b.addFile(icon_b_path);
    icon_w.addFile(icon_w_path);

    setIcon(icon_b);
    setText(text);

    setStyleSheet(SB_DISABLED_BUTTON_CSS);
}

void SidebarButton::setEnabledStyle ()
{
    setIcon(icon_w);
    setStyleSheet(SB_ENABLED_BUTTON_CSS);
}

void SidebarButton::setDisabledStyle ()
{
    setIcon(icon_b);
    setStyleSheet(SB_DISABLED_BUTTON_CSS);
}
