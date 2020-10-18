#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <myhead.h>

//显示黑色底板
extern int black_show();
//任意位置显示不大于800*480的任意大小的BMP图片
extern int show_any_bmp(int bmp_x,int bmp_y,int any_x,int any_y,char *bmp_name);
//任意位置显示缩小的图片  参数：缩小倍数，图片路径名，位置坐标
extern int reduce_bmp(char *bmp_name,int new_w,int new_h,int any_x,int any_y);
//任意位置任意大小的图片的特效
extern int show_bmp_super(int bmp_x,int bmp_y,int any_x,int any_y,char *bmp_name,int n);
//拼接成1600*480的图片并从右往左展开显示
extern int splicing_bmp(int *p,int *q);
//相册界面
extern int pic_menu();
//显示相册操作按钮
void photo_show(int w,int h,int x,int y,char *buf);
//显示主界面
extern int menu();
//注册登录信息
extern int apply_info();
//匹配账号
extern int find_name(lgin *p,char *name);
//匹配密码
extern int find_pass(lgin *p,char *pass);
//显示登录界面
extern int longin_show();
//显示缩略图
extern struct list_head *reduce_show(struct list_head *p,klist *bmphead,int *n);
//寻找点击到的图片名字
extern struct list_head *find_bmp(struct list_head *p,klist *bmphead,int n);
//寻找上一页要显示第一个缩略图片的名字
extern struct list_head *find_bmp_up(struct list_head *p,klist *bmphead,int n);
//点击缩略图中的某个图片的显示
extern struct list_head *someone_show(struct list_head *p,klist *head,int n,int m);

#endif