#include <myhead.h>
#include <botton.h>
#include <display.h>

int main(int argc,char **argv)
{
	//打开lcd驱动
	lcdfd=open("/dev/fb0",O_RDWR);
	if(lcdfd==-1)
	{
		perror("打开lcd失败!\n");
		return -1;
	}
	while(1)
	{
		//显示登录界面
		int ret = longin_show();
		if(ret == QUITL)
		{
			close(lcdfd);
			return 0;  //退出系统
		}
			
		menu();  //主界面操作
	}
}