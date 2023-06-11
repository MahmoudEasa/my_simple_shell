#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

extern char **environ;

/**
 * struct built_fun - handle commands
 * @cmd: command
 * @fun: function
 *
 * Discription: handle Commands
 */

typedef struct built_fun
{
	char *cmd;
	void (*fun)(char **commands);
} Built_fun;

void execute_from_file(char **argv, Built_fun *built);
void handle_line(char *line, char **argv, Built_fun *built);
void prompt(void);
void handle_hash(char **args);
void run_fork(char *arg0, char **args, int *status);
void file_error(char *arg0, char *file);
void handle_new_line(char *line, int line_len);
int handle_s_sep(char *line, int line_len, char **argv, Built_fun *built);
int check_builtin(char **args, Built_fun *built);
void check_command(char **argv, char **args, int *status);
void exe(char *arg0, char **args);
void execute_from_stdin(char **argv, Built_fun *built);
void ctrl_c(int signum);
void handle_cd(char **args);
void handle_exit(char **args);
void handle_setenv(char **args);
void handle_unsetenv(char **args);
void handle_alias(char **args);
void _free(char **cmd);
char *_getenv(char *name);
char **split_str(char *str, char *tok);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2, int len);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
char *_strtok(char *str, char *delims);
int _strcmp_(char *s1, char *s2);
int _atoi(char *s);
void _chdir(char **path);
char *check_path(char **path, char *old_path, char *new_path, char *name_var);
void update_pwd(char *old_path, char *new_path);
void free_paths(char *old_path, char *new_path, char **path);
void handle_error(char *path);
int _setenv_(char *var_name, char *new_value, int flag);
char *concat(char *var_name, char *new_value);
int environ_size(char **env);

#endif /* #ifndef SHELL_H */

