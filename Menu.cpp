#include "FamilyTreeFunctions.h"
#include "Menu.h"

void Menu(ListRoot *l)
{
    ofstream fo;
    FMem member;
    string TempName;
    int choice, subChoice, importChoice;
    string InputFileName, OutputFileName;
    bool isSaved = true;
    FileMenu(l, InputFileName);
    do
    {
        system("cls");
        cout << "Current tree--------------------\n\n";
        PrintTree(l);
        cout << "Menu----------------------------" << endl;
        cout << "1. Add member" << endl;
        cout << "2. Add child to a member node by name" << endl;
        cout << "3. Find member by name" << endl;
        // Lưu vào file input ban đầu
        cout << "4. Save" << endl;
        // Lưu vào file khác
        cout << "5. Save as" << endl;
        cout << "6. Import/ Create another tree" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            AddMemberInterface(l, member);
            cout << endl;
            isSaved = false;
            break;
        case 2:
            AddChildInterface(l, isSaved);
            cout << endl;
            break;
        case 3:
            FindMemberInterface(l);
            system("pause");
            cout << endl;
            break;
        // case 4:
        //     if (l->root == NULL)
        //     {
        //         cout << "Tree is empty!" << endl;
        //         break;
        //     }
        //     PrintTree(l);
        //     system("pause");
        //     break;
        case 4:
            if (InputFileName.empty())
            {
                string prevOutputFileName = OutputFileName;
                SaveAsInterface(fo, l, OutputFileName, !InputFileName.empty());
                if (prevOutputFileName != OutputFileName)
                    InputFileName = OutputFileName;
                cout << endl;
                break;
            }
            else
            {
                SaveInterface(fo, l, InputFileName);
                isSaved = true;
                cout << endl;
                break;
            }
        case 5:
            SaveAsInterface(fo, l, OutputFileName, !InputFileName.empty());
            cout << endl;
            break;
        case 6:
            if (!isSaved)
            {
                cout << isSaved << endl;
                system("cls");
                cout << "Tree's data has been changed!" << endl;
                cout << "Do you want to save it? " << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "3. Back" << endl;
                cin >> subChoice;
                while (subChoice != 3)
                {
                    if (subChoice == 1)
                    {
                        if (!InputFileName.empty())
                            SaveInterface(fo, l, InputFileName);
                        else
                        {
                            SaveAsInterface(fo, l, OutputFileName, !InputFileName.empty());
                            InputFileName = OutputFileName;
                        }
                        InputFileName = "";
                        FileMenu(l, InputFileName, true);
                        isSaved = true;
                        cout << endl;
                        break;
                    }
                    else if (subChoice == 2)
                    {
                        InputFileName = "";
                        FileMenu(l, InputFileName, true);
                        isSaved = true;
                        cout << endl;
                        break;
                    }
                    cout << "Invalid choice, please enter again: ";
                    cin >> subChoice;
                }
                break;
            }
            else
            {
                InputFileName = "";
                FileMenu(l, InputFileName, true);
                cout << endl;
                break;
            }
        default:
            break;
        }

        cout << endl;
    } while (choice != 7);
}