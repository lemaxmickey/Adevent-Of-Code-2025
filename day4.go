/******************************************************************************
 * $File: day4.go $
 * $Date: 2026-01-02 01:30:30 E. Africa Standard Time $
 * $Revision: 1.0 $
 * $Creator: Mike4847 $
 * $Notice: (C) Copyright 2025 by BanditMan, Inc. All Rights Reserved. $

 *****************************************************************************/
package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	grid := readFileToGrid("rolls.txt")
	//printGrid(grid)

	totalRemoved := 0
	
	//TODO(mike): Remove the "MARKED" accessibles in each iterations. 
	
	for{
		count := countAccessible(grid)
		if count == 0{
			break
		}
		totalRemoved += count
	}
	fmt.Printf("\nAnd after the removal the total is %d\n", totalRemoved)
}

func readFileToGrid(filename string) [][]string {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	var grid [][]string

	for scanner.Scan() {
		line := scanner.Text()
		row := strings.Split(line, "")
		grid = append(grid, row)
	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	return grid
}

func printGrid(grid [][]string) {
	fmt.Println("Grid:")
	for _, row := range grid {
		for _, cell := range row {
			fmt.Printf("%s", cell)
		}
		fmt.Println()
	}
}
//NOTE(mike): first pass is to identify the accesibles
// the second pass is for removing the accessibles on a single pass
func countAccessible(grid [][]string) int {
	if len(grid) == 0 {
		return 0
	}

	accessible := 0
	toremove := [][2]int{}
	

	for i := 0; i < len(grid); i++ {
		for j := 0; j < len(grid[i]); j++ {
			if grid[i][j] == "@" {
				adjacentRolls := countAdjacentRolls(grid, i, j)

				if adjacentRolls < 4 {
					accessible++
					toremove = append(toremove, [2]int{i, j})					
				}
			}
		}
	}

	for _, cell :=  range toremove {
		grid[cell[0]][cell[1]] = "."
	}

	return accessible
}


func countAdjacentRolls(grid [][]string, i int, j int) int {
	count := 0
	rows := len(grid)
	cols := len(grid[0])

	directions := [][2]int{
		{-1, -1}, {-1, 0}, {-1, 1},
		{0, -1}, {0, 1},
		{1, -1}, {1, 0}, {1, 1},
	}

	for _, dir := range directions {
		newI := i + dir[0]
		newJ := j + dir[1]

		if newI >= 0 && newI < rows && newJ >= 0 && newJ < cols {
			if grid[newI][newJ] == "@" {
				count++
			}
		}
	}

	return count
}
