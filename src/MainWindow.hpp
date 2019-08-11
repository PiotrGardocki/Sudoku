#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QLayout>

class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = nullptr);

private:
    template<typename ButtonType>
    ButtonType * createButton(QLayout & layout, const std::string & text);
};

template<typename ButtonType>
ButtonType * MainWindow::createButton(QLayout & layout, const std::string & text)
{
    ButtonType * button = new ButtonType(QString::fromStdString(text), this);
    layout.addWidget(button);
    return button;
}

#endif // MAINWINDOW_HPP
