#ifndef _BITMAP_
#define _BITMAP_
#include<sys/types.h>  
#include <cstdio>
#include <memory>
#include <functional>
#include <cassert>
#include <vector>
#include <cmath>
#include <DC/utils/Table.hpp>
#pragma pack(2)
/*
 *
 *文件头结构体
 *
 */
struct BitMapFileader
{   
	u_int16_t bfType;   //标识图像为bmp文件,判断文件是否为bmp文件,即用该值与"0x4d42"比较是否相等即可,0x4d42 = 19778;
	u_int32_t bfSize;   //文件大小
	u_int16_t bfReserved1;   //预保留位1
	u_int16_t bfReserved2;   //预保留位2
	u_int32_t bfOffBits;     //图像数据区的起始位置
};   //16byte
/*
 *
 *文件信息头结构体
 *
 */
struct BitMapInfoader  
{   
	u_int32_t biSize;   //图像数据快大小
	u_int32_t biWidth;   //宽度
	u_int32_t biight;   //高度
	u_int16_t biPlanes;   //1
	u_int16_t biBitCount;   //像素位数
	u_int32_t biCompression;   //压缩方式
	u_int32_t biSizeImage;    //图像区数据大小
	u_int32_t biXPelsPerMeter;   //水平分辨率,像素每米
	u_int32_t biYPelsPerMeter;   
	u_int32_t biClrUsed;         //位图实际用到的颜色数
	u_int32_t biClrImportant;   //位图显示过程,重要的颜色数;0--所有都重要
};  //40byte
/*
 *red,green,blue 0~255
 */
struct RGB{
	u_int8_t B;
	u_int8_t G;
	u_int8_t R;
};
/*
 *位置类
 */
struct Pos{
	int64_t X;
	int64_t Y;
};
/*
 *
 *存储位图的类
 *
 */
