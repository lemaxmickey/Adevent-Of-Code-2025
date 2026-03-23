package main

// By Michael Eleman
// The snippet below was compiled in quest of explaining "THE EFFECTIVE" way of solving >>
// problem : Advent of code day8
//

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
	"strconv"
	"strings"
)

// Junction represents a 3D coordinate in space.
type Junction struct {
	x, y, z int
}

// Edge represents a connection between two junctions and its squared distance.
type Edge struct {
	u, v   int
	distSq int // Pure integer math, completely avoiding math.Sqrt i.e this is because the CPU cycles needed is way to expensive
}

// Find locates the absolute root of the set, applying Path Compression.
func Find(parent []int, i int) int {
	if parent[i] == i {
		return i
	}
	// Path compression: flatten the tree recursively
	parent[i] = Find(parent, parent[i])
	return parent[i]
}

// Union merges two sets based on their roots, utilizing Union by Size.
// Union now returns the new circuit size, or 0 if a cycle was detected
func Union(parent []int, size []int, u int, v int) int {
	rootU := Find(parent, u)
	rootV := Find(parent, v)

	// Cycle detection: already in the same circuit
	if rootU == rootV {
		return 0
	}

	var newSize int
	// Union by Size
	if size[rootU] < size[rootV] {
		parent[rootU] = rootV
		size[rootV] += size[rootU]
		newSize = size[rootV]
	} else {
		parent[rootV] = rootU
		size[rootU] += size[rootV]
		newSize = size[rootU]
	}

	return newSize
}
func main() {
	filename := "day8.txt"
	fil, err := os.Open(filename)
	if err != nil {
		log.Fatal("Opening the file failed: ", err)
	}
	defer fil.Close()

	scanner := bufio.NewScanner(fil)
	var junctions []Junction

	// Phase 1: Parse the file
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Split(line, ",")
		if len(parts) >= 3 {
			x, _ := strconv.Atoi(strings.TrimSpace(parts[0]))
			y, _ := strconv.Atoi(strings.TrimSpace(parts[1]))
			z, _ := strconv.Atoi(strings.TrimSpace(parts[2]))
			junctions = append(junctions, Junction{x, y, z})
		}
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	N := len(junctions)
	if N == 0 {
		log.Fatal("No junctions found.")
	}
	fmt.Printf("Successfully parsed %d junctions.\n", N)

	// Phase 2: Generate all unique edges
	// Pre-allocate slice capacity to prevent reallocation overhead: N * (N - 1) / 2
	capacity := (N * (N - 1)) / 2
	edges := make([]Edge, 0, capacity)

	for i := 0; i < N; i++ {
		for j := i + 1; j < N; j++ {
			dx := junctions[i].x - junctions[j].x
			dy := junctions[i].y - junctions[j].y
			dz := junctions[i].z - junctions[j].z

			distSq := dx*dx + dy*dy + dz*dz
			edges = append(edges, Edge{u: i, v: j, distSq: distSq})
		}
	}

	// Phase 3: Sort edges to find the global minimums
	// This pushes the complexity to O(E log E)
	sort.Slice(edges, func(i, j int) bool {
		return edges[i].distSq < edges[j].distSq
	})

	//Safely determine how many edges to process (up to 1000)
	limit := 1000
	if len(edges) < 1000 {
		limit = len(edges)
	}

	// Phase 4: Union-Find Initialization
	parent := make([]int, N)
	size := make([]int, N)
	for i := 0; i < N; i++ {
		parent[i] = i // Every node is its own root
		size[i] = 1   // Every circuit starts with size 1
	}

	// Phase 5: Process the shortest edges to build the circuits
	for i := 0; i < limit; i++ {
		edge := edges[i]
		Union(parent, size, edge.u, edge.v)
	}

	// Phase 6: Extract isolated circuits and calculate the final result
	var circuitSizes []int
	for i := 0; i < N; i++ {
		// If a node is its own parent, it is the absolute root of a distinct circuit
		if parent[i] == i {
			circuitSizes = append(circuitSizes, size[i])
		}
	}

	// Phase 5: Kruskal's Algorithm for the Minimum Spanning Tree
	var finalU, finalV int

	for i := 0; i < len(edges); i++ {
		edge := edges[i]

		// Attempt to merge the circuits
		newSize := Union(parent, size, edge.u, edge.v)

		// HPC Early Exit: The moment the root size hits N, the graph is unified.
		if newSize == N {
			finalU = edge.u
			finalV = edge.v
			break
		}
	}

	// Phase 6: Part B Output Calculation
	x1 := junctions[finalU].x
	x2 := junctions[finalV].x

	fmt.Printf("Graph fully connected at the edge between Box %d and Box %d.\n", finalU, finalV)
	fmt.Printf("Part B Result (X-coordinates multiplied): %d\n", x1*x2)

	// // Sort the isolated circuit sizes in descending order
	// sort.Slice(circuitSizes, func(i, j int) bool {
	// 	return circuitSizes[i] > circuitSizes[j]
	// })

	// fmt.Println("Top circuit sizes:", circuitSizes)

	// if len(circuitSizes) >= 3 {
	// 	result := circuitSizes[0] * circuitSizes[1] * circuitSizes[2]
	// 	fmt.Printf("Result (Top 3 multiplied): %d\n", result)
	// } else {
	// 	fmt.Println("Less than 3 distinct circuits formed.")
	// }
}
