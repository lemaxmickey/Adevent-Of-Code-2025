#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <queue>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

/**
 * @brief Zero-allocation string slicing.
 * Mathematically: Projection S -> S[1, n-1)
 */
constexpr std::string_view remove_suf_pre(std::string_view strv) noexcept {
  return (strv.size() <= 2) ? std::string_view{}
                            : strv.substr(1, strv.size() - 2);
}

/**
 * @brief Converts binary string_view to numeric bitmask.
 * Basis: \sum_{i=0}^{n-1} b_i 2^{n-1-i}
 *
 */
uint64_t string_to_mask(std::string_view s) {
  uint64_t mask = 0;
  for (char c : s) {
    mask = (mask << 1) | (c == '1' ? 1 : 0);
  }
  return mask;
}

/**
 * @brief BFS on the F2^N vector space (Hypercube Graph).
 * Complexity: O(2^N * M) where M is button count.
 * // safety threshhold.
  // Create a bitmask of N ones (e.g., if N=3, mask is 0111 binary)
  // Mathematically: 2^N - 1
  // Sanitize: truncate button to the current field dimension N
 * @return positive integers represent the minimum toggles of the respective
 * buttons configuration.
 */
int solve_min_toggles(std::string_view indicator,
                      const std::vector<std::string_view> &buttons) {
  const std::string_view target_view = remove_suf_pre(indicator);
  const size_t N = target_view.size();

  if (N == 0)
    return 0;
  if (N > 30)
    return -2;

  const uint64_t target_configuration = string_to_mask(target_view);
  const uint64_t field_mask = (1ULL << N) - 1;
  // std::cout << "Complex sytems " << field_mask << std::endl;

  std::vector<uint64_t> button_masks;
  button_masks.reserve(buttons.size());
  for (const auto &b : buttons) {
    uint64_t b_mask = string_to_mask(remove_suf_pre(b)) & field_mask;
    button_masks.push_back(b_mask);
  }

  std::queue<std::pair<uint64_t, int>> q{};
  std::vector<bool> visited(1ULL << N, false);

  q.push({0, 0});
  visited[0] = true;

  while (!q.empty()) {
    const auto [current, dist] = q.front();
    q.pop();

    for (const uint64_t btn : button_masks) {
      const uint64_t next = current ^ btn;

      if (next == target_configuration)
        return dist + 1;

      // # of access < 2^N
      if (!visited[next]) {
        visited[next] = true;
        q.push({next, dist + 1});
      }
    }
  }
  return -1;
}
int main() {
  std::ifstream file("factory.txt");
  if (!file) {
    std::cerr << "Kernel Error: File stream acquisition failed.\n";
    return 1;
  }

  // Count lines via ranges (Functional pass)
  auto file_view = std::ranges::subrange(std::istreambuf_iterator<char>(file),
                                         std::istreambuf_iterator<char>());
  size_t lines = std::ranges::count(file_view, '\n');

  // Reset stream head
  file.clear();
  file.seekg(0, std::ios::beg);

  std::cout << "Systems Audit: " << lines << " configurations found.\n\n";

  std::string line;
  int line_idx = 1;

  int ans = 0;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    auto chunks =
        line | std::views::split(' ') | std::views::transform([](auto &&rng) {
          return std::string_view(&*rng.begin(), std::ranges::distance(rng));
        }) |
        std::ranges::to<std::vector<std::string_view>>();

    if (chunks.size() < 2)
      continue;

    // Logical Domain Mapping
    std::string_view indicator = chunks.front();
    std::string_view joltage = chunks.back();

    // Isolate button schematics (indices 1 to n-2)
    std::vector<std::string_view> buttons;
    if (chunks.size() > 2) {
      buttons.assign(chunks.begin() + 1, chunks.end() - 1);
    }

    std::cout << "Line " << line_idx++
              << " | Target: " << remove_suf_pre(indicator)
              << " | Req: " << remove_suf_pre(joltage) << "\n";

    int result = solve_min_toggles(indicator, buttons);
    ans += result;

    if (result >= 0) {
      std::cout << "  >> Result: Success. Optimal path: " << result
                << " toggles.\n";
    } else if (result == -2) {
      std::cout
          << "  >> Result: Error. State space exceeds memory threshold.\n";
    } else {
      std::cout << "  >> Result: Failure. Path non-existent in vector space.\n";
    }
    std::cout << "--------------------------------------------------\n";
  }

  std::cout << "The answer is " << ans << std::endl;

  return 0;
}