#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE (16 * 1024)
#define IMG_SIZE (16 * 1024)
#define SPL_HEADER_SIZE 16
#define SPL_HEADER "S5PC110 HEADER  "

int main(int argc, char **argv)
{
    FILE *fp;
    char *Buf, *a;
    int BufLen;
    int nbytes, fileLen;
    unsigned int checksum, count;
    int i;
    // int count = 0;
    if (argc != 3)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return -1;
    }
    BufLen = BUFSIZE;
    Buf = (char *)malloc(BufLen);
    if (!Buf)
    {
        printf("分配失败\r\n");
        return -1;
    }
    memset(Buf, 0x00, BufLen);
    fp = fopen(argv[1], "rb"); // 打开源 bin
    if (fp == NULL)
    {
        printf("source file open fail\r\n");
        free(Buf);
        return -1;
    }
    // 获取bin长度
    fseek(fp, 0L, SEEK_END);
    fileLen = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    // 源bin长度不得超过16k-16byte
    count = (fileLen < (IMG_SIZE - SPL_HEADER_SIZE)) ? fileLen : (IMG_SIZE - SPL_HEADER_SIZE);
    memcpy(&Buf[0], SPL_HEADER, SPL_HEADER_SIZE);        // 放入头16bety信息
    nbytes = fread(Buf + SPL_HEADER_SIZE, 1, count, fp); // 将fp里面的 信息加载到 16bety的后面 一共加载长度是16k-16byte
    if (nbytes != count)
    {
        printf("Error reading nbytes\r\n");
        free(Buf);
        fclose(fp);
        return -1;
    }
    fclose(fp);
    // 计算校验和
    a = Buf + SPL_HEADER_SIZE; // 指向除前16byte以外的位置
    for (i = 0, checksum = 0; i < IMG_SIZE - SPL_HEADER_SIZE; i++)
    {
        checksum += (0x000000FF) & *a++;
    }
    a = Buf + 8;                     // a其实就是一个灵活指针了
    *((unsigned int *)a) = checksum; // 将校验和放到 buf的8~15位
    // 写到目的bin
    fp = fopen(argv[2], "wb");
    if (fp == NULL)
    {
        printf("创建文件失败\r\n");
        free(Buf);
        return -1;
    }
    a = Buf;
    nbytes = fwrite(a, 1, BufLen, fp);
    if (nbytes != BufLen)
    {
        printf("Error writing nbytes\r\n");
        free(Buf);
        fclose(fp);
        return -1;
    }
    free(Buf);
    fclose(fp);
    return 0;
}