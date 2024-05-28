   #include "kernel/types.h"
    #include "kernel/stat.h"
    #include "user/user.h"
    #include "kernel/fs.h"
    char* get_name(char* path){//获取当前文件名
        char * p;
        for(p = path+strlen(path); p >= path && *p != '/'; p--);
        p++;
        return p;
    }
    void find(char *path, char* str){//类Unix系统中，目录被视为一种特殊类型的文件
        char buf[512];//存储路径
        struct dirent de;//目录结构体
        struct stat st;//文件结构体
        int fd = open(path, 0);//0表示以标准模式(读写模式)打开
        if(fd < 0){//打开失败
            fprintf(2, "find: cannot open %s\n", path);
        	return;
        }
        if(fstat(fd, &st) < 0){//通过文件描述符将对应的文件信息放入文件结构体stat中,若失败则返回-1
            fprintf(2, "find: cannot stat %s\n", path);
        	close(fd);
        	return;
        }
        switch(st.type){//判定打开类型
        	case T_DEVICE://判定为设备文件
        	case T_FILE://判定为普通文件
        	    if(!strcmp(str, get_name(path)))
        	        printf("%s\n",path);
        	    break;
        	case T_DIR://判定为目录
        	    strcpy(buf, path);
        	    char *p = buf + strlen(buf);
        	    *p = '/';
        	    p++;
        	    while(read(fd, &de, sizeof de) == sizeof de){//使用read从目录文件中读取目录条目，处理目录中文件
        	    	if(de.inum == 0)//该目录条目为空或未使用
        	    	    continue;
        	    	memmove(p, de.name, DIRSIZ);
        	    	p[DIRSIZ] = 0;
        	    	if(stat(buf, &st) < 0){//通过文件路径将对应的文件信息放入文件结构体stat中，若失败则返回-1
            	    printf("ls: cannot stat %s\n", buf);
            	    continue;
        	    	}
        	    	if(st.type == T_DEVICE || st.type == T_FILE){//判断为非目录文件
        	    	    if(!strcmp(str, get_name(buf)))
        	                printf("%s\n",buf);
        	    	}
        	    	else if(st.type == T_DIR && strcmp(".", get_name(buf)) && strcmp("..", get_name(buf)))//判定为子目录，递归处理，注意不要重复进入本目录以及父目录
        	    	    find(buf, str);
        	    }
        	    break;
        }
        close(fd);
        return;
    }
    int main(int argc, char *argv[]){
        if(argc == 3)
    	find(argv[1], argv[2]);
        else
        	printf("argument error\n");
        exit(0);
    }

