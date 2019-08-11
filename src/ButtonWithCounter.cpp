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

void ButtonWithCounter::connectFunction(std::function<bool()> functionToCall)
{
    connectedFunction = std::move(functionToCall);
}

void ButtonWithCounter::setMaxTimesToClick(unsigned short count)
{
    maxTimesToClick = count;
    if (count)
        setEnabled(true);
}

void ButtonWithCounter::emitSignalIfPossible(bool checked)
{
    if (maxTimesToClick && connectedFunction())
    {
        emit clicked(checked);
        --maxTimesToClick;

        if (maxTimesToClick == 0)
            setDisabled(true);
    }
}

void ButtonWithCounter::initConnection()
{
    connect(this, &QPushButton::clicked, this, &ButtonWithCounter::emitSignalIfPossible);
}
