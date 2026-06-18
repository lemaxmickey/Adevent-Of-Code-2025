#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <unordered_map>
#include <numeric>
#include <cstdint>


int main()
{
    std::fstream file("tachyon.txt");
    std::vector<std::string> maniFold;

    if(!file.is_open())
    {
        std::cerr << "Cannot open the file\n.Closing ...\n\r\n"<< std::endl;
        exit(1);
    }

    std::string line; 
    while(std::getline(file, line)) {
      if(!line.empty()) maniFold.push_back(line);
    }
       
    size_t width = maniFold[0].size();
    
    // Part A State
    std::vector<bool> beamsA(width, false);
    size_t splitCount = 0;

    // Part B State
    std::vector<int64_t> pathsB(width, 0);
    
    // Initial Position 'S'
    size_t startX = maniFold[0].find('S');
    beamsA[startX] = true;
    pathsB[startX] = 1;

    for (size_t y = 0; y < maniFold.size(); ++y) {
        std::vector<bool> nextBeamsA(width, false);
        std::vector<int64_t> nextPathsB(width, 0);

        for (size_t x = 0; x < width; ++x) {
            // Process Part A
            if (beamsA[x]) {
                if (maniFold[y][x] == '^') {
                    splitCount++;
                    if (x > 0) nextBeamsA[x-1] = true;
                    if (x + 1 < width) nextBeamsA[x+1] = true;
                } else {
                    nextBeamsA[x] = true;
                }
            }

            // Process Part B
            if (pathsB[x] > 0) {
                if (maniFold[y][x] == '^') {
                    if (x > 0) nextPathsB[x-1] += pathsB[x];
                    if (x + 1 < width) nextPathsB[x+1] += pathsB[x];
                } else {
                    nextPathsB[x] += pathsB[x];
                }
            }
        }
        std::swap(beamsA, nextBeamsA);
        std::swap(pathsB, nextPathsB);
    }

    uint64_t noOfBeams = std::accumulate(beamsA.begin(), beamsA.end(), 0);
    std::cout <<  noOfBeams << std::endl;

    uint64_t totalPaths = std::accumulate(pathsB.begin(), pathsB.end(), 0ULL);
    std::cout << "Part B Total Pathways: " << totalPaths << std::endl;
    // std::cout << line.c_str();
    return EXIT_SUCCESS;
}







