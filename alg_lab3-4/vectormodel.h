#ifndef VECTORMODEL_H
#define VECTORMODEL_H

#include <QAbstractListModel>

class VectorModel : public QAbstractListModel
{
public:
    VectorModel(QObject *parent = nullptr);

    void setVector(const QVector<int> &vector);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role) const;

private:
    QString valueAt(int offset) const;

    const QVector<int> *vector_;
};

#endif // VECTORMODEL_H
