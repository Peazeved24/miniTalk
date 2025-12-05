so veyre straightforward project but my main problem was to modulated that ***.
  

so it all started with 
a buch of vars inside of that *** 

  - void ft_sinalhandler(int sig)
{
    static int j = 0;
    static int i = 0; // index para comprar com a g_bits agora
    static int len = 0; // len criada 
    static char c = 0; // meu char criado apos os 8 bits de contagem
    static char *msg = NULL;;// armazena a msg aqui. 

    if(g_bits < 32) // receber o len.
    {
        ft_lenhandler(&len, sig);
        if(++g_bits == 32) // ja tenho a minha len.
        {
            if(len == 0)
            {
                ft_resetvars(&len, &i, &c, &j , &g_bits, &msg);
                return;
            }
            ft_strhandler(&msg, len);
        } 
    }
    else
    {
        if (ft_charhanlder(&c, sig, &i)) // Caractere completo
        {
            msg[j++] = c;
            c = 0;
            if (j == len)
            {
                ft_putmsg(msg, j);
                ft_resetvars(&len, &i, &c, &j, &g_bits, &msg);
                return;
            }
  or :
    ft_resetvars(&len, &i, &c, &j , &g_bits, &msg); ( :D ) --- thousand and thousand of var to reset and use ...
until i discorver 1 trick :
    - A fcking S T R U C T !!!!
      - 1  family of a bunch of vars :
  typedef struct s_struct
{
    int j; // index para chars
    int i;  // contagem de bits.
    int len;  // msg len + to alloc.
    char c;  // o meu char
    char *msg; // a msg em si !
}t_struct;
      so the problem was not the amount of vars at the end but yes the way i was using it ...
          - so insted of having this - ft_resetvars(&len, &i, &c, &j , &g_bits, &msg)
              i could have this
              - static int s;
                    so i could do this
                        ft_resetvars(&s, &g_bits); // cal my struct with all the vars on inside + global var (exemple)
                        - insted of  ft_resetvars(&len, &i, &c, &j , &g_bits, &msg);
        - plus this 
        void ft_msghandler(t_struct *s);
        void ft_lenhandler(t_struct *s, int sig);
        void ft_resetvars(t_struct *s, int *g_bits);
        int ft_charhanlder(t_struct *s, int sig);
        void ft_putmsg(t_struct *s);
          -compared to this: ...
              int ft_charhanlder(char *c, int sig, int *i)
              ft_resetvars(&len, &i, &c, &j , &g_bits, &msg);
              etc..
