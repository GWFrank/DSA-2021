#include <stdio.h>
#include <stdlib.h>


#define MAX_L 1000005

long double eval(char *str){
    // split the line into segments by + and -
    // result is the curent result before last + or -
    // seg is the value of current segment
    long double result=0;
    char cross_seg_op='+';
    long double seg=1;
    char in_seg_op='*';
    long double seg_pc=0;
    int i=0;
    while (str[i] != 0) {
        switch (str[i]) {
        case '+': case '-':
            if (in_seg_op == '*') {
                seg *= seg_pc;
            } else if (in_seg_op == '/') {
                seg /= seg_pc;
            }
            if (cross_seg_op == '+') {
                result += seg;
            } else if (cross_seg_op == '-') {
                result -= seg;
            }
            cross_seg_op = str[i];
            // reset segment bc we see + or -
            seg=1;
            seg_pc=0;
            in_seg_op='*';
            break;
        case '*': case '/':
            if (in_seg_op == '*') {
                seg *= seg_pc;
            } else if (in_seg_op == '/') {
                seg /= seg_pc;
            }
            in_seg_op = str[i];
            // reset seg_pc
            seg_pc = 0;
            break;
        case '(':
            seg_pc = eval(&str[i+1]);
            int par_cnt=0;
            // jump i to the end of this parentheses
            // bc this parenthese has been evaluated
            while (1) {
                if (str[i] == '(') {
                    par_cnt++;
                } else if (str[i] == ')') {
                    par_cnt--;
                }
                if (par_cnt <= 0) {
                    break;
                } else {
                    i++;
                }
            }
            break;
        case ')':
            if (in_seg_op == '*') {
                seg *= seg_pc;
            } else if (in_seg_op == '/') {
                seg /= seg_pc;
            }
            if (cross_seg_op == '+') {
                result += seg;
            } else if (cross_seg_op == '-') {
                result -= seg;
            }
            return result;
        }

        int digit = str[i]-'0';
        if (digit >= 0 && digit <= 9) {
            seg_pc = 10*seg_pc + digit;
        }
        i++;
    }
    if (in_seg_op == '*') {
        seg *= seg_pc;
    } else if (in_seg_op == '/') {
        seg /= seg_pc;
    }
    if (cross_seg_op == '+') {
        result += seg;
    } else if (cross_seg_op == '-') {
        result -= seg;
    }
    return result;
}


int main(){
    char line[MAX_L];
    while (scanf("%s", line) != EOF) {
        long double eval_result = eval(line);
        printf("%.15LF\n", eval_result);
    }
    return 0;
}