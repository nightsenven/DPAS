#ifndef BOTTON_H_
#define BOTTON_H_
#include <myhead.h>

#define QUITL 0           //退出系统
#define QUITM 100           //退出主界面

#define LOGIN 1          //登录界面
#define MMENU 2          //主界面
#define NUSIC 3          //音频界面
#define MOVIE 4          //视频界面
#define POTHO 5          //相册界面
#define GAME2048 6       //2048游戏界面

#define PALYMP3 7        //播放暂停mp3按键
#define PREVMP3 8        //上一首mp3按键
#define NEXTMP3 9        //下一首mp3按键
#define KILLMP3 10        //停止播放mp3按键
#define QUITMP3 11       //退出mp3界面按键

#define QUITMP4 12       //退出mp4界面按键
#define PALYMP4 13       //播放视频按键
#define PREVMP4 14       //上一个mp4按键
#define NEXTMP4 15       //下一个mp4按键
#define PSMP4 17         //播放暂停mp4按键
#define STOPMP4 18       //停止播放视频

#define QUITPT 21         //退出相册按键
#define PREVPT 22         //上一张按键
#define NEXTPT 23         //下一张按键

#define LOGINNAME 24      //登录用户名
#define LOGINPASS 25      //登录密码
#define LOGINAPPLY 26      //注册

#define APPLYNAME 27     //注册账号
#define APPLYPASS 28      //注册密码
#define APPLY 29		//开始注册
#define CANCEL 30		//取消注册

#define UP 31       	//向上划屏
#define DOWN 32			//向下划屏
#define LEFT 33			//向左划屏
#define RIGHT 34		//向右划屏

#define ENLARGE 35         //放大按键
#define REDUCE 36         //缩小按键

//按键封装
extern int botton_out();
//登录按键封装
extern int botton_out_login();
//注册按键封装
extern int botton_out_apply();
//主界面按键封装
extern int botton_out_menu();
//mp3按键封装
extern int botton_out_mp3();
//mp4按键封装
extern int botton_out_mp4();
//相册按键封装
extern int botton_out_photo();

#endif