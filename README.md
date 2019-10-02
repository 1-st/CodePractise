# DapperCode
这是短小的代码仓库,用于在无聊的时候打法时间,大部分是一些简单的算法实现,

每个实现对应一个目录(以数字为标号)

...
部分会给出golang和cpp两个版本

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
### macro/
	file.hpp:F_IO文件操作宏的定义(此宏用在每个文件的开始,定义ifstream为in,ofstream为out)
## src/
### 1/
	矩阵链乘法(我也不知道为什么暂时鸽鸽鸽)
### 2/
	比特币PoW算法的简单c语言模仿(需要openssl头文件)
