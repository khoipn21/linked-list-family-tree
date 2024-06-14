#include "FamilyTreeFunctions.h"
#include "Menu.h"

void FileMenu(ListRoot *l, string &InputFileName, bool restart)
{
    system("cls");
    int importChoice;
    cout << "Choose an option to start?" << endl;
    cout << "1. Create a new tree" << endl;
    cout << "2. Import an existing tree" << endl;
    if (restart)
        cout << "3. Back to menu" << endl;
    cout << "Enter your choice: ";
    cin >> importChoice;
    cout << endl;

    while (importChoice != 1 && importChoice != 2 && (restart ? importChoice != 3 : true))
    {
        cout << "Invalid choice, please enter again: ";
        cin >> importChoice;
        cout << endl;
    }

    if (importChoice == 3)
        return;
    if (importChoice == 1)
    {
        l->root = NULL;
        return;
    }
    if (importChoice == 2) l->root = NULL;
    ReadTreeFromFile(l, InputFileName);
    cout << "\nImported tree-------------------\n\n";
    PrintTree(l);
    system("pause");
}

void AddMemberInterface(ListRoot *l, FMem member)
{
    Input(l, member);
    cout << "Member added!" << endl;
    system("pause");
}

void AddChildInterface(ListRoot *l, bool &isSaved)
{
    string parentName;
    FMem member;
    int subChoice;
    do
    {
        cout << "Enter parent name: ";
        cin >> parentName;
        if (FindMemberByName(l->root, parentName) != NULL)
        {
            cout << "Enter child name: ";
            cin >> member.name;
            cout << "Enter year of birth: ";
            cin >> member.yearOfBirth;
            AddChild(l, parentName, member);
            cout << "Child added!" << endl;
            isSaved = false;
            system("pause");
            break;
        }

        cout << "Parent not found!" << endl;
        cout << "Do you want to continue?: " << endl;
        cout << "1. Re-enter" << endl;
        cout << "2. Back to menu" << endl;
        cin >> subChoice;

        if (subChoice == 2)
            break;
    } while (subChoice != 2);
}

void FindMemberInterface(ListRoot *l)
{
    system("cls");
    string MemberName;
    int subChoice;
    cout << "Enter name: ";
    cin >> MemberName;

    do
    {
        if (FindMemberByName(l->root, MemberName) != NULL)
        {
            PrintNodeInfo(FindMemberByName(l->root, MemberName));
            break;
        }

        cout << "Member not found!" << endl;
        cout << "Do you want to continue?: " << endl;
        cout << "1. Re-enter" << endl;
        cout << "2. Back to menu" << endl;
        cin >> subChoice;

        if (subChoice == 2)
            break;

        cout << "Enter name: ";
        cin >> MemberName;

    } while (subChoice != 2);
}

void SaveInterface(ofstream &fo, ListRoot *l, string fileName)
{
    system("cls");
    int tempChoice;
    cout << "Expecting the tree to be updated to file..." << endl;
    PrintTree(l);
    cout << "Confirm to make changes to '" << fileName << "'?: " << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cin >> tempChoice;
    while (tempChoice != 2)
    {
        if (tempChoice == 1)
        {
            fo.open(fileName);
            PrintTreeToFile(fo, l->root, "", true, 0);
            fo.close();
            cout << "Tree saved to file '" << fileName << "'!" << endl;
            system("pause");
            break;
        }
        cout << "Invalid choice, please enter again: ";
        cin >> tempChoice;
    }
}

void SaveAsInterface(ofstream &fo, ListRoot *l, string fileName, bool isImported)
{
    system("cls");
    int subChoice;
    cout << "Expecting the tree to be updated to file..." << endl;
    PrintTree(l);
    if (!isImported)
    {
        cout << "This is a new tree, do you want to save it to a new file?: " << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cout << "Choice: ";
        cin >> subChoice;
        while (subChoice != 2 && subChoice != 1)
        {
            cout << "Invalid choice, please enter again: ";
            cin >> subChoice;
        }
        if (subChoice == 2)
            return;
    }
    cout << "Enter file name (.txt file): ";
    cin >> fileName;

    while (!isValidFileName(fileName))
    {
        system("cls");
        cout << "File name: " << fileName << endl;
        cout << "File error(s): \n";
        if (!isValidFileName(fileName))
            cout << "- File name is not valid for a .txt file." << endl;
        int choice;
        cout << "Enter file name again?: " << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cout << "Choice: ";
        cin >> choice;
        do
        {
            if (choice == 1)
            {
                cout << "Enter file name (.txt): ";
                cin >> fileName;
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
        } while (choice != 1 || choice != 2);
    }

    if (FileExists(fileName))
    {
        system("cls");
        cout << "File '" << fileName << "' exists, do you want to overwrite it ? " << endl;
        cout << "1. Yes" << endl;
        cout << "2. No (Save a copy)" << endl;
        cout << "Choice: ";
        cin >> subChoice;
        while (subChoice != 2 && subChoice != 1)
        {
            cout << "Invalid choice, please enter again: ";
            cin >> subChoice;
        }
        if (subChoice == 2)
        {
            const string nameTemp = fileName.substr(0, fileName.find(".txt"));
            string temp = fileName;
            int tempInd = 1;
            while (FileExists(temp))
            {
                temp = nameTemp + "(" + to_string(tempInd) + ")" + ".txt";
                tempInd++;
            }
            fileName = temp;
        }
    }
    fo.open(fileName);
    PrintTreeToFile(fo, l->root, "", true, 0);
    cout << "Tree saved to file '" << fileName << "'!" << endl;
    system("pause");
    fo.close();
}