# CodePractise
一些短小的代码,用于在无聊的时候打法时间,大部分是一些简单的算法实现,

每个实现对应一个目录(以数字为标号)

...

```
project
│   README.md
│   .gitignore    
│   ...
└───include/DC
│   │defer.hpp
│   │...
│   └───macro
│       │   file.hpp
│       │   ...
│   
└───src
    │   makefile_template 
    └───1
        │   main.cpp
        │   makefile
        │   ...
```
## include/DC/
### defer.hpp
	利用lambda模仿golang defer
### utils/
	自定义的重复性高的代码工具
	table.hpp(简易的二维数组类)
	type.hpp(自己定义感觉顺眼的类型名)
### macro/
	file.hpp:F_IO文件操作宏的定义(此宏用在每个文件的开始,定义ifstream为in,ofstream为out)  
	
## src/
### 1/
	矩阵链乘
### 2/
	PoW的c语言写意代码(需要openssl头文件)
### 3/
	求最长字串(LCS),保存了所有状态
## 4/
    蹩脚的遗传算法求方程的解
