# Tongji: A Survivor’s Guide

这个名为“Tongji: A Survivor’s Guide”的迷宫游戏，以同济校园生活为主题元素，在游戏中穿插过去一个学期的充实学习生活的回忆，是同学们在学习之余放松心情缓解压力的好方式。
该游戏是基于VS2019和easyx开发，迷宫部分基于BFS算法和Prim算法自动生成随机迷宫，实现玩家控制人物行走于二维迷宫中，收集宝石（课本）的动画效果，并计算时间与得分，此外在首页用简单的递归函数实现了樱花动画。


该游戏以同济校园生活为主题元素，首页的樱花递归动画，樱花致意了同济爱校路的春日，递归函数致意了精彩的高程课；游戏迷宫部分使用基于BFS算法（个人原创改进）和Prim算法随机生成迷宫，游戏人物粉色灵感来自于济勤粉；游戏成功时，玩家到达尾页，会发现小人收集的宝石转化为了书本，整个游戏的得分以绩点形式显示，联系校园生活，鼓励玩家在现实学习生活努力奋发。
该游戏基于VS2019和easyx开发，迷宫部分基于宽度优先搜索法生成随机迷宫，同时我也制作了基于Prim算法的自动生成迷宫，进行对比，最终版程序应用的是基于宽度优先搜索法的程序，该部分为改进算法，代码完全原创。
计时实现输入同时显示时间，多线程并行（thread，detach）实现了这一点。
背景图片的绘制综合运用了putimage,loadimage函数和easyx绘图工具，BeginBatchDraw，FlushBatchDraw等减少画面的闪烁现象。济勤人图片效果使用了遮罩层，对原图片部分像素进行隐藏。

本游戏的分为5个cpp,main.cpp包含main函数负责调用其他函数，
First_Page.cpp负责绘制动画樱花效果，并显示游戏的标题，花色与树干标题框的颜色，枝桠角度均用rand函数产生一定随机性，更具美感。
Second_Page.cpp显示游戏规则，代码量少，但为清晰起见，我分了一个cpp.
Maze.cpp功能包括产生（initial_maze，generate_maze函数，运用BFS算法和栈的思想）并绘制迷宫（print_maze函数）产生随机位置的宝石（random_place函数）和控制人物移动（get_move函数及其调用的负责小人迈步动画的cartoon函数）。

![image](https://github.com/TitusVespasian/Maze_Runner/blob/master/images/01.jpg)

Timing函数中运用多线程并行实现输入同时有显示时间。

![image](https://github.com/TitusVespasian/Maze_Runner/blob/master/images/02.jpg)

GPA.cpp负责显示尾页计算分数

## 游戏效果：

![image](https://github.com/TitusVespasian/Maze_Runner/blob/master/images/03.jpg)

起始页的樱花递归动画，背景是同济草坪照片来自百度图片

游戏简介

![image](https://github.com/TitusVespasian/Maze_Runner/blob/master/images/04.jpg)

随机生成的迷宫，迷宫中的济勤人，和位置随机的宝石，右下角游戏时间

![image](https://github.com/TitusVespasian/Maze_Runner/blob/master/images/05.jpg)

![image](https://github.com/TitusVespasian/Maze_Runner/blob/master/images/06.jpg)

小人右转动画

游戏结束图（一分中内完成）

![image](https://github.com/TitusVespasian/Maze_Runner/blob/master/images/07.jpg)

## 创新点：

initial_maze函数，受BFS算法启发，使整个地图产生被墙（灰）包围的通路（黄），然后随机选择一个方格作为起点，随机选一个方向，检查此方向隔了一个灰的格子，若其为黄，则格子入栈，两个黄格和中间灰格变为红格；若其为红再选一个方向，若该方格四周均为红，则指向栈顶的指针下移至找到四周不全是红格的黄格，直至所有黄格变红为止。红格为通路，灰格为墙。
计时函数为实现获取玩家输入同时显示时间，应用多线程并行，每秒更新提高程序效率。

同时界面添加同济校园生活元素是设计上的创新。
