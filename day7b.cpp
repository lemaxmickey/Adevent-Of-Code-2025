#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using std::string;
using std::fstream;
using std::cout;
using std::vector;



// NOTE(mike

int main()
{
  
  fstream file("tachyon.txt");
  size_t start_idx;
  if (!file.is_open())
    {
      cout << "error opening the file" << std::endl;
      exit(1);
    }
  
  vector<string> maniFold;

  string line;
  //NOTE(mike): read the content of the file into a 2-D matrix/manifold.
  while(std::getline(file, line) && (!line.empty()))
    {
      maniFold.push_back(line);
    }
  start_idx = maniFold[0].find('S');
  size_t diffTimelines = quantumTachyion(maniFold, start_idx );


  cout << "The answer to the part b is :\t" << diffTimelines << std::endl;

  
    
  return 0;
}
