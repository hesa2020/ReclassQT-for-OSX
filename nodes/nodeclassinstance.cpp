#include "nodeclassinstance.h"

NodeClassInstance::NodeClassInstance(BaseNode *parent) : BaseNode (parent)
{
}

QVariant NodeClassInstance::GetData(int column)
{
    if(column == 0)
    {
        return QVariant(QString("%1").arg(offset, 0, 16).rightJustified(4, '0').toUpper());
    }
    else if(column == 1)
    {
        return QVariant(QString("%1").arg(parentItem()->offset + offset, 0, 16).rightJustified(8, '0').toUpper());
    }
    else if(column == 2)
    {
        return QVariant(pNode->Name);
    }
    else if(column == 3)
    {
        return QVariant(Name);
    }
    return QVariant("");
}
