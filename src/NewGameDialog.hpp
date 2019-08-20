#ifndef NEWGAMEDIALOG_HPP
#define NEWGAMEDIALOG_HPP

#include <QDialog>

class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameDialog(QWidget * parent = nullptr);

    float getLevel() const;

private:
    float level;
};

#endif // NEWGAMEDIALOG_HPP
