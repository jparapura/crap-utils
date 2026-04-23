#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

void print_entry(const char *type, const char *text) {
  printf("%s\t%s\n", type, text);
}

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
      print_entry("-", entry->d_name);
      break;
    case S_IFDIR:
      print_entry("d", entry->d_name);
      break;
    default:
      print_entry("unknown type", "unknown name");
      break;
    }
  }

  closedir(dir);

  return 0;
}
