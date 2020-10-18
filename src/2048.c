#include <myhead.h>
#include <botton.h>
#include <display.h>
#include <game.h>

int flag=0;

//获取随机数用来随机显示图片特效
int get_random()
{
	srand((unsigned)time(NULL));    //固定随机数序列
	
	int ret = rand()%5;      //随机获取0-4的数字
	return ret;
}
//获取2或者4
int get_2or4()
{
	int buf[2]={2,4};
	srand((unsigned)time(NULL));    //固定随机数序列
	int ret=rand()%2;   //随机获取0-1的数字
	return buf[ret];
}

//获取某一个空位置范围的随机位置
int get_random_place(int *ret1,int *ret2,int x1,int y1,int x2,int y2)
{
	
	srand((unsigned)time(NULL));    //固定随机数序列
	*ret1 = rand()%(x2-x1+1)+x1;   //随机获取x1-x2的数字
	*ret2 = rand()%(y2-y1+1)+y1;   //随机获取y1-y2的数字
	
	return 0;
}

//显示所有格子的信息对应的图片
int show_array(int arr[4][4])
{ 	
	int x,y;            //遍历数组时需要用到的循环变量
	char bmp_path[30];     //格子的值所代表的图片名字
	for(x=0;x<4;x++)  //列的个数
	{
		for(y=0;y<4;y++)    //行的个数
		{
			if(arr[x][y]!=0)
			{
				//拼接文件路径
				sprintf(bmp_path,"2048/%d.bmp",arr[x][y]);
				show_any_bmp(100,100,13+117*y,13+117*x,bmp_path);
			}	
		}
	}
	return 0;
}

//判断是否有2048  有返回0，无返回-1
int sure_the_2048(int arr[4][4])
{
	int i,j;
	for(i=0;i<4;i++)   //行
		for(j=0;j<4;j++)   //列
			if(arr[i][j]==2048)
				return 0;
	return -1;
}
//判断是否有空位置  有返回0，无返回-1
int sure_the_place(int arr[4][4])
{
	int i,j;
	for(i=0;i<4;i++)   //行
		for(j=0;j<4;j++)   //列
			if(arr[i][j]==0)
				return 0;
	return -1;
}

//随机获取位置并赋值2或者4   赋值成功返回0；
int for_arr_place(int arr[4][4],int *x,int *y)
{
	int i,j,k=-1,l=-1,n=4,m=4;
	for(i=0;i<4;i++)   //行
	{	
		for(j=0;j<4;j++)   //列
			if(arr[i][j]==0)
			{
				k=i;
				break;
			}
		if(k!=-1)
			break;	
	}
	if(k==-1)            //位置满了
		return -1;
	for(j=0;j<4;j++)    //列
	{	
		for(i=0;i<4;i++)  //行
			if(arr[i][j]==0)
			{
				l=j;
				break;
			}
		if(l!=-1)
				break;			
	}
			
	for(i=3;i>=0;i--)   //行
	{
		for(j=0;j<4;j++)   //列
			if(arr[i][j]==0)
			{
				n=i;
				break;
			}
		if(n!=4)
			break;
	}
	for(j=3;j>=0;j--)    //列
	{	
		for(i=0;i<4;i++)  //行
			if(arr[i][j]==0)
			{
				m=j;
				break;
			}
		if(m!=4)
			break;			
	}
	printf("k:%d,l:%d,n:%d,m:%d\n",k,l,n,m);    //用于提高获取随机值的效率
	while(1)
	{
		get_random_place(x,y,k,l,n,m);         //获取位置
		if(arr[*x][*y]==0)              //判断这个位置是否是空的  反则继续获取位置
		{
			arr[*x][*y]=get_2or4();  //赋值2或者4
			return 0;
		}
	}
}

//交换数据
void swap(int *data,int *src)
{
	*data=*data+*src;
	*src=*data-*src;
	*data=*data-*src;
}

