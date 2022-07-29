#include <iostream>
#include <string>

#include "Exception.h"
#include "ConsoleColors.h"
#include "InterfaceText.h"

using namespace std;


int main()
{  
    setlocale(LC_ALL, "Russian");

    string state;
    while (true) 
    {
        try {
            ShowCurrentMenu(state);
            char choice;
            cin >> choice;
            get<1>(allfuncs[state])(state, choice);
        }
        catch (Exception error) 
        {   
                SetConsoleTextAttribute(HCONSOLE, (WORD)((Red << 4) | White));
                cerr << endl << error.report();
                SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));
                cout << endl;
        }
    }
   return 0;
}