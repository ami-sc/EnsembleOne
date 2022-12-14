#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>

class ConfirmDialog : public QDialog
{
    public:
        ConfirmDialog ();

        void confirmAction ();
        void cancelAction  ();

        inline bool getDeleteStatus () { return to_delete; }

    private:
        QVBoxLayout* _layout = nullptr;

        QLabel*      confirm_text   = nullptr;
        QWidget*     button_pair    = nullptr;
        QHBoxLayout* pair_layout    = nullptr;
        QPushButton* confirm_button = nullptr;
        QPushButton* cancel_button  = nullptr;

        bool to_delete = false;
};

#endif