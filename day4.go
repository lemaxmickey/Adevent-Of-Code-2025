/******************************************************************************
 * $File: day4.go $
 * $Date: 2025-12-28 14:49:30 E. Africa Standard Time $
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
	printGrid(grid)

	count := countAccessible(grid)
	fmt.Printf("\nAccessible rolls: %d\n", count)
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

func countAccessible(grid [][]string) int {
	if len(grid) == 0 {
		return 0
	}

	accessible := 0

	for i := 0; i < len(grid); i++ {
		for j := 0; j < len(grid[i]); j++ {
			if grid[i][j] == "@" {
				adjacentRolls := countAdjacentRolls(grid, i, j)

				if adjacentRolls < 4 {
					accessible++
				}
			}
		}
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
