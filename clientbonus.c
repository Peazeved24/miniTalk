/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientbonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peazeved <peazeved@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:09:48 by peazeved          #+#    #+#             */
/*   Updated: 2025/12/19 15:07:33 by peazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"


volatile sig_atomic_t g_ack = 0;

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

void ft_pidverify(int s_pid)
{
    if (kill(s_pid, 0) == -1)
    {
        ft_putstr("Invalid PID.\n");
        exit(1);
    }
}

void ft_wakeup(void)
{
    while (!g_ack)
        pause(); // espera pelo ack
    g_ack = 0;
}

void ft_clienthandler(int sig)
{
    if (sig == SIGUSR2)
        g_ack = 1;
}

void ft_lenprocess(int len, int bit, int s_pid)
{

    if(len == 0)
    {
        while(bit >= 0)
        {
            kill(s_pid, SIGUSR1);
            ft_wakeup();
            bit--;   
        }
        return;
    }
    while (bit >= 0)
    {
        if ((len >> bit) & 1)   
            kill(s_pid, SIGUSR2);
        else
            kill(s_pid, SIGUSR1);
        ft_wakeup();
        bit--;
    }
}

void ft_charprocess(int len, char *msg, int s_pid)
{
    int i = 0;
    while (i < len)
    {
        char c = msg[i];
        int b = 7;
        while (b >= 0)
        {
            if ((c >> b) & 1)
                kill(s_pid, SIGUSR2);
            else
                kill(s_pid, SIGUSR1);
            ft_wakeup();
            b--;
        }
        i++;
    }
}

int main(int ac, char **av)
{
    if (ac != 3)
    {
        ft_putstr("few args\n");
        return 1;
    }
    if (!ft_isdigit(av[1]))
    {
        ft_putstr("NUMBERS only!\n");
        return 1;
    }
    int s_pid = ft_atoi(av[1]);
    char *msg = av[2];
    int len = ft_strlen(msg);

    ft_pidverify(s_pid);
    struct sigaction sa;
    sa.sa_handler = ft_clienthandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR2, &sa, NULL);
    ft_lenprocess(len, 31, s_pid);
    ft_charprocess(len, msg, s_pid);

    return 0;
}
