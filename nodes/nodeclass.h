#ifndef NODECLASS_H
#define NODECLASS_H

#include "nodes/basenode.h"

class NodeClass : public BaseNode
{
public:
    explicit NodeClass(BaseNode *parentItem = 0);
    virtual ~NodeClass(){}

    QString Code;
    int RequestPosition;

    virtual QVariant GetData(int column);
    virtual bool IsEditable(int column);

    virtual NodeType GetType() { return nt_class; }
    virtual unsigned long GetMemorySize()		{unsigned long size = 0; for (int i=0; i < Nodes.size();i++) size += Nodes[i]->GetMemorySize(); return size;}

};

#endif // NODECLASS_H
