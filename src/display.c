#include <myhead.h>
#include <getinfo.h>
#include <display.h>
#include <botton.h>
#include <player.h>

//显示黑色底板
int black_show()
{
	// //打开lcd驱动
	// int lcdfd=open("/dev/fb0",O_RDWR);
	// if(lcdfd==-1)
	// {
		// perror("打开lcd失败!\n");
		// return -1;
	// }
	
	int *mmap_bmp = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, lcdfd, 0);

	/* 映射内存 */
	int j,k;
	for(j=0; j<480; j++)
		for(k=0; k<800; k++)
			*(mmap_bmp+j*800+k) = 0x000000;

	/*关闭内存映射*/
	munmap(mmap_bmp, 800*480*4);
	
	// close(lcdfd);
	return 0;
}

//任意位置显示不大于800*480的任意大小的BMP图片
int show_any_bmp(int bmp_x,int bmp_y,int any_x,int any_y,char *bmp_name)
{
	int bmpfd = open(bmp_name,O_RDWR);//打开BMP图片
	if(bmpfd == -1)
	{
		perror("open err!");
		return -1;
	}
	// //打开lcd驱动
	// int lcdfd=open("/dev/fb0",O_RDWR);
	// if(lcdfd==-1)
	// {
		// perror("打开lcd失败!\n");
		// return -1;
	// }
	//定义一个数组，依据图片的大小
	char bmpbuf[bmp_x*bmp_y*3];
	int lcdbuf[bmp_x*bmp_y];
	int lastbuf[bmp_x*bmp_y];
	
	lseek(bmpfd,54,SEEK_SET);  //从头偏移图片属性信息54个字节
	//读取bmp图片的RGB数据
	int i,j;
	for(i=0; i<bmp_y; i++)  //按行读取
	{
		read(bmpfd, &bmpbuf[i*bmp_x*3], bmp_x*3);
		int tmp;
		for(tmp=bmp_x*3; tmp%4 != 0; tmp++);
		lseek(bmpfd,tmp-bmp_x*3,SEEK_CUR);
	}
	
	//3字节转换成4字节
	for(i=0; i<bmp_x*bmp_y; i++)
		lcdbuf[i] = bmpbuf[i*3+2]<<16|bmpbuf[i*3+1]<<8|bmpbuf[i*3+0];
	
	//图片按行颠倒
	for(i=0; i<bmp_x; i++)   //列
		for(j=0; j<bmp_y; j++)  //行
			lastbuf[(bmp_y-1-j)*bmp_x+i] = lcdbuf[i+j*bmp_x];

	int *mmap_bmp = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, lcdfd, 0);

	/* 映射内存 */
	int k;
	for(j=0; j<bmp_y; j++)
		for(k=0; k<bmp_x; k++)
			*(mmap_bmp+(j+any_y)*800+any_x+k) = lastbuf[j*bmp_x+k];

	/*关闭内存映射*/
	munmap(mmap_bmp, 800*480*4);
	//关闭
	close(bmpfd);

	return 0;
}

//任意位置显示缩小的图片  参数：图片路径名,缩小倍数，位置坐标
int reduce_bmp(char *bmp_name,int new_w,int new_h,int any_x,int any_y)
{
	int bmpfd = open(bmp_name,O_RDWR);//打开BMP图片
	if(bmpfd == -1)
	{
		perror("open err!");
		return -1;
	}
	// //打开lcd驱动
	// int lcdfd=open("/dev/fb0",O_RDWR);
	// if(lcdfd==-1)
	// {
		// perror("打开lcd失败!\n");
		// return -1;
	// }
	int old_w,old_h,wn,hn;
	get_bmp_wh(bmp_name,&old_w,&old_h);             //获取图片的宽高
	
	if(new_w<0||new_h<0)
		return -1;
	
	//计算缩小倍数
	wn = old_w/new_w;
	hn = old_h/new_h;
	
	char oldbuf[old_w*old_h*3];  //保存原照片数据
	
	int lcdbuf[old_w*old_h];    //保存转码数据
	int lastbuf[old_w*old_h];    //保存翻转后的数据
	
	int newbuf[new_w*new_h];  //保存缩放后的照片数据
	
	lseek(bmpfd,54,SEEK_SET);  //从头偏移图片属性信息54个字节
	
	int i,j,k,temp;
	for(i=0; i<old_h; i++)  //按行读取
	{
		read(bmpfd, &oldbuf[i*old_w*3], old_w*3);
		for(temp=old_w*3; temp%4 != 0; temp++);
		lseek(bmpfd,temp-old_w*3,SEEK_CUR);
	}
	
	//3字节转换成4字节
	for(i=0; i<old_w*old_h; i++)
		lcdbuf[i] = oldbuf[i*3+2]<<16|oldbuf[i*3+1]<<8|oldbuf[i*3+0];
	
	//图片按行颠倒
	for(i=0; i<old_w; i++)   //列
		for(j=0; j<old_h; j++)  //行
			lastbuf[(old_h-1-j)*old_w+i] = lcdbuf[i+j*old_w];

	//缩放
	for(i=0,k=0; i<new_h && k<old_h; i++,k=k+hn)
		for(j=0; j<new_w; j++)
			newbuf[i*new_w+j] = lastbuf[k*old_w+j*wn];

	int *mmap_bmp = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, lcdfd, 0);

	/* 映射内存 */
	for(i=0; i<new_h; i++)
		for(j=0; j<new_w; j++)
			*(mmap_bmp+(i+any_y)*800+any_x+j) = newbuf[i*new_w+j];

	/*关闭内存映射*/
	munmap(mmap_bmp, 800*480*4);
	//关闭
	close(bmpfd);
	// close(lcdfd);	
	return 0;
}

