#ifndef MYHEAD_H_
#define MYHEAD_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <time.h>
#include "kernel_list.h"
#include <sys/ioctl.h>
#include <linux/soundcard.h>
#include <math.h>

#define PATHSIZE 80
#define NAMESIZE 20
#define PASSSIZE 16

int lcdfd;

//定义内核链表的大结构体
typedef struct kernel_list
{
	char path[PATHSIZE];
	struct list_head mylist;
}klist;

//定义登录信息结构体
typedef struct login_info
{
	char name[NAMESIZE];
	char password[PASSSIZE];
}lgin;

extern klist *init_list();  //初始化内核链表
extern klist *new_node(char *path); //新建新节点
//释放内核链表的所有堆空间
extern int free_klist(klist *head);
//打开目录,保存所有.bmp图片
extern int open_dir_save_bmp(char *dirpath,klist *head);
//打开目录,保存所有.mp3音乐
extern int open_dir_save_mp3(char *dirpath,klist *head);
//操作bmp上下翻页
extern int operation_bmp();
//打开目录,保存所有.mp4或者.avi音乐
extern int open_dir_save_movie(char *dirpath,klist *head);







#endif