//移动数组的数据，n表示移动的方向
int move(int arr[4][4],int n)
{
	int x,y,i;
	int moveflag=0;         //判断数组的数据是否移动过
	/*
		按列进行数据的计算
	*/
	if(n==DOWN)                 //向下移动
	{
		for(y=0;y<4;y++)    //控制每一列的数据                                        
			for(x=3;x>=0;x--)    //从最下面第一个开始遍历
				if(arr[x][y]!=0)  //找到第一个非空位置
					for(i=x-1;i>=0;i--)   //在此基础上往上遍历
						if(arr[i][y]!=0)   //找到第一个非空的位置（相当于是相邻的数据）
						{
							if(arr[x][y]==arr[i][y])
							{
								moveflag=1;
								arr[x][y] = arr[x][y]*2;
								arr[i][y] = 0;
								x=x-1;
							}
							break;
						}									
		for(y=0;y<4;y++)    //控制每一列的数据交换
			for(x=3;x>=0;x--)    //从最下面第一个开始遍历
				if(arr[x][y]==0)   //找到第一个空位置
					for(i=x-1;i>=0;i--)   //在此基础上往上遍历
						if(arr[i][y]!=0)   //找到第一个不是空的位置
						{
							moveflag=1;
							swap(&arr[x][y],&arr[i][y]);   //交换
							break;
						}
	}							
	if(n==UP)              //向上移动
	{
		for(y=0;y<4;y++)    //控制每一列的数据                                        
			for(x=0;x<4;x++)    //从最下面第一个开始遍历
				if(arr[x][y]!=0)  //找到第一个非空位置
					for(i=x+1;i<4;i++)   //在此基础上往上遍历
						if(arr[i][y]!=0)   //找到第一个非空的位置（相当于是相邻的数据）
						{
							if(arr[x][y]==arr[i][y])
							{
								moveflag=1;
								arr[x][y] = arr[x][y]*2;
								arr[i][y] = 0;
								x++;
							}
							break;
						}		
		for(y=0;y<4;y++)    //控制每一列的数据交换					
			for(x=0;x<4;x++)    //从最上面第一个开始遍历
				if(arr[x][y]==0)   //找到第一个空位置
					for(i=x+1;i<4;i++)   //在此基础上往上遍历
						if(arr[i][y]!=0)   //找到第一个不是空的位置
						{
							moveflag=1;
							swap(&arr[x][y],&arr[i][y]);   //交换
							break;
						}	
	}

		/*
			按行进行数据的计算
		*/
	if(n==RIGHT)           //向右移动
	{		
		for(x=0;x<4;x++)    //控制每一行的数据                                        
			for(y=3;y>=0;y--)    //从最右边第一个位置开始遍历
				if(arr[x][y]!=0)  //找到第一个非空位置
					for(i=y-1;i>=0;i--)   //在此基础上往左遍历
						if(arr[x][i]!=0)   //找到第一个非空的位置（相当于是相邻的数据）
						{
							if(arr[x][y]==arr[x][i])
							{
								moveflag=1;
								arr[x][y] = arr[x][y]*2;
								arr[x][i] = 0;
								y--;
							}
							break;
						}
		for(x=0;x<4;x++)    //控制每一行的数据交换                 
			for(y=3;y>=0;y--)    //从最右边第一个开始遍历
				if(arr[x][y]==0)   //找到第一个空位置
					for(i=y-1;i>=0;i--)   //在此基础上往上遍历
						if(arr[x][i]!=0)   //找到第一个不是空的位置
						{	
							moveflag=1;
							moveflag=1;						
							swap(&arr[x][y],&arr[x][i]);   //交换
							break;
						}	
	}
	if(n==LEFT)              //向左移动
	{
		for(x=0;x<4;x++)    //控制每一行的数据                                        
			for(y=0;y<4;y++)    //从最左边第一个位置开始遍历
				if(arr[x][y]!=0)  //找到第一个非空位置
					for(i=y+1;i<4;i++)   //在此基础上往左遍历
						if(arr[x][i]!=0)   //找到第一个非空的位置（相当于是相邻的数据）
						{
							if(arr[x][y]==arr[x][i])
							{
								moveflag=1;
								arr[x][y] = arr[x][y]*2;
								arr[x][i] = 0;
								y++;
							}
							break;
						}
		for(x=0;x<4;x++)    //控制每一行的数据交换  				
			for(y=0;y<4;y++)    //从最左边第一个开始遍历
				if(arr[x][y]==0)   //找到第一个空位置
					for(i=y+1;i<4;i++)   //在此基础上往上遍历
						if(arr[x][i]!=0)   //找到第一个不是空的位置
						{
							moveflag=1;
							swap(&arr[x][y],&arr[x][i]);   //交换
							break;
						}	
		
	}
	if(moveflag == 0)             
		return -1;         //数组和副本数组数据相同，证明没移动，则返回-1

	return 0;               //移动成功，返回0
}

