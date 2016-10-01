#include <iostream>
#include <algorithm>
#include <vector>

const ssize_t DEFAULT_START = 0;
const ssize_t DEFAULT_END = 1;

class Request {
  public:
    Request(const ssize_t& start_time = DEFAULT_START, const ssize_t& end_time = DEFAULT_END): _start_time(start_time), _end_time(end_time) {}
    ~Request() {}
    ssize_t start_time() { return _start_time; }
    ssize_t end_time() { return _end_time; }

    Request& operator = (const Request& rhs) {
      _start_time = rhs._start_time;
      _end_time = rhs._end_time;
      return *this;
    }

  protected:
    ssize_t _start_time;
    ssize_t _end_time;
};

bool compare_requests (Request lhs, Request rhs) { return lhs.end_time() < rhs.end_time(); }

void read_requests(std::vector<Request>& list) {
  while(true) {
    if (std::cin.eof()) {
      break;
    }
    ssize_t start, end;
    std::cin >> start;
    std::cin >> end;
    list.push_back(Request(start, end));
  }
  std::sort(list.begin(), list.end(), compare_requests);
}

size_t count_requests(std::vector<Request> requests) {
  size_t satisfied = 1;
  size_t current_end_id = 0;
  for (size_t i = 1; i < requests.size(); ++i) {
    if (requests[i].start_time() >= requests[current_end_id].end_time()) {
      ++satisfied;
      current_end_id = i;
    }
  }
  return satisfied;
}

int main() {
  std::vector<Request> requests;
  read_requests(requests);
  std::cout << count_requests(requests);
  return 0;
}

