int main() {
int x, y ;
char op, op_output;
scanf("%d %c %d", &x, &op ,&y);
 switch (op) {
   case '+':
     printf("%d", x+y);
    break;
  case '-':
    printf("%d", x-y);
    break;
  case '*':
    printf("%d", x*y);
    break;
  case '/':
    printf("%.2f", (float)x/y);
    break;
  case '%':
    printf("%d", x%y);
    break;
  default:
    printf("Unknown Operator");





}
