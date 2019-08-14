#include "NewGameDialog.hpp"

#include <QPushButton>
#include <QVBoxLayout>

NewGameDialog::NewGameDialog(QWidget * parent)
    : QDialog(parent, Qt::WindowType::Popup)
{
    QVBoxLayout * layout = new QVBoxLayout;
    setLayout(layout);

    QPushButton * easy = new QPushButton("easy", this);
    layout->addWidget(easy);
    connect(easy, &QPushButton::clicked, [this](){ level = 15; accept(); });

    QPushButton * medium = new QPushButton("medium", this);
    layout->addWidget(medium);
    connect(medium, &QPushButton::clicked, [this](){ level = 40; accept(); });

    QPushButton * hard = new QPushButton("hard", this);
    layout->addWidget(hard);
    connect(hard, &QPushButton::clicked, [this](){ level = 80; accept(); });
}

int NewGameDialog::getLevel() const
{
    return level;
}
