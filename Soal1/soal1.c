#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>




int main (int argc, char *argv[]){
pid_t pid, sid;
pid = fork();
if (pid < 0)exit(EXIT_FAILURE);
if (pid > 0) exit(EXIT_SUCCESS);
umask(0);
sid = setsid();
if (sid < 0) exit(EXIT_FAILURE);
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);

time_t waktu = time(NULL);
struct tm currentTime = *localtime(&waktu);
int detik, menit, jam;
if(*argv[1]=='*')detik = -1;
detik = atoi(argv[1]);
if(*argv[2]=='*')menit = -1;
menit = atoi(argv[2]);
if(*argv[3]=='*')jam = -1;
jam = atoi(argv[3]);

if (argc < 5 || argc > 5){
printf("argumen harus 4\n");
exit(EXIT_FAILURE);
}

if (jam < -1 || jam > 23 || menit < -1 || menit > 59 || detik < -1 || detik > 59) {
printf("waktu hatus tepat");
exit(EXIT_FAILURE);
}
while (1){
waktu = time(NULL);
struct tm currentTime = *localtime(&waktu);
if ((currentTime.tm_hour == jam || jam == -1) && (currentTime.tm_min == menit || menit == -1) && (currentTime.tm_sec == detik || detik == -1)) {
if (fork()==0) execl("/bin/bash", "bash", argv[argc-1], NULL);
}
sleep(1);
}
}