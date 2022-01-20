#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

int pipe_std_to_socket(char * name) {
    int localsocket, len;
    if((localsocket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        return 1;
    }

    size_t name_len = strlen(name);
    struct sockaddr_un remote;

    remote.sun_path[0] = '\0';
    strcpy(remote.sun_path+1, name);
    remote.sun_family = AF_UNIX;

    len = 1 + name_len + offsetof(struct sockaddr_un, sun_path);

    if(connect(localsocket, (struct sockaddr*) &remote, len) == -1) {
        return 1;
    }
    dup2( localsocket, STDOUT_FILENO );
    dup2( localsocket, STDERR_FILENO );

    return 0;
}