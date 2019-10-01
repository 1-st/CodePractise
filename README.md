# DapperCode
这是短小的代码仓库,用于在无聊的时候打法时间,大部分是一些简单的算法实现,

每个实现对应一个目录(以数字为标号)

...
部分会给出golang和cpp两个版本

```
project
│   README.md
│   .gitignore    
│
└───include/DC
│   │
│   └───defer
│       │   defer.hpp
│       │   ...
│   
└───src
    │   
    └───1
        │   main.cpp
        │   makefile
        │   ...
```
## include/DC目录内容
### defer
	defer.hpp:利用lambda模仿golang defer
### utils
	自定义的重复性高的代码工具

	macro.hpp:F_IO文件操作宏的定义(此宏用在每个文件的开始,定义ifstream为in,ofstream为out)
## src目录内容
### 1
	矩阵链乘法
