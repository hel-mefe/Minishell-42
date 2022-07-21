#include "../parsing.h"

int is_dollar_char_valid(char c)
{
    return (!is_space(c) && (ft_isalnum(c) || c == '_'));
}

char    *get_dollar(char *s)
{
    size_t  i;

    i = 0;
    while (s[i] && is_dollar_char_valid(s[i]))
        i++;
    return (slice(s, 0, i));
}

t_dollar *get_all_dollars(char *s, char **env, t_env *main_env)
{
    size_t      i;
    t_dollar    *new;
    t_dollar    *head;
    char        *dollar;

    i = 0;
    head = NULL;
    while (s[i])
    {
        if (s[i] == '$' && is_dollar_valid(s + i + 1))
        {
            dollar = get_dollar(s + i + 1);
            i += ft_strlen(dollar);
            new = new_dollar(dollar, get_dollar_val(dollar, env, main_env));
            push_back_dollar(&head, new);
        }
        else
            i++;
    }
    return (head);
}

char    *get_dollar_val(char *var, char **env, t_env *main_env)
{
    size_t  i;
    size_t  len;

    len = ft_strlen(var);
    i = 0;
    while (main_env)
    {
        if (!ft_strcmp(var, main_env->name))
            return (ft_strdup(main_env->data));
        main_env = main_env->next;
    }
    return (slice(var, 0, 0));
}

char	*digit_after_dollar(char *s, char *r, size_t *a, size_t *b)
{
	char	*res;
	char	*part;

	part = slice(s, *a, *b);
	res = ft_strjoin_free(r, part);
	*a += 1;
	*b = *a + 1;
	return (res);
}


char    *expand_string(t_dollar *dollars, char **env, int *place, char *s)
{
    size_t  i;
    size_t  j;
    char    *res;
    char    *part;
    char    *k_res;
    int     singly;

    singly = 0;
    res = NULL;
    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] == '\'')
            singly = !singly;
        if (s[i] == '$' && ft_isdigit(s[i + 1]) && !singly)
			res = digit_after_dollar(s, res, &i, &j);
        else if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_') && !singly)
        {
            if (j != i)
            {
                k_res = part;
                part = slice(s, j, i);
                res = ft_strjoin_free(res, part);
            }
            k_res = res;
            res = ft_strjoin(res, dollars->val);
            i += ft_strlen(dollars->var);
            j = i + 1;
            dollars = dollars->next;
            if (k_res)
                free(k_res);
        }
        else if (s[i] == '$' && s[i + 1] == '?' && !singly)
        {
            if (j != i)
            {
                k_res = res;
                part = slice(s, j, i);
                res = ft_strjoin_free(res, part);
                // if (k_res)
                //     free(k_res);
                // free(part);
            }
            // k_res = res;
            part = ft_itoa(get_nb_status);
            res = ft_strjoin_free(res, part);
            // if (k_res)
            //     free(k_res);
            i += 1;
            j = i + 1;
        }
        i++;
    }
    if (i != j)
    {
        // k_res = res;
        part = slice(s, j, i);
        res = ft_strjoin_free(res, part);
        // if (k_res)
        //     free(k_res);
    }
    if (res && !res[0])
    {
        if (*place == INFILE || *place == OUTFILE)
            *place = NONE_AMBIGUOUS;
        else
            *place = NONE;
    }
    return (res);
}


// char    *expand_dollar(char *s)
// {
//     t_dollar    *dollars;
//     char        *res;
//     char        *part;
//     size_t      i;
//     size_t      j;

//     dollars = get_all_dollars(s);
//     res = NULL;
//     return ()
//     // i = -1;
//     // j = 0;
//     // while (s[++i])
//     // {
//     //     if (s[i] == '$' && is_dollar_valid(s + i + 1))
//     //     {
//     //         part = slice(s, j, i);
//     //         j = i;
//     //         res = ft_strjoin()
//     //     }
//     // }
// }