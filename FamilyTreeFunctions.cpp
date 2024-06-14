#include "FamilyTreeFunctions.h"

void AgeHandler(FMem parent, FMem &member)
{
    while (member.yearOfBirth < parent.yearOfBirth + 18)
    {
        cout << "Enter year of birth must be >= 18 years greater than father (" << parent.yearOfBirth + 18 << "): ";
        cin >> member.yearOfBirth;
    }
}


void AddMember(ListRoot *l, FMem member)
{
    FNode *node = GetNode(member);
    if (l->root == NULL)
    {
        l->root = node;
    }
    else
    {
        AgeHandler(l->root->data, node->data);
        if (l->root->children == NULL)
        {
            l->root->children = node;
            node->father = l->root;
        }
        else
        {
            FNode *current = l->root->children;
            while (current->sibling != NULL)
            {
                current = current->sibling;
            }
            current->sibling = node;
            node->father = l->root;
        }
    }
}

void Input(ListRoot *l, FMem member)
{

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, member.name);
    cout << "Enter year of birth: ";
    cin >> member.yearOfBirth;
    AddMember(l, member);
}

FNode *FindMemberByName(FNode *start, const string &name)
{

    if (start == NULL)
    {
        return NULL;
    }

    if (start->data.name == name)
    {
        return start;
    }

    FNode *sibling = FindMemberByName(start->sibling, name);
    if (sibling)
    {
        return sibling;
    }

    return FindMemberByName(start->children, name);
}

void AddChild(ListRoot *l, const string &parentName, FMem child)
{

    FNode *parent = FindMemberByName(l->root, parentName);

    if (parent == NULL)
    {
        return;
    }

    AgeHandler(parent->data, child);
    FNode *childNode = GetNode(child);

    childNode->father = parent;

    if (parent->children == NULL)
    {
        parent->children = childNode;
    }
    else
    {

        FNode *current = parent->children;
        while (current->sibling != NULL)
        {
            current = current->sibling;
        }
        current->sibling = childNode;
    }
}

void PrintNodeInfo(FNode *node)
{

    if (node == NULL)
    {
        cout << "Not found" << endl;
        return;
    }

    bool parentFlag = node->father != NULL;
    cout << "Name:" << node->data.name << " (" << node->data.yearOfBirth << ")" << endl;

    if (node->children != NULL)
    {
        cout << "Children:" << endl;
        FNode *child = node->children;
        while (child != NULL)
        {
            cout << "-" << child->data.name << " (" << child->data.yearOfBirth << ")" << endl;
            child = child->sibling;
        }
    }

    if (!parentFlag)
    {
        cout << "This is root node" << endl;
    }
    else
    {
        FNode *parent = node->father;
        cout << "Parent: " << parent->data.name << endl;

        if (parent->children != node || node->sibling != NULL)
        {
            cout << "Siblings: " << endl;
            FNode *sib = parent->children;
            while (sib != NULL)
            {

                if (sib == node)
                {
                    sib = sib->sibling;
                    continue;
                }
                cout << "-" << sib->data.name << " (" << sib->data.yearOfBirth << ")" << endl;
                sib = sib->sibling;
            }
        }
        else
        {
            cout << "No siblings" << endl;
        }
    }

    cout << endl;
}

void PrintAllNodes(FNode *node, string prefix = "", bool isLast = true, int level = 0)
{

    if (node == NULL)
        return;

    if (node->father != NULL)
        cout
            << prefix << "|" << endl;
    cout << prefix;

    if (isLast)
    {
        string temp = (node->father == NULL) ? "" : "\\";
        int tempMul = (node->father == NULL) ? 0 : 1;
        cout << temp << string(level * 2, '-');
        prefix += string(level * 2 + tempMul, ' ');
    }
    else
    {
        cout << "|" << string(level * 2, '-');
        prefix += "|" + string(level * 2, ' ');
    }

    cout << "<" << node->data.name << " (" << node->data.yearOfBirth << ")" << ">" << endl;

    FNode *child = node->children;
    level++;
    while (child != NULL)
    {
        PrintAllNodes(child, prefix, child->sibling == NULL, level);
        child = child->sibling;
    }
}

void PrintTree(ListRoot *l)
{
    if (l->root == NULL)
    {
        cout << "The family tree is empty.\n\n";
        return;
    }

    PrintAllNodes(l->root);
    cout << endl;
}