class BitMap
{
	/*
	 *像素点RGB二维数组
	 *
	 */
	std::unique_ptr<Table<RGB>>  content = nullptr;
	/*
	 *画笔大小
	 *
	 */
	uint32_t penSize = 1;
	/*
	 *
	 * 文件指针
	 *
	 */
	FILE * fp = nullptr;
	/*
	 *文件头
	 *
	 */
	BitMapFileader file;
	/*
	 *文件信息头
	 *
	 */
 	BitMapInfoader	info;
public:
	/*
	 *展示文件头
	 */
	void ShowFileader(){
		printf("位图文件头:\n") ;
		printf("文件头类型:%d\n",file.bfType);    
		printf("文件大小:%d\n",file.bfSize);    
		printf("保留字_1:%d\n",file.bfReserved1);    
		printf("保留字_2:%d\n",file.bfReserved2);    
		printf("实际位图数据的偏移字节数:%d\n",file.bfOffBits);    
	}
	/*
	 *展示文件信息头
	 */
	void ShowInfoader(){    
			printf("位图信息头:\n");    
			printf("结构体的长度:%d\n",info.biSize);    
			printf("位图宽:%d\n",info.biWidth);    
			printf("位图高:%d\n",info.biight);    
			printf("biPlanes平面数:%d\n",info.biPlanes);    
			printf("biBitCount采用颜色位数:%d\n",info.biBitCount);    
			printf("压缩方式:%d\n",info.biCompression);    
			printf("biSizeImage实际位图数据占用的字节数:%d\n",info.biSizeImage);    
			printf("X方向分辨率:%d\n",info.biXPelsPerMeter);    
			printf("Y方向分辨率:%d\n",info.biYPelsPerMeter);    
			printf("使用的颜色数:%d\n",info.biClrUsed);    
			printf("重要颜色数:%d\n",info.biClrImportant);
	}
	/*
	 *展示文件信息头和文件头
	 */
	BitMap& Info(){
		this->ShowFileader();
		this->ShowInfoader();
		return *this;
	}
	/*
	 *默认为黑色画笔
	 *
	 */
	std::function<void(RGB&)> pen = [](RGB & color){
					color.R = 0x00;
					color.G = 0x00;
					color.B = 0x00;};
	//TODO
	/*
	 *
	 *默认创建位图文件,设置一个底色,加载在内存
	 *未完成,没有严格按照bmp格式处理,暂时只支持
	 *长宽都是4的倍数
	 *
	 *
	 */	BitMap & Default4x
		(uint64_t x_size,
		 uint64_t y_size,
		 RGB color=RGB{0xff,0xff,0xff}){
		if(x_size%4!=0||y_size%4!=0){
			fprintf(stderr,"error:developing...");
			exit(-1);
		}
		file.bfType = 19778;
		file.bfSize = x_size*y_size*3+122;
		file.bfReserved1 = 0;
		file.bfReserved2 = 0;
		file.bfOffBits = 122;

		info.biSize = 108;
		info.biWidth = x_size;
		info.biight = y_size;
		info.biPlanes = 1;
		info.biBitCount = 24;
		info.biCompression =  0;
		info.biSizeImage = x_size*y_size*3;
		info.biXPelsPerMeter = 11811;
		info.biYPelsPerMeter = 11811;
		info.biClrUsed = 0;
		info.biClrImportant = 0;
		
		if(content!=nullptr){
			content=nullptr;
		}
		content = std::make_unique<Table<RGB>>();
		content->setSize(x_size,y_size);
		for(u_int32_t i=0;i<x_size;i++){
			for(u_int32_t j=0;j<y_size;j++){
				content->arr[i][j] = color;
			}
		}
		return *this;
	}
	/*
	 *
	 *从文件加载位图到内存,
	 *链式调用,返回原来对象的引用
	 *
	 */	BitMap & Load(const char * path){
		if(fp!=nullptr){
			fclose(fp);
		}
		fp = fopen(path,"rb");
		fread(&(file), 1, sizeof(BitMapFileader), fp);  
		fread(&(info), 1, sizeof(BitMapInfoader), fp);
		fseek(fp,file.bfOffBits,SEEK_SET);
		content = std::make_unique<Table<RGB>>();
		content->setSize(info.biWidth,info.biight);
		for(u_int32_t y =0;y<info.biight;y++){
			for(u_int32_t x = 0;x<info.biWidth;x++){
				fread(&content->arr[x][y],1,sizeof(RGB),fp);
			}
		}
		return *this;
	}
	/*
	 *
	 *从内存存储位图到文件,
	 *链式调用,返回原来的对象引用
	 *
	 */	BitMap & Save(const char * path){
		if(fp!=nullptr){
			fclose(fp);
		}
		fp = fopen(path,"w+");

		if(content==nullptr){
			fprintf(stderr,"have't load.\n\n");
			exit(-1);
		}
		fwrite(&file,1,sizeof(BitMapFileader),fp);
		fwrite(&info,1,sizeof(BitMapInfoader),fp);
		fseek(fp,file.bfOffBits,SEEK_SET);
		for(u_int32_t y =0;y<info.biight;y++){
			for(u_int32_t x = 0;x<info.biWidth;x++){
				fwrite(&content->arr[x][y],1,sizeof(RGB),fp);
			}
		}
		fclose(fp);
		fp = nullptr;
		return *this;
	}
	/*
	 *获取某一个像素点的引用
	 */
	RGB& At(uint64_t X,uint64_t Y){
		return content->arr[X][Y];
	}
	/*
	 *传入lambda,在lambda内对尺寸大小进行处理,
	 *按与原来尺寸的相对比例缩放图像
	 *
	 */
	BitMap & ReSize(std::function<void(uint32_t &,uint32_t &)> f){
		uint32_t Src_x = info.biWidth;
		uint32_t Src_y = info.biight;
		f(info.biWidth,info.biight);

		assert(info.biWidth!=Src_x||info.biight!=Src_y);

		const uint32_t & Dst_x = info.biWidth;
		const uint32_t & Dst_y = info.biight;
		if((Dst_x==0)||(Dst_y==0)){
			info.biWidth = Src_x;
			info.biight = Src_y;
			fprintf(stderr,"invalid size : 0\n\n");
		}
		if((Src_x>65536)||(Src_y>65536)||(Dst_x>65536)||(Dst_y>65536)){
			zoom_Slow(Src_x,Src_y);
		}else{
			zoom(Src_x,Src_y);
		}
		return *this;
	}
	/*
	 *向控制台打印点,从下标为第一个参数的点开始到下标为第二个参数的点
	 *省略参数将打印所有像素
	 *省略第二个参数,从第一个参数开始打印到尾
	 *
	 */
	BitMap & Print(uint64_t start=0,uint64_t end=0){
		if(end<=start){
			end = content->X*content->Y-1;
		}
		u_int64_t count = 0;
		for(u_int64_t i =0;i<content->X;i++){
			for(u_int64_t j=0;j<content->Y;j++){
				if(count>end){
					goto end;
				}
				if(count>=start){
					printf("[%2x %2x %2x] ",content->arr[i][j].R,content->arr[i][j].G,content->arr[i][j].B);
				}
				count++;
			}
			printf("\n\n\n\n");
		}
		end:
		printf("\n");
		return *this;
	}
	
