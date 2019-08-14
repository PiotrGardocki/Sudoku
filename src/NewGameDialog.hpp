#ifndef NEWGAMEDIALOG_HPP
#define NEWGAMEDIALOG_HPP

#include <QDialog>

class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameDialog(QWidget * parent = nullptr);

    int getLevel() const;

private:
    int level;
};

#endif // NEWGAMEDIALOG_HPP
