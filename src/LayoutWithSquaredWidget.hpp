#ifndef LAYOUTWITHSQUAREDWIDGET_HPP
#define LAYOUTWITHSQUAREDWIDGET_HPP

#include <QLayout>

#include <memory>

class LayoutWithSquaredWidget : public QLayout
{
public:
    LayoutWithSquaredWidget(QWidget * parent = nullptr);

    virtual void addItem(QLayoutItem * newItem) override;
    virtual int count() const override;
    virtual QLayoutItem * itemAt(int index) const override;
    virtual QLayoutItem * takeAt(int index) override;

    virtual void setGeometry(const QRect & rect) override;
    virtual QSize sizeHint() const override;

private:
    std::unique_ptr<QLayoutItem> item;
};

#endif // LAYOUTWITHSQUAREDWIDGET_HPP
