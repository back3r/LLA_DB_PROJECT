#include <fcntl.h>
#include <stdio.h>
// #include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
  unsigned short version;
  unsigned short employees;
  unsigned int filesize;
} database_header_t;

int main(int argc, char *argv[]) {

  database_header_t dbheader = {0};
  struct stat dbstat = {0};

  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 0;
  }

  int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
  if (fd == -1) {
    perror("open");
    return -1;
  }

  if (read(fd, &dbheader, sizeof(dbheader)) != sizeof(dbheader)) {
    perror("read");
    close(fd);
    return -1;
  };

  printf("DB Version: %u\n", dbheader.version);
  printf("DB Employees: %u\n", dbheader.employees);
  printf("DB File Length: %u\n", dbheader.filesize);

  if (fstat(fd, &dbstat) < 0) {
    perror("fstat");
    close(fd);
    return -1;
  }

  printf("DB File Length, reported by stat: %lu\n", dbstat.st_size);

  if (dbstat.st_size != dbheader.filesize) {
    printf("Get out of here hacker!\n");
    close(fd);
    return -2;
  }

  close(fd);

  return 0;
}
