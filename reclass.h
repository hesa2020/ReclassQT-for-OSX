#ifndef RECLASS_H
#define RECLASS_H

#include "treemodel.h"

#include "classes.h"
#include "nodes/nodeclass.h"
#include <QList>

class MainWindow;

class ReclassProjectNode
{
public:
    QString Address;//Only used for root classes.
    QString Name;
    int Type;
    int Class;
    QList<ReclassProjectNode*> Nodes;
};

class ReClass : public QObject
{
    QList<NodeClass*> Classes = QList<NodeClass*>();
    QList<ReclassProjectNode*> ProjectNodes = QList<ReclassProjectNode*>();
public:
    TreeModel *model = nullptr;
    ReClass(MainWindow* mainWindow);

    BaseNode* ProjectNodeToBaseNode(ReclassProjectNode* projectNode, BaseNode* parent = nullptr);

    bool IsNodeValid(BaseNode* pCheckNode);
    BaseNode* isNodeRef(BaseNode* pTestNode);
    void DeleteClass(BaseNode* pClass);

    void CalcOffsets(BaseNode* pClass);
    void CalcAllOffsets();
    void ClearSelection();
    void ClearHidden();

public slots:
    void on_ClassesTree_doubleClicked(const QModelIndex &index);
};

#endif // RECLASS_H
