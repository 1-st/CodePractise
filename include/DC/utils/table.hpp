#ifndef _TABLE_H_
#define _TABLE_H_

template <class T>
struct table {
  unsigned long X;
  unsigned long Y;
  T** arr;
  table() = default;
  table(unsigned long x, unsigned long y):X(x),Y(y){
		arr = new T*[X];
		for(int i=0;i<X;i++){
			arr[i] = new T[Y];
		}
  }
  ~table() {
		for(unsigned long i=0;i<X;i++){
			delete [] arr[i];
		}
		delete[] arr;
	}
  T* operator[](const int& n) { return arr[n]; }
};

#endif
