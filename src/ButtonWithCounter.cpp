#include "ButtonWithCounter.hpp"

ButtonWithCounter::ButtonWithCounter(QWidget * parent)
    : QPushButton(parent)
{
    initConnection();
}

ButtonWithCounter::ButtonWithCounter(const QString & text, QWidget * parent)
    : QPushButton(parent), basicText(text)
{
    initConnection();
    updateText();
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

    updateText();
}

void ButtonWithCounter::emitSignalIfPossible(bool checked)
{
    if (maxTimesToClick && connectedFunction())
    {
        emit clickedAndAccepted(checked);
        --maxTimesToClick;

        if (maxTimesToClick == 0)
            setDisabled(true);

        updateText();
    }
}

void ButtonWithCounter::initConnection()
{
    connect(this, &QPushButton::clicked, this, &ButtonWithCounter::emitSignalIfPossible);
}

void ButtonWithCounter::updateText()
{
    setText(basicText + '(' + QString::number(maxTimesToClick) + ')');
}
