#include<cstdio>
#include<cstring>
#include<cstdlib> 
// ����ÿ���ַ�����
#define MAX_NUM 1024
using namespace std;
void generateBySecond(char* filename, int startIdx, int t);
void generateByStartEnd(char* filename, int startIdx, int start, int end);
int str2int(char* str);
void time2timeFormat(int milliseconds, char* ans);
void generateBySecond(char* filename, int startIdx, int t) {
    // �Ժ�����Ϊʱ���
    int timestamp = 0;
    char buf[MAX_NUM + 1];
    char bufAns[MAX_NUM * 2];

    FILE* fp = fopen(filename, "r");
    FILE* fpAns = fopen("result.srt", "w");
    if (fp == NULL) {
        printf("%s �ļ�������\n", filename);
        system("pause");
        exit(0);
    }
    if (fpAns == NULL) {
        printf("result.srt�ļ��޷�����\n");
        system("pause");
        exit(0);
    }
    char startStr[20], endStr[20];
    while (fgets(buf, MAX_NUM, fp)) {
        time2timeFormat(timestamp, startStr);
        time2timeFormat(timestamp + t * 1000, endStr);
        sprintf(bufAns, "%d\n%s --> %s\n%s\n", startIdx++, startStr, endStr, buf);
        fwrite(bufAns, sizeof(char), strlen(bufAns), fpAns);
        timestamp += t * 1000;
    }
    fclose(fp);
    fclose(fpAns);
}
void generateByStartEnd(char* filename, int startIdx, int start, int end) {
    // �Ժ�����Ϊʱ���
    int timestamp = start * 1000;
    char buf[MAX_NUM + 1];
    char bufAns[MAX_NUM * 2];

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("%s �ļ�������\n", filename);
        system("pause");
        exit(0);
    }
    // �ȿ�һ���ܹ��ж�����
    int lineCnt = 0;
    while (fgets(buf, MAX_NUM, fp)) {
        lineCnt++;
    }
    // �����������Ϳ���֪��ÿ����Ļ������ʱ����
    int step = (end - start) * 1000 / lineCnt;
    fclose(fp);

    fp = fopen(filename, "r");
    FILE* fpAns = fopen("result.srt", "w");
    if (fp == NULL) {
        printf("%s �ļ�������\n", filename);
        system("pause");
        exit(0);
    }
    if (fpAns == NULL) {
        printf("result.srt�ļ��޷�����\n");
        system("pause");
        exit(0);
    }
    char startStr[20], endStr[20];
    while (fgets(buf, MAX_NUM, fp)) {
        time2timeFormat(timestamp, startStr);
        time2timeFormat(timestamp + step, endStr);
        sprintf(bufAns, "%d\n%s --> %s\n%s\n", startIdx++, startStr, endStr, buf);
        fwrite(bufAns, sizeof(char), strlen(bufAns), fpAns);
        timestamp += step;
    }
    fclose(fp);
    fclose(fpAns);


}
int str2int(char* str) {
    int sum = 0, len = strlen(str);
    for (int i = 0; i < len; i++) {
        sum = sum * 10 + str[i] - '0';
    }
    return sum;
}
void time2timeFormat(int milliseconds, char* ans) {
    int h, m, s, mi;
    mi = milliseconds % 1000;
    s = milliseconds / 1000 % 60;
    m = milliseconds / 1000 / 60 % 60;
    h = milliseconds / 1000 / 60 / 60;
    sprintf(ans, "%d:%02d:%02d,%d", h, m, s, mi);
}
int main(int argc, char* argv[]) {
    if (argc == 1) {
        // Ĭ�� 5 ��һ����Ļʱ��,���±�Ϊ0��ʼ
        generateBySecond("subtitle.txt", 0, 5);
    }
    else if (argc == 3) {
        // �޶�ÿ t ��һ����Ļʱ��
        generateBySecond("subtitle.txt", str2int(argv[1]), str2int(argv[2]));
    }
    else if (argc == 4) {
        // ͨ���޶���ʼ�ͽ���ʱ�䣬ʹ����Ļƽ����ÿһ��ʱ����
        generateByStartEnd("subtitle.txt", str2int(argv[1]), str2int(argv[2]), str2int(argv[3]));
    }
    printf("ת�����\n");
    system("pause");
    return 0;
}