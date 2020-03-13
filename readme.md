# SoalShiftSISOP20_modul2_D05
## Kelompok B02
* 05111840000085 - Imanuel Banifernando Simatupang 
* 05111840000098 - Patrick Cipta Winata
### 1. Soal Nomor 1 
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:
a. Program menerima 4 argumen berupa:
i. Detik: 0-59 atau * (any value)
ii. Menit: 0-59 atau * (any value)
iii. Jam: 0-23 atau * (any value)
iv. Path file .sh

b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai

c. Program hanya menerima 1 config cron

d. Program berjalan di background (daemon)

e. Tidak boleh menggunakan fungsi system()

### Jawaban

a. Program menerima 4 argumen berupa: i. Detik: 0-59 atau * (any value) ii. Menit: 0-59 atau * (any value) iii. Jam: 0-23 atau * (any value) iv. Path file .sh

b.Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai :
```if (argc < 5 || argc > 5){
printf("argumen harus 4\n");
exit(EXIT_FAILURE);
}
if (jam < -1 || jam > 23 || menit < -1 || menit > 59 || detik < -1 || detik > 59) {
printf("waktu hatus tepat");
exit(EXIT_FAILURE);
```
c. Program hanya menerima 1 config cron dimana program kami hanya menerima satu config cron dimana kami hanya membuat kurang dari 5 argumen

d. Program daemon
```
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
```
e. Tidak boleh menggunakan fungsi system()


### Soal Nomor 3
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).

a. Program buatan jaya harus bisa membuat dua direktori di
“/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.

b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori
“/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak
hanya itu tugasnya.

c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di
dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan
pengelompokan, semua file harus dipindahkan ke
“/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke
“/home/[USER]/modul2/indomie/”.

d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/”
harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu
3 detik kemudian membuat file bernama “coba2.txt”.

### Jawaban

a. ```
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
    ```
Setelah membuat child, program menyuruh child untuk membuat directory yang baru bernama indomie. Program akan membuat child lagi untuk membuat directory sedaap ketika parent sudah selesai menunggu proses sebelumnya berjalan (selama 5 detik)

b.  ```
 if(fork()==0)
    {
      char *argv[] = {"unzip","/home/asus/modul2/jpg.zip", NULL};
      execv("/usr/bin/unzip", argv);
    }
    ```

Program lalu membuat child baru lagi untuk ekstrak file zip yang ada dengan cara mengeksekusi fungsi unzip.

c. ```
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
        ```
Program memindahkan file yang bertipe direktori (d) ke direktori sedaap yang sudah dibuat sebelumnya dengan fungsi find dengan kedalaman folder yang dicari sebanyak 1. 
Program memindahkan file yang bertipe file (f) ke direktori indomie yang sudah dibuat sebelumnya dengan fungsi find dengan kedalaman folder yang dicari sebanyak 1.

d.  ```
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
    ```
 Membuat file kosong bernama coba1.txt dan coba2.txt dengan selang waktu 3 detik ke direktori yang dipindah ke indomie.