//居中位置任意大小的图片的特效
int show_bmp_super(int bmp_x,int bmp_y,int any_x,int any_y,char *bmp_name,int n)
{
	int bmpfd = open(bmp_name,O_RDWR);//打开BMP图片
	if(bmpfd == -1)
	{
		perror("open err!");
		return -1;
	}
	// //打开lcd驱动
	// int lcdfd=open("/dev/fb0",O_RDWR);
	// if(lcdfd==-1)
	// {
		// perror("打开lcd失败!\n");
		// return -1;
	// }
	//定义一个数组，依据图片的大小
	char bmpbuf[bmp_x*bmp_y*3];
	int lcdbuf[bmp_x*bmp_y];
	int lastbuf[bmp_x*bmp_y];
	
	lseek(bmpfd,54,SEEK_SET);  //从头偏移图片属性信息54个字节
	//读取bmp图片的RGB数据
	int i,j,k,l;   //计数变量
	for(i=0; i<bmp_y; i++)  //按行读取
	{
		read(bmpfd, &bmpbuf[i*bmp_x*3], bmp_x*3);
		int tmp;
		for(tmp=bmp_x*3; tmp%4 != 0; tmp++);
		lseek(bmpfd,tmp-bmp_x*3,SEEK_CUR);
	}
	
	//3字节转换成4字节
	for(i=0; i<bmp_x*bmp_y; i++)
		lcdbuf[i] = bmpbuf[i*3+2]<<16|bmpbuf[i*3+1]<<8|bmpbuf[i*3+0];
	
	//图片按行颠倒
	for(i=0; i<bmp_x; i++)   //列
		for(j=0; j<bmp_y; j++)  //行
			lastbuf[(bmp_y-1-j)*bmp_x+i] = lcdbuf[i+j*bmp_x];

	int *mmap_bmp = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, lcdfd, 0);

	/* 映射内存 */
	/*  从左往右百叶窗展开 */
	if(n==0)
	{
		for(j=0;j<40;j++)  //控制每一组显示多少列像素点
		{
			for(k=0; k<bmp_y; k++)   //控制每一列像素点
				for(i=0; i<bmp_x/40; i++)   //控制在哪几行同时显示这几列的像素点
					*(mmap_bmp+(k+any_y)*800+any_x+i*40+j) = lastbuf[k*bmp_x+i*40+j];
			usleep(10000);    //20ms
		}		
	}
	//从下往上展开
	if(n==1)
	{
		int tep_x=bmp_x;
		int tep_k=0;
		for(j=bmp_y-1; j>=0; j--)      //从下往上显示一个等腰三角形的像素点
		{
			for(k=tep_k; k<tep_x; k++)
			{
				*(mmap_bmp+(j+any_y)*800+k+any_x) = lastbuf[j*bmp_x+k];  
			}
			tep_k++;
			tep_x--;	
			usleep(2000);    //5ms
			if(tep_k==tep_x || tep_k+1==tep_x)   //判断是否显示了一个等腰三角形
			{
				i=j;
				l=j;
				while(1)               //同时显示剩余的像素点
				{
					if(i>=bmp_y&&l<=0)
						break;
					if(l!=0)
					{
						for(k=0; k<bmp_x; k++)
							*(mmap_bmp+(l+any_y)*800+any_x+k) = lastbuf[l*bmp_x+k];   //向上显示剩余的像素点
						l--;
					}
					if(i!=bmp_y)
					{
						for(k=0; k<tep_k; k++)
							*(mmap_bmp+(i+any_y)*800+any_x+k) = lastbuf[i*bmp_x+k];  //向下显示左边剩余的像素点
						for(k=tep_x; k<bmp_x; k++)
							*(mmap_bmp+(i+any_y)*800+any_x+k) = lastbuf[i*bmp_x+k]; //向下显示右边剩余的像素点
						i++;
					}
					if(tep_k!=0)
						tep_k--;
					if(tep_x!=bmp_x)
						tep_x++;
					usleep(5000);    //5ms
				}
				break;
			}
		}	
	}
	
		
	/* 从上往下的百叶窗展开 */
	if(n==2)
	{
		for(j=0;j<40;j++)  //控制每一组显示多少行像素点
		{
			for(k=0; k<bmp_x; k++)   //控制每一行像素点
				for(i=0; i<bmp_y/40; i++)   //控制在哪几行同时显示这几行的像素点
					*(mmap_bmp+(i*40+j+any_y)*800+any_x+k) = lastbuf[(i*40+j)*bmp_x+k];
			usleep(20000);    //10ms
		}
	}
	
	/* 从中间旋转展开 */
	if(n==3)
	{
		int x=25,y=15;       //旋转的宽度
		k=bmp_x/2,i=bmp_y/2,j=0;     //k,i控制在哪个位置先旋转，j控制同时显示的像素点
		int flag = 0;
		while(1)
		{
			if(flag==0)
			{
				if(i==0&&k==bmp_x-50)         //图片的所有像素点显示停止的条件
					break;
				if(i==bmp_y/2+y+30 || i==bmp_y)    //向下显示停止的条件
				{
					i=i-30;
					y=y+15;
					while(1)
					{
						if(k==bmp_x/2-x-25 || k==0)    //向左显示停止的条件
						{
							k=k+50;
							x=x+25;
							flag = 1;
							break;
						} 
						for(j=0;j<30;j++)    //同时显示26个像素点
							*(mmap_bmp+(i+any_y+j)*800+any_x+k) = lastbuf[(i+j)*bmp_x+k];  //向左显示像素点
						usleep(100);    //延时1ms
						k--;		
					}
				}
				for(j=0;j<50;j++)    //同时显示50个像素点
					*(mmap_bmp+(i+any_y)*800+any_x+k+j) = lastbuf[i*bmp_x+k+j];	  //向下显示像素点
				usleep(100);    //延时1ms	
				i++;
			}
			if(flag==1)
			{
				for(j=0;j<50;j++)       //同时显示50个像素点
					*(mmap_bmp+(i+any_y)*800+any_x+k-j) = lastbuf[i*bmp_x+k-j];   //向上显示像素点
				if(i==bmp_y/2-y || i==0)      //向上显示停止的条件
				{
					y=y+15;
					while(1)
					{
						if(k==bmp_x/2+x+50 || k==bmp_x)     //向右显示停止的条件
						{
							if(k!=bmp_x)
								k=k-50;
							else
								k=bmp_x-50;
							i++;
							x=x+25;
							flag = 0;
							break;
						}
						for(j=0;j<30;j++)     //同时显示30个像素点
							*(mmap_bmp+(i+j+any_y)*800+any_x+k) = lastbuf[(i+j)*bmp_x+k]; //向右显示像素点
						usleep(100);    //延时1ms
						k++;
					}
				}
				usleep(100);    //延时1ms
				i--;
			}	
		}		
	}			
	
	/*居中按圆展开*/
	if(n==4)
	{
		int r;    //半径
		for(r=1; r*r<(bmp_x/2)*(bmp_x/2)+(bmp_y/2)*(bmp_y/2); r++)	
			for(k=0; k<bmp_x; k++)
				for(j=0; j<bmp_y; j++)
					if(((k-bmp_x/2)*(k-bmp_x/2)+(j-bmp_y/2)*(j-bmp_y/2)) < r*r)
						*(mmap_bmp+(j+any_y)*800+any_x+k) = lastbuf[j*bmp_x+k];
	}
	
	/*关闭内存映射*/
	munmap(mmap_bmp, 800*480*4);
	//关闭
	close(bmpfd);
	// close(lcdfd);	
	return 0;
}

