def largest_joltage_partb(bank : str)->int:
    """
    NOTE(mike):
    The idea that drives this routine is:
    
    """
    answer = []
    digits = [int(ch) for ch in bank if ch.isdigit()]
    if len(digits) < 12:
        return 0

    i = 3
    while(i > 0):
        print(digits)
        d1 = min(digits)
        print(d1)
        idx1 = digits.index(d1)
        digits.pop(idx1)
        i-= 1


    print(digits)
    

def largest_joltage(line: str) -> int:
    """
    NOTE(mike):
    Finds the largest two-digit number formed by two digits in the line,
    preserving their original relative order.
    """
    # Extract all digits as a list of integers
    digits = [int(ch) for ch in line if ch.isdigit()]
    
    # We need at least 2 digits to form a number
    if len(digits) < 2:
        return 0
    d1 = max(digits[:-1])   
    idx1 = digits.index(d1)
    
    remaining_digits = digits[idx1+1:]
    d2 = max(remaining_digits)
    
    return d1 * 10 + d2

def read_text() -> list:
    """Reads the input file and returns a list of lines."""
    try:
        with open("day3.txt", "r") as f:
            return [line.strip() for line in f.readlines()]
    except FileNotFoundError:
        print("Error: File 'day3.txt' not found.")
        return []


def select_max_in_order(line: str, k: int) -> int:
    """
    Selects k digits from `line` in their original order (no reordering)
    to form the maximal possible k-digit number. Returns 0 if there are
    fewer than k digits.
    Greedy approach: for each pick i, choose the largest digit in the
    window [start .. n - (k - i)] (inclusive), then move start after it.
    """
    digits = [int(ch) for ch in line if ch.isdigit()]
    n = len(digits)
    if n < k:
        return 0

    selected = []
    start = 0
    # For each of the k picks
    for i in range(k):
        # last index we can choose for this pick so that we still have
        # enough digits left for the remaining picks:
        last_index = n - (k - i)
        max_digit = -1
        max_idx = start
        # scan allowed window for the largest digit (first occurrence of max)
        for j in range(start, last_index + 1):
            d = digits[j]
            if d > max_digit:
                max_digit = d
                max_idx = j
                if max_digit == 9:  # early exit, can't do better than 9
                    break
        selected.append(str(max_digit))
        start = max_idx + 1

    return int("".join(selected))

def largest_joltage_part2(line: str) -> int:
    """Part 2 behavior: pick 12 digits in order to form the largest twelve-digit number."""
    return select_max_in_order(line, 12)

def main():
    """Main function to read input, compute the sum, and display results."""
    lines = read_text()
    if not lines:
        return

    #largest_joltage_partb(str(234234234234278))
    #total_sum = 0
    #for line in lines:
    #    total_sum += largest_joltage(line)

    total_part2 = sum(largest_joltage_part2(line) for line in lines)
    
   ### print(f"The sum of the joltages is: {total_sum}")
    print(f"The sum of the jolatges in part  is \t {total_part2}")
    

if __name__ == "__main__":
    main()
