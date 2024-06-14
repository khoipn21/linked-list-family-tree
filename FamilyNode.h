#ifndef FAMILYNODE_H
#define FAMILYNODE_H

#include "FamilyMember.h"

typedef struct FamilyNode
{
    FMem data;
    FamilyNode *father;
    FamilyNode *children;
    FamilyNode *sibling;
} FNode;

#endif