/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peazeved <peazeved@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:27:02 by peazeved          #+#    #+#             */
/*   Updated: 2025/12/05 14:45:40 by peazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"


static int g_bits;

static int ft_lenprocess(t_struct *s, int sig)
{
    if(g_bits < 32)
    {
        ft_lenhandler(s, sig);
        if(++g_bits == 32)
        {
            if(s->len == 0)
            {
                ft_resetvars(s, &g_bits);
                return 0; // n ha len .
            }
            ft_msghandler(s);
        }
        return 1;
    }
    return 0; // acabou de processar.
}

static void ft_sinalhandler(int sig)
{
    static t_struct s;
    if(ft_lenprocess(&s, sig))
        return;
    if(ft_charhanlder(&s, sig)) // Caractere completo
    {
        s.msg[s.j++] =s.c;
        s.c = 0;
        if (s.j == s.len)
        {
            ft_putmsg(&s);
            ft_resetvars(&s, &g_bits);
            return;
        }
    }
    g_bits++; // g_bits incrementa a cada sinal processado no modo mensagem.

}

int main()
{
    unsigned int pid = getpid(); 
    write(1, "PID: ", 5); // async- singnal - free.
    ft_putnbr(pid);
    write(1, "\n",1);
    signal(SIGUSR1, ft_sinalhandler);
    signal(SIGUSR2, ft_sinalhandler);
    write(1, "\n", 1);
    while(1)
    {
        pause();
    }
    return 0;
}