#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
struct arg_struct{
    char* arg1=(char*)"/";
    char* arg2;
    int thread_count;
};

int fileIsFound=0;
char findfile(const char* dirname, const char* key, int thread_count){
    while(fileIsFound==0){
        DIR *dir=opendir(dirname);
        if (dir==NULL){
            return 0;
        }
        struct dirent *entry;
        entry=readdir(dir);
        while(entry!=NULL){
            //printf("Thread%d %hhd %s\n",thread_count,entry->d_type,entry->d_name);
            char path[1024]={ 0 };
            strcat(path, dirname);
            if(strcmp(entry->d_name, key)==0){
                strcat(path, "/");
                strcat(path,key);
                printf("Thread %d - FILE FOUND! %s\n",thread_count, path);
                fileIsFound=1;
                return 0;
            }
            if(entry->d_type==DT_DIR && strcmp(entry->d_name, ".") !=0 && strcmp(entry->d_name, "..") !=0 ){
                if(dirname=="/"){}
                else{
                    strcat(path, "/");
                }
                strcat(path,entry->d_name);
                char a=findfile(path,key, thread_count);
                if(a==1){
                    return 0;
                }
            }
            entry=readdir(dir);
        }
        closedir(dir);
        return 0;
    }
    return 0;
}char arr[256][256];

void *findfile_multithread(void *arguments){
    struct arg_struct *args = (arg_struct *)arguments;
    DIR *dir;
    struct dirent *entry;
    long int startdir[100];
    int it=0;
    dir = opendir("/");
    while ( (entry = readdir(dir)) != NULL) {
        startdir[it]=telldir(dir);
        strcpy(arr[it],entry->d_name);
        it+=1;
    };
    seekdir(dir, startdir[args->thread_count]);
    char c[100]="/";
    strcat(c,arr[args->thread_count]);
    if(strcmp(c,"/.")==0 || strcmp(c,"/..")==0){
        usleep(100);
    }
    findfile(c, args->arg2, args->thread_count);
    return 0;
}
void search(char toFind[]){
    struct arg_struct args;
    args.arg2=toFind;
    pthread_t threads[8];
    for(int i=0;i<8;i++){
        args.thread_count=i;
        if(pthread_create(&(threads[i]), NULL, &findfile_multithread, (void *)&args)!=0){
            printf("Thread %d created\n", i );
        }
        if(fileIsFound==1){
            break;}
        usleep(50);
    }
    for(int i=0;i<8;i++){
        pthread_join(threads[i],NULL);
    }
}