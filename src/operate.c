#include <myhead.h>
#include <display.h>
#include <botton.h>
#include <game.h>

//操作图片
int operation_bmp(struct list_head *p,klist *bmphead)
{
	int flag = 0;
	int mark = 0;
	int w,h,start_x,start_y,ret;
	p=p->next;
	if(p == &(bmphead->mylist))
		p=p->next;
	klist *n = list_entry(p,klist,mylist);	
	while(1)
	{
		if(flag == 0)
		{
			black_show(); //显示黑底
			sure_bmp_place(&w,&h,&start_x,&start_y,n->path);  //获取居中显示的起始坐标strat_x,start_y
			photo_show(w,h,start_x,start_y,n->path);
		}
		int botton = botton_out_photo();       //获取按键操作
		switch(botton)
		{
			case QUITPT:                   //返回上一级
						return 0;       
			case PREVPT:                   //上一张 
				black_show(); //显示黑底
				p = p->prev;
				if(p == &(bmphead->mylist))
					p = p->prev;
				n = list_entry(p,klist,mylist);
				sure_bmp_place(&w,&h,&start_x,&start_y,n->path);  //居中
				photo_show(w,h,start_x,start_y,n->path);
				flag = 1;
				mark=0;
				break;
			case NEXTPT:                  //下一张
				black_show(); //显示黑底
				p = p->next;
				if(p == &(bmphead->mylist))
					p = p->next;
				n = list_entry(p,klist,mylist);
				sure_bmp_place(&w,&h,&start_x,&start_y,n->path);   //获取居中坐标和图片的宽高
				photo_show(w,h,start_x,start_y,n->path);  
				flag = 1;
				mark=0;
				break;
			case REDUCE:                //缩小图片
				mark++;
				black_show(); //显示黑底
				get_bmp_wh(n->path,&w,&h);             //获取图片的宽高
				int new_w = w-mark*20;
				int new_h = h-mark*20;
				start_x = 400-new_w/2;
				start_y = 240-new_h/2;
				reduce_bmp(n->path,new_w,new_h,start_x,start_y);
				show_any_bmp(50,50,740,10,"返回.bmp");
				show_any_bmp(100,100,10,370,"上一页.bmp");
				show_any_bmp(100,100,690,370,"下一页.bmp");
				show_any_bmp(50,50,50,240,"reduce.bmp");
				break;
			// case ENLARGE:              //放大图片
				// black_show(); //显示黑底
				// break;	
			case UP:       //以特效形式展示当前图片
				black_show(); //显示黑底
				ret = get_random();    //获取随机数
				sure_bmp_place(&w,&h,&start_x,&start_y,n->path);  //居中
				show_bmp_super(w,h,start_x,start_y,n->path,ret);    //居中随机特效展开
				show_any_bmp(50,50,740,10,"返回.bmp");
				show_any_bmp(100,100,10,370,"上一页.bmp");
				show_any_bmp(100,100,690,370,"下一页.bmp");
				show_any_bmp(50,50,50,240,"reduce.bmp");
			
				flag = 1;
				mark=0;
				break;
			case DOWN:    //以特效形式展示当前图片
				black_show(); //显示黑底
				ret = get_random();    //获取随机数
				sure_bmp_place(&w,&h,&start_x,&start_y,n->path);  //居中
				show_bmp_super(w,h,start_x,start_y,n->path,ret);     //居中随机特效展开
				show_any_bmp(50,50,740,10,"返回.bmp");
				show_any_bmp(100,100,10,370,"上一页.bmp");
				show_any_bmp(100,100,690,370,"下一页.bmp");
				show_any_bmp(50,50,50,240,"reduce.bmp");
			
				flag = 1;
				mark=0;
				break;
			case LEFT:    //以左移形式展示下一张
				get_bmp_wh(n->path,&w,&h);
				int bmpbuf1[800*480];
				bzero(bmpbuf1,sizeof(bmpbuf1));
				get_bmp_info(n->path,bmpbuf1,w,h);   //获取当前图片拼成800*480的图片的数据
				p = p->next;
				if(p == &(bmphead->mylist))
					p = p->next;
				n = list_entry(p,klist,mylist);
				get_bmp_wh(n->path,&w,&h);    //获取下一张图片的宽高
				int bmpbuf2[800*480];
				bzero(bmpbuf2,sizeof(bmpbuf2));
				get_bmp_info(n->path,bmpbuf2,w,h);   //获取下一张图片拼成800*480的图片的数据
				splicing_bmp(bmpbuf1,bmpbuf2);    //拼接成1600*480的图片并从右往左滑动
				show_any_bmp(50,50,740,10,"返回.bmp");
				show_any_bmp(100,100,10,370,"上一页.bmp");
				show_any_bmp(100,100,690,370,"下一页.bmp");
				show_any_bmp(50,50,50,240,"reduce.bmp");
			
				flag = 1;
				mark=0;
				break;
			case RIGHT:         //以特效形式展示下一张
				black_show(); //显示黑底
				p = p->prev;
				if(p == &(bmphead->mylist))
					p = p->prev;
				n = list_entry(p,klist,mylist);
				sure_bmp_place(&w,&h,&start_x,&start_y,n->path);    //居中
				ret = get_random();    //获取随机数
				show_bmp_super(w,h,start_x,start_y,n->path,ret);    //居中随机特效展开
				show_any_bmp(50,50,740,10,"返回.bmp");
				show_any_bmp(100,100,10,370,"上一页.bmp");
				show_any_bmp(100,100,690,370,"下一页.bmp");
				show_any_bmp(50,50,50,240,"reduce.bmp");

				flag = 1;
				mark=0;
				break;
		}
	}
}

