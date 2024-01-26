#include <cstdint>
#include <cstdlib>
#include <iostream>

int main() {
  for (uint32_t i = 1; i < 4; ++i) {
    std::string s = "mpic++ A";
    s += i + '0';
    s += ".cpp -o a.exe";
    system(s.data());
    for (uint32_t j = 1; j < 9; ++j) {
      std::string ss = "mpiexec -n ";
      ss += '0' + j;
      ss += " a.exe";
      system(ss.data());
    }
  }
}