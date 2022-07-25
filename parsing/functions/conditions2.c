#include "../../include/parsing.h"

int is_syntax_token(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

int is_singly(char c)
{
    return (c == '\'');
}

int is_doubly(char c)
{
    return (c == '\"');
}