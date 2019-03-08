#ifndef NODECLASSINSTANCE_H
#define NODECLASSINSTANCE_H

#include "nodes/nodeclass.h"

class NodeClassInstance: public BaseNode
{
public:
    explicit NodeClassInstance(BaseNode *parentItem = 0);
    virtual ~NodeClassInstance(){}

    NodeClass* pNode;

    virtual QVariant GetData(int column);

    virtual NodeType GetType() { return nt_instance; }
    virtual unsigned long GetMemorySize() { return pNode->GetMemorySize(); }
};
#endif // NODECLASSINSTANCE_H
