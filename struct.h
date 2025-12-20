/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peazeved <peazeved@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:05:40 by peazeved          #+#    #+#             */
/*   Updated: 2025/12/18 15:24:06 by peazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT

#include <unistd.h> // getpid, , write, pause
#include <signal.h> // signals, SIGUSR2 , kill
#include <stdlib.h> // malloc, free, exit.
#include <string.h>

typedef struct s_struct
{
    int j; // index para chars
    int i;  // contagem de bits.
    int len;  // msg len + to alloc.
    char c;  // o meu char
    char *msg; // a msg em si !
}t_struct;

//client.
int ft_strlen(char *str); 
int ft_atoi(char *str);
void ft_putstr(char  *str);
void ft_putchar(char c);
void ft_putnbr(unsigned int n);
int ft_isdigit(char *str);

//server
void    ft_msghandler(t_struct *s);
void    ft_resetvars(t_struct *s, int *g_bits);
void    ft_putmsg(t_struct *s);
void    *ft_memset(void *b, int c, size_t len);
#endif