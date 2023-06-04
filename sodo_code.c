/*[
    Exit Status
        0	The script to be executed consisted solely of zero or
            	more blank lines or comments, or both.

        1-125	A non-interactive shell detected an error other than
                command_file not found or executable, including but not
                limited to syntax, redirection, or variable assignment
                errors.

        126	A specified command_file could not be executed due to an
                [ENOEXEC] error (see Section 2.9.1.1, Command Search and
                Execution, item 2).

        127	A specified command_file could not be found by a non-
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

1- getline
2- strtok
3- Handle ; && ||
4- Handle variables replacement
	Handle the $? variable
	Handle the $$ variable

IF argc = 2
    execute_from_file(argv);
ELSE
    execute_from_stdin(argv);
*/

#include "main.h"

int main(int argc, char **argv)
{
	Built_fun built[8] = {
		{"cd", _chdir},
		{"exit", handle_exit},
		{"setenv", handle_setenv},
		{"unsetenv", handle_unsetenv},
		{"alias", handle_alias},
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
		{
			handle_line(line, argv, built);
			line = NULL;
		}
		if (line)
			free(line);
	fclose(fp);
}

void handle_line(char *line, char **argv, Built_fun *built)
{
	int line_len, status;
	char **args = NULL;

	if (!line)
		return;
	line_len = _strlen(line);
	handle_new_line(line, line_len);
	/* handle_s_sep => ; */
	if (handle_s_sep(line, line_len, argv, built) == 1)
		return;
	/* handle_logic_sep => && || */
/*	if (handle_logic_sep(line, line_len, argv, built) == 1)
		return;*/

	args = split_str(line, " \t");
	free(line);
	if (!args)
		return;

	handle_hash(args);
	/* if check_builtin == 1 no builtin command */
	if (check_builtin(args, built) == 1)
		check_command(argv, args, &status);
	if (args)
		_free(args);
}

int handle_s_sep(char *line, int line_len, char **argv, Built_fun *built)
{
	int found = 0, i, status;
	char **args = NULL, **args2 = NULL;

	for (i = 0; i < line_len; i++)
	{
		if (line[i] == ';')
		{
			found = 1;
			args = split_str(line, ";");
			free(line);
			if (!args)
				exit(EXIT_FAILURE);
			i = 0;
			while (args[i])
			{
				args2 = split_str(args[i], " \t");
				if (!args2)
				{
					_free(args);
					exit(EXIT_FAILURE);
				}
				handle_hash(args2);
				/* if check_builtin == 1 no builtin command */
				if (check_builtin(args2, built) == 1)
					check_command(argv, args2, &status);
				if (args2)
					_free(args2);
				i++;
				args2 = NULL;
			}
			if (args)
				_free(args);
			break;
		}
	}
	return (found);
}

void prompt()
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "($) ", 4);
}

void handle_hash(char **args)
{
	int i = 0, j;

	while (args[i])
	{
		if (*args[i] == '#')
		{
			j = i;
			while (args[j])
				free(args[j++]);
			args[i] = NULL;
			break;
		}
		i++;
	}
}

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
	int arg0_len = _strlen(args[0]);
	int cmd_len;

	while(built->cmd)
	{
		if (_strcmp_(args[0], built->cmd) == 0)
		{
			cmd_len = _strlen(built->cmd);
			if (arg0_len != cmd_len)
				return (1);

			built->fun(args);
			return (0);
		}
		built++;
	}
	return (1);
}

void check_command(char **argv, char **args, int *status)
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
				run_fork(path, args, status);
				return;
			}
			path_tok = _strtok(NULL, ":");
		}
		file_error(argv[0], args[0]);
		if (!isatty(STDIN_FILENO))
			exit(127);
	}
	else
	{
		if (stat(args[0], &st) == 0)
			run_fork(args[0], args, status);
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
	char *line;
	size_t n;

	while(1)
	{
		prompt();
		signal(SIGINT, ctrl_c);
		line = NULL;
		if (getline(&line, &n, stdin) != -1)
			handle_line(line, argv, built);
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDIN_FILENO, "\n", 1);
			free(line);
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

void handle_cd(char **args)
{
	printf("Hello %s\n", args[0]);
}

void handle_exit(char **args)
{
	int num;

	if (args[1])
	{
		num = _atoi(args[1]);
		_free(args);
		exit(num);
	}
	else
	{
		_free(args);
		exit(EXIT_SUCCESS);
	}
}

void handle_setenv(char **args)
{
	printf("Hello %s\n", args[0]);
}

void handle_unsetenv(char **args)
{
	printf("Hello %s\n", args[0]);
}

void handle_alias(char **args)
{
	printf("Hello %s\n", args[0]);
}

