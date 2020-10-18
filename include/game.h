#ifndef GAME_H_
#define GAME_H_

#include <myhead.h>

//获取随机数用来随机显示图片特效
extern int get_random();
//获取2或者4
extern int get_2or4();
//获取某一个空位置范围的随机位置
extern int get_random_place(int *ret1,int *ret2,int x1,int y1,int x2,int y2);
//显示所有格子的信息对应的图片
extern int show_array(int arr[4][4]);
//判断是否有2048  有返回0，无返回-1
extern int sure_the_2048(int arr[4][4]);
//随机获取位置并赋值2或者4   赋值成功返回0；否则位置满了返回-1；
extern int for_arr_place(int arr[4][4],int *x,int *y);
//判断是否有空位置  有返回0，无返回-1
extern int sure_the_place(int arr[4][4]);
//交换数据
extern void swap(int *data,int *src);
//移动数组的数据，n表示移动的方向
extern int move(int arr[4][4],int n);
//显示格子数据图片
extern int show_place_bmp(int arr[4][4],int *x,int *y);
//2048游戏操作
extern int opera_2048();
#endif