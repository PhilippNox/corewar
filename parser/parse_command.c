//
// Created by Virgil Legros on 16/01/2020.
//
#include "asm.h"

int 	is_command(char **line)
{
	int i;

	i = -1;
	skip_spaces(line);
	while (++i < COMMANDS_NUM)
		if (!ft_strncmp(*line, g_commands[i].name, g_commands[i].name_len))
			return (i);
	return (-1);
}

char 	*parse_arg(char **line)
{
	char *arg_start;
	char *arg_end;

	arg_start = *line;
	while (ft_isspace(*arg_start))
		arg_start++;
	arg_end = arg_start;
	while (!ft_isspace(*arg_end) &&
		*arg_end != SEPARATOR_CHAR &&
		*arg_end != COMMENT_CHAR &&
		*arg_end != ALC_COMMENT_CHAR)
		arg_end++;
	*line = ft_strchr(*line, SEPARATOR_CHAR) + 1;
	*arg_end = '\0';
	return (ft_strdup(arg_start));
}

char	**parse_command(char *line, const int cmd)
{
	int i;
	char **args;

	line = line + g_commands[cmd].name_len;
	args = (char**)ft_memalloc(sizeof(char*));
	i = -1;
	while(++i < g_commands[cmd].num_of_args)
		args[i] = parse_arg(&line);
	return (args);
}