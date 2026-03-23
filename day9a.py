# Code by Mike4847 (Michael Eleman)
# Advent of Code 2025 - Day 9 (Parts A and B)

from itertools import combinations


def read_vertices(path="redTiles.txt"):
    with open(path) as f:
        return [tuple(map(int, line.strip().split(','))) for line in f if line.strip()]


def is_inside_polygon(x, y, vertices):
    inside = False
    n = len(vertices)
    for i in range(n):
        j = (i - 1) % n
        xi, yi = vertices[i]
        xj, yj = vertices[j]
        if ((yi > y) != (yj > y)) and (x < (xj - xi) * (y - yi) / (yj - yi) + xi):
            inside = not inside
    return inside


def shoelace_area2(vertices):
    total = 0
    n = len(vertices)
    for i in range(n):
        x1, y1 = vertices[i]
        x2, y2 = vertices[(i + 1) % n]
        total += x1 * y2 - x2 * y1
    return abs(total)


def boundary_lattice_points(vertices):
    total = 0
    n = len(vertices)
    for i in range(n):
        x1, y1 = vertices[i]
        x2, y2 = vertices[(i + 1) % n]
        total += abs(x2 - x1) + abs(y2 - y1)
    return total


def solve_part_a(vertices):
    area2 = shoelace_area2(vertices)
    boundary = boundary_lattice_points(vertices)
    interior = (area2 - boundary + 2) // 2
    total_red_and_green = interior + boundary
    return interior, total_red_and_green


def build_inside_prefix(vertices):
    xs = sorted({x for x, _ in vertices})
    ys = sorted({y for _, y in vertices})
    ix = {x: i for i, x in enumerate(xs)}
    iy = {y: i for i, y in enumerate(ys)}

    nx = len(xs) - 1
    ny = len(ys) - 1

    inside = [[0] * nx for _ in range(ny)]
    for j in range(ny):
        cy = (ys[j] + ys[j + 1]) / 2
        for i in range(nx):
            cx = (xs[i] + xs[i + 1]) / 2
            inside[j][i] = 1 if is_inside_polygon(cx, cy, vertices) else 0

    prefix = [[0] * (nx + 1) for _ in range(ny + 1)]
    for j in range(ny):
        run = 0
        for i in range(nx):
            run += inside[j][i]
            prefix[j + 1][i + 1] = prefix[j][i + 1] + run

    return xs, ys, ix, iy, prefix


def rect_sum(prefix, i1, j1, i2, j2):
    return prefix[j2][i2] - prefix[j1][i2] - prefix[j2][i1] + prefix[j1][i1]


def solve_part_b(vertices):
    xs, ys, ix, iy, prefix = build_inside_prefix(vertices)

    best_area = 0
    best_pair = None

    for (x1, y1), (x2, y2) in combinations(vertices, 2):
        if x1 == x2 or y1 == y2:
            continue

        xa, xb = (x1, x2) if x1 < x2 else (x2, x1)
        ya, yb = (y1, y2) if y1 < y2 else (y2, y1)

        i1, i2 = ix[xa], ix[xb]
        j1, j2 = iy[ya], iy[yb]

        cell_count = (i2 - i1) * (j2 - j1)
        if cell_count == 0:
            continue

        if rect_sum(prefix, i1, j1, i2, j2) != cell_count:
            continue

        area = (xb - xa + 1) * (yb - ya + 1)
        if area > best_area:
            best_area = area
            best_pair = (xa, ya, xb, yb)

    return best_area, best_pair


def solve():
    try:
        vertices = read_vertices("redTiles.txt")
    except FileNotFoundError:
        print("Error: redTiles.txt not found.")
        return

    green_tiles, total_red_green = solve_part_a(vertices)
    part_b_area, part_b_pair = solve_part_b(vertices)

    print(f"Part A - Green Tiles: {green_tiles}")
    print(f"Part A - Red+Green Tiles: {total_red_green}")
    print(f"Part B - Largest Rectangle Area: {part_b_area}")
    if part_b_pair:
        x1, y1, x2, y2 = part_b_pair
        print(f"Part B - Opposite Red Corners: ({x1}, {y1}) and ({x2}, {y2})")


if __name__ == "__main__":
    solve()