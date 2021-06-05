# Games101

## 介绍

本项目是在学习 [GAMES101：现代计算机图形学入门](http://games-cn.org/intro-graphics/) 自然而然的产物，包括作业，笔记，资源等。  
主要分为两部分：理论和实践，理论包括 [课程笔记](https://www.jianshu.com/nb/50253025) 和 [虎书（《Fundamentals of Computer Graphics》第四版）笔记](https://www.jianshu.com/nb/50247611)。实践部分主要在该项目中，代码中有详细的注释。

## 环境搭建

课程本身是附带了一个 Linux 的虚拟机的，可以保证每个学员的环境都是一样的，但我是用的 Windows + VsCode 来完成的。下面介绍如何配置。
先完成这个 [大佬](https://zhuanlan.zhihu.com/p/259208999) 写的内容，如果觉得有用的话可以去给原地址给这个大佬点赞... 期间我遇到了一些问题，这里也都做了说明，希望对大家有帮助（如果有人看的话）。为了防止大佬的链接挂掉，所以我在这里记录了完整过程，里面绝大部分是复制的大佬的内容。

### CMake安装

- 安装文件 [CMake下载](https://link.zhihu.com/?target=https%3A//cmake.org/download/)
- 安装的时候选择 Add CMake to the system PATH for all users，加入系统环境变量的路径，保证可以在命令行使用
- 命令行输入cmake --help,验证是否安装成功  

### 安装 Gcc 编译器 mingw

- 安装文件 [mingw下载](https://link.zhihu.com/?target=https%3A//osdn.net/projects/mingw/releases/)
- 解压到任意地方，并且把bin的路径添加到系统环境变量PATH中
- 命令行输入g++ -v,验证是否安装成功

### VSCode，以及插件安装

- 安装文件[VSCode下载](https://link.zhihu.com/?target=https%3A//code.visualstudio.com/)，安装完成以后安装对应插件
- C/C++，mirosoft
- Cmake, twxx
- Cmake Tool, mirosoft
![Vs Code 插件](https://github.com/ZhangQR/Games101/raw/master/Images/README01.png)

### Eigen库编译

- 下载地址 [Eigen](https://link.zhihu.com/?target=http%3A//eigen.tuxfamily.org/index.php%3Ftitle%3DMain_Page)
- 解压到任意目录，eigen 的根目录下新建一个build目录
- 打开 cmake 软件，source目录设置成 eigen 的根目录，build 目录设置成刚刚新建的目录，然后点击 configure，出来的 makefile 的格式选择 mingw，等待 config 结束
- 点击 generate
- 管理员权限运行cmd，进入 build 目录，运行 mingw32-make,之后运行 mingw32-make install
- 删除解压出来的这个 eigen 目录(因为上面安装的已经安装到了 c 盘 Program File x86 里了，有时候 build 的时候会找错路径)

Clone 本项目，Windows 上 Vs Code 配置好 C++ 环境之后可以直接运行，不需要再下载 Eigen。
（**额外说明：完成之后你会发现其实只需要使用 `C:\Program Files (x86)\Eigen3\include\eigen3\Eigen` 里面的文件，所以我已经把这里面的内容复制到了本项目，如果您是直接 Clone 的话，不需要再下载编译 Eigen 库，只需要在编码的时候注意找到 include 的里面的所需的头文件即可**）

### OpenCV 库编译

- 下载地址 [Browse /opencv-win at SourceForge.net](https://link.zhihu.com/?target=https%3A//sourceforge.net/projects/opencvlibrary/files/opencv-win/)，安装说明 [Installation in Windows](https://link.zhihu.com/?target=https%3A//docs.opencv.org/master/d3/d52/tutorial_windows_install.html)
- 解压到任意目录，opencv/source/ 目录下新建一个 build 目录
- 打开 cmake 软件，source 目录设置成 opencv/source/ 目录，build目录设置成刚刚新建的目录，然后点击 configure，出来的 makefile 的格式选择 mingw，等待 config 结束
- 找到 OPENCV_ENABLE_ALLOCATOR_STATS，不勾选后面的对勾(不这样会编译错误), 再次点击 configure，之后点击 generate
- 管理员权限运行 cmd，进入 build 目录，运行 mingw32-make(这个很慢),之后运行 mingw32-make install
- 设置 opencv 的环境变量,管理员权限运行 cmd, 执行 setx -m OpenCV_DIR path_to_build/lib/，然后把 path_to_build/bin 添加到 path 系统环境变量里
（额外说明：之前用的低版本的 opencv，总是会出错，然后换成了最新版 4.5.2 的，就好了；刚安装好的 opencv 是自带 build 目录的，我是直接把他删掉，再按照上面的步骤来；如果在 mingw32-make 到 98% 的时候报了关于 python 的错，可以在 cmake 的时候去掉 **BUILD_opencv_python**）

### 环境变量

完成了大佬的步骤之后，PATH 里面应该已经有了 CMake，MinGW 和 opencv。下面把新建一个 `CC` 变量，值为 `gcc.exe 完整目录`；新建一个 `CXX` 变量，值为 `g++.exe 完整目录`。

### 运行

在 VsCode 中打开一个终端，在某一个 Assignment 下面新建一个文件夹叫做 Build，终端进入 Build。依次执行

``` bash
cmake -G "MinGW Makefiles" ..
mingw32-make -j4
```

没有报错的话会在 build 目录出现一个可执行文件，运行即可。
(如果报了关于 **OpenCV_DIR** 的错，那可能是因为你在设置这个环境变量之前就打开了 VSCode 的终端，所以需要重开一下)  

## 作业  

每一次作业都会在一个单独的 Assignment 文件夹中，Build 里面的东西我没删，在我自己的电脑上是每次都会被覆盖的，如果没有覆盖可以自己手动把 Build 里面所有的东西都删除。

### Assignment0

主要就是搭建环境，然后自己探索一下。  

### Assignment1

1、基础：实现使用 AD 来控制三角形绕着 Z 轴旋转：
![绕着 z 轴旋转](https://github.com/ZhangQR/Games101/raw/master/Images/01_01.gif)

旋转矩阵和透视投影矩阵的写法可以参考 [这篇](https://www.jianshu.com/p/51ea1dfa68bc)。

2、进阶：实现绕着任意轴旋转三角形：  
![绕着 x 轴旋转](https://github.com/ZhangQR/Games101/raw/master/Images/01_02.gif)
![绕着 y 轴旋转](https://github.com/ZhangQR/Games101/raw/master/Images/01_03.gif)
![绕着 (1,1,0) 轴旋转](https://github.com/ZhangQR/Games101/raw/master/Images/01_04.gif)
