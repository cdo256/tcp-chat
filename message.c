#include "socket.h"
#include "util.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

#define SCRATCH_LENGTH 256

static char scratch_buffer[SCRATCH_LENGTH];

int send_format(SOCKET socket, char *fmt, ...) {
  va_list va;
  va_start(va, fmt);
  int length = vsnprintf(scratch_buffer, SCRATCH_LENGTH, fmt, va);
  if (length < 0 || length >= SCRATCH_LENGTH) {
    eprintf("vsnprintf returned %d\n", length);
    return -1;
  }
  scratch_buffer[length] = '\0';
  send_string(socket, scratch_buffer);
}

int send_identify(SOCKET socket, char *username) {
  return send_format(socket, "/identify %s", username);
}