#include "nodehex32.h"

NodeHex32::NodeHex32(BaseNode *parent) : BaseNode (parent)
{
}

QVariant NodeHex32::GetData(int column)
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
        return QVariant(".....");
    }
    else if(column == 3)
    {
        return QVariant("00 00 00 00");
    }
    else if(column == 4)
    {
        return QVariant("0.000  0  0x0");
    }
    return QVariant("");
}
