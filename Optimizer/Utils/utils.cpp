#include "../Constants/pch.h"

namespace Utils {
template <class Item>
std::vector<Item> intersection(std::vector<Item>& a, std::vector<Item>& b) {
  std::vector<Item> result;
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  int a_ptr = 0, b_ptr = 0;
  while (a_ptr < a.size() && b_ptr < b.size()) {
    if (a[a_ptr] < b[b_ptr]) {
      a_ptr++;
    } else if (a[a_ptr] > b[b_ptr]) {
      b_ptr++;
    } else {
      result.push_back(a[a_ptr]);
      a_ptr++;
      b_ptr++;
    }
  }

  return result;
}

template <class Item>
std::vector<Item> omit(const std::vector<Item>& original, const Item& toRemove) {
  std::vector<Item> result;
  result.reserve(original.size());

  for (Item item : original) {
    if (item == toRemove) continue;
    result.push_back(item);
  }

  return result;
}

}  // namespace Utils