//拼接成1600*480的图片并从右往左展开显示
int splicing_bmp(int *p,int *q)
{
	// //打开lcd驱动
	// int lcdfd=open("/dev/fb0",O_RDWR);
	// if(lcdfd==-1)
	// {
		// perror("打开lcd失败!\n");
		// return -1;
	// }
	
	int buf[1600*480]={0};

	int i,j,k;
	/* 拼接成1600*480的数据  */
	for(j=0;j<480;j++)
		for(i=0;i<800;i++)
		{
			buf[j*1600+i]=p[j*800+i];
			buf[j*1600+i+800]=q[j*800+i];
		}
			
	int *mmap_bmp = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, lcdfd, 0);

	/* 映射内存 */
	/*  从右往左移动 */
	for(i=0;i<800;i+=10)
		for(j=0; j<480; j++)
			for(k=0; k<800; k++)
				*(mmap_bmp+j*800+k) = buf[j*1600+k+i];
	
	/*关闭内存映射*/
	munmap(mmap_bmp, 800*480*4);
	// close(lcdfd);	
	return 0;	
}

//显示缩略图
struct list_head *reduce_show(struct list_head *p,klist *bmphead,int *n)
{
	int any_x = 50,any_y = 50;
	int i=0;
	if(p->next!=&(bmphead->mylist))
		black_show(); //显示黑底
	while(1)
	{
		p=p->next;
		if(any_x>=800)
		{
			any_x = 50;
			any_y += 220;
		}
		if(any_y>=480||p==&(bmphead->mylist))
		{
			p=p->prev;
			*n=i;
			break;
		}
			
		klist *s = list_entry(p,klist,mylist);

		reduce_bmp(s->path,150,150,any_x,any_y);
		any_x += 250;
		i++;
	}
	
