#include "treemodel.h"
#include "nodes/basenode.h"
#include "nodes/nodeclass.h"
#include "nodes/nodehex32.h"

#include <QStringList>
#include <QColor>
#include <QDebug>

TreeModel::TreeModel(QObject *parent) : QAbstractItemModel(parent)
{
    rootItem = new BaseNode();
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<BaseNode*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    qDebug() << role;
    if (role == Qt::ForegroundRole)
    {
        BaseNode *node = static_cast<BaseNode*>(index.internalPointer());
        if (index.column() == 0)
        {
            return QVariant( QColor("#FF0000") );
        }
        else if (index.column() == 1)
        {
            if(node->GetType() == nt_class)
            {
                return QVariant( QColor("#0000FF") );
            }
            return QVariant( QColor("#00C800") );
        }
        else if (index.column() == 2)
        {
            if(node->GetType() == nt_class)
            {
                return QVariant( QColor("#0000FF") );
            }
            return QVariant( QColor("#0000FF") );
        }
        else if (index.column() == 3)
        {
            if(node->GetType() == nt_class)
            {
                return QVariant( QColor("#FF8000") );
            }
            return QVariant( QColor( Qt::black ) );
        }
        else if (index.column() == 4)
        {
            return QVariant( QColor("#FF8000") );
        }
        return QVariant( QColor( Qt::black ) );
    }

    if(role == Qt::EditRole)
    {
        //Return current value ??
        return QVariant("TEST");
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    BaseNode *item = static_cast<BaseNode*>(index.internalPointer());
    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    BaseNode *item = static_cast<BaseNode*>(index.internalPointer());
    if(item->IsEditable(index.column()))
    {
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }
    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);
    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    BaseNode *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<BaseNode*>(parent.internalPointer());

    BaseNode *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    BaseNode *childItem = static_cast<BaseNode*>(index.internalPointer());
    BaseNode *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    BaseNode *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<BaseNode*>(parent.internalPointer());

    return parentItem->childCount();
}
