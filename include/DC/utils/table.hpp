#ifndef _TABLE_H_
#define _TABLE_H_
template <class T>
struct table {
  unsigned long X = 0;
  unsigned long Y = 0;
  T** arr = nullptr;
  explicit table() = default;
  explicit table(unsigned long x, unsigned long y) { set(x, y); }
  bool set(unsigned long x, unsigned long y) {
    if (arr != nullptr || X != 0 || Y != 0) return false;
    arr = new T*[x];
    for (int i = 0; i < x; i++) {
      arr[i] = new T[y];
    }
    X = x;
    Y = y;
    return true;
  }
  bool clear() {
    if (arr == nullptr || X == 0 || Y == 0) return false;
    for (unsigned long i = 0; i < X; i++) {
      delete[] arr[i];
    }
    delete[] arr;
    arr = nullptr;
		X=0;
		Y=0;
    return true;
  }
  ~table() { clear(); }
  //注意不返回自己,所以只有二重下标运算
  T* operator[](const unsigned long& n) { return arr[n]; }
};

#endif