	printf("i:%d\n",i);
	return 	p;
}

//寻找点击到的图片名字
struct list_head *find_bmp(struct list_head *p,klist *bmphead,int n)
{
	if(n<0)
		return NULL;
	int i,flag=0;
	for(i=1; i<=n; i++)
	{
		flag=1;
		if(p == &(bmphead->mylist))
			p = p->prev;
		p=p->prev;	
	}
	if(flag == 0)
		return NULL;
	return p;
}

//寻找上一页要显示第一个缩略图片的名字
struct list_head *find_bmp_up(struct list_head *p,klist *bmphead,int n)
{
	int i=0;
	while(p->prev!=&(bmphead->mylist))
	{
		i++;
		p=p->prev;
		if(i==(6+n))
			return p;	
	}
	return NULL;
}

//点击缩略图中的某个图片的显示
struct list_head *someone_show(struct list_head *p,klist *head,int n,int m)
{
	struct list_head *q = p;
	p = find_bmp(p,head,n);     //寻找点击到的图片名字
	if(p)
	{
		operation_bmp(p,head);    //进入相册操作界面
		p = find_bmp(p,head,m);   //退出上下页操作之后保存点击之前的第一个缩略图的名字
		p = reduce_show(p,head,&n);   //显示点击图片之前的缩略图
		return p;
	}
	return q;
}

//相册界面
int pic_menu()
{
	//创建一个保存.bmp图片的内核链表
	klist *bmphead = init_list();
	if(bmphead==NULL)
	{
		printf("创建内核链表失败！\n");
		return -1;
	}
	open_dir_save_bmp("dog",bmphead);   //打开图片目录保存里面的图片路径名
	
	int w,h;
	struct list_head *p = &(bmphead->mylist);
	struct list_head *q;
	int n;   //确定缩略图显示了多少个
	p = reduce_show(p,bmphead,&n);     //显示缩略图
	while(1)
	{
		int act = act_screen();
		switch(act)
		{
			case 1:
				q = p;
				p = find_bmp(p,bmphead,n);		//寻找点击到的图片名字
				if(p)
				{
					operation_bmp(p,bmphead);     //进入相册操作界面
					//p = find_bmp(p,bmphead,0);    //退出上下页操作之后保存点击之前的第一个缩略图的名字
					p = reduce_show(p,bmphead,&n);   //显示点击图片之前的缩略图
				}
				p = q;
				break;
			case 2:
				p = someone_show(p,bmphead,n-1,1);
				break;
			case 3:
				p = someone_show(p,bmphead,n-2,2);
				break;
			case 4:
				p = someone_show(p,bmphead,n-3,3);
				break;
			case 5:
				p = someone_show(p,bmphead,n-4,4);
				break;
			case 6:
				p = someone_show(p,bmphead,n-5,5);
				break;
			case UP:        //往上翻页缩略图
				p = find_bmp_up(p,bmphead,n);
				if(p!=NULL)
					p = reduce_show(p,bmphead,&n);
				else
					p = reduce_show(&(bmphead->mylist),bmphead,&n);
				break;
			case RIGHT:
				free_klist(bmphead);  //释放链表的堆空间
				return 0;
			case DOWN:      //往下翻页缩略图
				p = reduce_show(p,bmphead,&n);
				break;
			case LEFT:
				free_klist(bmphead);  //释放链表的堆空间
				return 0;
		}
	}
}

