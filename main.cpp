#include <iostream>
#include "LibShelter.h"
using namespace ShelterSpace ;
using namespace std;

int main(int argc, char** argv)
{
    // seed random number generator
    srand(time(nullptr));
    // test command line arguments
    if(argc != 5)
    {
        cerr << "incorrect number of command lines " <<endl ;
        cerr << "Please run " << argv[0] << " <rows><cols><number of turns><number of utopians> "<<endl;
        exit(ERROR_ARGC);
    }
    int intRows = GetInt(argv[1]);
    int intCols = GetInt (argv[2]);
    int intTurns  = GetInt(argv[3]);
    int intUtopians = GetInt(argv[4]);
    //range check
    if(intRows < MIN && intCols <MIN && intTurns <MIN && intUtopians <MIN )
    {
        cerr << " Command line arguments must be atleast less thn 6" <<endl ;
        exit(ERROR_RANGE);
    }
    TwoArray arrWorld ;
    arrWorld = InitWorld(intRows,intCols,intTurns,intUtopians);
    bool blnContinue = true ;
    do
    {
        system("cls");
        OutputWorld(arrWorld,intRows,intCols);
        cout << "a) Up " <<endl
             << "b) Down "<<endl
             << "c) Left "<<endl
             << "d) Right "<<endl
             << "Selection : ";
             char chSelect = '\0';
             cin >> chSelect ;
        switch(tolower(chSelect))
        {
         case 'a':
         case 'b':
         case 'c':
         case 'd':
             MoveUtopians(arrWorld,intRows,intCols);
            break ;
         case 'x':
            blnContinue = false ;
            break ;
         default :
            cerr << " Incorrect seletion , please retry " <<endl ;
            break ;
        }

    }while(blnContinue);
    return SUCCESS;
}
