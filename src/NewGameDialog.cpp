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
    connect(easy, &QPushButton::clicked, [this](){ level = 15.f; accept(); });

    QPushButton * medium = new QPushButton("medium", this);
    layout->addWidget(medium);
    connect(medium, &QPushButton::clicked, [this](){ level = 40.f; accept(); });

    QPushButton * hard = new QPushButton("hard", this);
    layout->addWidget(hard);
    connect(hard, &QPushButton::clicked, [this](){ level = 80.f; accept(); });
}

float NewGameDialog::getLevel() const
{
    return level;
}
