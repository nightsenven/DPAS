#include <myhead.h>

//打开目录,保存所有.bmp图片
int open_dir_save_bmp(char *dirpath,klist *head)
{
	//读取目录里的所有.bmp文件
	DIR *dp = opendir(dirpath);  //打开目录
	struct dirent *p;
	char bmp_path[PATHSIZE];
	while(p = readdir(dp))
	{
		if(p->d_type == DT_REG)  //判断是否是普通文件
		{
			if(strstr(p->d_name,".bmp")) //判断是否是.bmp文件
			{
				bzero(bmp_path,PATHSIZE);
				sprintf(bmp_path,"%s/%s",dirpath,p->d_name);
				klist *new = new_node(bmp_path); //创建新节点
				list_add_tail(&(new->mylist),&(head->mylist));  //尾插
			}				
		}
	}
	return 0;
}

//打开目录,保存所有.mp3音乐
int open_dir_save_mp3(char *dirpath,klist *head)
{
	//读取目录里的所有.bmp文件
	DIR *dp = opendir(dirpath);  //打开目录
	struct dirent *p;
	char mp3_path[PATHSIZE];
	while(p = readdir(dp))
	{
		if(p->d_type == DT_REG)  //判断是否是普通文件
		{
			if(strstr(p->d_name,".mp3")) //判断是否是音频文件
			{
				bzero(mp3_path,PATHSIZE);
				sprintf(mp3_path,"%s/%s",dirpath,p->d_name);
				klist *new = new_node(mp3_path); //创建新节点
				list_add_tail(&(new->mylist),&(head->mylist));  //尾插
			}				
		}
	}
	return 0;
}

//打开目录,保存所有.mp4或者.avi音乐
int open_dir_save_movie(char *dirpath,klist *head)
{
	//读取目录里的所有.bmp文件
	DIR *dp = opendir(dirpath);  //打开目录
	struct dirent *p;
	char mp3_path[PATHSIZE];
	while(p = readdir(dp))
	{
		if(p->d_type == DT_REG)  //判断是否是普通文件
		{
			if(strstr(p->d_name,".mp4") || strstr(p->d_name,".avi")) //判断是否是视频文件
			{
				bzero(mp3_path,PATHSIZE);
				sprintf(mp3_path,"%s/%s",dirpath,p->d_name);
				klist *new = new_node(mp3_path); //创建新节点
				list_add_tail(&(new->mylist),&(head->mylist));  //尾插
			}				
		}
	}
	return 0;
}

