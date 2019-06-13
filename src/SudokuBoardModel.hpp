#ifndef SUDOKUBOARDMODEL_HPP
#define SUDOKUBOARDMODEL_HPP

#include "SudokuBoard.hpp"

#include <QAbstractTableModel>

class SudokuBoardModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit SudokuBoardModel(QObject * parent = nullptr);

    virtual int columnCount(const QModelIndex & index = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex & index = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;

    virtual Qt::ItemFlags flags(const QModelIndex & index) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    SudokuIndex toSudokuIndex(const QModelIndex & index) const;

private:
    SudokuBoard board;
};

#endif // SUDOKUBOARDMODEL_HPP
