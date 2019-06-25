#include "LayoutWithSquaredWidget.hpp"

#include <cmath>

LayoutWithSquaredWidget::LayoutWithSquaredWidget(QWidget *parent)
    : QLayout(parent)
{
}

void LayoutWithSquaredWidget::addItem(QLayoutItem *newItem)
{
    item.reset(newItem);
}

int LayoutWithSquaredWidget::count() const
{
    if (item)
        return 1;
    return 0;
}

QLayoutItem *LayoutWithSquaredWidget::itemAt(int index) const
{
    if (index == 0 && item)
        return item.get();
    return nullptr;
}

QLayoutItem *LayoutWithSquaredWidget::takeAt(int index)
{
    if (index == 0 && item)
    {
        QLayoutItem * itemToRelease = item.release();
        return itemToRelease;
    }
    return nullptr;
}

void LayoutWithSquaredWidget::setGeometry(const QRect &rect)
{
    if (!item)
        return;

    int itemSize = std::min(rect.width(), rect.height());
    QRect itemRect(rect.x(), rect.y(), itemSize, itemSize);
    item->setGeometry(itemRect);
}

QSize LayoutWithSquaredWidget::sizeHint() const
{
    return item->sizeHint();
}
