#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
  pid_t child_id;
  int status;

  child_id = fork();

  if (child_id < 0) {
    exit(1);
  }

  if (child_id == 0) {
    char *argv[] = {"mkdir","/home/asus/modul2/indomie"};
    execv("/bin/mkdir", argv);
  } else {
    while ((wait(&status)) > 0);
    sleep(5);
    if(fork()==0)
    {
      char *argv[] = {"mkdir","/home/asus/modul2/sedaap"};
      execv("/bin/mkdir", argv);
    }
    if(fork()==0)
    {
      char *argv[] = {"unzip","/home/asus/modul2/jpg.zip", NULL};
      execv("/usr/bin/unzip", argv);
    }
    else
    {
      while ((wait(&status)) > 0);
      if(fork()==0)
      {
        char *argv[] = {"find", "/home/asus/modul2/jpg/.", "-maxdepth", "1", "-type", "d", "-exec", "mv", "{}", "/home/asus/modul2/indomie", ";", NULL};
        execv("/usr/bin/find", argv);
      }
      else
      {
        while ((wait(&status)) > 0);
        if(fork()==0)
        {
          char *argv[] = {"find", "/home/asus/modul2/jpg/.", "-maxdepth", "1", "-type", "f", "-exec", "mv", "{}", "/home/asus/modul2/sedaap", ";", NULL};
          execv("/usr/bin/find", argv);
        }
        else
        {
          if(fork()==0)
          {
            char *argv[] = {"find", "/home/asus/modul2/indomie/.", "-mindepth", "1", "-type", "d", "-exec", "touch", "{}/coba1.txt", ";", NULL};
            execv("/usr/bin/find", argv);
          }
          else
          {
            while ((wait(&status)) > 0);
            sleep(3);
            char *argv[] = {"find", "/home/asus/modul2/indomie/.", "-mindepth", "1", "-type", "d", "-exec", "touch", "{}/coba2.txt", ";", NULL};
            execv("/usr/bin/find", argv);
          }
        }
      }
    }
  }
}
