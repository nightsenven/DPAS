#ifndef GETINFO_H_
#define GETINFO_H_
#include <myhead.h>
//获取bmp图片的宽和高
extern int get_bmp_wh(char *bmp_name,int *w,int *h);
//根据图片的宽高获取居中显示的位置
extern int sure_bmp_place(int *w,int *h,int *start_x,int *start_y,char *bmppath);
//获取划屏的起始值
extern int get_screen_act_start(int *start_x,int *start_y);
//获取划屏的结束值
extern int get_screen_act_end(int *end_x,int *end_y);
//获取图片的数据
extern int get_bmp_info(char *bmp_name,int *lastbuf,int bmp_w,int bmp_h);
//从文件读取用户信息
extern lgin *read_info(lgin user[],int n);
//保存登录信息到文件中
extern int save_for_info(lgin user);

#endif