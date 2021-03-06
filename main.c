#include "main.h"

int main() {

  struct stat *foo = (struct stat *) malloc(sizeof(struct stat));

  char path[] = "main.h";
  if ( stat(path, foo) < 0 ) { //stat getting run here
    printf("\nERROR: %d - %s\n", errno, strerror(errno));
  } else {
    
    printf("\nFILE NAME: %s\n", path);

    //PRINTING THE SIZE
    float size = foo->st_size;

    char s[4][4]= {
      " B",
      " KB",
      " MB",
      " GB",
    };
    int i = 0;//counter for unit of size
    while(size / 1024 > 1) {
      size = size/1024;
      i++;
    }
    printf("FILE SIZE: %f%s\n",size,s[i]);

    //mode_t from sys/stat.h has a bunch of useful predefined vars for stuff
    printf("FILE PERMISSIONS: ");\
    printf( (foo->st_mode & S_IRUSR) ? "r" : "-");
    printf( (foo->st_mode & S_IWUSR) ? "w" : "-");
    printf( (foo->st_mode & S_IXUSR) ? "x" : "-");
    printf( (foo->st_mode & S_IRGRP) ? "r" : "-");
    printf( (foo->st_mode & S_IWGRP) ? "w" : "-");
    printf( (foo->st_mode & S_IXGRP) ? "x" : "-");
    printf( (foo->st_mode & S_IROTH) ? "r" : "-");
    printf( (foo->st_mode & S_IWOTH) ? "w" : "-");
    printf( (foo->st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    

    //converting epoch time (UNIX timestamp) to human-readable time
    //by using localtime() to conv timer to more convenient 'tm' struct
    time_t atime = foo->st_atime;
    struct tm timestamp = *localtime(&atime);
    
    size_t bufSize = 30;
    char *buf = (char *) malloc( sizeof(char) * bufSize );

    strftime(buf, bufSize, "%a %b %d %H:%M:%S %Y\n", &timestamp);
    printf("LAST TIME ACCESSED: %s\n", buf);

    free(buf);
   }

  free(foo);
  return 0;
}
