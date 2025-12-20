/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peazeved <peazeved@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:47:37 by peazeved          #+#    #+#             */
/*   Updated: 2025/12/19 14:29:41 by peazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}

void ft_pidverify(int pid)
{

    if(kill(pid, 0) == -1) // condicao de seguranca do pid.
    {
        ft_putstr("not valid Server PID!\n");
        exit(1);
    }
}

void ft_getlen(int len, int b, int pid)
{
    while(b >= 0)
    {
        if((len >> b) & 1)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        b--;
        usleep(100);
    }
}

void ft_builchar(int len, char *msg, int pid)
{
    int i = 0;
    unsigned char c = 0;    
    int b = 7; 
    while(i < len)
    {
        c = msg[i]; // associar o char ao index.
        b = 7;
        while(b >= 0)
        {
            if((c >> b) & 1)
                kill(pid, SIGUSR2);
            else
                kill(pid, SIGUSR1);
            b--;
            usleep(100);
        }
        i++;
    }
    
}

int main(int ac, char **av)
{
    if(ac != 3)
    {
        write(1, "\n", 1);
        return 1;
    }
    if(!ft_isdigit(av[1]))
    {
        ft_putstr("PID only with numbers\n");
        return 1;   
    }
    int pid = ft_atoi(av[1]); // pid do server
    char *msg = av[2]; 
    int len = ft_strlen(msg);  // len da msg a enviar.
    ft_pidverify(pid);
    ft_getlen(len, 31, pid);
    ft_builchar(len , msg, pid);
    return 0;
}


/*
    0 o lado do client !
        - pega o pid do server e manda uma msg.
            -
*/