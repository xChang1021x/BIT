#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <utime.h>
#include <sys/time.h>
#include <fcntl.h>

#define MAXN 1024

void SyncInfo(char* source,char* dest)//同步文件属性
{
	struct stat statbuf;   //stat结构
	struct utimbuf timeby; //文件时间结构
	stat(source, &statbuf); //获取文件属性
	timeby.actime = statbuf.st_atime;  //修改时间属性，存取时间
	timeby.modtime = statbuf.st_mtime; //修改时间
	utime(dest, &timeby);
}

void SyncSoftLink(char* source,char* dest)//同步软链接
{
	//同步软链接信息
	struct stat statbuf;
	lstat(source, &statbuf);
	struct timeval ftime[2];
	ftime[0].tv_usec = 0;
	ftime[0].tv_sec = statbuf.st_atime;
	ftime[1].tv_usec = 0;
	ftime[1].tv_sec = statbuf.st_mtime;
	lutimes(dest, ftime);
}

int Parse(int argc, char *argv[]) // 检测输入与目标文件是否有误
{
	//判断参数出错
	if (argc != 3)
	{
		printf("非法参数\n");
		printf("请规范格式: ./mycp.exe <path> <path> \n");
		return -1;
	}
	//判断源是否存在
	DIR *dir=opendir(argv[1]);
	int file=open(argv[1],O_RDONLY);
	if(dir==NULL&&file==-1)//打开失败
	{
		printf("未知路径\n");
		close(file);
		closedir(dir);
		return -1;
	}
	//源文件存在，判断类型
	struct stat statbuf;
	lstat(argv[1], &statbuf);
	if (S_IFREG & statbuf.st_mode)//标准文件
	{
		close(file);
		closedir(dir);
		return 1;
	}
	else//目录
	{
		if ((dir = opendir(argv[2])) == NULL)//保证目标目录存在
		{
			mkdir(argv[2], statbuf.st_mode);
			printf("创建%s目录\n",argv[2]);
		}
		close(file);
		closedir(dir);
		return 0;
	}
}

void CopySoftLink(char *source, char *dest) //复制软链接
{
	//复制软链接
    char buffer[2 * MAXN];
    char oldpath[MAXN];
    getcwd(oldpath, sizeof(oldpath));
    strcat(oldpath, "/");
    memset(buffer, 0, sizeof(buffer));
    readlink(source, buffer, 2 * MAXN);//读取软链接到buffer
    symlink(buffer, dest);//将软链接赋给dest
}

void CopyFile(char *source, char *target) // 直接复制
{
    //打开与创建文件
	struct stat statbuf;
    stat(source, &statbuf);
	int fd_source = open(source, 0); //打开文件，文件描述符
    int fd_target = creat(target, statbuf.st_mode); //创建新文件,返回文件描述符
	
	//利用缓冲区传输文件
	char BUFFER[MAXN]; //缓冲区
	int wordbit; //记录读取的字节数
    while ((wordbit = read(fd_source, BUFFER, MAXN)) > 0)//循环读取，直到文件读完
    {
        //写入目标文件
        if (write(fd_target, BUFFER, wordbit) != wordbit)
        {
            printf("写入过程发生错误!\n");
            exit(-1);
        }
    }

	//关闭文件
    close(fd_source); 
    close(fd_target);
}

void CopyDir(char *source, char *dest) // 将源目录信息复制到目标目录下
{
    char source_path[MAXN / 2];//两个path是临时路径，用于构造各种路径。
    char dest_path[MAXN / 2];
	
    //打开源目录
    DIR *dir;
	if (NULL == (dir = opendir(source)))//打开目录,返回指向DIR结构的指针
	{
		printf("打开源文件夹错误\n");
		exit(-1);
	}

	//递归复制目录
	memset(dest_path,0,sizeof(dest_path));
    strcpy(dest_path, dest);
    strcat(dest_path, "/"); 
	struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)//遍历源目录
    {
		//根据类型进行处理
        if (entry->d_type == 4) // 目录文件
        {
			//跳过.和..两个特殊目录
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
			//正常目录，构造路径
            memset(source_path, 0, sizeof(source_path));
            strcpy(source_path, source);
            strcat(source_path, "/");
            strcat(source_path, entry->d_name);
			memset(dest_path,0,sizeof(dest_path));
			strcpy(dest_path, dest);
			strcat(dest_path, "/");
            strcat(dest_path, entry->d_name);
			//创建目录
			struct stat statbuf;
            stat(source_path, &statbuf);         //统计文件属性信息
            mkdir(dest_path, statbuf.st_mode); //创建目标目录
			//递归调用
            CopyDir(source_path, dest_path);
			//同步信息
            SyncInfo(source_path,dest_path);
        }
        else if (entry->d_type == 10) // 软链接文件
        {
			//构造路径
            memset(source_path, 0, sizeof(source_path));
			strcpy(source_path, source);
			strcat(source_path, "/");
			strcat(source_path, entry->d_name);
			memset(dest_path,0,sizeof(dest_path));
			strcpy(dest_path, dest);
			strcat(dest_path, "/");
			strcat(dest_path, entry->d_name);
			//复制软链接
            CopySoftLink(source_path, dest_path);
			//同步信息，使用软链接的同步函数
			SyncSoftLink(source_path,dest_path);
        }
        else // 普通文件
        {
            //构造路径
			memset(source_path, 0, sizeof(source_path));
			strcpy(source_path, source);
			strcat(source_path, "/");
			strcat(source_path, entry->d_name);
			memset(dest_path,0,sizeof(dest_path));
			strcpy(dest_path, dest);
			strcat(dest_path, "/");
			strcat(dest_path, entry->d_name);
			//复制软链接
			CopyFile(source_path, dest_path);
			//同步信息
			SyncInfo(source_path,dest_path);
        }
    }
    closedir(dir);
}


int main(int argc, char *argv[])
{
	int copy_stat=Parse(argc, argv);
    if(copy_stat==-1)//异常
	{
		return -1;
	}
	else if(copy_stat==1)//标准文件
	{
		CopyFile(argv[1],argv[2]);
		SyncInfo(argv[1],argv[2]);
		printf("文件复制完毕\n");
		
		return 1;
	}
	else if(copy_stat==0)//目录
	{
		CopyDir(argv[1], argv[2]); //开始复制
		SyncInfo(argv[1],argv[2]); //同步信息
		printf("目录复制完毕\n");
		
		return 0;
	}
        
    return 0;    
}
