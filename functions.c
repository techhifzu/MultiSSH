int valid_port(int *port) {

  int result = 0;

  if ((*port > 0) && (*port < 65536))
    result = 1;

 return result;

}

void remove_new_line(char *string) {

  for(int i = 0; i < strlen(string); i++) {

    char *c = strchr(string, '\n');

    if (c)
      *c = 0;

    }
}

// run command(s), and display any resulting output
int run_command(ssh_session session, char *command) {
  ssh_channel channel;
  int rc;
  char buffer[2048];
  int nbytes;

  channel = ssh_channel_new(session);

  if (channel == NULL)
    return SSH_ERROR;

  rc = ssh_channel_open_session(channel);

  if (rc != SSH_OK) {
    ssh_channel_free(channel);
    return rc;
  }

 rc = ssh_channel_request_exec(channel, command);

 if (rc != SSH_OK) {
  ssh_channel_close(channel);
  ssh_channel_free(channel);
  return rc;
  }

  nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);

  while (nbytes > 0) {

    if (fwrite(buffer, 1, nbytes, stdout) != nbytes) {
      ssh_channel_close(channel);
      ssh_channel_free(channel);
      return SSH_ERROR;
    }

  nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);

 }

 if (nbytes < 0) {
   ssh_channel_close(channel);
   ssh_channel_free(channel);
   return SSH_ERROR;
 }

 ssh_channel_send_eof(channel);
 ssh_channel_close(channel);
 ssh_channel_free(channel);

return SSH_OK;

}
