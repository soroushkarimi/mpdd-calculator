#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "argtable3.h"

#define VERSION "0.1.0"

struct arg_lit *verb, *help, *version, *catalog;
struct arg_int *level;
struct arg_dbl *operand1, *operand2;
struct arg_str *operator;
struct arg_file *o;
struct arg_end *end;

const char *operators[] = {"+","-","*","/","%","&","|","~","sqrt","exp","pow", "log", "log10","ceil","floor","sin","cos"};
const char *unary_operators[] = {"~","sqrt","exp", "log", "log10","ceil","floor","sin","cos"};

bool Verbose = false;

int main(int argc, char *argv[])
{
    void *argtable[] = {
        help    = arg_litn(NULL, "help", 0, 1, "this is a simple calculator program for MPDD class"),
        version = arg_litn(NULL, "version", 0, 1, VERSION),
        catalog = arg_litn(NULL, "catalog", 0, 1, "print available operators"),
        verb    = arg_litn("v", "verbose", 0, 1, "verbose output"),
        o       = arg_filen("o", NULL, "myfile", 0, 1, "output file"),
        operator = arg_strn(NULL, "operator","<char[]>", 0, 1, "Operator"),
        operand1 = arg_dbln(NULL, "operand1","<double>", 0, 1, "Operand 1"),
        operand2 = arg_dbln(NULL, "operand2","<double>", 0, 1, "Operand 2"),
        end     = arg_end(20),
    };
    
    int exitcode = 0;
    char progname[] = "Soroush_MPDD_Calculator.exe";
    
    int nerrors;
    nerrors = arg_parse(argc,argv,argtable);

    if (help->count > 0)
    {
        printf("\nUsage: %s", progname);
        arg_print_syntax(stdout, argtable, "\n");
        printf("Soroush Calculator MPDD Demonstration.\n");
        printf("When using unary operators the second operand will be ignored.\n");
        printf("For binary operators double will be cast to int.\n\n");
        arg_print_glossary(stdout, argtable, "  %-25s %s\n");
        exitcode = 0;
        goto exit;
    }

    if (nerrors > 0)
    {
        arg_print_errors(stdout, end, progname);
        printf("Try '%s --help' for more information.\n", progname);
        exitcode = 1;
        goto exit;
    }

    if(version->count> 0) {
        printf("%s version is: %s\n",progname, VERSION);
    }
    if(verb->count> 0) {
        Verbose = true;
    }

    if (catalog->count> 0) {
        for(int i = 0; i < 17; i++) {
            printf("op %d:\t %s\n",i+1, operators[i]);
        }
        exitcode = 0;
        goto exit;
    }

    double operand_1 = 0;
    double operand_2 = 0;

    if(operator->count>0){
        if(Verbose == true) {
            printf("operator:\t %s\n", operator->sval[0]);
        }
    } else {
        if(Verbose == true) {
            printf("no operator defined\n");
        }
        arg_print_errors(stdout, end, progname);
        printf("Try '%s --help' for more information.\n", progname);
        exitcode = 1;
        goto exit;
    }

    if(operand1->count>0){
        if(Verbose == true) {
            printf("operand 1:\t %f\n", operand1->dval[0]);
        }
        operand_1 = operand1->dval[0];
    } else {
        if(Verbose == true) {
            printf("no operand defined.\n");
        }
        arg_print_errors(stdout, end, progname);
        printf("Try '%s --help' for more information.\n", progname);
        exitcode = 1;
        goto exit;
    }

    if(operand2->count>0){
        bool isUnary = false;
        for(int i = 0; i < 9; i++) {
            if(strcmp(operator->sval[0], unary_operators[i]) == 0) {
                isUnary = true;
                break;
            }
        }
        if(isUnary){
            if(Verbose == true) {
                printf("operand 2:\t %f (IGNORED)\n", operand2->dval[0]);
            }
            operand_2 = operand2->dval[0];
        } else {
            if(Verbose == true) {
                printf("operand 2:\t %f\n", operand2->dval[0]);
            }
            operand_2 = operand2->dval[0];
        }
        
    }

    bool operator_match = false;
    for(int i = 0; i < 17; i++) {
        if(strcmp(operator->sval[0], operators[i]) == 0) {
            operator_match = true;
            break;
        }
    }
    if(operator_match != true) {
        if(Verbose == true) {
            printf("Err: Operator is not valid/supported\n");
        }
        exitcode = 0;
        goto exit;
    }

    double res = 0;

    // Addittion
    if(strcmp(operator->sval[0], "+") == 0) {
        res = operand_1 + operand_2;
    }
    // Subtraction
    if(strcmp(operator->sval[0], "-") == 0) {
        res = operand_1 - operand_2;
    }

    // Multiplication
    if(strcmp(operator->sval[0], "*") == 0) {
        res = operand_1 * operand_2;
    }

    // Division
    if(strcmp(operator->sval[0], "/") == 0) {
        if(operand_2 == 0) {
            if(Verbose == true) {
                printf("Err: Division by 0 is not allowed\n");
            }
            exitcode = 0;
            goto exit;
        }
        res = operand_1 / operand_2;
    }

    // Modulo
    if(strcmp(operator->sval[0], "%") == 0) {
        res = (int) operand_1 % (int) operand_2;
    }

    // And
    if(strcmp(operator->sval[0], "&") == 0) {
        res = (int) operand_1 & (int) operand_2;
    }

    // Or
    if(strcmp(operator->sval[0], "|") == 0) {
        res = (int) operand_1 | (int) operand_2;
    }

    // Not
    if(strcmp(operator->sval[0], "~") == 0) {
        res = ~ (int) operand_1;
    }

    // Bitwise And
    if(strcmp(operator->sval[0], "^") == 0) {
        res = (int) operand_1 ^ (int) operand_2;
    }

    // sqrt
    if(strcmp(operator->sval[0], "sqrt") == 0) {
        res = sqrt(operand_1);
    }

    // exp
    if(strcmp(operator->sval[0], "exp") == 0) {
        res = exp(operand_1);
    }

    // pow
    if(strcmp(operator->sval[0], "pow") == 0) {
        res = pow(operand_1, operand_2);
    }

    // log
    if(strcmp(operator->sval[0], "log") == 0) {
        res = log(operand_1);
    }

    // log10
    if(strcmp(operator->sval[0], "log10") == 0) {
        res = log10(operand_1);
    }

    // ceil
    if(strcmp(operator->sval[0], "ceil") == 0) {
        res = ceil(operand_1);
    }

    // floor
    if(strcmp(operator->sval[0], "floor") == 0) {
        res = floor(operand_1);
    }

    // sin
    if(strcmp(operator->sval[0], "sin") == 0) {
        res = sin(operand_1);
    }

    // cos
    if(strcmp(operator->sval[0], "cos") == 0) {
        res = cos(operand_1);
    }
    if(Verbose == true) {
        printf("result:\t\t %f\n", res);
    }

    if(o->count > 0) {
        if(Verbose == true) {
            printf("result saved to: %s\n", o->filename[0]);
        }
        FILE *fp;
        fp = fopen(o->filename[0], "w+");
        fprintf(fp, "%f", res);
        fclose(fp);
    }

exit:
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
    return exitcode;
}