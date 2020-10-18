#include <myhead.h>
#include <getinfo.h>
#include <botton.h>

//登录按键封装
int botton_out_login()
{
	int touch_x,touch_y;
	get_screen_act_start(&touch_x,&touch_y);    //获取触摸坐标
	if(touch_x>310 && touch_x<670 && touch_y>160 && touch_y<205)   //用户名
		return LOGINNAME;
	if(touch_x>278 && touch_x<668 && touch_y>210 && touch_y<269)  //密码
		return LOGINPASS;
	if(touch_x>145 && touch_x<275 && touch_y>312 && touch_y<370)  //登录
		return MMENU;
	if(touch_x>538 && touch_x<680 && touch_y>312 && touch_y<370)   //注册
		return LOGINAPPLY;
	if(touch_x>650 && touch_x<768 && touch_y>398 && touch_y<455)   //退出系统
		return QUITL;
	
}
//注册按键封装
int botton_out_apply()
{
	int touch_x,touch_y;
	get_screen_act_start(&touch_x,&touch_y);    //获取触摸坐标
	if(touch_x>332 && touch_x<504 && touch_y>169 && touch_y<205)   //注册账号
		return APPLYNAME;
	if(touch_x>332 && touch_x<504 && touch_y>223 && touch_y<263)   //注册密码
		return APPLYPASS;
	if(touch_x>263 && touch_x<330 && touch_y>293 && touch_y<332)   //开始注册
		return APPLY;
	if(touch_x>513 && touch_x<580 && touch_y>293 && touch_y<330)   //取消注册
		return CANCEL;
}

//主界面按键封装
int botton_out_menu()
{
	int touch_x,touch_y;
	get_screen_act_start(&touch_x,&touch_y);    //获取触摸坐标
	if(touch_x>465&&touch_x<565 && touch_y>340&&touch_y<440)  //音频
		return NUSIC;
	if(touch_x>265&&touch_x<365 && touch_y>340&&touch_y<440)  //视频
		return MOVIE;
	if(touch_x>70&&touch_x<170 && touch_y>340&&touch_y<440)  //相册
		return POTHO;
	if(touch_x>640&&touch_x<740 && touch_y>340&&touch_y<440)   //2048
		return GAME2048;
	if(touch_x>738 && touch_x<788 && touch_y>10 && touch_y<60)   //退出系统
			return QUITM;
}
//mp3按键封装
int botton_out_mp3()
{
	int touch_x,touch_y;
	get_screen_act_start(&touch_x,&touch_y);    //获取触摸坐标
	if(touch_x>720 && touch_x<770 && touch_y>18 && touch_y<68)  //退出mp3
		return QUITMP3;
	if(touch_x>90 && touch_x<190 && touch_y>348 && touch_y<448)   //上一曲mp3
		return PREVMP3;
	if(touch_x>250 && touch_x<350 && touch_y>348 && touch_y<448)   //播放暂停mp3
		return PALYMP3;
	if(touch_x>420 && touch_x<520 && touch_y>348 && touch_y<448)   //下一曲mp3
		return NEXTMP3;
	if(touch_x>620 && touch_x<720 && touch_y>348 && touch_y<448)   //停止播放mp3
		return KILLMP3;
}

//mp4按键封装
int botton_out_mp4()
{
	int touch_x,touch_y;
	get_screen_act_start(&touch_x,&touch_y);    //获取触摸坐标
	if(touch_x>738 && touch_x<788 && touch_y>415 && touch_y<465)  //退出、停止播放mp4 
		return STOPMP4;
	if(touch_x>738 && touch_x<788 && touch_y>10 && touch_y<60)  //退出
		return QUITMP4;
	if(touch_x>340 && touch_x<440 && touch_y>360 && touch_y<460)  //播放mp4
		return PALYMP4;
	if(touch_x>30 && touch_x<80 && touch_y>415 && touch_y<465)  //上一曲mp4
		return PREVMP4;
	if(touch_x>188 && touch_x<238 && touch_y>415 && touch_y<465) //下一曲mp4
		return NEXTMP4;
	if(touch_x>110 && touch_x<160 && touch_y>415 && touch_y<465)  //播放暂停mp4
		return PSMP4;
}
//相册按键封装
int botton_out_photo()
{
	int start_x=0,start_y=0,end_x=0,end_y=0;
	get_screen_act_start(&start_x,&start_y);       //获取划屏动作
	get_screen_act_end(&end_x,&end_y);
	if(end_x==0 && end_y==0)
	{
		if(start_x>740 && start_x<790 && start_y>10 && start_y<60)   //退出相册按键
			return QUITPT;
		if(start_x>10 && start_x<110 && start_y>370 && start_y<470)   //上一张按键
			return PREVPT;
		if(start_x>690 && start_x<790 && start_y>370 && start_y<470)   //下一张按键
			return NEXTPT;	
		if(start_x>50 && start_x<100 && start_y>240 && start_y<290)   //缩小按键
			return REDUCE;	
		// if(start_x>700 && start_x<750 && start_y>240 && start_y<290)    //放大按键
			// return ENLARGE;
	}
	else
	{
		if(end_y-start_y>0 && end_y-start_y > abs(end_x-start_x))   //对应x，y坐标的差值绝对值比较
		{
			printf("你向下划屏了！\n");
			return DOWN;
		}								           
		else if(end_y-start_y<0 && (abs(end_y-start_y) > abs(end_x-start_x)))   //对应x，y坐标的差值绝对值比较
		{
			printf("你向上划屏了！\n");
			return UP;
		}	
		else if(end_x-start_x<0 && (abs(end_y-start_y)<abs(end_x-start_x)))  //对应x，y坐标的差值绝对值比较
		{
			printf("你向左划屏了！\n");
			return LEFT;
		}	
		else if(end_x-start_x>0 && end_x-start_x > abs(end_y-start_y))   //对应x，y坐标的差值绝对值比较
		{
			printf("你向右划屏了！\n");
			return RIGHT;
		}
	}	
}

