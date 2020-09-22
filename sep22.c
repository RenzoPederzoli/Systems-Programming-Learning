// #include <stdio.h>
// #include <signal.h>
// //#include <unistd.h>
// #include <stdlib.h>

// void control_c(int x) {
//   printf("you typed control c\n");
// }

// void alarmclock(int x) {
//   printf("Alarm went off\n");
//   exit(0);
// }

// int main() {
//   int i;
//   signal(SIGINT, control_c);
//   signal(SIGALRM, alarmclock);
//   alarm(10);
//   for (i = 0; 1; i++) {
//     printf("%d", i);
//     fflush(stdout); //flushes everything in stdout buffer array
//     sleep(2);
//   }
// }

#include <stdlib.h>
//#include <dirent.h>
#include <stdio.h>

int main() {
  DIR * d = opendir(".");
  while(1) {
    struct stat * s;
    struct dirent * e = readdir(d);
    if (e == NULL)
      break;
    printf("found file %s\n", e ->d_name);
    s = stat(e->d_name); // stat gives some info about a file that you can print but it is not a struct stat
    // code online to see exact formatting
  }
  printf("end of dir\n");
  closedir(d);
}
