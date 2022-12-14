#include "ConfirmDialog.h"

ConfirmDialog::ConfirmDialog ()
{
    setWindowTitle("Delete Playlist");
    setFixedSize(380, 100);

    _layout = new QVBoxLayout {};

    confirm_text = new QLabel
    {
        "Are you sure you want to delete this playlist? This is irreversible."
    };

    _layout -> addWidget(confirm_text, Qt::AlignCenter);

    button_pair    = new QWidget     {};
    pair_layout    = new QHBoxLayout {};
    confirm_button = new QPushButton {"Yes"};
    cancel_button  = new QPushButton {"No"};

    confirm_button -> setMaximumWidth(80);

    connect(confirm_button, &QPushButton::released,
            this, &ConfirmDialog::confirmAction);

    cancel_button  -> setMaximumWidth(80);

    connect(cancel_button, &QPushButton::released,
            this, &ConfirmDialog::cancelAction);

    pair_layout -> addWidget(confirm_button);
    pair_layout -> addWidget(cancel_button);

    button_pair -> setLayout(pair_layout);

    _layout -> addWidget(button_pair);

    setLayout(_layout);
}

void ConfirmDialog::confirmAction ()
{
    to_delete = true;
    close();
}

void ConfirmDialog::cancelAction ()
{
    to_delete = false;
    close();
}
