# C_Advanced_Process_Control_and_Server_Extension

### Description:
The "C_Advanced_Process_Control_and_Server_Extension" GitHub repository contains two advanced C programming tasks that focus on process control using signals and extending a network server to handle multiple simultaneous connections. These tasks demonstrate the practical application of signal handling and network programming in C.

### Task 1 - Program Execution Timeout (my_timeout):
Program Function: my_timeout limits the duration of a given program. It accepts an integer specifying the number of seconds and a command (with optional arguments) to execute.
Process and Signal Handling:
Spawns a child process to execute the given command.
Sets an alarm using sigaction to trigger after the specified duration.
If the child process does not terminate before the alarm, it is killed, and my_timeout exits with a non-zero status.
If the child process terminates on time, my_timeout exits with the child's exit status.

### Task 2 - Echo Server with Concurrent Connections:
Server Enhancement: Extends the previously built echo server to handle multiple client requests concurrently.
Child Process Creation:
For each client request, the server spawns a child process.
Each child process handles one client request, allowing simultaneous connections.
Signal Handling for Process Completion:
The parent process registers a signal handler for SIGCHLD.
Uses waitpid with WNOHANG in a loop within the signal handler to handle all completed child processes.

### Repository Contents:
Source code for the my_timeout program demonstrating signal handling and process control.
Extended echo server code capable of handling multiple client connections concurrently.
Documentation detailing the functionality, usage instructions, and implementation details for each task.
Additional resources on signal handling and network programming in C.

To compile:

    'make'

To run my_timeout:

    ./my_timeout <time> <command> <time2>

    <time>: The maximum execution time (in seconds) allowed for the command.
    <command>: The command you want to execute within the specified time limit.
    <time2>: An optional argument, specific to the <command>, indicating how long the command should run before completing its task.

Example:

    ./my_timeout 5 sleep 10

To run server/client:

    ./server

    ./client localhost

Note: use in seperate/split terminals
