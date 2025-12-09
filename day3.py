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
    
   .
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

def main():
    """Main function to read input, compute the sum, and display results."""
    lines = read_text()
    if not lines:
        return
    
    total_sum = 0
    for line in lines:
        total_sum += largest_joltage(line)
    
    print(f"The sum of the joltages is: {total_sum}")

if __name__ == "__main__":
    main()
