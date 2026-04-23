#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

void color_red() { printf("\033[1;31m"); }
void color_blue() { printf("\033[1;34m"); }
void color_reset() { printf("\033[0m"); }

void print_entry(void (*color)(), const char *type, const char *text) {
  color();
  printf("%s\t%s\n", type, text);
  color_reset();
}

void ls(const char *target_dir) {
  DIR *dir = opendir(target_dir);
  if (dir == NULL) {
    perror("opendir");
    return;
  }

  struct dirent *entry;
  struct stat buffer;
  char path[1024];

  while ((entry = readdir(dir))) {
    snprintf(path, sizeof(path), "%s/%s", target_dir, entry->d_name);

    int status = stat(path, &buffer);

    if (status == -1) {
      perror("stat");
      return;
    }

    switch (buffer.st_mode & S_IFMT) {
    case S_IFREG:
      print_entry(color_reset, "-", entry->d_name);
      break;
    case S_IFDIR:
      print_entry(color_blue, "d", entry->d_name);
      break;
    default:
      print_entry(color_red, "unknown type", "unknown name");
      break;
    }
  }

  closedir(dir);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    ls(".");
  } else {
    ls(argv[1]);
  }
  return 0;
}
