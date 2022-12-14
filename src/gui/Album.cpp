#include "Album.h"

Album::Album (string title, string artist, string art_b64)
{
    _layout = new QVBoxLayout {};
    artwork_b64 = art_b64;

    setStyleSheet(INACTIVE_ALBUM_CSS);

    _layout -> setSpacing(0);
    _layout -> setMargin(10);

    setFixedSize(160, 200);

    _title = new QLabel {};
    _title -> setAlignment(Qt::AlignCenter);

    _full_title = new QString {QString::fromStdString(title)};

    /* Elide text. */
    QFontMetrics fmetrics {_title -> font()};
    QString elided_txt = fmetrics.elidedText(QString::fromStdString(title),
                                             Qt::ElideRight, 130);
    _title -> setText(elided_txt);

    /* Set bold font for album title. */
    QFont _font = _title -> font();
    _font.setBold(true);
    _title -> setFont(_font);

    _artist = new QLabel {};
    _artist -> setAlignment(Qt::AlignCenter);

    QFontMetrics art_metrics {_artist -> font()};
    QString elided_art = art_metrics.elidedText(QString::fromStdString(artist),
                                                Qt::ElideRight, 130);
    _artist -> setText(elided_art);

    _img = new QPixmap {140, 140};
    _img -> loadFromData(QByteArray::fromBase64(art_b64.c_str()));

    _artbox  = new QLabel {};

    _artbox -> setPixmap(*_img);
    _artbox -> setScaledContents(true);

    _layout -> addWidget(_artbox);
    _layout -> addWidget(_title);
    _layout -> addWidget(_artist);

    setLayout(_layout);
}

Album::~Album ()
{
    delete _artwork;
    _artwork = nullptr;
}

bool Album::getExpandedState ()
{
    return _expandedstate;
}

void Album::setExpandedState (bool expanded)
{
    if (expanded)
    {
        setStyleSheet(ACTIVE_ALBUM_CSS);

        update();

        _expandedstate = true;
    }
    else
    {
        setStyleSheet(INACTIVE_ALBUM_CSS);

        update();

        _expandedstate = false;
    }

}
