#ifndef FAMILYTREEFUNCTIONS_H
#define FAMILYTREEFUNCTIONS_H

#include "ListRoot.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

inline FNode *GetNode(FMem member)
{
    FNode *newNode = new FNode;
    newNode->data = member;
    newNode->father = nullptr;
    newNode->children = nullptr;
    newNode->sibling = nullptr;
    return newNode;
}

inline void InitList(ListRoot *l)
{
    l->root = NULL;
}

inline bool isValidFileName(const string &fileName)
{
    regex pattern("^[a-zA-Z0-9_-]+\\.txt$");
    return regex_match(fileName, pattern);
}

inline bool FileExists(const string &fileName)
{
    fs::path currentDir = fs::current_path();
    return fs::exists(fileName);
}

void AddMember(ListRoot *l, FMem member);
void Input(ListRoot *l, FMem member);
FNode *FindMemberByName(FNode *start, const string &name);
void AddChild(ListRoot *l, const string &parentName, FMem child);
void ReadTreeFromFile(ListRoot *l, string &fileName);
void PrintTreeToFile(ofstream &fo, FNode *node, string prefix, bool isLast, int level);
void PrintNodeInfo(FNode *node);
void PrintAllNodes(FNode *node, string prefix, bool isLast, int level);
FMem ProcessMemberData(string s);
int CountLevel(string s);
void PrintTree(ListRoot *l);
void Menu(ListRoot *l);

#endif
