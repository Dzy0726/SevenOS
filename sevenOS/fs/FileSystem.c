/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            FileSystem.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Dong Zhenyu, 2020
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

#define NULL ((void*)0)

/*****************************************************************************
 *                                文件系统
 *****************************************************************************/
#define MAX_FILE_PER_LAYER 10
#define MAX_FILE_NAME_LENGTH 20
#define MAX_CONTENT_ 50
#define MAX_FILE_NUM 100


/*********************************文件块结构体*********************************/
struct fileBlock 
{
    int fileID;//文件编号
    char fileName[MAX_FILE_NAME_LENGTH];//文件名称
    int fileType; //文件类型，0是文本文件，1是文件夹
    char content[MAX_CONTENT_];//文本文件的内容
    int fatherID;//父级文件的ID
    int childrenNumber;//每一层的文件数目（最多10个）
    int children[MAX_FILE_PER_LAYER];//每一层的文件
};

struct fileBlock files[MAX_FILE_NUM];
int IDLog[MAX_FILE_NUM];
int fileIDCount = 0; //记录文件数目
int currentFileID = 0;//当前使用的文件的编号


/*********************************文件系统初始化*********************************/
void FSInit() 
{

    for (int i = 0; i < MAX_FILE_NUM; i++) 
    {
        files[i].childrenNumber = 0;
        files[i].fileID = -2;// -2 表示不存在
        IDLog[i] = '\0';
    }
    //初始化第一个文件
    IDLog[0] = 1;
    files[0].fileID = 0; //表示开始
    strcpy(files[0].fileName, "root");
    strcpy(files[0].content, "welcome to use file system!");
    files[0].fileType = 2;//2此处表示根目录
    files[0].fatherID = 0;
    files[0].childrenNumber = 0;
    currentFileID = 0;
    fileIDCount = 1;
}


/*********************************文件系统命令集*********************************/
void FSCommand() {
    printf("      ====================================================================\n");
    printf("      #                        Welcome to sevenOS              ******    #\n");
    printf("      #                            File Manager                **        #\n");
    printf("      #                                                        ******    #\n");
    printf("      #         [COMMAND]                 [FUNCTION]           **        #\n");
    printf("      #                                                        **        #\n");
    printf("      #     $ create [filename] |   create a new .txt file               #\n");
    printf("      #     $ mkdir [dirname]   |   create a new folder                  #\n");
    printf("      #     $ ls                |   list the elements in this level      #\n");
    printf("      #     $ cd [dirname]      |   switch work path to this directory   #\n");
    printf("      #     $ cd ..             |   return to the superior directory     #\n");
    printf("      #     $ rm [name]         |   delete a file or directory           #\n");
    printf("      #     $ help              |   show command list of this system     #\n");
    printf("      #     $ read [filename]   |   show the file's content              #\n");
    printf("      #     $ edit [filename]   |   edit the file's content              #\n");
    printf("      #  -> $ save              |   save all changes on the hard disk    #\n");
    printf("      #     $ quit              |   quit the file manager                #\n");
    printf("      #                        Powered by Group7                         #\n");
    printf("      #                       ALL RIGHT REVERSED                         #\n");
    printf("      ====================================================================\n");

    printf("\n\n");
}


/********************************初始化文件块********************************/
void initFileBlock(int fileID, char* fileName, int fileType) 
{
    files[fileID].fileID = fileID;
    strcpy(files[fileID].fileName, fileName);
    files[fileID].fileType = fileType;
    files[fileID].fatherID = currentFileID;
    files[fileID].childrenNumber = 0;
}


/********************************int转string********************************/
void toString(char* temp, int i) 
{
    if (i / 100 < 0)
        temp[0] = (char)48;
    else
        temp[0] = (char)(i / 100 + 48);
    if ((i % 100) / 10 < 0)
        temp[1] = '0';
    else
        temp[1] = (char)((i % 100) / 10 + 48);
    temp[2] = (char)(i % 10 + 48);
}


