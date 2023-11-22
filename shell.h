#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convertnum_function() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@count_line: the shell error count
 *@error_num: the shell error code for exit()s
 *@line_count_flag: if on count this line of input
 *@file_name: shell program filename
 *@link_env: linked list local copy of environ
 *@mode_environ: custom modified copy of environ from LL env
 *@his_tory: shell history node
 *@node_alias: the alias node
 *@environ_changed: on if environ was changed
 *@exec_status: the return status of the last exec'd command
 *@cmd_buffer: address of pointer to cmd_buf, on if chaining
 *@cmd_buffer_type: CMD_type ||, &&, ;
 *@_readfd: the fd from which to read line input
 *@hist_count: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int count_line;
	int error_num;
	int line_count_flag;
	char *file_name;
	list_t *link_env;
	list_t *his_tory;
	list_t *node_alias;
	char **mode_environ;
	int environ_changed;
	int exec_status;

	char **cmd_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buffer_type; /* CMD_type ||, &&, ; */
	int _readfd;
	int hist_count;
} inf_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(inf_t *);
} builtin_table;


char **strwords(char *s, char *delim);
char **strto_two(char *string, char delim);
char *_strcopy(char *dst, char *source);
char *dup_string(const char *string);
void put_string(char *string);
int _putchar(char ch);
int string_len(char *str);
int str_compare(char *str1, char *str2);
char *haystack_check(const char *hay_string, const char *n);
char *string_cat(char *d, char *source);
int shell_loop(inf_t *inf, char **v);
int find_builtin_cmd(inf_t *inf);
void find_command(inf_t *inf);
void fork_command(inf_t *inf);
int test_delim(inf_t *inf, char *buffer, size_t *k);
void chain_check(inf_t *f, char *buffer, size_t *a, size_t c, size_t l);
int alias_rep(inf_t *i);
int vars_rep(inf_t *inf);
int string_rep(char **o, char *n);
char *mem_set_(char *q, char t, unsigned int num);
void free_strings(char **ss);
void *realloc_mem(void *t, unsigned int o, unsigned int n);
int check_cmd(inf_t *inf, char *p);
char *char_dup(char *str_path, int s, int p);
char *find_command_path(inf_t *inf, char *str_path, char *c);
int free_pointer(void **p);
int main(int arg_count, char **arg_vector);
size_t linklist_len(const list_t *ptr);
char **list_array(list_t *h);
size_t list_print(const list_t *head);
list_t *begin_node(list_t *n, char *pref, char ch);
ssize_t index_node(list_t *h, list_t *n);
list_t *list_add_node(list_t **h, const char *s, int n);
list_t *node_end(list_t **h, const char *s, int n);
size_t _printlist(const list_t *head);
int delete_node(list_t **h, unsigned int i);
void free_list(list_t **h_ptr);
char *history_file(inf_t *inf);
int write_existing(inf_t *inf);
int read_existing(inf_t *inf);
int add_history_list(inf_t *inf, char *buffer, int count);
int history_renumber(inf_t *inf);
ssize_t buf_command(inf_t *inf, char **buffer, size_t *l);
ssize_t minus_line(inf_t *inf);
ssize_t read_buffer(inf_t *inf, char *buffer, size_t *j);
int get_line(inf_t *inf, char **pt, size_t *len);
void block_copy(__attribute__((unused))int num_signal);
void initialize_struct(inf_t *inf);
void set_struct(inf_t *inf, char **v);
void free_struct(inf_t *inf, int a_ll);
char **_get_environ(inf_t *inf);
int unset_env(inf_t *inf, char *v);
int set_env(inf_t *inf, char *v, char *val);
char *_strncopy(char *d, char *s, int num);
char *str_cat(char *d, char *source, int num);
char *str_char(char *str, char ch);
int str_int(char *str);
void _print_error(inf_t *inf, char *str);
int print_dec(int p, int fd);
char *convertnum_function(long int n, int b, int flags);
void comments_remover(char *buffer);
void input_string(char *string);
int error_putchar(char ch);
int put_fd(char ch, int fd);
int puts_fd(char *string, int fd);
int print_env(inf_t *inf);
char *get_env(inf_t *inf, const char *m);
int myset_env(inf_t *inf);
int myunset_env(inf_t *inf);
int envlist_populate(inf_t *inf);
int shell_history(inf_t *inf);
int alias_string(inf_t *inf, char *s);
int setstring_alias(inf_t *inf, char *s);
int _printalias(list_t *n);
int shell_alias(inf_t *inf);
int shell_exit(inf_t *inf);
int shell_cd(inf_t *inf);
int _myhelp(inf_t *inf);
int interactive_mode(inf_t *inf);
int char_delim(char ch, char *d);
int check_alpha(int ch);
int convert_string_to_int(char *str);
void handlehome_dir(inf_t *inf, char *buff);
void handle_oldPWD(inf_t *inf);
void handle_specificdir(inf_t *inf, char *dir);
int ch_currentdir(inf_t *inf);

#endif /* SHELL_H */
