#define NUMBER '0'   /* signal that a number was found */
#define FUNCTION 'f' /* signal that a named function */

void push(double);
double pop(void);
void clear(void);
int getop(char[]);
int getch(void);