/********************************写出到硬盘的虚拟文件********************************/
void WriteDisk(int len)
{
    char temp[MAX_FILE_NUM * 150 + 103];
    int i = 0;
    temp[i] = '^';
    i++;
    toString(temp + i, fileIDCount);
    i = i + 3;
    temp[i] = '^';
    i++;
    for (int j = 0; j < MAX_FILE_NUM; j++) 
    {
        if (IDLog[j] == 1) 
        {
            toString(temp + i, files[j].fileID);
            i = i + 3;
            temp[i] = '^';
            i++;
            for (int h = 0; h < strlen(files[j].fileName); h++) 
            {
                temp[i + h] = files[j].fileName[h];
                if (files[j].fileName[h] == '^')
                {
                    temp[i + h] = (char)1;
                }
            }
            i = i + strlen(files[j].fileName);
            temp[i] = '^';
            i++;
            temp[i] = (char)(files[j].fileType + 48);
            i++;
            temp[i] = '^';
            i++;
            for (int h = 0; h < strlen(files[j].content); h++) 
            {
                temp[i + h] = files[j].content[h];
                if (files[j].content[h] == '^')
                {
                    temp[i + h] = (char)1;
                }
            }
            i = i + strlen(files[j].content);
            temp[i] = '^';
            i++;
            toString(temp + i, files[j].fatherID);
            i = i + 3;
            temp[i] = '^';
            i++;
            for (int m = 0; m < MAX_FILE_PER_LAYER; m++) 
            {
                toString(temp + i, files[j].children[m]);
                i = i + 3;
            }
            temp[i] = '^';
            i++;
            toString(temp + i, files[j].childrenNumber);
            i = i + 3;
            temp[i] = '^';
            i++;
        }
    }
    int fd = 0;
    int length = 0;
    fd = open("ss", O_RDWR);
    assert(fd != -1);
    length = write(fd, temp, strlen(temp));
    assert(length == strlen(temp));
    close(fd);
}


/********************************字符转int********************************/
int toInt(char* temp) 
{
    int result = 0;
    for (int i = 0; i < 3; i++)
    {
        result = result * 10 + (int)temp[i] - 48;
    }
    return result;
}


/********************************读取硬盘的虚拟文件********************************/
int ReadDisk() 
{
    char readbuf[1000];//读入内容的缓冲区
    int fd = 0;// file descriptor文件描述符 
    int length = 0;
    fd = open("ss", O_RDWR);//可读可写
    assert(fd != -1);
    length = read(fd, readbuf, 1000);//读fd指的内容到readbuf中，最多读1000bytes
    assert(length == 1000);
    readbuf[length] = 0;
    int r = 1;
    fileIDCount = toInt(readbuf + r);
    r = r + 4;
    for (int i = 0; i < fileIDCount; i++) 
    {
        int ID = toInt(readbuf + r);
        IDLog[ID] = 1;
        files[ID].fileID = ID;
        r = r + 4;
        for (int i = 0; i < MAX_FILE_NAME_LENGTH; i++) 
        {
            if (readbuf[r] == '^')
                break;
            else if (readbuf[r] == (char)1)
                files[ID].fileName[i] = '^';
            else
                files[ID].fileName[i] = readbuf[r];
            r++;
        }
        r++;
        files[ID].fileType = (int)readbuf[r] - 48;
        r = r + 2;
        for (int j = 0; j < MAX_CONTENT_; j++) 
        {
            if (readbuf[r] == '^')
                break;
            else if (readbuf[r] == (char)1)
                files[ID].content[j] = '^';
            else
                files[ID].content[j] = readbuf[r];
            r++;
        }
        r++;
        files[ID].fatherID = toInt(readbuf + r);
        r = r + 4;
        for (int j = 0; j < MAX_FILE_PER_LAYER; j++) 
        {
            files[ID].children[j] = toInt(readbuf + r);
            r = r + 3;
        }
        r++;
        files[ID].childrenNumber = toInt(readbuf + r);
        r = r + 4;
    }
    return length;
}


/********************************创建文件********************************/
int createFile(char* fileName, int fileType)
{
    if (files[currentFileID].childrenNumber == MAX_FILE_PER_LAYER)
    {
        printf("Sorry you cannot add more files in this layer.\n");
        return 0;
    }
    else 
    {
        for (int i = 0; i < files[currentFileID].childrenNumber; i++) 
        {
            if (strcmp(files[files[currentFileID].children[i]].fileName, fileName) == 0) 
            {
                if (fileType) 
                {
                    printf("You have a folder of same name!\n");
                }
                else 
                {
                    printf("You have a file of same name!\n");
                }
                return 0;
            }
        }
        fileIDCount++;
        int target = 0;
        for (int i = 0; i < MAX_FILE_NUM; i++) 
        {
            if (IDLog[i] == 0) 
            {
                target = i;
                break;
            }
        }
        initFileBlock(target, fileName, fileType);
        files[currentFileID].children[files[currentFileID].childrenNumber] = target;
        files[currentFileID].childrenNumber++;
        if (fileType) 
        {
            printf("Create directory %s successful!\n", fileName);
        }
        else 
        {
            printf("Create file %s successful!\n", fileName);
        }
        IDLog[target] = 1;
        return 1;
    }
}


