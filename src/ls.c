#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

int main() {
  char *target_dir = ".";

  DIR *dir = opendir(target_dir);
  if (dir == NULL) {
    perror("ls");
    return 1;
  }

  struct dirent *entry;

  while ((entry = readdir(dir))) {
    struct stat buffer;
    int status = stat(entry->d_name, &buffer);
    if (status == -1) {
      perror("stat");
      return 1;
    }
    switch (buffer.st_mode & S_IFMT) {
    case S_IFREG:
      printf("%s\n", entry->d_name);
      break;
    default:
      printf("unknown\n");
      break;
    }
  }

  closedir(dir);

  return 0;
}