//显示相册操作按钮
void photo_show(int w,int h,int x,int y,char *buf)
{
	show_any_bmp(w,h,x,y,buf);
	show_any_bmp(50,50,740,10,"返回.bmp");
	show_any_bmp(100,100,10,370,"上一页.bmp");
	show_any_bmp(100,100,690,370,"下一页.bmp");
	show_any_bmp(50,50,50,240,"reduce.bmp");
	//show_any_bmp(50,50,700,240,"enlarge.bmp");
}

//匹配账号
int find_name(lgin *p,char *name)
{
	for(p=p;*(p->name) != '\0'; p++)
	{
		if(!strcmp(p->name,name))
			return 0;
	}
	return -1;
}
//匹配密码
int find_pass(lgin *p,char *pass)
{
	for(p=p;*(p->password) != '\0'; p++)
	{
		if(!strcmp(p->password,pass))
			return 0;
	}
	return -1;
}

//注册登录信息
int apply_info()
{
	lgin user;    //定义一个登录信息结构体
	memset(user.name, 0, sizeof(user.name));    //清空
	memset(user.password,0,sizeof(user.password));    //清空
	while(1)
	{
		show_any_bmp(400,250,200,100,"注册.bmp"); //显示注册界面
		int botton = botton_out_apply();
		switch(botton)
		{
			case APPLYNAME:
				printf("请注册新用户名：\n");
				scanf("%s",user.name);
				while(getchar()!='\n');
				break;
			case APPLYPASS:
				printf("请输入密码：\n");
				scanf("%s",user.password);
				while(getchar()!='\n');
				// printf("请再次输入密码：\n");
				// scanf("%s",user.surepass);
				break;
			case APPLY:
				save_for_info(user);
				show_any_bmp(200,86,300,197,"注册成功.bmp"); //显示登录成功
				return 0;
			case CANCEL:
				return -1;
		}	
	}
}

//显示登录界面
int longin_show()
{
	lgin users[20] = {0};    //定义一个登录信息结构体数组
	lgin user;
	lgin *p;
	bzero(user.name,sizeof(user.name));
	bzero(user.password,sizeof(user.password));
	int flag = 0,mark = 0;
	int ret1,ret2;
	while(1)
	{
		show_any_bmp(800,480,0,0,"jiemian.bmp"); //显示登录界面
		int botton = botton_out_login();       //获取按键操作
		switch(botton)
		{
			case LOGINNAME:  //登录用户名
				flag = 0;
				printf("请输入用户名：\n");
				scanf("%s",user.name);
				while(getchar()!='\n');
				break;
			case LOGINPASS:   //登录密码
				flag = 0;
				printf("请输入密码：\n");
				scanf("%s",user.password);
				while(getchar()!='\n');
				break;
			case LOGINAPPLY:  //注册
				flag = 0;
				mark = 0;
				printf("注册\n");
				apply_info();
				break;
			case MMENU:  //登录
				p = read_info(users,20);
				printf("登录\n");
				flag = 1;
				break;
			case QUITL:   //退出系统
				printf("退出\n");
				return QUITL;
		}
		if(flag == 1)
		{
			ret1 = find_name(p,user.name);    //匹配账号
			ret2 = find_pass(p,user.password);   //匹配密码
			if(ret1 == 0 && ret2 == 0)     //账号密码正确
			{
				show_any_bmp(200,86,300,197,"登录成功.bmp"); //显示登录成功
				usleep(500000);
				return MMENU;
			}
				
			else
			{
				printf("账号或密码错误！\n");
				show_any_bmp(299,85,250,197,"登录失败.bmp"); //显示登录失败
				usleep(500000);
				mark++;
			}		
		}
		if(mark == 3)
			return QUITL;
	}
}

//显示主界面
int menu()
{
	while(1)
	{
		show_any_bmp(800,480,0,0,"menu.bmp"); //显示主操作界面
		int botton = botton_out_menu();       //获取按键操作
		switch(botton)
		{
			case NUSIC:    //音频
				show_any_bmp(800,480,0,0,"player.bmp"); //显示mp3界面
				loop_playback();
				break;
			case MOVIE:   //视频
				playback_movie();
				break;
			case POTHO:   //相册
				pic_menu();
				//up_down_bmp();
				break;
			case GAME2048:    //2048游戏
				opera_2048();
				break;
			case QUITM:    //注销登录
				return QUITL;
		}
	}
}


