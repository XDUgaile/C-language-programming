#include <cstdio>
#include <cstring>
#include <cstdlib>

const static int BUFFER_SIZE 	= 128 * 1024 * 1024;	// ��������С128MB
const static int BLOCK_SIZE 	= 127;				// ���С

unsigned char inbuf[BUFFER_SIZE], outbuf[BUFFER_SIZE];
int insize = 0, outsize = 0;

/****************************
/ ���ļ�
/ para fileName: �ļ���
/ return: �Ƿ�򿪳ɹ�
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
/ �����ļ�
/ para fileName: �ļ���
/ return: �Ƿ񱣴�ɹ�
****************************/
bool save(const char *fileName) {
	FILE *f = fopen(fileName, "wb");
	if (!f)
		return false;
	fwrite(outbuf, sizeof(unsigned char), outsize, f);
	return false;
}

/****************************
/ ��������
/ para buf: ���ݴ洢��
/ para fsize: ��ǰ��С
/ return: �Ƿ�����ɹ�
****************************/
bool push_back(unsigned char *buf, int &fsize, const unsigned char data) {
	if (fsize >= BUFFER_SIZE)
		return 0;
	buf[fsize++] = data;
	return 1;
}

/****************************
/ RLEѹ��
/ return: �Ƿ�ѹ���ɹ�
****************************/
bool compress() {
	int cur = 0;	// ��ǰλ��
	while (cur < insize) {
		int r = cur;
		// �ҵ���Զ����ͬ�����������Ҷ˵�, ���䳤�Ȳ��������С
		while (r < insize - 1 &&
			   r - cur + 1 < BLOCK_SIZE &&
			   inbuf[r + 1] == inbuf[cur])
			r++;
		// ����ͬ��������
		if (r > cur) {
			unsigned char len = r - cur + 1;
			len |= 0x80;	// ���ϱ��, ����������
			if (!push_back(outbuf, outsize, len))
				return false;
			if (!push_back(outbuf, outsize, inbuf[cur]))
				return false;
			cur = r + 1;
		}
		// ��ǰ�����һ����
		else if (cur == insize - 1) {
			if (!push_back(outbuf, outsize, 1))
				return false;
			if (!push_back(outbuf, outsize, inbuf[cur]))
				return false;
			cur++;
		}
		// û����ͬ������
		else {
			// ����Զ��������ͬ�����Ҷ˵�, ���䳤�Ȳ��������С
			r = cur + 1;
			while (r < insize - 1 &&
					 r - cur + 1 < BLOCK_SIZE &&
					 inbuf[r] != inbuf[r + 1])
				r++;
			r -= (r < insize - 1);
			// ��������
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
/ RLE��ѹ
/ return: �Ƿ��ѹ�ɹ�
****************************/
bool decompress() {
	int cur = 0;	// ��ǰλ��
	while (cur < insize) {
		unsigned char len = inbuf[cur++];
		// ����������ͬ�α��
		if (len & 0x80) {
			len ^= 0x80;	// �õ���ʵ����
			unsigned char c = inbuf[cur++];
			while (len--)
				if (!push_back(outbuf, outsize, c))
					return false;
		}
		// û��������ͬ�α��, ������������ͬ
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
