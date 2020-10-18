#include <myhead.h>
#include <display.h>
#include <botton.h>

//循环播放音乐
int loop_playback()
{
	//创建一个保存.mp3的内核链表
	klist *mp3head = init_list();
	if(mp3head==NULL)
	{
		printf("创建内核链表失败！\n");
		return -1;
	}
	open_dir_save_mp3("music",mp3head);  //打开音频目录保存里面的音频路径名
	int touch_x,touch_y;
	int flag = 0;
	char mp3path[PATHSIZE];
	struct list_head *q = &(mp3head->mylist);
	q = q->next;
	while(1)
	{
		bzero(mp3path,PATHSIZE);
		klist *n = list_entry(q,klist,mylist);
		int botton = botton_out_mp3();       //获取按键操作
		switch(botton)
		{
			case QUITMP3:   //退出mp3界面
				if(flag!=0)
					system("killall  -KILL  madplay &");	     //停止播放
				free_klist(mp3head);  //释放链表的堆空间
				return 0;
			case PREVMP3:     //上一首
				q = q->prev;
				if(q == &(mp3head->mylist))
					q = q->prev;
				n = list_entry(q,klist,mylist);
				system("killall  -KILL  madplay");	     //停止播放
				sprintf(mp3path,"madplay %s &",n->path);  //拼接播放命令
				printf("mp3path:%s\n",mp3path);
				system(mp3path);
				show_any_bmp(100,100,250,348,"播放.bmp");
				if(flag == 0|| flag == 2)
					flag = 1;
				break;
			case NEXTMP3:    //下一首
				q = q->next;
				if(q == &(mp3head->mylist))
					q = q->next;
				n = list_entry(q,klist,mylist);
				system("killall  -KILL  madplay");	     //停止播放
				sprintf(mp3path,"madplay %s &",n->path);  //拼接播放命令
				printf("mp3path:%s\n",mp3path);
				system(mp3path);
				show_any_bmp(100,100,250,348,"播放.bmp");
				if(flag == 0|| flag == 2)
					flag = 1;
				break;
			case PALYMP3:    //播放暂停
				if(flag == 0)
				{
					sprintf(mp3path,"madplay %s &",n->path);  //拼接播放命令
					printf("mp3path:%s\n",mp3path);
					system(mp3path);
					show_any_bmp(100,100,250,348,"播放.bmp");
				}
				if(flag == 1)
				{
					system("killall  -STOP  madplay &");	 //暂停播放
					show_any_bmp(800,480,0,0,"player.bmp");
				}			
				if(flag == 2)
				{
					system("killall  -CONT  madplay &");  //继续播放
					show_any_bmp(100,100,250,348,"播放.bmp");
					flag = 0;
				}
				flag++;
				break;
			case KILLMP3:           //停止播放
				if(flag!=0)
				{
					system("killall  -KILL  madplay &");	     //停止播放
					show_any_bmp(800,480,0,0,"player.bmp");
				}
				flag = 0;
				break;
		}
	}
}

//播放视频
int playback_movie()
{
	//创建一个保存视频的内核链表
	klist *moviehead = init_list();
	if(moviehead==NULL)
	{
		printf("创建内核链表失败！\n");
		return -1;
	}
	open_dir_save_movie("movie",moviehead); //打开视频目录保存里面的视频路径名
	int touch_x,touch_y;
	int flag = 0;
	char moviepath[PATHSIZE];
	struct list_head *q = &(moviehead->mylist);
	q = q->next;
	while(1)
	{
		show_any_bmp(800,480,0,0,"movie.bmp"); //显示视频界面
		bzero(moviepath,PATHSIZE);
		klist *n = list_entry(q,klist,mylist);
		n = list_entry(q,klist,mylist);
		int botton = botton_out_mp4();       //获取按键操作
		switch(botton)
		{
			case QUITMP4:         //退出mp4
				free_klist(moviehead);  //释放链表的堆空间
				return 0;
			case PALYMP4:         //播放mp4
				black_show(); //显示黑底
				show_any_bmp(50,50,110,415,"stop.bmp");
				while(1)
				{
					show_any_bmp(50,50,738,415,"返回.bmp");
					show_any_bmp(50,50,30,415,"上一曲.bmp");
					show_any_bmp(50,50,188,415,"下一曲.bmp");
					botton = botton_out_mp4();       //获取按键操作
					switch(botton)
					{
						case STOPMP4:    //停止播 返回
							if(flag!=0)
								system("killall  -KILL  mplayer");	     //停止播放
							flag = -1;
							break;
						case PREVMP4:    //上一曲
							black_show(); //显示黑底
							q = q->prev;
							if(q == &(moviehead->mylist))
								q = q->prev;
							n = list_entry(q,klist,mylist);
							system("killall  -KILL  mplayer");	     //停止播放
							sprintf(moviepath,"mplayer %s -zoom -x 600  -y 360 &",n->path);  //拼接播放命令
							printf("moviepath:%s\n",moviepath);
							system(moviepath);
							show_any_bmp(50,50,110,415,"play.bmp");
							if(flag == 0|| flag == 2)
								flag = 1;
							break;
						case NEXTMP4:    //下一曲
							black_show(); //显示黑底
							q = q->next;
							if(q == &(moviehead->mylist))
								q = q->next;
							n = list_entry(q,klist,mylist);
							system("killall  -KILL  mplayer");	     //停止播放
							sprintf(moviepath,"mplayer %s -zoom -x 400  -y 240 &",n->path);  //拼接播放命令
							printf("moviepath:%s\n",moviepath);
							system(moviepath);
							show_any_bmp(50,50,110,415,"play.bmp");
							if(flag == 0|| flag == 2)
								flag = 1;
							break;
						case PSMP4:   //播放暂停
							if(flag == 0)
							{
								black_show(); //显示黑底
								sprintf(moviepath,"mplayer %s -zoom -x 800  -y 400 &",n->path);  //拼接播放命令
								printf("moviepath:%s\n",moviepath);
								system(moviepath);
								show_any_bmp(50,50,110,415,"play.bmp");
							}
							if(flag == 1)
							{
								system("killall  -STOP  mplayer &");	 //暂停播放
								show_any_bmp(50,50,110,415,"stop.bmp");  
							}
								
							if(flag == 2)
							{
								system("killall  -CONT  mplayer &");  //继续播放
								show_any_bmp(50,50,110,415,"play.bmp");
								flag = 0;
							}	
							flag++;
							break;
					}
					if(flag == -1)
					{
						flag = 0;
						break;
					}		
				}
				break;
		}	
	}
}


