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
