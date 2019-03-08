#ifndef NODEHEX32_H
#define NODEHEX32_H

#include "nodes/basenode.h"

class NodeHex32 : public BaseNode
{
public:
    explicit NodeHex32(BaseNode *parentItem = 0);
    virtual ~NodeHex32(){}

    virtual QVariant GetData(int column);
    virtual NodeType GetType() { return nt_hex32; }
    virtual unsigned long GetMemorySize() { return 4; }

};

#endif // NODEHEX32_H
