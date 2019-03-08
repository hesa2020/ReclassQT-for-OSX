#include "nodes/nodeclass.h"

NodeClass::NodeClass(BaseNode *parent) : BaseNode (parent)
{
    offset = 0x400000L;

    //printf( "[+] Created offset: %p Characters: %d\n", offset, NumDigits( offset ) );

    strOffset = "400000";
    //RequestPosition = -1;
}

QVariant NodeClass::GetData(int column)
{
    if(column == 0)
    {
        if(parentItem()->GetType() == nt_instance)
        {
            return QVariant(QString("%1").arg(parentItem()->offset, 0, 16).rightJustified(4, '0').toUpper());
        }
        return QVariant(QString("%1").arg(offset, 0, 16).rightJustified(4, '0').toUpper());
    }
    else if(column == 1)
    {
        return QVariant("Class");
    }
    else if(column == 2)
    {
        return QVariant(Name);
    }
    else if(column == 3)
    {
        int size = 0;
        for(BaseNode* node : Nodes)
        {
            size += node->GetMemorySize();
        }
        return QVariant(QString("[%1]").arg(size));
    }
    return QVariant("");
}
