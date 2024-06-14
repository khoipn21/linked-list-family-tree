#ifndef MENU_H
#define MENU_H

void FileMenu(ListRoot *l, string &InputFileName, bool restart = false);
void AddMemberInterface(ListRoot *l, FMem member);
void AddChildInterface(ListRoot *l, bool &isSaved);
void FindMemberInterface(ListRoot *l);
void SaveInterface(ofstream &fo, ListRoot *l, string filename);
void SaveAsInterface(ofstream &fo, ListRoot *l, string fileName, bool isImported);

#endif
