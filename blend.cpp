#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//���ͼƬ����ɫ��������RGB
char src1[1000][1000][3];
char src2[1000][1000][3];
char dst[1000][1000][3];

//λͼ�ļ�ͷ
struct bfHead
{
	long bfSize;	//˵����λͼ�Ĵ�С 
	long bfReserved;	//��������Ϊ0 
	long bfOffBits;		//���ļ�ͷ��ʼ��ʵ�ʵ�ͼ������֮���ƫ���� 
};

//λͼ��Ϣͷ
struct biHead
{
	long biSize;	//˵����Ϣͷ�ṹ��ռ�ݵ��ֽ��� 
	long biWidth;   //ͼ�Ŀ��
	long biHeight;  //ͼ�ĸ߶�
	short biBitCount;   //���ص�λ��ȣ�24��Ϊ24λ���ͼ
	long biCompression;	//ͼ������ѹ������ 
	long biSizeImage;	//ͼ��Ĵ�С 
	long biXPelsPerMeter;	//ˮƽ�ֱ��� 
	long biYpelsPerMeter;
};

int main(int argc, char* argv[])
{
    struct bfHead bfSrc1, bfSrc2;
    struct biHead biSrc1, biSrc2;

    //��2��ԭʼ�ļ� ����ȡ����
    //fp��ָ�룬����ָ��FILE���͵Ķ���
    FILE *fp1 = fopen(argv[1], "r+b");
    FILE *fp2 = fopen(argv[3], "r+b");

    //��ϵİٷֱȣ��������� 80% ��percentΪ0.8
    double percent = 0;
    for (int i = 0; i < strlen(argv[2]) - 1; ++i)
        percent = percent * 10 + (argv[2][i] - '0');
    percent /= 100;

    //��Ŀ���ļ� ��д������
    //����ļ�������û�еģ�fopen�ᴴ��һ���µ��ļ���������ļ��Ѿ����ڣ�fopen�Ὣ�串�ǵ�
    FILE *fp3 = fopen(argv[4], "w+b");

    //��ȡλͼ�ļ�ͷ λͼ��Ϣͷ
    //���ļ�fp�ж�ȡsize*count���ֽڣ���bfSrc�����ݴ�ŵ��ڴ��ָ�룩�� 
    fread(&bfSrc1, 14, 1, fp1);
    fread(&bfSrc2, 14, 1, fp2);
    fread(&biSrc1, 40, 1, fp1);
    fread(&biSrc2, 40, 1, fp2);

    //��ȡ��ɫ��������
    //������ ��������
    for (int y = biSrc1.biHeight - 1; y >= 0; --y)
    {
        //������ ��ǰ���
        for (int x = 0; x < biSrc1.biWidth; ++x)
        {
            //�ļ��������а���BGR��˳��洢��������RGB��˳��洢
            for (int k = 2; k >= 0; --k)
            {
                fread(&src1[x][y][k], 1, 1, fp1);
                fread(&src2[x][y][k], 1, 1, fp2);
            }
        }
    }

    //������ص�Ŀ���ļ�����
    for (int y = biSrc1.biHeight - 1; y >= 0; --y)
    {
        for (int x = 0; x<biSrc1.biWidth; ++x)
        {
            for (int k = 2; k >= 0; --k)
                dst[x][y][k] = src1[x][y][k] * percent + src2[x][y][k] * (1 - percent);
        }
    }

    //дĿ���ļ�

    fwrite(&bfSrc1,14,1,fp3);	//bmp�ļ�ͷ��С14bit 
    fwrite(&biSrc1,40,1,fp3);	//bmp��Ϣͷ��С40bit 
    for (int y = biSrc1.biHeight - 1; y >= 0; --y)
    {
        for (int x = 0; x<biSrc1.biWidth; ++x)
        {
            for (int k = 2; k >= 0; --k)
                fwrite(&dst[x][y][k], 1, 1, fp3);
        }
    }

    printf("ִ�гɹ�\n");
//    }

    //�ر��ļ�
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return 0;
}

