#include "SudokuBoardModel.hpp"

#include <QString>

SudokuBoardModel::SudokuBoardModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

int SudokuBoardModel::columnCount(const QModelIndex &index) const
{
    if (index.isValid())
        return 0;
    return 9;
}

int SudokuBoardModel::rowCount(const QModelIndex &index) const
{
    if (index.isValid())
        return 0;
    return 9;
}

QVariant SudokuBoardModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();

    auto sudokuIndex = toSudokuIndex(index);

    if (board.isFieldEmpty(sudokuIndex))
        return QString("");
    else
        return QString::fromStdString(board.getFieldAsString(sudokuIndex));
}

bool SudokuBoardModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    auto sudokuIndex = toSudokuIndex(index);
    bool ok;
    auto number = value.toInt(&ok);

    if (ok)
    {
        if (number < 1 || number > 9)
            return false;
        board.setNumber(sudokuIndex, static_cast<unsigned short>(number));
    }

    if (!ok)
    {
        auto str = value.toString();
        if (str.size() != 0)
            return false;
        board.setFieldAsEmpty(sudokuIndex);
    }

    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags SudokuBoardModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemNeverHasChildren;
}

QVariant SudokuBoardModel::headerData(int /*section*/, Qt::Orientation /*orientation*/, int /*role*/) const
{
    return QVariant();
}

SudokuIndex SudokuBoardModel::toSudokuIndex(const QModelIndex &index) const
{
    return SudokuIndex(static_cast<unsigned short>(index.row()),
                       static_cast<unsigned short>(index.column()));
}
