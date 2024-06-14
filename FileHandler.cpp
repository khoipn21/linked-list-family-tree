#include "FamilyTreeFunctions.h"
#include <cstdlib>

void ReadTreeFromFile(ListRoot *l, string &fileName)
{
	system("cls");
    cout << "Enter file name (Ex: tree.txt): ";
    cin.ignore();
    getline(cin, fileName);
    cout << endl;

    while (!isValidFileName(fileName) || !FileExists(fileName))
	{
		cout << "File name: " << fileName << endl;  
        cout << "File error(s): \n";
        if(!isValidFileName(fileName)) cout << "- File name is not valid for a .txt file." << endl;
		if (!FileExists(fileName)) cout << "- File not found." << endl;
        int choice;
		cout << "Enter file name again?: " << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cout << "Choice: ";
		cin >> choice;
        while (choice != 1 || choice != 2) {
            if (choice == 1)
            {
                system("cls");
                cout << "Enter file name (Ex: tree.txt): ";
                cin.ignore();
                getline(cin, fileName);
                break;
			}
			else if (choice == 2)
			{
				return;
			}
			else
			{
				cout << "Invalid choice, please enter again: ";
				cin >> choice;
			}
        }
    }

    /*if (!FileExists(fileName))
    {
        cout << "File not found." << endl;
        cout << "Enter file name again?: " << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            ReadTreeFromFile(l, fileName);
        }
    }*/
    ifstream fi(fileName);
    // while (!fi.is_open())
    //{
    //     cout << "File not found." << endl;
    //     cout << "Enter file name again: ";
    //     getline(cin, fileName);
    //     fi.open(fileName, ios::in);
    //     // fi.open("fileName");
    // }

    // if (!fi.is_open())
    // {
    //     cout << "File not found." << endl;
    //     return;
    // }
    string line;
    vector<string> lineArr;
    // int level = 0;
    int tempIndex = 1;
    while (getline(fi, line))
    {
        if (line.find(">") > line.length())
        {
            continue;
        }
        lineArr.push_back(line);
    }
    for (int i = 0; i < lineArr.size(); i++)
    {
        FNode *node = GetNode(ProcessMemberData(lineArr[i]));
        if (l->root == NULL)
        {
            l->root = node;
        }
        for (int k = tempIndex; k < lineArr.size(); k++)
        {
            if (CountLevel(lineArr[k]) == CountLevel(lineArr[i]) + 1)
            {
                if (lineArr[k].find("\\") == lineArr[i].find("<"))
                {
                    AddChild(l, node->data.name, ProcessMemberData(lineArr[k]));
                    break;
                }
                if (lineArr[k].find_last_of("|") == lineArr[i].find("<"))
                {
                    AddChild(l, node->data.name, ProcessMemberData(lineArr[k]));
                    continue;
                }
            }
        }
        tempIndex++;
    }
    fi.close();
}

void PrintTreeToFile(ofstream &fo, FNode *node, string prefix = "", bool isLast = true, int level = 0)
{
    if (node == NULL)
        return;

    if (node->father != NULL)
        fo << prefix << "|" << endl;
    fo << prefix;

    if (isLast)
    {
        string temp = (node->father == NULL) ? "" : "\\";
        int tempMul = (node->father == NULL) ? 0 : 1;
        fo << temp << string(level * 2, '-');
        prefix += string(level * 2 + tempMul, ' ');
    }
    else
    {
        fo << "|" << string(level * 2, '-');
        prefix += "|" + string(level * 2, ' ');
    }

    fo << "<" << node->data.name << " (" << node->data.yearOfBirth << ")" << ">" << endl;

    FNode *child = node->children;
    level++;
    while (child != NULL)
    {

        PrintTreeToFile(fo, child, prefix, child->sibling == NULL, level);
        child = child->sibling;
    }
}