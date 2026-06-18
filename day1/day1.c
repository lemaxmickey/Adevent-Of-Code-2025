/******************************************************************************
 * $File: day1.c $
 * $Date: 2025-12-03 14:48:08 E. Africa Standard Time $
 * $Revision: 1.0 $
 * $Creator: Mike4847 $
 * $Notice: (C) Copyright 2025 by BanditMan, Inc. All Rights Reserved. $

 *****************************************************************************/

//NOTE(MIKE): Advent of code 2025.

#include <stdio.h>
#include <stdlib.h>

int rotation(int start, char *direction, int *clicks) {
    int result;
    switch(*direction) {
        case 'L':
            result = ((start - *clicks) % 100 + 100) % 100;  // Handle negatives
            break;
        case 'R':
            result = (start + *clicks) % 100;
            break;
        default:
            result = start;
    }
    return result;
}

int main() {
    char *file = "dayOne.txt";
    FILE *inputs = fopen(file, "r");
    
    if(inputs == NULL) {
        puts("Can't open the file...  \nExiting.. .");
        exit(1);
    }
    
    int zeroSum = 0;
    char letter;
    int number;
    int start = 50;
    
    puts("Opening file... .");
    
    while(fscanf(inputs, " %c%d", &letter, &number) == 2) {
        int result = rotation(start, &letter, &number);
        
       
        if(result == 0) {
            zeroSum++;
        }
        
        
        start = result;
        
        printf("letter: %c, number: %d, new position: %d\n", letter, number, result);
    }
    
    printf("\nThe answer for Advent of Code 2025 Day 1 is: %d\n", zeroSum);
    
    fclose(inputs);
    return 0;
}
