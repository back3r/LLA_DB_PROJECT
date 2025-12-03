#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/common.h"
#include "../include/file.h"

int create_db_file(char *filename) {

  int fd = open(filename, O_RDWR);

  if (fd != STATUS_ERROR) {
    close(fd);
    printf("File already exists.\n");
    return STATUS_ERROR;
  }

  fd = open(filename, O_RDWR | O_CREAT, 0644);

  if (fd == STATUS_ERROR) {
    perror("open");
    return STATUS_ERROR;
  }

  return fd;
}

int open_db_file(char *filename) {
  int fd = open(filename, O_RDWR);
  if (fd == STATUS_ERROR) {
    perror("open");
    return STATUS_ERROR;
  }
  return fd;
}
