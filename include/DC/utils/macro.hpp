#define F_IO                          \
	std::ifstream in("input.dat");   \
	std::ofstream out("output.dat"); \
	defer [&out,&in](){           \
		out.close();                   \
		in.close();                    \
	};
