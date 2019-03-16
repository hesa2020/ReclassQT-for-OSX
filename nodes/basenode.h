#ifndef BASENODE_H
#define BASENODE_H

#include "classes.h"
#include <QList>
#include <QVariant>
#include <QString>

class BaseNode
{
    bool bHidden;
    bool bSelected;
    QVector<bool> bOpen;
public:
    explicit BaseNode(BaseNode *parentItem = 0);
    virtual ~BaseNode();

    void appendChild(BaseNode *child);

    BaseNode *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column);
    int row() const;
    BaseNode *parentItem();

    unsigned long offset;
    QString strOffset;

    QString Name;
    QString Comment;
    BaseNode* pParent;

    virtual QVariant GetData(int column){ return QVariant(""); }
    virtual unsigned long GetMemorySize() { return 0; }
    virtual NodeType GetType() { return NodeType::nt_base; }
    virtual bool IsEditable(int column) { return false; }

    QString GetStringFromMemory( char* pMemory, int Length )
    {
        QString asc;
        for (int i = 0; i < Length; i++)
        {
            if (isprint( pMemory[i] & 0xFF))
            {
                asc += pMemory[i];
            } else {
                asc += '.';
            }
        }
        return asc;
    }

    QString GetStringFromMemoryW( wchar_t* pMemory, int Length )
    {
        QString asc;
        for (int i=0; i < Length;i += sizeof( wchar_t ) )
        {
            asc += iswprint( pMemory[i] ) > 0 ? pMemory[i] : L'.';
        }
        return asc;
    }

    QList<BaseNode*> Nodes;
    BaseNode *m_parentItem;
};

#endif // BASENODE_H
