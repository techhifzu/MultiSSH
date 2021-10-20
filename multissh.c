/*
 * Multi SSH 0.3
 * Run commands on multiple SSH Servers easily.
 * Author: Hifzurrahman Patel (https://hifzu.tech)
 */
#define SSH_SERVERS_LIST "sshservers"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <libssh/libssh.h>
#include "functions.c"

extern int errno;

int main(int argc, char *argv[]) {

  FILE * ssh_fp;
  char *ssh_line = NULL;
  int error_number, rc, ssh_port, line_number;
  size_t ssh_line_len = 0;
  ssize_t ssh_line_read;
  char *ssh_server;
  char *string_ssh_port;
  char *ssh_username;
  char *ssh_password;
  ssh_session single_ssh_session;

// requires one argument
  if (argc != 2) {

    fprintf(stderr, "Usage: %s 'command(s)'\n", argv[0]);
    exit(EXIT_FAILURE);

  }

  ssh_fp = fopen(SSH_SERVERS_LIST, "r");

// check for ssh list file
   if (ssh_fp == NULL) {

      error_number = errno;
      fprintf(stderr, "Error opening SSH servers list '%s': %s\n", SSH_SERVERS_LIST, strerror(error_number));
      exit(EXIT_FAILURE);

    }

// read ssh list file
  while ((ssh_line_read = getline(&ssh_line, &ssh_line_len, ssh_fp)) != -1) {

      line_number = 1;

      ssh_server = strtok(ssh_line,":");
      string_ssh_port = strtok(NULL,":");
      ssh_username = strtok(NULL,":");
      ssh_password = strtok(NULL,":");

      ssh_port = atoi(string_ssh_port);

      if (strlen(ssh_line) > 512)
         fprintf(stderr, "Error with line %d, maximum length reached in %s, each line must be no more than 512 characters long.\n", line_number, SSH_SERVERS_LIST);

      if (!(valid_port(&ssh_port)))
         fprintf(stderr, "Error invalid port number %d in the file '%s', line %d.\n", ssh_port, SSH_SERVERS_LIST, line_number);

         single_ssh_session = ssh_new();

      if (single_ssh_session == NULL)
         fprintf(stderr, "Error creating new session.\n");

      ssh_options_set(single_ssh_session, SSH_OPTIONS_HOST, ssh_server);
      ssh_options_set(single_ssh_session, SSH_OPTIONS_PORT, &ssh_port);
      ssh_options_set(single_ssh_session, SSH_OPTIONS_USER, ssh_username);

      rc = ssh_connect(single_ssh_session);

      if (rc != SSH_OK)
        fprintf(stderr, "Error connecting to %s: %s\n", ssh_server, ssh_get_error(single_ssh_session));

      remove_new_line(ssh_password);

      rc = ssh_userauth_password(single_ssh_session, NULL, ssh_password);

  // if logged in, run command(s)
      if (rc == SSH_AUTH_SUCCESS) {
        printf("%s@%s:\n", ssh_username, ssh_server);
        run_command(single_ssh_session, argv[1]);
        puts("");
      }

      else {
        fprintf(stderr, "Error: %s, in %s line %d\n",
        ssh_get_error(single_ssh_session), SSH_SERVERS_LIST, line_number);
      }

      ssh_disconnect(single_ssh_session);
      ssh_free(single_ssh_session);

    }

  free(ssh_line);
  fclose(ssh_fp);

  return 0;

}
