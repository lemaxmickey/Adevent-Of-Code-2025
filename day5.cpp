/******************************************************************************
 * $File: day5.cpp $
 * $Date: 2026-01-06 00:14:28 E. Africa Standard Time $
 * $Revision: 1.0 $
 * $Creator: Mike4847 $
 * $Notice: (C) Copyright 2026 by BanditMan, Inc. All Rights Reserved. $

 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <set>
#include <filesystem>
#include <vector>
#include <string>

using std::string;
using std::vector;

namespace fs = std::filesystem;

struct Range {
    long long start;
    long long end;
};

auto isFresh(long long ingredient_id, const vector<Range>& ranges) -> bool {
    // Check if ingredient_id falls within any range (inclusive)
    for (const auto& range : ranges) {
        if (ingredient_id >= range.start && ingredient_id <= range.end) {
            return true;  // Fresh! 
        }
    }
    return false;  // Spoiled
}

auto main() -> int {
    fs::path file_path = "database.txt";

    if(!  fs::exists(file_path)) {
        std::cerr << "File not found:  " << file_path << std:: endl;
        return 1;
    }

    std::ifstream input(file_path);

    if(!  input.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return 1;
    }

    string line;
    vector<Range> ranges;
    vector<long long> ingredient_ids;
    bool empty_found = false;


    
    // NOTE(mike):Skip empty lines but mark transition
    while(std::getline(input, line)) {
        if(line.empty()) {
            empty_found = true;
            continue;
        }
        if (!  empty_found) {
            size_t pos = line.find('-');
            if (pos != string::npos) {
                long long start = std::stoll(line.substr(0, pos));
                long long end = std::stoll(line.substr(pos + 1));
                ranges.push_back({start, end});
               
            }
        } else {
            long long id = std::stoll(line);
            ingredient_ids.push_back(id);
        }
    }

    // Count fresh ingredients
    int fresh_count = 0;
    for (long long id : ingredient_ids) {
        if (isFresh(id, ranges)) {
            std::cout << "ID " << id << " is FRESH\n";
            fresh_count++;
        } else {
            std::cout << "ID " << id << " is SPOILED\n";
        }
    }

  std::cout << "Total fresh ingredients: " << fresh_count << std::endl;

    return 0;
}
