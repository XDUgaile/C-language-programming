#include <cstdio>
#include <cstring>
#include <cstdlib>

const static int BUFFER_SIZE 	= 128 * 1024 * 1024;	// 缓存区大小128MB
const static int BLOCK_SIZE 	= 127;				// 块大小

unsigned char inbuf[BUFFER_SIZE], outbuf[BUFFER_SIZE];
int insize = 0, outsize = 0;

/****************************
/ 打开文件
/ para fileName: 文件名
/ return: 是否打开成功
****************************/
int load(const char *fileName) {
	FILE *f = fopen(fileName, "rb");
	if (!f)
		return 0;
	insize = fread(inbuf, sizeof(unsigned char), BUFFER_SIZE, f);
	if (!feof(f))
		return -1;
	fclose(f);
	return 1;
}

/****************************
/ 保存文件
/ para fileName: 文件名
/ return: 是否保存成功
****************************/
bool save(const char *fileName) {
	FILE *f = fopen(fileName, "wb");
	if (!f)
		return false;
	fwrite(outbuf, sizeof(unsigned char), outsize, f);
	return false;
}

/****************************
/ 输入数据
/ para buf: 数据存储区
/ para fsize: 当前大小
/ return: 是否输入成功
****************************/
bool push_back(unsigned char *buf, int &fsize, const unsigned char data) {
	if (fsize >= BUFFER_SIZE)
		return 0;
	buf[fsize++] = data;
	return 1;
}

/****************************
/ RLE压缩
/ return: 是否压缩成功
****************************/
bool compress() {
	int cur = 0;	// 当前位置
	while (cur < insize) {
		int r = cur;
		// 找到最远的相同连续段区间右端点, 区间长度不超过块大小
		while (r < insize - 1 &&
			   r - cur + 1 < BLOCK_SIZE &&
			   inbuf[r + 1] == inbuf[cur])
			r++;
		// 有相同的连续段
		if (r > cur) {
			unsigned char len = r - cur + 1;
			len |= 0x80;	// 打上标记, 并输入数据
			if (!push_back(outbuf, outsize, len))
				return false;
			if (!push_back(outbuf, outsize, inbuf[cur]))
				return false;
			cur = r + 1;
		}
		// 当前是最后一个点
		else if (cur == insize - 1) {
			if (!push_back(outbuf, outsize, 1))
				return false;
			if (!push_back(outbuf, outsize, inbuf[cur]))
				return false;
			cur++;
		}
		// 没有相同连续段
		else {
			// 找最远连续不相同区间右端点, 区间长度不超过块大小
			r = cur + 1;
			while (r < insize - 1 &&
					 r - cur + 1 < BLOCK_SIZE &&
					 inbuf[r] != inbuf[r + 1])
				r++;
			r -= (r < insize - 1);
			// 输入数据
			unsigned char len = r - cur + 1;
			if (!push_back(outbuf, outsize, len))
				return false;
			for(int i = cur; i <= r; i++)
				if (!push_back(outbuf, outsize, inbuf[i]))
					return false;
			cur = r + 1;
		}
	}
	return true;
}

/****************************
/ RLE解压
/ return: 是否解压成功
****************************/
bool decompress() {
	int cur = 0;	// 当前位置
	while (cur < insize) {
		unsigned char len = inbuf[cur++];
		// 具有连续相同段标记
		if (len & 0x80) {
			len ^= 0x80;	// 得到真实长度
			unsigned char c = inbuf[cur++];
			while (len--)
				if (!push_back(outbuf, outsize, c))
					return false;
		}
		// 没有连续相同段标记, 后续连续不相同
		else
			while (len--)
				if (!push_back(outbuf, outsize, inbuf[cur++]))
					return false;
	}
	return true;
}

int main(int argc, char *argv[]) {
	const char *operation = argv[2];
	const char *inputFile = argv[1];
	const char *outputFile = argv[3];

	int op = -1;
	if (!strcmp(operation, "-c"))
		op = 1;
	else if (!strcmp(operation, "-d"))
		op = 0;
	else {
		printf("ERROR: Unknown operation: \"%s\"\n", operation);
		exit(EXIT_FAILURE);
	}

	switch (load(inputFile)) {
		case 0: printf("ERROR: File \"%s\" Not Exists\n", inputFile); exit(EXIT_FAILURE);
		case -1: printf("ERROR: File \"%s\" Is Too Large\n", inputFile); exit(EXIT_FAILURE);
	}

	if (!(op ? compress() : decompress())) {
		printf("ERROR: %s Failed\n", op ? "Compressed" : "Decompressed");
		exit(EXIT_FAILURE);
	}

	if (save(outputFile)) {
		printf("ERROR: Can't Save To File \"%s\"\n", outputFile);
		exit(EXIT_FAILURE);
	}

	printf("%s Successfully!", op ? "Compressed" : "Decompressed");
	return 0;
}