//划屏or触摸
int act_screen()
{
	int start_x=0,start_y=0,end_x=0,end_y=0;
	get_screen_act_start(&start_x,&start_y);       //获取划屏动作
	get_screen_act_end(&end_x,&end_y);
	if(end_x==0 && end_y==0)
	{
		if(start_x>50 && start_x<200 && start_y>50 && start_y<200)   //显示第一张图
			return 1;
		if(start_x>300 && start_x<450 && start_y>50 && start_y<200)   //显示第二张图
			return 2;
		if(start_x>550 && start_x<700 && start_y>50 && start_y<200)   //显示第三张图
			return 3;
		if(start_x>50 && start_x<200 && start_y>270 && start_y<430)   //显示第四张图
			return 4;
		if(start_x>300 && start_x<450 && start_y>270 && start_y<430)   //显示第五图
			return 5;
		if(start_x>550 && start_x<700 && start_y>270 && start_y<430)   //显示第六张图
			return 6;		
	}
	else
	{
		if(end_y-start_y>0 && end_y-start_y > abs(end_x-start_x))   //对应x，y坐标的差值绝对值比较
		{
			printf("你向下划屏了！\n");
			return DOWN;
		}								           
		else if(end_y-start_y<0 && (abs(end_y-start_y) > abs(end_x-start_x)))   //对应x，y坐标的差值绝对值比较
		{
			printf("你向上划屏了！\n");
			return UP;
		}	
		else if(end_x-start_x<0 && (abs(end_y-start_y)<abs(end_x-start_x)))  //对应x，y坐标的差值绝对值比较
		{
			printf("你向左划屏了！\n");
			return LEFT;
		}	
		else if(end_x-start_x>0 && end_x-start_x > abs(end_y-start_y))   //对应x，y坐标的差值绝对值比较
		{
			printf("你向右划屏了！\n");
			return RIGHT;
		}
	}	
}

//设置2048的划屏和按键动作
int act_2048(int flag)
{
	int start_x=0,start_y=0,end_x=0,end_y=0;
	get_screen_act_start(&start_x,&start_y);       //获取划屏动作
	get_screen_act_end(&end_x,&end_y);
	if(end_x==0 && end_y==0)
	{
		// if(start_x>50 && start_x<200 && start_y>50 && start_y<200)   //开始游戏
			// return 1;
		if(start_x>530 && start_x<630 && start_y>45 && start_y<90)   //新游戏
			return 1;
		if(start_x>550 && start_x<630 && start_y>400 && start_y<450)   //退出
			return 2;
	}
	else
	{
		if(flag==0)
		{
			if(end_y-start_y > abs(end_x-start_x))   //对应x，y坐标的差值绝对值比较
			{
				printf("你向下划屏了！\n");
				return DOWN;
			}		
			else if(end_y-start_y<0 && (abs(end_y-start_y)>abs(end_x-start_x)))   //对应x，y坐标的差值绝对值比较
			{
				printf("你向上划屏了！\n");
				return UP;
			}		
			else if(end_x-start_x<0 && (abs(end_y-start_y)<abs(end_x-start_x)))  //对应x，y坐标的差值绝对值比较
			{
				printf("你向左划屏了！\n");
				return LEFT;
			}	
			else if(end_x-start_x > abs(end_y-start_y))   //对应x，y坐标的差值绝对值比较
			{
				printf("你向右划屏了！\n");
				return RIGHT;
			}	
		}
		
	}
}


