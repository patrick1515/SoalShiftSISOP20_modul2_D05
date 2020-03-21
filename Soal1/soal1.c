#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

void run(char *str){ 
    char *script[] = {"bash", str, NULL};
    execv("/bin/bash", script); 
} 

int main(int argc, char *argv[]) {
    int jam, menit, detik;
    int jam_sekarang, menit_sekarang, detik_sekarang;
    if(argc < 5 || argc > 5){
        printf("Argumen yang dimasukkan harus 4\n");
        return 0;
    }
    if((strcmp(argv[1], "*")) == 0)detik = -2;
    else detik = atoi(argv[1]);
    if (detik == 0 && *argv[1] != '0'){ 
        printf("Argumen detik harus angka\n");
        return 0;
    }
    if((strcmp(argv[2], "*")) == 0)menit = -2;
    else menit = atoi(argv[2]);
    if (menit == 0 && *argv[2] != '0'){ 
        printf("Argumen menit harus angka\n");
        return 0;
    }
    if((strcmp(argv[3], "*")) == 0)jam = -2;
    else jam = atoi(argv[3]);
    if (jam == 0 && *argv[3] != '0'){ 
        printf("Argumen jam harus angka\n");
        return 0;
    }
    if(jam > 23 || jam < -1 || menit > 59 || menit < -1 || detik > 59 || detik < -1){
        printf("Range waktu harus benar\n");
        return 0;
    }
   
    char alamat[100];
    strncpy(alamat, argv[4], 99);
    alamat[100] = '\0';
    pid_t pid, sid;
    pid = fork();
    if (pid < 0)
      exit(EXIT_FAILURE);
    if (pid > 0) 
      exit(EXIT_SUCCESS);
    umask(0);
    sid = setsid();
    if (sid < 0)
      exit(EXIT_FAILURE);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1){
        time_t sekarang = time(NULL);
        struct tm *now_tm = localtime(&sekarang);
        detik_sekarang = now_tm->tm_sec;
        menit_sekarang = now_tm->tm_min;
        jam_sekarang = now_tm->tm_hour;
        if(jam_sekarang == jam || jam == -1)
            if(menit_sekarang == menit || menit == -1)
                if(detik_sekarang == detik || detik == -1){
                    pid_t child;
                    child = fork();
                    int status;
                    if (child == 0)
                        run(alamat); 
                    else 
                        while ((wait(&status)) > 0);
                }
        sleep(1);
    }
}
