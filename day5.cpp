/******************************************************************************
 * $File: day5.cpp $
 * $Date: 2026-01-19 10:46:36 E. Africa Standard Time $
 * $Revision: 1.0 $
 * $Creator: Mike4847 $
 * $Notice: (C) Copyright 2026 by BanditMan, Inc. All Rights Reserved. $

 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
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


auto countFreshIds(const vector<Range>& mergedRanges) -> long long {
    long long count = 0;
    for (const auto& range : mergedRanges) {
        count += (range.end - range.start + 1);
    }
    return count;
}

auto mergeRanges(vector<Range>& ranges) -> vector<Range> {
    if (ranges.empty()) return {};
    
    // Sort ranges by start value
    std::sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
        return a.start < b.start;
    });
    
    vector<Range> merged;
    merged.push_back(ranges[0]);
    
    for (size_t i = 1; i < ranges.size(); i++) {
        Range& last = merged.back();
        const Range& current = ranges[i];
        
        // Check if current overlaps or is adjacent to last
        if (current.start <= last. end + 1) {
            // Merge:  extend the end if needed
            last.end = std::max(last.end, current.end);
        } else {
            // No overlap, add as new range
            merged.push_back(current);
        }
    }
    
    return merged;
}


auto main() -> int {
    fs::path file_path = "database.txt";

    if(!  fs::exists(file_path)) {
        std::cerr << "File not found:  " << file_path << std:: endl;
        return 1;
    }

    std::ifstream input(file_path);

    if(!input.is_open()) {
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
        if (!empty_found) {
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


    //NOTE(mike): The idea is simply count 'ALL' of the fresh infredient ID ranges
    // considered to be fresh.. 
    // Count fresh ingredients

    // Efficient Part B solution
    vector<Range> mergedRanges = mergeRanges(ranges);
    long long fresh_range_count = countFreshIds(mergedRanges);
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
    std::cout << "The value of the 'fresh' ingredients is:\t"<< fresh_range_count ;

    std::cout << "Part B - Total unique fresh IDs: " << fresh_range_count << std::endl;
    return 0;
}
