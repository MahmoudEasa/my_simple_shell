#include "shell.h"

/**
 * run_fork - run fork and execv function
 * @arg0: string
 * @args: array of line command
 * @status: integer
 */

void run_fork(char *arg0, char **args, int *status)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error ");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		exe(arg0, args);
	else
		waitpid(pid, status, 0);
}


