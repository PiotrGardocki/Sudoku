#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = nullptr);

private:
    QPushButton * createButton(QLayout & layout, const std::string & text);
};

#endif // MAINWINDOW_HPP
