#ifndef _FILE_H_
#define _FILE_H_
#include <fstream>
#define F_IO                                                                   \
  std::ifstream in("input.dat");                                               \
  std::ofstream out("output.dat");                                             \
  defer[&out, &in]() {                                                         \
    out.close();                                                               \
    in.close();                                                                \
  }

#endif
