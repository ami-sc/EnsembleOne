#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

class AddDialog : public QDialog
{
    public:
        AddDialog ();

        void submitAction ();

        QString getText ();

    private:
        QHBoxLayout* _layout = nullptr;

        QGroupBox*   name_box   = nullptr;
        QHBoxLayout* box_layout = nullptr;

        QLineEdit*   name_input    = nullptr;
        QPushButton* submit_button = nullptr;
};

#endif
