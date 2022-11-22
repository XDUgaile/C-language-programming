#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//存放图片的颜色点阵数据RGB
char src1[1000][1000][3];
char src2[1000][1000][3];
char dst[1000][1000][3];

//位图文件头
struct bfHead
{
	long bfSize;	//说明该位图的大小 
	long bfReserved;	//保留设置为0 
	long bfOffBits;		//从文件头开始到实际的图像数据之间的偏移量 
};

//位图信息头
struct biHead
{
	long biSize;	//说明信息头结构所占据的字节数 
	long biWidth;   //图的宽度
	long biHeight;  //图的高度
	short biBitCount;   //像素点位深度，24则为24位真彩图
	long biCompression;	//图像数据压缩类型 
	long biSizeImage;	//图像的大小 
	long biXPelsPerMeter;	//水平分辨率 
	long biYpelsPerMeter;
};

int main(int argc, char* argv[])
{
    struct bfHead bfSrc1, bfSrc2;
    struct biHead biSrc1, biSrc2;

    //打开2个原始文件 供读取数据
    //fp是指针，用来指向FILE类型的对象。
    FILE *fp1 = fopen(argv[1], "r+b");
    FILE *fp2 = fopen(argv[3], "r+b");

    //混合的百分比，例如输入 80% 则percent为0.8
    double percent = 0;
    for (int i = 0; i < strlen(argv[2]) - 1; ++i)
        percent = percent * 10 + (argv[2][i] - '0');
    percent /= 100;

    //打开目标文件 供写入数据
    //这个文件可能是没有的，fopen会创建一个新的文件；如果该文件已经存在，fopen会将其覆盖掉
    FILE *fp3 = fopen(argv[4], "w+b");

    //读取位图文件头 位图信息头
    //从文件fp中读取size*count个字节，放bfSrc（数据存放的内存的指针）里 
    fread(&bfSrc1, 14, 1, fp1);
    fread(&bfSrc2, 14, 1, fp2);
    fread(&biSrc1, 40, 1, fp1);
    fread(&biSrc2, 40, 1, fp2);

    //读取颜色点阵数据
    //遍历列 从下向上
    for (int y = biSrc1.biHeight - 1; y >= 0; --y)
    {
        //遍历行 从前向后
        for (int x = 0; x < biSrc1.biWidth; ++x)
        {
            //文件数据流中按照BGR的顺序存储，我们以RGB的顺序存储
            for (int k = 2; k >= 0; --k)
            {
                fread(&src1[x][y][k], 1, 1, fp1);
                fread(&src2[x][y][k], 1, 1, fp2);
            }
        }
    }

    //混合像素到目标文件数据
    for (int y = biSrc1.biHeight - 1; y >= 0; --y)
    {
        for (int x = 0; x<biSrc1.biWidth; ++x)
        {
            for (int k = 2; k >= 0; --k)
                dst[x][y][k] = src1[x][y][k] * percent + src2[x][y][k] * (1 - percent);
        }
    }

    //写目标文件

    fwrite(&bfSrc1,14,1,fp3);	//bmp文件头大小14bit 
    fwrite(&biSrc1,40,1,fp3);	//bmp信息头大小40bit 
    for (int y = biSrc1.biHeight - 1; y >= 0; --y)
    {
        for (int x = 0; x<biSrc1.biWidth; ++x)
        {
            for (int k = 2; k >= 0; --k)
                fwrite(&dst[x][y][k], 1, 1, fp3);
        }
    }

    printf("执行成功\n");
//    }

    //关闭文件
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return 0;
}