	/*
	 *更改画笔
	 *
	 */
	BitMap & PixelMap(std::function<void(RGB &)> p){
		pen = p;
		return *this;
	}
	/*
	 *更改画笔尺寸
	 *
	 */
	BitMap & PenSize(uint32_t size){
		penSize = size;
		return *this;
	}
	/*
	 *画一条有粗细的线,默认粗细为1,使用single_line方法
	 *粗细等于0,相当于粗细等于1
	 *在粗细大于1的时候,使用Point方法低效画点
	 */
	BitMap & Line(Pos a,Pos b){
		Pos left,right;
		right = a.X>b.X?a:b;
		left  = a.X>b.X?b:a;
		uint32_t tempSize=penSize;
		if(tempSize<=1){
			single_line(a,b,[this](Pos p){
				pen(At(p.X,p.Y));
			});
		}else{
			single_line(a,b,[this](Pos p){
				Point(p.X,p.Y);		
			});
		}
		return *this;
	}
	/*
	 *对所有像素点使用画笔方法
	 *
	 */
	BitMap & FillAll(){
		for(uint32_t i = 0;i<content->X;i++){
			for(uint32_t j =0;j<content->Y;j++){
				pen(At(i,j));
			}
		}
		return *this;
	}
	/*
	 *
	 *此函数画单条线
	 *Pos a,b  线两端的端点
	 *std::function <void(Pos)> f 对某点使用的画笔方法,存储在pen中 
	 */
	void single_line(Pos a,Pos b,std::function<void(Pos)> f){
		auto left=a.X<b.X?a:b;
		auto right=a.X<b.X?b:a;
		auto len_x = a.X>b.X?a.X-b.X:b.X-a.X;
		auto len_y = a.Y>b.Y?a.Y-b.Y:b.Y-a.Y;
		if(left.X==right.X){
			auto downY = left.Y>right.Y?right.Y:left.Y;
			auto upY = left.Y>right.Y?left.Y:right.Y;
			for(auto y = downY;y<=upY;y++){
				safe_draw(Pos{left.X,y},f);
			}
		}else if(left.Y<right.Y){//left.X<right.X
			if(len_x>len_y){
				for(auto x = left.X;x<right.X;x++){
					auto y = left.Y+(x-left.X)*len_y/len_x;
					safe_draw(Pos{x,y},f);
				}
			}else if(len_x==len_y){
				for(auto x=left.X,y=left.Y;x<=right.X&&y<=right.Y;x++,y++){
					safe_draw(Pos{x,y},f);
				}
			}else{
				for(auto y = left.Y;y<right.Y;y++){
					auto x = left.X+(y-left.Y)*len_x/len_y;
					safe_draw(Pos{x,y},f);
				}
			}
		}else if(left.Y==right.Y){
			for(auto x = left.X;x<=right.X;x++){
				safe_draw(Pos{x,left.Y},f);
			}
		}else if(left.Y>right.Y){//left.X<right.X
			if(len_x>len_y){
				for(auto x = left.X;x<right.X;x++){
					auto y = left.Y-(x-left.X)*len_y/len_x;
					safe_draw(Pos{x,y},f);
				}
			}else if(len_x==len_y){
				for(auto x=left.X,y=left.Y;x<=right.X&&y>=right.Y;x++,y--){
					safe_draw(Pos{x,y},f);
				}
			}else{
				for(auto y = right.Y;y<left.Y;y++){
					auto x = right.X-(y-right.Y)*len_x/len_y;
					safe_draw(Pos{x,y},f);
				}
			}
		}
	}
	/*
	 *此函数防止打印点的时候超过图像边界
	 *
	 */
	void safe_draw(Pos p,std::function<void(Pos)> f){
		if(p.X>(int64_t)content->X||p.X<0||p.Y>(int64_t)content->Y||p.Y<0){
			return;
		}
		f(p);
	}

