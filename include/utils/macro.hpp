#define F_IO                          \
	std::ifstream input("input.dat");   \
	std::ofstream output("output.dat"); \
	defer [&output,&input](){           \
		output.close();                   \
		input.close();                    \
	};
