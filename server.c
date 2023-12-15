#include "net.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PORT 6969

void handle_request(int nfd) {
   FILE *network = fdopen(nfd, "r+");
   char *line = NULL;
   size_t size;
   ssize_t num;

   if (network == NULL) {
      perror("fdopen");
      close(nfd);
      return;
   }

   while ((num = getline(&line, &size, network)) >= 0) {
      // echo back to the client
      write(nfd, line, num);
   }

   free(line);
   fclose(network);
}

void run_service(int fd) {
   while (1) {
      int nfd = accept_connection(fd);
      if (nfd != -1) {
         printf("Connection established...\n");

         // Fork a child process to handle the request
         pid_t child_pid = fork();

         if (child_pid < 0) {
               perror("fork");
               close(nfd);
         } else if (child_pid == 0) { // child process
               close(fd); // close the listening socket in the child
               handle_request(nfd);
               printf("Connection closed...\n");
               close(nfd);
               exit(0);
         } else { // parent process
               close(nfd); // close the accepted socket in the parent
         }
      }
   }
}

int main(void) {
   int fd = create_service(PORT);

   if (fd == -1) {
      perror(0);
      exit(1);
   }

   printf("Listening on port: %d...\n", PORT);

   // register a signal handler for SIGCHLD
   struct sigaction sa;
   sa.sa_handler = SIG_IGN; // ignore child termination signals
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART;
   sigaction(SIGCHLD, &sa, NULL);

   run_service(fd);
   close(fd);

   return 0;
}