/******************************************************************************
 * $File: day2.cpp $
 * $Date: 2025-12-08 22:44:18 E. Africa Standard Time $
 * $Revision: 1.0 $
 * $Creator: Michael Eleman $
 * $Notice: (C) Copyright 2025 by BanditMan, Inc. All Rights Reserved. $

 *****************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ios>
#include <cstdlib>
#include <vector>


using std::cout;
using std::cin;
using std::string;
using std::vector;


//XXX(mike): Advent of code 2025
// Adventure of Day 2's implementation



bool is_same(string *str)
{
  bool answer = true;
  int i;
  int j ;
  for ( i = 0, j =  str->size() - 1; (i + j) < str->size(); i++, j++ )
    {
      if(str->at(i) != str->at(j))
	{
	  answer = false;
	  break
	}
       
    }

  return answer;
}

long long isValidId(long long &firstId, long long &lastId)
{
  long long start = firstId, end = lastId;
  long long answer = 0;
  while(start != end)
    {
      if(std::to_string(start).length() % != 2)
	{
	  start++;
	  continue;
	}else
	{
	  if(is_same(std::to_string(start)))
	    {
	      answer += start;
	    }
	}

      start ++;
    }

  return answer;
}


int main(void)
{
  std::fstream file("Ranges.txt", std::ios::in|std::ios::out);

  if(!file.is_open())
    {
      std::cerr << "File couldn't be opened";
      std::exit(1);
    }


  std::stringstream sstream;
  sstream << file.rdbuf() ;

  cout << sstream.str() << std::endl;

  file.close();

  // TODO(mike): manipulate the stringstream object.

  std::string line;
  long long firstId , lastId;

  line.clear();
  while(std::getline(sstream , line, ','))
    {
      std::size_t pos = line.find('-');

      firstId = std::stoll(line.substr(0, pos));
      lastId =  std::stoll(line.substr(pos + 1));

      std::pair<bool , long long> result = isValidId(firstId, lastId);
      if(result.)
    }
 
  
  return 0;
}
