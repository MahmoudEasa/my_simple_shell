#include "shell.h"

/**
 * check_builtin - handle builtin functions
 * @args: array of line command
 * @built: struct to handle builtin functions
 *
 * Return: 1 if there is builtin function or 0 if not
 */

int check_builtin(char **args, Built_fun *built)
{
	int arg0_len;
	int cmd_len;

	if (args[0])
	{
		arg0_len = _strlen(args[0]);
		while (built->cmd)
		{
			if (_strcmp_(args[0], built->cmd) == 0)
			{
				cmd_len = _strlen(built->cmd);
				if (arg0_len != cmd_len)
					return (0);

				built->fun(args);
				return (1);
			}
			built++;
		}
	}
	return (0);
}

