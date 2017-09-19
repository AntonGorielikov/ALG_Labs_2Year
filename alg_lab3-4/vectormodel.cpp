#include "vectormodel.h"

VectorModel::VectorModel(QObject *parent)
    : QAbstractListModel(parent)
{}

void VectorModel::setVector(const QVector<double> &vector)
{
    vector_ = &vector;
}

int VectorModel::rowCount(const QModelIndex &parent) const
{
    return vector_->size();
}

QVariant VectorModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::TextAlignmentRole)
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    else if(role == Qt::DisplayRole)
    {
        return vector_->at(index.row());
    }

    return QVariant();
}

QVariant VectorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    return QObject::tr("Values");
}