/********************************显示当前目录全部文件********************************/
void showFile() 
{
    printf("The elements in %s.\n", files[currentFileID].fileName);        //通过currentFileID获取当前路径s
    printf("-----------------------------------------\n");
    printf("  filename |    type   | id  \n");
    for (int i = 0; i < files[currentFileID].childrenNumber; i++) 
    {    //遍历每个孩子
        printf("%10s", files[files[currentFileID].children[i]].fileName);
        if (files[files[currentFileID].children[i]].fileType == 0) 
        {
            printf(" | .txt file |");
        }
        else 
        {
            printf(" |   folder  |");
        }
        printf("%3d\n", files[files[currentFileID].children[i]].fileID);
    }
    printf("-----------------------------------------\n");
}


/********************************查找文件********************************/
int searchFile(char* name) 
{
    for (int i = 0; i < files[currentFileID].childrenNumber; i++) 
    {
        if (strcmp(name, files[files[currentFileID].children[i]].fileName) == 0) 
        {
            return files[currentFileID].children[i];
        }
    }
    return -2;
}


/********************************返回上一层********************************/
void returnFile(int ID) 
{
    currentFileID = files[ID].fatherID;
}


/********************************删除文件********************************/
void deleteFile(int ID) 
{
    if (files[ID].childrenNumber > 0) 
    {
        for (int i = 0; i < files[ID].childrenNumber; i++) 
        {
            deleteFile(files[files[ID].children[i]].fileID);
        }
    }
    IDLog[ID] = 0;
    files[ID].fileID = -2;
    files[ID].childrenNumber = 0;
    for (int i = 0; i < MAX_CONTENT_; i++)
    {
        files[ID].content[i] = '\0';
    }
    for (int i = 0; i < MAX_FILE_NAME_LENGTH; i++)
    {
        files[ID].fileName[i] = '\0';
    }
    files[ID].fileType = -1;
    for (int i = 0; i < MAX_FILE_PER_LAYER; i++)
    {
        files[ID].children[i] = -1;
    }
    files[ID].fatherID = -2;
    fileIDCount--;
}


