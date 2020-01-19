/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 20:46:31 by jziemann          #+#    #+#             */
/*   Updated: 2019/12/26 20:46:34 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"

static short	reverse_short(short s)
{
    unsigned char c1, c2;

    c1 = s & 0xff;
    c2 = (s >> 8) & 0xff;
    return ((c1 << 8) + c2);
}

static int		reverse_int(int s)
{
    unsigned short c1, c2;

    c1 = reverse_short(s & 0xffff);
    c2 = reverse_short( (s >> 16) & 0xffff);
    return ((c1 << 16) + c2);
}

int			ft_is_numeric(char *str)
{
    while(*str)
        if (!ft_isdigit(*str++))
            return (0);
    return (1);
}

void        reg_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    int r_val;

    r_val = ft_atoi(++arg);
    arg_parse->size = 1;
    arg_parse->type = T_REG;
    arg_parse->bin = r_val; // one byte
//    write(1, &arg_parse->bin, arg_parse->size);
//    printf("\nsize %d\n type %u\n", arg_parse->size, arg_parse->type);
}

void        dir_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    unsigned int   dir_val;
    int             temp;

    temp = ft_atoi(++arg);
    dir_val = temp < 0 ? ~(temp * -1) + 1 : temp;
    arg_parse->bin = dir_size == 4 ? reverse_int((int)dir_val) : reverse_short((short)dir_val);
    arg_parse->size = dir_size;
    arg_parse->type = T_DIR;

}

void        indir_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    unsigned int    ind_val;
    int             temp;

    temp = ft_atoi(arg);
    ind_val = temp < 0 ? ~((temp * -1)) + 1 : temp;
    arg_parse->type = T_IND;
    arg_parse->size = 2;
    arg_parse->bin = reverse_short((short)ind_val);

}

void        label_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    arg_parse->label = (t_label *)ft_memalloc(sizeof(t_label));
    //мы должны знать вместо какого аргумента он тут стоит
//    printf("LABEL %s\n", ++arg);
    arg_parse->label->name = ft_strdup(arg);
    //arg_parse->label->position = pos;
    arg_parse->type = T_LABEL;
    arg_parse->size = dir_size;
    arg_parse->label->size = dir_size; //label
}
/**
 * определяем к какому типу относится аргументы
 * является ли он меткой
 * кодируем в бинарный вид
 * @param agr аргумент команды
 * @param pos
 * @param dir_size
 * @return pointer !!
 */
t_arg		*get_arg(char *arg, int dir_size, t_pvec *label_vec)
{
    t_arg *arg_parse;

    arg_parse = (t_arg *)ft_memalloc(sizeof(t_arg));
    if (arg[0] == 'r')
    {
        if (arg[1] == ':')
        {
            label_arg(arg_parse, 1, arg + 2);
            ft_ptr_vec_pushback(label_vec, arg_parse);
        }
        else
        {
            reg_arg(arg_parse, dir_size, arg); // unused dir_size
        }
    }
    else if (arg[0] == '%')
    {
        if (arg[1] == ':')
        {
            label_arg(arg_parse, dir_size, arg + 2);
            ft_ptr_vec_pushback(label_vec, arg_parse);
        }
        else
        {
            dir_arg(arg_parse, dir_size, arg);
        }
    }
    else if (arg[0] == ':')
    {
        label_arg(arg_parse, 2, arg);

        ft_ptr_vec_pushback(label_vec, arg_parse);
    }
    else if (ft_is_numeric(arg))
        indir_arg(arg_parse, dir_size, arg); // unused dir_size
    else
    {

        printf("GOVNO");
        exit(0);
    }
    return (arg_parse);
}