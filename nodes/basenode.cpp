#include "nodes/basenode.h"
#include <QStringList>

#include "BaseNode.h"

BaseNode::BaseNode(BaseNode *parent)
{
    m_parentItem = parent;
}

BaseNode::~BaseNode()
{
    qDeleteAll(Nodes);
}

void BaseNode::appendChild(BaseNode *item)
{
    Nodes.append(item);
}

BaseNode *BaseNode::child(int row)
{
    return Nodes.value(row);
}

int BaseNode::childCount() const
{
    return Nodes.count();
}

int BaseNode::columnCount() const
{
    return 10;
}

QVariant BaseNode::data(int column)
{
    return GetData(column);
}

BaseNode *BaseNode::parentItem()
{
    return m_parentItem;
}

int BaseNode::row() const
{
    if (m_parentItem)
        return m_parentItem->Nodes.indexOf(const_cast<BaseNode*>(this));

    return 0;
}
