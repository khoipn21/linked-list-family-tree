#include "FamilyTreeFunctions.h"

FMem ProcessMemberData(string s)
{
    FMem member;
    int tempIndex = s.find("<");
    member.name = s.substr(tempIndex + 1, s.find("(") - tempIndex - 2);
    member.yearOfBirth = stoi(s.substr(s.find("(") + 1, s.find(")") - s.find("(") - 1));
    return member;
}

int CountLevel(string s)
{
    int count = 0;
    for (int i = s.find("-"); i < s.length(); i++)
    {
        if (s[i] == '-')
            count++;
    }
    return count / 2;
}