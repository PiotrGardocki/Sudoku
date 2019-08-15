#ifndef BUTTONWITHCOUNTER_HPP
#define BUTTONWITHCOUNTER_HPP

#include <QPushButton>

#include <functional>

class ButtonWithCounter : public QPushButton
{
    Q_OBJECT

public:
    explicit ButtonWithCounter(QWidget * parent = nullptr);
    explicit ButtonWithCounter(const QString & text, QWidget * parent = nullptr);

    void connectFunction(std::function<bool()> functionToCall);
    void setMaxTimesToClick(unsigned short count);

signals:
    void clickedAndAccepted(bool checked = false);

private slots:
    void emitSignalIfPossible(bool checked = false);

private:
    void initConnection();
    void updateText();

private:
    std::function<bool()> connectedFunction;
    QString basicText;
    unsigned short maxTimesToClick = 0;
};

#endif // BUTTONWITHCOUNTER_HPP
