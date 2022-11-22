#include <windows.h>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

class BitMap {
private:
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	LPRGBQUAD colorTable;
	int width, height, bitCount;
	int getLineSize();
	int getDataSize();
	int getHeaderSize();
	int getColorTableSize();
	void setFileHeader();
	void setInfoHeader();
	bool writeFile(FILE *f);
public:
	unsigned char *dataBuf;
	BitMap(){}
	BitMap(int width, int height, int bitCount);
	bool load(const char *fileName);
	bool save(const char *fileName);
	BitMap scale(const double rate);
	int getBitCount();
};

/**********************************
/ 构造函数
/ para width: 图片宽度
/ para height: 图片高度
/ para bitCount: 图片位深
**********************************/
BitMap::BitMap(int width, int height, int bitCount):
			width(width), height(height), bitCount(bitCount) {
	colorTable = NULL;
	int dataSize = getDataSize();
	dataBuf = (unsigned char*)malloc(dataSize); // 分配数据空间
	memset(dataBuf, 0, sizeof(dataSize));
}

/**********************************
/ 计算一行的大小
/ return: 当前属性对应的一行的数值大小
**********************************/
int BitMap::getLineSize() {
	return (width * bitCount / 8 + 3) / 4 * 4;
}

/**********************************
/ 计算整个图像的大小
/ return: 当前属性对应的图像真实大小
**********************************/
int BitMap::getDataSize() {
	return sizeof(unsigned char) * bitCount / 8 * height * getLineSize();
}

/**********************************
/ 计算位图文件的 header 大小
/ return: 当前属性对应的 header 大小
**********************************/
int BitMap::getHeaderSize() {
	return sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + getColorTableSize();
}

/**********************************
/ 计算位图文件的调色板大小
/ return: 调色板大小
**********************************/
int BitMap::getColorTableSize() {
	if (colorTable == NULL)
		return 0;
	else
		return sizeof(RGBQUAD) * 256;
}

/**********************************
/ 设置 BITMAPFILEHEADER 的属性
**********************************/
void BitMap::setFileHeader() {
	fileHeader.bfType = 0x4D42;
	fileHeader.bfSize = getHeaderSize() + getDataSize();
	fileHeader.bfOffBits = getHeaderSize();
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
}

/**********************************
/ 设置 BITMAPINFOHEADER 的属性
**********************************/
void BitMap::setInfoHeader() {
	infoHeader.biWidth = width;
	infoHeader.biHeight = height;
	infoHeader.biBitCount = bitCount;
	infoHeader.biSizeImage = getDataSize();
	infoHeader.biSize = 40;
	infoHeader.biPlanes = 1;
	infoHeader.biCompression = 0;
	infoHeader.biClrImportant = 0;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;
}

/**********************************
/ 读取位图
/ para fileName: 位图文件
/ return: 是否读取成功, 文件不存在读取失败
**********************************/
bool BitMap::load(const char *fileName) {
	FILE *f = fopen(fileName, "rb");
	if (!f)
		return false;
	fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, f); // 读取 BITMAPFILEHEADER
	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, f); // 读取 BITMAPINFOHEADER
	width = infoHeader.biWidth;
	height = infoHeader.biHeight;
	bitCount = infoHeader.biBitCount;
	// 位深小于等于8的位图还需读入调色板
	if (bitCount <= 8) {
	    colorTable = new RGBQUAD[256];
	    fread(colorTable, 1, getColorTableSize(), f);
	}
	else
		colorTable = NULL;
	// 读取位图数据
	dataBuf = new unsigned char[infoHeader.biSizeImage];
	fread(dataBuf, 1, infoHeader.biSizeImage, f);
	fclose(f);
	return true;
}

/**********************************
/ 将位图所有数据写入文件
/ para f: 需要写如的目标文件
/ return: 是否写入成功, 文件不存在写入失败
**********************************/
bool BitMap::writeFile(FILE *f) {
	if (!f)
		return false;
	// 将header写入位图文件
	fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, f);
	fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, f);
	// 将调色板写入位图文件
	if (colorTable != NULL)
		fwrite(colorTable, 1, getColorTableSize(), f);
	// 将数据写入位图文件
	fwrite(dataBuf, 1, infoHeader.biSizeImage, f);
	return true;
}

/**********************************
/ 保存位图
/ para fileName: 位图文件
/ return: 是否保存成功
**********************************/
bool BitMap::save(const char *fileName) {
	FILE* f = fopen(fileName, "wb"); // 创建或打开文件
	if (!f)
		return false;
	// 设置Header属性
	setFileHeader();
	setInfoHeader();
	// 将数据写入文件
	if (!writeFile(f))
		return false;
	fclose(f);
	return true;
}

/**********************************
/ 缩放位图
/ para ratio: 缩放比例
/ return: 缩放后的位图
**********************************/
BitMap BitMap::scale(const double ratio) {
	// 新建一个缩放后的位图, 数据为空
	BitMap bitmap(round(width * ratio), round(height * ratio), bitCount);
	if (colorTable != NULL) {
		bitmap.colorTable = new RGBQUAD[256];
		memcpy(bitmap.colorTable, colorTable, getColorTableSize());
	}
	else
		bitmap.colorTable = NULL;
	int lineSize = bitmap.getLineSize(), originLineSize = getLineSize();
	int l = bitCount / 8;
	for(int i = 0; i < bitmap.height; i++) {
		for(int j = 0; j < bitmap.width; j++) {
			int x = j / ratio, y = i / ratio; // 原图像对应的点
			if (x >= 0 && x < width && y >= 0 && y < height){
				unsigned char *dst = bitmap.dataBuf + (lineSize * i + j * l);
				unsigned char *src = dataBuf + (originLineSize * y + x * l);
				memcpy(dst, src, l);
			}
		}
	}
	return bitmap;
}

/*********************************
/ 获取位深
/ return: 位图位深
*********************************/
int BitMap::getBitCount() {
	return bitCount;
}

int main(int argc, char const *argv[]) {
	const char *inputFile = argv[1];
	const char *outputFile = argv[3];
	double ratio = atoi(argv[2]) / 100.0;
	BitMap input, output;
	if (!input.load(inputFile)) {
		printf("ERROR: File \"%s\" Not Exists\n", inputFile);
		exit(EXIT_FAILURE);
	}
	// 由于比 8 位更小的位深一个像素不到一个字节, 处理需完全展开字节, 较为麻烦, 所以不处理了 ^_^
	if (input.getBitCount() < 8) {
		printf("ERROR: Unsupported File Format\n");
		exit(EXIT_FAILURE);
	}
	output = input.scale(ratio);
	if (!output.save(outputFile)) {
		printf("ERROR: Can't Save To File \"%s\"\n", outputFile);
		exit(EXIT_FAILURE);
	}
	puts("Zoom Successfully!");
	return 0;
}
