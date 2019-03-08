#include "reclass.h"

#include "nodes/nodeclassinstance.h"
#include "nodes/nodehex32.h"
#include "mainwindow.h"

ReClass::ReClass(MainWindow* mainWindow)
{
    model = new TreeModel();

    //Demo Project:
    ReclassProjectNode* gameObjectClass = new ReclassProjectNode();
    gameObjectClass->Type = nt_class;
    gameObjectClass->Name = "GameObject";
    for(int i = 0; i < 16; i++)
    {
        ReclassProjectNode* node = new ReclassProjectNode();
        node->Type = nt_hex32;
        node->Name = "";
        gameObjectClass->Nodes.append(node);
    }

    ProjectNodes.append(gameObjectClass);

    ReclassProjectNode* gameControllerNode = new ReclassProjectNode();
    gameControllerNode->Type = nt_class;
    gameControllerNode->Name = "GameController";

    for(int i = 0; i < 16; i++)
    {
        ReclassProjectNode* node = new ReclassProjectNode();
        node->Type = nt_hex32;
        node->Name = "";
        gameControllerNode->Nodes.append(node);
    }

    ReclassProjectNode* gameClassInstance = new ReclassProjectNode();
    gameClassInstance->Type = nt_instance;
    gameClassInstance->Name = "LocalPlayer";
    gameClassInstance->Class = 0;

    gameControllerNode->Nodes.append(gameClassInstance);

    ProjectNodes.append(gameControllerNode);

    //Add classes to the LEFT Menu:
    mainWindow->AddClassMenu("GameObject");
    mainWindow->AddClassMenu("GameController");

    //Show the first project class:
    ReclassProjectNode* projectNode = ProjectNodes[0];
    if(projectNode)
    {
        BaseNode* node = ProjectNodeToBaseNode(projectNode, model->rootItem);
        model->rootItem->appendChild(node);
        CalcOffsets(node);
    }
}

void ReClass::on_ClassesTree_doubleClicked(const QModelIndex &index)
{
    //delete model->rootItem->Nodes[0];
    model->rootItem->Nodes.clear();
    ReclassProjectNode* projectNode = ProjectNodes[index.row()];
    if(projectNode)
    {
        BaseNode* node = ProjectNodeToBaseNode(projectNode, model->rootItem);
        model->rootItem->appendChild(node);
        CalcOffsets(node);
    }
}

BaseNode* ReClass::ProjectNodeToBaseNode(ReclassProjectNode* projectNode, BaseNode* parent)
{
    BaseNode* returnNode = nullptr;
    switch(projectNode->Type)
    {
        case nt_class:
        {
            returnNode = new NodeClass(parent);
            returnNode->Name = projectNode->Name;
            for(ReclassProjectNode* subProjectNode : projectNode->Nodes)
            {
                BaseNode* subNode = ProjectNodeToBaseNode(subProjectNode, returnNode);
                if(subNode != nullptr)
                {
                    returnNode->appendChild(subNode);
                }
            }
        }
        break;
        case nt_instance:
        {
            returnNode = new NodeClassInstance(parent);
            returnNode->Name = projectNode->Name;
            ReclassProjectNode* classNode = ProjectNodes[projectNode->Class];
            if(classNode)
            {
                NodeClass* subNode = (NodeClass*) ProjectNodeToBaseNode(classNode, returnNode);
                if(subNode != nullptr)
                {
                    ((NodeClassInstance*)returnNode)->pNode = subNode;
                    returnNode->appendChild(subNode);
                }
            }
        }
        break;
        case nt_hex32:
        {
            returnNode = new NodeHex32(parent);
            returnNode->Name = projectNode->Name;
        }
        break;
    }
    return returnNode;
}

void ReClass::CalcOffsets(BaseNode* pClass)
{
    unsigned long offset = 0;
    for(int i = 0; i < pClass->Nodes.size(); i++)
    {
        pClass->Nodes[i]->offset = offset;
        if(pClass->Nodes[i]->GetType() == nt_instance)
        {
            if(pClass->Nodes[i]->Nodes.size() > 0)
            {
                pClass->Nodes[i]->Nodes[0]->offset = offset + pClass->Nodes[i]->parentItem()->offset;
                CalcOffsets(pClass->Nodes[i]->Nodes[0]);
            }
        }
        offset += pClass->Nodes[i]->GetMemorySize();
    }
}

void ReClass::CalcAllOffsets()
{
    for(unsigned long i = 0; i < Classes.size(); i++)
    {
        CalcOffsets(Classes[i]);
    }
}

void ReClass::ClearSelection()
{

}
void ReClass::ClearHidden()
{

}
