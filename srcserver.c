/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcserver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peazeved <peazeved@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 01:20:16 by peazeved          #+#    #+#             */
/*   Updated: 2025/12/05 14:32:28 by peazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"



void ft_msghandler(t_struct *s)
{
    s->msg = malloc((s->len + 1));
    if(!s->msg)
        exit(1);
    s->msg[s->len] = '\0';
}

void ft_lenhandler(t_struct *s, int sig)
{
    s->len <<= 1;
    if(sig == SIGUSR2)
        s->len |=1;
}

void ft_resetvars(t_struct *s, int *g_bits)
{
    ft_putchar('\n');
    s->len = 0;   
    s->i = 0;
    s->j = 0;
    s->c = 0;
    *g_bits = 0;
    if(s->msg)
    {
        free(s->msg);
        s->msg = NULL;
    }
}

int ft_charhanlder(t_struct *s, int sig)
{
    s->c <<= 1;
    if(sig == SIGUSR2)
        s->c |= 1;
    s->i++;
    if(s->i == 8)
    {
        s->i = 0;
        return 1;     
    }     
    return 0;
}

void ft_putmsg(t_struct *s)
{
   s->msg[s->j] = '\0';
    ft_putstr(s->msg);
    ft_putchar('\n');
}
