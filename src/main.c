#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/common.h"
#include "../include/file.h"

void print_usage(char *argv[]) {
  printf("Usage: %s -n -f <database_file>\n", argv[0]);
  printf("\t -n - create new database file\n");
  printf("\t -f - (required) path to database file\n");
  return;
}

int main(int argc, char *argv[]) {
  char *filepath = NULL;
  bool newfile = false;
  int c;

  int database_fd = -1;

  while ((c = getopt(argc, argv, "nf:")) != -1) {
    switch (c) {
    case 'n':
      newfile = true;
      break;
    case 'f':
      filepath = optarg;
      break;
    case '?':
      printf("Unknown option -%c\n", c);
      break;
    default:
      return -1;
    }
  }

  if (filepath == NULL) {
    printf("Filepath is a required argument.\n");
    print_usage(argv);
  }

  if (newfile) {
    database_fd = create_db_file(filepath);
    if (database_fd == STATUS_ERROR) {
      printf("Unable to create database file.\n");
      return STATUS_ERROR;
    }
  } else {
    database_fd = open_db_file(filepath);
    if (database_fd == STATUS_ERROR) {
      printf("Unable to open database file.\n");
      return STATUS_ERROR;
    }
  }

  printf("Newfile: %d\n", newfile);
  printf("Filepath: %s\n", filepath);

  return 0;
}

/*
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
*/
