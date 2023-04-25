#ifndef LIBSHELTER_H
#define LIBSHELTER_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cassert>

using namespace std;
namespace ShelterSpace
{
    // array values
  const int VAL_HOME = 1 ;
  const int VAL_UTOPIAN = 2 ;
  const int VAL_UTOPIAN_AT_HOME = 3 ;
  const int VAL_COMPLAINCE_OFFICER = 4 ;
  const int VAL_SPACE = 5;
  //output characters
  const char CH_HOME = 'H';
  const char CH_UTOPIAN = 'P';
  const char CH_UTOPIAN_AT_HOME = 'U';
  const char CH_OFFICER ='C';
  const char CH_SPACE = '.';
  //Error values
  const int SUCCESS = 0 ;
  const int ERROR_RANGE = -1 ;
  const int ERROR_ARGC = -2 ;
  const int ERROR_CONV = -3 ;
  const int UP =1  ;
  const int DOWN =2 ;
  const int LEFT = 3 ;
  const int RIGHT = 4 ;

  // array definations
  typedef int* OneArray ;
  typedef int** TwoArray ;

  const int MIN = 5 ;
  //Functions
  int GetInt(string strInt);
  TwoArray MemoryAlloc(int intRows ,int intCols);
  TwoArray InitWorld (int intRows , int intCols , int intTurns, int intUtopians);
  void DeallocMemory(TwoArray& arrWorld, int intRows);
  void OutputWorld(TwoArray arrWorld,int intRows, int intCols);
//  void MoveUtopian(TypeTwoArray arrWorld, TypeTwoArray arrTemp, int intRows, int intCols, int intRow, int intCol);
  void MoveUtopians(TwoArray arrWorld,int intRows , int intCols );
  int CheckEnd(TwoArray arrWorld,int intRows,int intCols , int intTurns,int intUtopians);




}
#endif // LIBSHELTER_H
