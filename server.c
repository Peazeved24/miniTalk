/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peazeved <peazeved@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:27:02 by peazeved          #+#    #+#             */
/*   Updated: 2025/12/19 12:34:21 by peazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"


static int g_bits; 

int ft_charhanlder(t_struct *s, int sig)
{
    s->c <<= 1;
    if(sig == SIGUSR2)
        s->c |= 1;
    s->i++;
    if(s->i == 8)
    {   
        s->i = 0;
        return 1;  // ?
    }     
    return 0;
}

static int ft_lenhandler(t_struct *s, int sig)
{
    if(g_bits < 32)
    { 
        s->len <<= 1;
        if(sig == SIGUSR2)
            s->len |= 1;
        g_bits++;
        if(g_bits == 32)
        {
            if(s->len == 0)
            {
                ft_resetvars(s, &g_bits);
                return 0;
            }
            ft_msghandler(s);
        }
        return 1;
    }
    return 0; // acabou de processar.
}

void ft_sinalhandler(int sig)
{
    static t_struct s;
    if(ft_lenhandler(&s, sig))
        return;
    if(ft_charhanlder(&s, sig)) // Caractere completo
    {
        if(s.j < s.len)
            s.msg[s.j++] = s.c;
        s.c = 0;
        if(s.j == s.len)
        {
            ft_putmsg(&s);
            ft_resetvars(&s, &g_bits);
            return; // ?
        }
    }
    g_bits++; // ?
}

int main()
{
    unsigned int pid = getpid(); 
    write(1, "PID: ", 5); // async- singnal - free.
    ft_putnbr(pid);
    write(1, "\n",1);
    ft_putstr("________________TEXT_ZONE________________\n");
    signal(SIGUSR1, ft_sinalhandler);
    signal(SIGUSR2, ft_sinalhandler);
    while(1)
    {
        pause();
    }
    return 0;
}