//显示格子数据图片
int show_place_bmp(int arr[4][4],int *x,int *y)
{
	int ret;
	char bmp_path[30]={0};
	show_any_bmp(800,480,0,0,"2048.bmp");
	show_array(arr);
	ret = for_arr_place(arr,x,y);
	if(ret!=-1)
	{
		//拼接文件路径
		sprintf(bmp_path,"2048/%d.bmp",arr[*x][*y]);
		show_any_bmp(100,100,13+117*(*y),13+117*(*x),bmp_path);
	}
	ret = sure_the_2048(arr);   //判断是否有2048
	if(ret==0)
	{
		printf("游戏通关！\n");
		show_any_bmp(400,200,50,100,"gamesuccess.bmp");
		memset(arr,0,sizeof(arr));
		sleep(1);
		flag=1;
		return 0;
	}
	
	return 1;
}


//2048游戏操作
int opera_2048()
{
	show_any_bmp(800,480,0,0,"2048.bmp");
	
	int arr[4][4] = {0};
	int x,y,i,j;
	int ret;
	
	while(1)
	{
		int botton = act_2048(flag);
		switch(botton)
		{
			case 1:                   //新游戏
				memset(arr,0,sizeof(arr));
				for_arr_place(arr,&x,&y);
				for_arr_place(arr,&x,&y);
				show_any_bmp(800,480,0,0,"2048.bmp");   
				show_array(arr);
				flag=0;
				break;
			case 2:                   //退出游戏
				flag=0;
				return 0;
			case UP:              //向上移动
				ret = move(arr,botton);
				if(ret!=-1)
					show_place_bmp(arr,&x,&y);   //显示格子数据图片
				else
					ret = sure_the_place(arr);    //判断是否有空位置
					if(ret==-1)
					{
						printf("游戏结束！\n");
						show_any_bmp(400,246,50,100,"gameover.bmp");	
						memset(arr,0,sizeof(arr));
						flag=1;
						sleep(1);	
						break;
					}
				break;
			case DOWN:                //向下移动
				ret = move(arr,botton);
				if(ret!=-1)
					show_place_bmp(arr,&x,&y);   //显示格子数据图片
				else
					ret = sure_the_place(arr);    //判断是否有空位置
					if(ret==-1)
					{
						printf("游戏结束！\n");
						show_any_bmp(400,246,50,100,"gameover.bmp");	
						memset(arr,0,sizeof(arr));
						flag=1;
						sleep(1);	
						break;
					}
				break;
			case LEFT:               //向左移动
				ret = move(arr,botton);
				if(ret!=-1)
					show_place_bmp(arr,&x,&y);   //显示格子数据图片
				else
					ret = sure_the_place(arr);    //判断是否有空位置
					if(ret==-1)
					{
						printf("游戏结束！\n");
						show_any_bmp(400,246,50,100,"gameover.bmp");	
						memset(arr,0,sizeof(arr));
						flag=1;
						sleep(1);	
						break;
					}
				break;
			case RIGHT:                 //向右移动
				ret = move(arr,botton);
				if(ret!=-1)
					show_place_bmp(arr,&x,&y);   //显示格子数据图片
				else
					ret = sure_the_place(arr);    //判断是否有空位置
					if(ret==-1)
					{
						printf("游戏结束！\n");
						show_any_bmp(400,246,50,100,"gameover.bmp");	
						memset(arr,0,sizeof(arr));
						flag=1;
						sleep(1);	
						break;
					}
				break;
		}
	}
}