/********************************文件系统管理********************************/
void FSManage(int fd_stdin) 
{
    char readbuf[128];//读入用户输入
    char cmd[8];//命令
    char filename[120];
    char buf[1024];
    int m, n;
    char _name[MAX_FILE_NAME_LENGTH];
    FSInit();
    int len = ReadDisk();
    FSCommand();

    while (1) 
    {
        for (int i = 0; i <= 127; i++)
        {
            readbuf[i] = '\0';
        }
        for (int i = 0; i < MAX_FILE_NAME_LENGTH; i++)
        {
            _name[i] = '\0';
        }
        printf("\n/%s:", files[currentFileID].fileName);

        int r = read(fd_stdin, readbuf, 70);
        readbuf[r] = 0;
        assert(fd_stdin == 0);

        char target[2];
        for (int i = 0; i <= 1 && i < r; i++) 
        {
            target[i] = readbuf[i];
        }
        if (readbuf[0] == 'c' && readbuf[1] == 'r' && readbuf[2] == 'e' 
            && readbuf[3] == 'a' && readbuf[4] == 't' && readbuf[5] == 'e') 
        {
            if (readbuf[6] != ' ') 
            {
                printf("You should add the filename, like \"create XXX\".\n");
                printf("Please input [help] to know more.\n");
                continue;
            }
            for (int i = 0; i < MAX_FILE_NAME_LENGTH && i < r - 3; i++) 
            {
                _name[i] = readbuf[i + 7];
            }
            createFile(_name, 0);
        }
        else if (readbuf[0] == 'm' && readbuf[1] == 'k' && readbuf[2] == 'd' 
                && readbuf[3] == 'i' && readbuf[4] == 'r') 
        {
            if (readbuf[5] != ' ') 
            {
                printf("You should add the dirname, like \"mkdir XXX\".\n");
                printf("Please input [help] to know more.\n");
                continue;
            }
            char N[MAX_FILE_NAME_LENGTH];
            for (int i = 0; i < MAX_FILE_NAME_LENGTH && i < r - 3; i++) 
            {
                _name[i] = readbuf[i + 6];
            }
            createFile(_name, 1);
        }
        else if(readbuf[0] == 'r' && readbuf[1] == 'e' && readbuf[2] == 'a' && readbuf[3] == 'd')
        {
            if(readbuf[4] != ' ')
            {
                printf("You should add the filename, like \"read XXX\".\n");
                printf("Please input [help] to know more.\n");
                continue;   
            }
            for (int i = 0; i < MAX_FILE_NAME_LENGTH && i < r - 3; i++)
             {
                _name[i] = readbuf[i + 5];
            }
            int ID = searchFile(_name);
            if(ID >= 0)
            {
                if(files[ID].fileType == 1)
                {
                    printf("Cannot read a directory!\n");
                    printf("You can only use command [read] to read a .txt file.\n"); 
                }
                else
                {
                    printf("--------------------------------------------"
                     "\n%s\n--------------------------------------------\n", files[ID].content);
                }
            }
            else
            {
                printf("No such file!\n");
            }
        }
        else if(readbuf[0] == 'e' && readbuf[1] == 'd' && readbuf[2] == 'i' && readbuf[3] == 't')
        {
            if(readbuf[4] != ' ')
            {
                printf("You should add the filename, like \"edit XXX\".\n");
                printf("Please input [help] to know more.\n");
                continue;   
            }
            for (int i = 0; i < MAX_FILE_NAME_LENGTH && i < r - 3; i++) 
            {
                _name[i] = readbuf[i + 5];
            }
            int ID = searchFile(_name);
            if(ID >= 0)
            {
                if(files[ID].fileType == 1)
                {
                    printf("Cannot edit a directory!\n");
                    printf("You can only use command [edit] to edit a .txt file.\n"); 
                }
                else
                {
                    printf("Please input the text you want to write:\n");
                    int r = read(fd_stdin, files[ID].content, MAX_CONTENT_);
                    files[ID].content[r] = 0;
                }
            }
            else
            {
                printf("No such file!\n");
            }
        }
        else if (strcmp(readbuf, "ls") == 0) 
        {
            showFile();
        }
        else if (strcmp(target, "cd") == 0) 
        {
            if (readbuf[2] == ' ' && readbuf[3] == '.' && readbuf[4] == '.') 
            {
                returnFile(currentFileID);
                continue;
            }
            else if (readbuf[2] != ' ') 
            {
                printf("You should add the dirname, like \"cd XXX\".\n");
                printf("Please input [help] to know more.\n");

                continue;
            }
            for (int i = 0; i < MAX_FILE_NAME_LENGTH && i < r - 3; i++) 
            {
                _name[i] = readbuf[i + 3];
            }
            int ID = searchFile(_name);
            if (ID >= 0 && files[ID].fileType == 1) 
            {
                currentFileID = ID;
                continue;
            }
            else if(ID >=0 && files[ID].fileType == 0)
            {
                printf("Cannot [cd] a text file!\n");
                printf("You can only use command [cd] to enter the directory.\n");
            }
            else
            {
                printf("No such directory!\n");
            }
        }
        else if (strcmp(target, "rm") == 0) 
        {
            if (readbuf[2] != ' ') 
            {
                printf("You should add the filename or dirname, like \"rm XXX\".\n");
                printf("Please input [help] to know more.\n");
                continue;
            }
            for (int i = 0; i < MAX_FILE_NAME_LENGTH && i < r - 3; i++)
            {
                _name[i] = readbuf[i + 3];
            }
            int ID = searchFile(_name);
            if (ID >= 0) 
            {
                printf("Delete <%s> successfully!\n",_name);
                deleteFile(ID);
                for (int i = 0; i < files[currentFileID].childrenNumber; i++) 
                {
                    if (ID == files[currentFileID].children[i]) 
                    {
                        for (int j = i + 1; j < files[currentFileID].childrenNumber; j++) 
                        {
                            files[currentFileID].children[i] = files[currentFileID].children[j];
                        }
                        files[currentFileID].childrenNumber--;
                        break;
                    }
                }
            }
            else
            {
                printf("No such file!\n");
            }
        }
        else if (strcmp(readbuf, "save") == 0)
        {
            WriteDisk(1000);
            printf("Save to disk successfully!\n");
        }
        else if (strcmp(readbuf, "help") == 0)
        {
            printf("\n");
            FSCommand();
        }
        else if (strcmp(readbuf, "quit") == 0) 
        {
            printf("Tip:\n");
            printf("    If you don't use [save],all changes will not be written to the hard disk.\n");
            printf("    Do you want to save changes? [y/n]\n");
            int r = read(fd_stdin, readbuf, 70);
            readbuf[r] = 0;
            if (strcmp(readbuf, "y") == 0) 
            {
                WriteDisk(1000);
                printf("Save to disk successfully!\n");
            }
            clear();
            commandList();
            break;
        }
        else if (!strcmp(readbuf, "clear")) 
        {
            clear();
        }
        else 
        {
            printf("Sorry, there no such command in the File Manager.\n");
            printf("You can input [help] to know more.\n");
        }
    }

}