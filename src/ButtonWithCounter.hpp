#ifndef BUTTONWITHCOUNTER_HPP
#define BUTTONWITHCOUNTER_HPP

#include "QPushButton"

#include <string>

class ButtonWithCounter : public QPushButton
{
    Q_OBJECT

public:
    explicit ButtonWithCounter(QWidget * parent = nullptr);
    explicit ButtonWithCounter(const QString & text, QWidget * parent = nullptr);

    void setMaxTimesToClick(unsigned short count);

signals:
    void clicked(bool checked = false);

private slots:
    void emitSignalIfPossible(bool checked = false);

private:
    void initConnection();

private:
    unsigned short maxTimesToClick = 0;
};

#endif // BUTTONWITHCOUNTER_HPP