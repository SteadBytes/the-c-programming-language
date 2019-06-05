#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void swap(char s[], int i, int j);

int main(void)
{
    char s[] = "this is a string";
    printf("reverse(\"%s\") = ", s);
    reverse(s);
    puts(s);
    return 0;
}

/* reverse: ex 4-13 reverse string s in place via a recursive procedure */
void reverse(char s[])
{
    /* declared internally to keep helper hidden */
    void reverse_helper(char s[], int l_index, int len);
    reverse_helper(s, 0, strlen(s));
}

/*
    reverse_helper: recursive procedure for reversing a string
       recursively swaps elements in s from the outside in
       i.e. s[0] and s[len - 1], then s[1] and s[len - 2] ... 
*/
void reverse_helper(char s[], int l_index, int len)
{
    int r_index = len - (l_index + 1);
    if (l_index < r_index)
    {
        /* recursive case: unswapped characters remain between l_index and r_index */
        swap(s, l_index, r_index);
        reverse_iter(s, ++l_index, len);
    }
    /* base case: no unswapped characters -> do nothing */
}

/* swap: swap characters at positions i, j in string s*/
void swap(char s[], int i, int j)
{
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
}