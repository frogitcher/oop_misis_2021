#include "exam.h"
#include <vector>

int main()
{
  std::vector<double> test_values = {1.1, 1.2, 1.3};
  std::vector<int> test_priority = {5, 4, 3};
  prior_queue<double> new_queue(test_values, test_priority);
  new_queue.print();
}