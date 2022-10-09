/* KR p. 76-79 */
#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
void swap(void);

main()
{
  int type; /* is it an operator or an operand or an EOF */
  double op2; /* for division */
  double op1; /*for pow*/
  double result; //for variable M
  char s[MAXOP]; /* hold operands (i.e., numbers) */
  result = 0;

  while((type = getop(s)) != EOF) {
    switch(type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      swap();
      push(pop() - pop());
      break;
    case '/':
      op2 = pop();
      if(op2 != 0.0)
		push(pop() / op2);
      else
		printf("error: zero divisor\n");
      break;
	case '%':
		op2 = pop();	
		if(op2 != 0.0){
			push(fmod(pop(), op2));
		}			
		else{
			printf("error: zero divisor\n");
		}
				
	 break;
	case 'S':
		push(sin(pop()));
		break;
	case 'E':
		push(exp(pop()));
		break;
	case 'P':
		op2 = pop();
		op1 = pop();
		if((op1==0 && op2 <=0) || (op1<0 && (op2 - (int)op2)!=0)){
			printf("cannot compute the power\n");
		}
		else{
			push(pow(op1, op2));
		}
		break;	
	case 'M':
		push(result);
	break;
    case '\n':
		result = pop();
      printf("\t%.8g\n", result);
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}

// Stack implementation

#define MAXVAL 100

int sp = 0; // "stack pointer" - current index for the spot above the top of stack
double val[MAXVAL];

void push (double f)
{
  if(sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n",f);
}

double pop(void)
{
  if(sp > 0)
    return val[--sp];
  else
    {
      printf("error: stack empty \n");
      return 0.0;
    }
}
void swap(void){
	double temp;
	temp = val[sp-1];
	val[sp-1] = val[sp-2];
	val[sp-2] = temp;
	
	
}

// prototypes for character buffer, implemented below
int getch(void);
void ungetch(int);

int getop(char s[]) // get either the next operand or the next operator
{
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if(!isdigit(c) && c != '.' && c!= '-')
    return c; /* not a number */
  i = 0;
 
  if(c == '-'){
	  if(!isdigit(c = getch())){
		ungetch(c);
		return '-';
	  }else{
		  s[++i] = c;
		  while(isdigit(s[++i] = c = getch()))
      ;
	  }	

  }
  if (isdigit(c)) /* collect integer part */
    while(isdigit(s[++i] = c = getch()))
      ;
  if(c=='.') /* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if(c != EOF)
    ungetch(c);
  return NUMBER;
}

// character buffer implementation

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0; // point to the array index

int getch(void)
{
  return(bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  if(bufp >= BUFSIZE){
    printf("ungetch: too many characters\n");
  }
  else
    {
      buf[bufp++] = c;
    }
}
