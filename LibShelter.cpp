#include "LibShelter.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cassert>
namespace ShelterSpace
{
     int GetInt(string strInt)
     {
         int intNum ;
         stringstream ss{strInt};
         ss>>intNum ;
         if(ss.fail())
         {
             cerr << "Cannot convert "<< strInt << " into integer" <<endl ;
             exit(ERROR_CONV);
         }
         return intNum ;
     }
     int GetRand(int intLower , int intUpper)
     {
         assert(intUpper>intLower);
         int intRange = intUpper - intLower + 1 ;
         return rand()%intRange + intLower;
     }
     bool IsInWorld(int intRows, int intCols, int intRow, int intCol)
     {
         return (intRow >=0 && intRow <intRows && intCol >=0 && intCol <intCols);
     }
     TwoArray MemoryAlloc(int intRows ,int intCols)
     {
         TwoArray arrNums ;
         arrNums = new OneArray[intRows];
         for(int r = 0 ; r <intRows ; r++)
         {
             arrNums[r] = new int[intCols];

         }
         return arrNums;
     }
     void findFeauture(TwoArray arrWorld ,int intRows , int intCols , int& intRow ,int& intCol ,int intFeature)
     {
         intRow = -1;
         intCol = -1 ;
         for(int r = 0 ; r<intRows;r++)
         {
             for(int c = 0 ; c<intCols;c++)
             {
                 if(arrWorld[r][c]==intFeature)
                 {
                      intRow = -1;
                      intCol = -1 ;
                      return ;
                 }
             }
         }
     }
     void PlaceFeature (TwoArray arrWorld , int intRows, int intCols,int intFeature )
     {
         int intRow = GetRand(0,intRows-1);
         int intCol = GetRand(0,intCols-1);
         while(arrWorld[intRow][intCol]!=VAL_SPACE)
         {
               int intRow = GetRand(0,intRows-1);
               int intCol = GetRand(0,intCols-1);
         }
         arrWorld[intRow][intCol] = intFeature ;
     }
     //Initialise world
     TwoArray InitWorld (int intRows , int intCols , int intTurns, int intUtopians)
     {
         TwoArray arrWorld = MemoryAlloc(intRows,intCols);
         for(int n = 0 ; n<intUtopians ;n++)
         {
             PlaceFeature(arrWorld,intRows,intCols,VAL_UTOPIAN);
             PlaceFeature(arrWorld,intRows,intCols,VAL_UTOPIAN_AT_HOME);
         }
         PlaceFeature(arrWorld,intRows,intCols,VAL_COMPLAINCE_OFFICER);
         PlaceFeature(arrWorld,intRows,intCols,VAL_HOME);
         return arrWorld ;
     }
     // output world
    void OutputWorld(TwoArray arrWorld,int intRows, int intCols)
    {
        for(int r = 0 ; r<intRows ; r++)
        {
            for(int c = 0 ; c<intCols ;c++)
            {
                switch(arrWorld[r][c])
                {
                case VAL_SPACE :
                    cout << CH_SPACE ;
                    break ;
                case VAL_HOME :
                    cout << CH_HOME ;
                    break ;
                case VAL_COMPLAINCE_OFFICER :
                    cout << CH_OFFICER ;
                    break ;
                case VAL_UTOPIAN :
                    cout << CH_UTOPIAN ;
                    break ;
                case VAL_UTOPIAN_AT_HOME:
                    cout << CH_UTOPIAN_AT_HOME ;
                    break ;
                default :
                    cerr << "Invalid array. please check " <<endl ;
                }
                cout << " ";
            }
            cout << endl;
        }
    }

    void MoveUtopian(TwoArray arrWorld, TwoArray arrTemp, int intRows, int intCols, int intRow, int intCol)
    {
        bool blnNotEmpty = true;
        do
        {
            int intDirection ;
            int intDRow = intRow;
            int intDCol = intCol;
            ///Calculate potential destination
            switch(intDirection)
            {
                case UP:
                    intDRow--;
                    break;
                case RIGHT:
                    intDCol++;
                    break;
                case DOWN:
                    intDRow++;
                    break;
                case LEFT:
                    intDCol--;
                    break;
            }
            if(IsInWorld(intRows, intCols, intDRow, intDCol))
            {
                ///If the destination is empty, then move the character
                if(arrTemp[intDRow][intDCol]==VAL_SPACE)
                {
                    arrTemp[intDRow][intDCol] = arrWorld[intRow][intCol];
                    blnNotEmpty = false;
                }
                else if(arrTemp[intRow][intCol]==VAL_SPACE)
                {
                    arrTemp[intRow][intCol] = arrWorld[intRow][intCol];
                    blnNotEmpty = false;
                }

            }
            else if(arrTemp[intRow][intCol]==VAL_SPACE)
            {
                arrTemp[intRow][intCol] = arrWorld[intRow][intCol];
                blnNotEmpty = false;
            }
        }while(blnNotEmpty);

    }
    void Dealloc(TwoArray &arrWorld, int intRows)
    {
        for(int r=0;r<intRows;r++)
            delete[] arrWorld[r];
        delete[] arrWorld;
        arrWorld = nullptr;
    }
    void CopyArray(TwoArray arrTo,TwoArray arrFrom, int intRows, int intCols)
    {
        for(int r=0;r<intRows;r++)
        {
            for(int c=0;c<intCols;c++)
            {
                arrTo[r][c]=arrFrom[r][c];
            }
        }
    }
    void MoveUtopians(TwoArray arrWorld, int intRows, int intCols)
    {
        TwoArray arrTemp = MemoryAlloc(intRows, intCols);
        for(int r=0;r<intRows;r++)
        {
            for(int c=0;c<intCols;c++)
            {
                ///See if the cell contains a character
                if(arrWorld[r][c]!=VAL_SPACE)
                {
                    ///Move the character
                    MoveUtopian(arrWorld, arrTemp, intRows, intCols, r, c);
                }
            }
        }

        ///Copy the temp array into the arrWorld
        CopyArray(arrWorld, arrTemp, intRows, intCols);
        Dealloc(arrTemp,intRows);
    }
    int CountTurnsFeature(TwoArray arrWorld, int intRows, int intCols, int intFeature)
    {
        int intCount = 0;
        for(int r=0;r<intRows;r++)
        {
            for(int c=0;c<intCols;c++)
            {
                if(arrWorld[r][c]==intFeature)
                    intCount++;
            }
        }
        return intCount;
    }
    int CountTurnsAround(TwoArray arrWorld, int intRows, int intCols, int intRow, int intCol, int intFeature)
    {
        int intCount = 0;
        for(int r=intRow-1;r<=intRow+1;r++)
        {
            for(int c=intCol-1;c<=intCol+1;c++)
            {
                if(IsInWorld(intRows,intCols, r,c))
                {
                    if(arrWorld[r][c]==intFeature)
                        intCount++;
                }
            }
        }
        return intCount;
    }


}
