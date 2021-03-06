/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champions_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:07:38 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/16 19:08:40 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	reverse_int(unsigned int *to_reverse)
{
	unsigned char	*original;
	int				i;
	unsigned char	tmp;

	original = (unsigned char *)to_reverse;
	i = -1;
	while (++i < 2)
	{
		tmp = original[i];
		original[i] = original[3 - i];
		original[3 - i] = tmp;
	}
}

static char	*invalid_champion(t_champ *champ)
{
	char	*err;

	reverse_int(&champ->magic);
	if (champ->magic != COREWAR_EXEC_MAGIC)
		return ("champion has an invalid header");
	if (champ->comm[COMMENT_LENGTH] || champ->name[PROG_NAME_LENGTH])
		return ("champion has an invalid header");
	reverse_int(&champ->code_size);
	if (champ->code_size > CHAMP_MAX_SIZE)
	{
		err = ft_itoa(CHAMP_MAX_SIZE);
		ft_putstr_fd("Champion size limit is ", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd(". ", 2);
		free(err);
		return ("champion size exceed max limit");
	}
	return (NULL);
}

static char	*get_champion(int fd, t_champ *champ, unsigned char *place)
{
	unsigned int	real_size;
	char			*error;

	real_size = read(fd, champ, HEADER_SIZE);
	if (real_size < HEADER_SIZE)
		return ("file is too small to be a champion");
	if ((error = invalid_champion(champ)))
		return (error);
	real_size = read(fd, place, champ->code_size);
	if (real_size != champ->code_size || read(fd, place, 1))
		return ("code size differs from what its header says");
	return (NULL);
}

void		init_champion(char *file, t_cbox *cbox, int cell, t_champ *champ)
{
	int		fd;
	char	*msg;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		finish_interface(cbox);
		cbox->flags = 0;
		ft_putstr_fd("Can't read source file ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
		exit(clean_all(cbox, INPUT_ERROR));
	}
	msg = get_champion(fd, champ, &(cbox->arena.arena[cell]));
	close(fd);
	if (msg)
	{
		finish_interface(cbox);
		cbox->flags = 0;
		ft_putstr_fd("Error with champion ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
		exit(clean_all(cbox, INPUT_ERROR));
	}
}
