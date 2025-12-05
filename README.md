So, very straightforward project, but my main problem was to modularize.

It all started with a bunch of variables inside.

void ft_sinalhandler(int sig) 
{ 
    static int j = 0; 
    static int i = 0; // index to compare with g_bits now
    static int len = 0; // message length
    static char c = 0; // char built after 8 bits
    static char *msg = NULL; // stores the message
}

if (g_bits < 32) // receiving the length
{
    ft_lenhandler(&len, sig);
    if (++g_bits == 32) // we have the length
    {
        if (len == 0)
        {
            ft_resetvars(&len, &i, &c, &j, &g_bits, &msg);
            return;
        }
        ft_strhandler(&msg, len);
    }
}
else
{
    if (ft_charhandler(&c, sig, &i)) // char complete
    {
        msg[j++] = c;
        c = 0;
        if (j == len)
        {
            ft_putmsg(msg, j);
            ft_resetvars(&len, &i, &c, &j, &g_bits, &msg);
            return;
        }
    }
    else
    {
        ft_resetvars(&len, &i, &c, &j, &g_bits, &msg); // :D
    }
}


Thousands of variables to reset and use… until I discovered one trick:

A f***ing S T R U C T !!!!

One family for all related variables:

typedef struct s_struct
{
    int j;    // index for chars
    int i;    // bit count
    int len;  // message length + to allocate
    char c;   // the current char
    char *msg; // the message itself
} t_struct;


So, the problem was not the number of variables at the end, but the way I was using them.

Instead of having this:

ft_resetvars(&len, &i, &c, &j, &g_bits, &msg);


I could have this:

static t_struct s;
ft_resetvars(&s, &g_bits); // call my struct with all vars inside + global var (example)


Plus, my function declarations became much cleaner:

void ft_msghandler(t_struct *s);
void ft_lenhandler(t_struct *s, int sig);
void ft_resetvars(t_struct *s, int *g_bits);
int ft_charhandler(t_struct *s, int sig);
void ft_putmsg(t_struct *s);


Compared to the old messy version:

int ft_charhandler(char *c, int sig, int *i);
ft_resetvars(&len, &i, &c, &j, &g_bits, &msg);