	BitMap & Point(uint32_t X,uint32_t Y){
		if(penSize>1){
			for(int64_t i = (int64_t)X-penSize/2;i<=X+penSize/2;i++){
				if(i<0||i>=(int64_t)content->X){
					continue;
				};
				for(int64_t j = (int64_t)Y-penSize/2;j<=Y+penSize/2;j++){
					if(j<0||j>=(int64_t)content->Y){
						continue;
					}
					else if(point_check_inside(i,j,Pos{X,Y})){
						pen(this->At(i,j));
					}
				}
			}
		}else{
			pen(At(X,Y));
		}
		return *this;
	}
	bool point_check_inside(uint32_t i,uint32_t j,Pos p){
		int64_t dis_x = p.X>=i?p.X-i:i-p.X;
		int64_t dis_y = p.Y>=j?p.Y-j:j-p.Y;
		if(pow(dis_x,2)+pow(dis_y,2)<=pow(penSize/2,2)){
			if(dis_x==penSize/2||dis_y==penSize/2){
				return false;
			}
			return true;
		}
		return false;
	}
	//向控制台打印,打印一个点
	void PrintPos(uint64_t X,uint64_t Y){
		printf("[%x %x %x] ",content->arr[X][Y].R,content->arr[X][Y].G,content->arr[X][Y].B);
	}
	~BitMap(){
		if(fp!=nullptr){
			fclose(fp);
		}
		content=nullptr;
	}
private:
	//备用函数,当图像大小超过65536的时候启用
	void zoom_Slow(uint32_t Src_x,uint32_t Src_y){
		const uint32_t & Dst_x = info.biWidth;
		const uint32_t & Dst_y = info.biight;
		auto new_content = std::make_unique<Table<RGB>>();
		new_content->setSize(Dst_x,Dst_y);

		for(uint32_t j = 0;j<Dst_y;j++){
				uint32_t y = j*Src_y/Dst_y;
			for(uint32_t i = 0;i<Dst_x;i++){
				uint32_t x = i*Src_x/Dst_x;
				new_content->arr[i][j] = content->arr[x][y];		
			}
		}

		content =std::move(new_content);
		file.bfSize = Dst_x*Dst_y*3+122;
		info.biSizeImage = Dst_x*Dst_y*3;
		printf("Scaled:Zoom_Slow()\n");
	}
	//缩放函数
	void zoom(uint32_t Src_x,uint32_t Src_y){
		const uint32_t & Dst_x = info.biWidth;
		const uint32_t & Dst_y = info.biight;
		auto new_content = std::make_unique<Table<RGB>>();
		new_content->setSize(Dst_x,Dst_y);
		//此处限制了最大尺寸为65536
		uint32_t temp_x = (Src_x<<16)/Dst_x+1;
		uint32_t temp_y = (Src_y<<16)/Dst_y+1;
		for(uint32_t j = 0;j<Dst_y;j++){
			uint32_t y = (j*temp_y)>>16;
			for(uint32_t i = 0;i<Dst_x;i++){
				uint32_t x = (i*temp_x)>>16;
				new_content->arr[i][j] = content->arr[x][y];		
			}
		}

		content =std::move(new_content);
		file.bfSize = Dst_x*Dst_y*3+122;
		info.biSizeImage = Dst_x*Dst_y*3;
	}
	
};


#pragma pack()
#endif
