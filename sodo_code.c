/*[
    Exit Status
        0		The script to be executed consisted solely of zero or
            	more blank lines or comments, or both.
        1-125	A non-interactive shell detected an error other than
                command_file not found or executable, including but not
                limited to syntax, redirection, or variable assignment
                errors.
        126		A specified command_file could not be executed due to an
                [ENOEXEC] error (see Section 2.9.1.1, Command Search and
                Execution, item 2).
        127		A specified command_file could not be found by a non-
                interactive shell.
        Otherwise, the shell shall return the exit status of the last
        command it invoked or attempted to invoke (see also the exit
        utility in Section 2.14, Special Built-In Utilities).

        Same error with your program hsh:
        $ echo "qwerty" | ./hsh
        ./hsh: 1: qwerty: not found
        $ echo "qwerty" | ./././hsh
        ./././hsh: 1: qwerty: not found
]

IF argc = 2
    execute_from_file(argv);
ELSE
    execute_from_stdin(argv);
*/

#include "main.h"

int main(int argc, char **argv)
{
	Built_fun built[7] = {
		{"cd", handle_cd},
		{"env", handle_env},
		{"exit", handle_exit},
		{"echo", handle_echo},
		{"alias", handle_alias},
		{"clear", handle_clear},
		{NULL, NULL},
	};

	if (argc == 2)
		execute_from_file(argv, built);
	else
		execute_from_stdin(argv, built);

	return (0);
}

void execute_from_file(char **argv, Built_fun *built)
{
    char *line = NULL;
    FILE *fp;
	size_t n;

    fp = fopen(argv[1], "r");
		if (fp == NULL)
		{
			file_error(argv[0], argv[1]);
			exit(127);
		}

		while (getline(&line, &n, fp) != -1)
			handle_line(line, argv, built);
	fclose(fp);
}

void handle_line(char *line, char **argv, Built_fun *built)
{
	int line_len;
	char **args;

	line_len = _strlen(line);
	handle_new_line(line, line_len);
	handle_hash(line, line_len);
	args = split_str(line, " \t");
	free(line);
	if (!args)
		return;
	/* if check_builtin == 1 no builtin command */
	if (check_builtin(args, built) == 1)
		check_command(argv, args);
	_free(args);
}

void prompt()
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "($) ", 4);
}

void handle_hash(char *line, int line_len)
{
	int i;

	for (i = 0; i < line_len; i++)
		if (line[i] == '#')
		{
			line[i] = '\0';
			break;
		}
}

void run_fork(char *arg0, char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error ");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		exe(arg0, args);
	else
		wait(&status);
}

void file_error(char *arg0, char *file)
{
	write(STDERR_FILENO, arg0, _strlen(arg0));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, file, _strlen(file));
	write(STDERR_FILENO, ": not found\n", 12);
}

void handle_new_line(char *line, int line_len)
{
	if (line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
}

int check_builtin(char **args, Built_fun *built)
{
	while(built->cmd)
	{
		if (_strcmp_(args[0], built->cmd) == 0)
		{
			built->fun(args);
			return (0);
		}
		built++;
	}
	return (1);
}

void check_command(char **argv, char **args)
{
	char *paths, path[100], *path_tok;
	struct stat st;

	if (*args[0] != '/' && *args[0] != '.')
	{
		paths = _getenv("PATH");
		path_tok = _strtok(paths, ":");
		while (path_tok)
		{
			_strcpy(path, path_tok);
			_strcat(path, "/");
			_strcat(path, args[0]);

			if (stat(path, &st) == 0)
			{
				run_fork(path, args);
				return;
			}
			path_tok = _strtok(NULL, ":");
		}
		file_error(argv[0], args[0]);
	}
	else
	{
		if (stat(args[0], &st) == 0)
			run_fork(args[0], args);
		else
			file_error(argv[0], args[0]);
	}
}

void exe(char *arg0, char **args)
{
	if (execve(arg0, args, environ) == -1)
	{
		perror("Error ");
		exit(EXIT_FAILURE);
	}
}

void execute_from_stdin(char **argv, Built_fun *built)
{
	char *line = NULL;
	size_t n;

	while(1)
	{
		prompt();
		signal(SIGINT, ctrl_c);
		if (getline(&line, &n, stdin) != -1)
			handle_line(line, argv, built);
		else
		{
			if (!isatty(STDIN_FILENO))
				write(STDIN_FILENO, "\n", 1);
			break;
		}
	}
}

void ctrl_c(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	prompt();
}

void handle_cd()
{
	printf("Hello\n");
}

void handle_env()
{
	printf("Hello\n");
}

void handle_exit()
{
	printf("Hello\n");
}

void handle_echo()
{
	printf("Hello\n");
}

void handle_alias()
{
	printf("Hello\n");
}

void handle_clear()
{
	printf("Hello\n");
}
