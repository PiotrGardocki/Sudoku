#include "ButtonWithCounter.hpp"

ButtonWithCounter::ButtonWithCounter(QWidget * parent)
    : QPushButton(parent)
{
    initConnection();
}

ButtonWithCounter::ButtonWithCounter(const QString & text, QWidget * parent)
    : QPushButton(text, parent)
{
    initConnection();
}

void ButtonWithCounter::setMaxTimesToClick(unsigned short count)
{
    maxTimesToClick = count;
}

void ButtonWithCounter::emitSignalIfPossible(bool checked)
{
    if (maxTimesToClick)
    {
        emit clicked(checked);
        --maxTimesToClick;
    }
}

void ButtonWithCounter::initConnection()
{
    connect(this, &QPushButton::clicked, this, &ButtonWithCounter::emitSignalIfPossible);
}
