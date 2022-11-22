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
/ ���캯��
/ para width: ͼƬ���
/ para height: ͼƬ�߶�
/ para bitCount: ͼƬλ��
**********************************/
BitMap::BitMap(int width, int height, int bitCount):
			width(width), height(height), bitCount(bitCount) {
	colorTable = NULL;
	int dataSize = getDataSize();
	dataBuf = (unsigned char*)malloc(dataSize); // �������ݿռ�
	memset(dataBuf, 0, sizeof(dataSize));
}

/**********************************
/ ����һ�еĴ�С
/ return: ��ǰ���Զ�Ӧ��һ�е���ֵ��С
**********************************/
int BitMap::getLineSize() {
	return (width * bitCount / 8 + 3) / 4 * 4;
}

/**********************************
/ ��������ͼ��Ĵ�С
/ return: ��ǰ���Զ�Ӧ��ͼ����ʵ��С
**********************************/
int BitMap::getDataSize() {
	return sizeof(unsigned char) * bitCount / 8 * height * getLineSize();
}

/**********************************
/ ����λͼ�ļ��� header ��С
/ return: ��ǰ���Զ�Ӧ�� header ��С
**********************************/
int BitMap::getHeaderSize() {
	return sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + getColorTableSize();
}

/**********************************
/ ����λͼ�ļ��ĵ�ɫ���С
/ return: ��ɫ���С
**********************************/
int BitMap::getColorTableSize() {
	if (colorTable == NULL)
		return 0;
	else
		return sizeof(RGBQUAD) * 256;
}

/**********************************
/ ���� BITMAPFILEHEADER ������
**********************************/
void BitMap::setFileHeader() {
	fileHeader.bfType = 0x4D42;
	fileHeader.bfSize = getHeaderSize() + getDataSize();
	fileHeader.bfOffBits = getHeaderSize();
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
}

/**********************************
/ ���� BITMAPINFOHEADER ������
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
/ ��ȡλͼ
/ para fileName: λͼ�ļ�
/ return: �Ƿ��ȡ�ɹ�, �ļ������ڶ�ȡʧ��
**********************************/
bool BitMap::load(const char *fileName) {
	FILE *f = fopen(fileName, "rb");
	if (!f)
		return false;
	fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, f); // ��ȡ BITMAPFILEHEADER
	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, f); // ��ȡ BITMAPINFOHEADER
	width = infoHeader.biWidth;
	height = infoHeader.biHeight;
	bitCount = infoHeader.biBitCount;
	// λ��С�ڵ���8��λͼ��������ɫ��
	if (bitCount <= 8) {
	    colorTable = new RGBQUAD[256];
	    fread(colorTable, 1, getColorTableSize(), f);
	}
	else
		colorTable = NULL;
	// ��ȡλͼ����
	dataBuf = new unsigned char[infoHeader.biSizeImage];
	fread(dataBuf, 1, infoHeader.biSizeImage, f);
	fclose(f);
	return true;
}

/**********************************
/ ��λͼ��������д���ļ�
/ para f: ��Ҫд���Ŀ���ļ�
/ return: �Ƿ�д��ɹ�, �ļ�������д��ʧ��
**********************************/
bool BitMap::writeFile(FILE *f) {
	if (!f)
		return false;
	// ��headerд��λͼ�ļ�
	fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, f);
	fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, f);
	// ����ɫ��д��λͼ�ļ�
	if (colorTable != NULL)
		fwrite(colorTable, 1, getColorTableSize(), f);
	// ������д��λͼ�ļ�
	fwrite(dataBuf, 1, infoHeader.biSizeImage, f);
	return true;
}

/**********************************
/ ����λͼ
/ para fileName: λͼ�ļ�
/ return: �Ƿ񱣴�ɹ�
**********************************/
bool BitMap::save(const char *fileName) {
	FILE* f = fopen(fileName, "wb"); // ��������ļ�
	if (!f)
		return false;
	// ����Header����
	setFileHeader();
	setInfoHeader();
	// ������д���ļ�
	if (!writeFile(f))
		return false;
	fclose(f);
	return true;
}

/**********************************
/ ����λͼ
/ para ratio: ���ű���
/ return: ���ź��λͼ
**********************************/
BitMap BitMap::scale(const double ratio) {
	// �½�һ�����ź��λͼ, ����Ϊ��
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
			int x = j / ratio, y = i / ratio; // ԭͼ���Ӧ�ĵ�
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
/ ��ȡλ��
/ return: λͼλ��
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
	// ���ڱ� 8 λ��С��λ��һ�����ز���һ���ֽ�, ��������ȫչ���ֽ�, ��Ϊ�鷳, ���Բ������� ^_^
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
