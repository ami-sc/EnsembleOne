#include "AddDialog.h"

AddDialog::AddDialog ()
{
    setWindowTitle("New Playlist");
    setFixedSize(350, 100);

    _layout = new QHBoxLayout {};

    name_box   = new QGroupBox   {"Playlist Name"};
    box_layout = new QHBoxLayout {};

    name_input    = new QLineEdit   {};
    submit_button = new QPushButton {"Create Playlist"};

    name_input -> setPlaceholderText("Type a playlist name...");

    connect(name_input, &QLineEdit::returnPressed,
            this, &AddDialog::submitAction);

    connect(submit_button, &QPushButton::released,
            this, &AddDialog::submitAction);

    box_layout -> addWidget(name_input);
    box_layout -> addWidget(submit_button);

    name_box -> setLayout(box_layout);

    _layout -> addWidget(name_box);

    setLayout(_layout);
}

void AddDialog::submitAction ()
{
    close();
}

QString AddDialog::getText ()
{
    return name_input -> text();
}
