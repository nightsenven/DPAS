#include <myhead.h>
#include <getinfo.h>


//获取bmp图片的宽和高
int get_bmp_wh(char *bmp_name,int *w,int *h)
{
	
	int bmpfd = open(bmp_name,O_RDWR);//打开BMP图片
	if(bmpfd == -1)
	{
		perror("open err!");
		return -1;
	}
	//bmp图片前54个字节的第18个字节之后的8个字节分别保存着图片的宽和高
	lseek(bmpfd,18,SEEK_SET);   
	read(bmpfd,w,4);  //获取bmp图片的宽
	read(bmpfd,h,4);  //获取bmp图片的高
	close(bmpfd);
	return 0;
}

//根据图片的宽高获取居中显示的位置
int sure_bmp_place(int *w,int *h,int *start_x,int *start_y,char *bmppath)
{
	int centre_x,centre_y;
	get_bmp_wh(bmppath,w,h);     //获取图片的宽高
	//求出显示屏的中心坐标
	centre_x = 800/2;
	centre_y = 480/2;
	//获取图片的起始位置
	*start_x = centre_x-*w/2;
	*start_y = centre_y-*h/2;
	if(*start_x<=0)
		*start_x = 0;
	if(*start_y<=0)
		*start_y = 0;
	return 0;
}

//获取一张800*480图片的数据
int get_bmp_info(char *bmp_name,int *savebuf,int bmp_w,int bmp_h)
{
	int bmpfd = open(bmp_name,O_RDWR);//打开BMP图片
	if(bmpfd == -1)
	{
		perror("open err!");
		return -1;
	}
	/*求出居中显示的起始坐标*/
	int start_x = 800/2-bmp_w/2;
	int start_y = 480/2-bmp_h/2;

	lseek(bmpfd,54,SEEK_SET);  //从头偏移图片属性信息54个字节
	
	char buf[bmp_w*bmp_h*3];
	int tempbuf[bmp_w*bmp_h];
	int lastbuf[bmp_w*bmp_h];
	bzero(buf,sizeof(buf));
	bzero(tempbuf,sizeof(tempbuf));
	bzero(lastbuf,sizeof(lastbuf));
	bzero(savebuf,sizeof(savebuf));
	
	int i,j;
	int tmp;
	for(i=0; i<bmp_h; i++)  //按行读取
	{
		read(bmpfd, &buf[i*bmp_w*3], bmp_w*3);
		for(tmp=bmp_w*3; tmp%4 != 0; tmp++);
		lseek(bmpfd,tmp-bmp_w*3,SEEK_CUR);
	}
	//3字节转换成4字节
	for(i=0; i<bmp_w*bmp_h; i++)
		tempbuf[i] = buf[i*3+2]<<16|buf[i*3+1]<<8|buf[i*3+0];
	//图片按行颠倒
	for(i=0; i<bmp_w; i++)   //列
		for(j=0; j<bmp_h; j++)  //行
			lastbuf[(bmp_h-1-j)*bmp_w+i] = tempbuf[i+j*bmp_w];
			
	for(j=0; j<bmp_h; j++)
		for(i=0; i<bmp_w; i++)
			savebuf[(j+start_y)*800+start_x+i] = lastbuf[i+j*bmp_w];
			
	close(bmpfd);
	return 0;
}

//获取划屏的起始值
int get_screen_act_start(int *start_x,int *start_y)
{
	//定义输入子系统模型有关的结构体变量
	struct input_event event;	
	//打开触摸屏的驱动
	int tsfd=open("/dev/input/event0",O_RDWR);
	if(tsfd==-1)
	{
		perror("打开触摸屏失败!\n");
		return -1;
	}
	
	int flag = 0;
	while(1)
	{
		//读取触摸屏的坐标
		read(tsfd,&event,sizeof(event));
		//判断一下事件类型
		if(event.type==EV_KEY) //说明触发的是按键事件
			if(event.code==BTN_TOUCH && event.value>0) //手按下去了
				printf("手按下去了！\n");
		if(event.type==EV_ABS && event.code==ABS_X)	
		{
			*start_x = event.value*800/1024;
			flag++;
		}	
		if(event.type==EV_ABS && event.code==ABS_Y)	
		{
			*start_y = event.value*480/600;
			flag++;
		}
		
		if(flag == 2)
			break;				
	}
	//关闭触摸屏
	close(tsfd);
	return 0;
}

//获取划屏的结束值
int get_screen_act_end(int *end_x,int *end_y)
{
	//定义输入子系统模型有关的结构体变量
	struct input_event event;	
	//打开触摸屏的驱动
	int tsfd=open("/dev/input/event0",O_RDWR);
	if(tsfd==-1)
	{
		perror("打开触摸屏失败!\n");
		return -1;
	}
	
	int flag = 0;
	while(1)
	{
		//读取触摸屏的坐标
		read(tsfd,&event,sizeof(event));
		if(event.type==EV_KEY) //说明触发的是按键事件
			if(event.code==BTN_TOUCH && event.value == 0) //手松开了
			{
				usleep(200000);            //延迟0.2s再测一遍
				printf("手松开了！\n");
				flag = 1;
			}
		if(flag == 1)	
			break;
		if(event.type==EV_ABS && event.code==ABS_X)					
			*end_x = event.value*800/1024;
		if(event.type==EV_ABS && event.code==ABS_Y)	
			*end_y = event.value*480/600;
	}
	//关闭触摸屏
	close(tsfd);
	return 0;
}

//从文件读取用户信息
lgin *read_info(lgin user[],int n)
{
	int fd = open("info/login_info.txt",O_RDWR);
	if(fd == -1)
	{
		perror("open err!");
		return NULL;
	}
	int i;
	for(i=0; i<n; i++)
	{
		int ret = read(fd,&user[i],sizeof(lgin));
		if(ret == 0)
			break;
		printf("user->name:%s,user->password:%s\n",user[i].name,user[i].password);
	}
	
	close(fd);
	return user;
}

//保存登录信息到文件中
int save_for_info(lgin user)
{
	int fd = open("info/login_info.txt",O_RDWR|O_APPEND);
	if(fd == -1)
	{
		perror("open err!");
		return -1;
	}

	write(fd,&user,sizeof(user));
	//write(fd,user.password,sizeof(user.password));
	close(fd);
	return 0;
}




