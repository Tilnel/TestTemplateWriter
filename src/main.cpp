#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <common.h>

static struct {
    char *abbr;
    char *name;
    char *description;
    int (*handler) ();
} arg_table [] = {
    { (char *)"-h", (char *)"--help", (char *)"Display information about all supported arguments", help },
    { (char *)"-p", (char *)"--cpp" , (char *)"Write test template for C++", write_cpp_template },
    { (char *)"-c", (char *)""      , (char *)"Write test template for C"  , write_c_template },
};
const int NR_ARG = (sizeof(arg_table) / sizeof(arg_table[0]));
int (*Todo) () = NULL;

static inline int arg_parser(const int argc, char **argv) {
   /*   For return value, we hope :             *
    *   0 for normal exit,                      *
    *   1 for no argument,                      *
    *   2 for unknown argument,                 *
    *   What if we need the wrong argument?     *
    *   i.e. return a char*. How?   (TODO)      */
    int tmp = 0, i, j;
    if (argc == 1) return 1;
    for (i = 1; i < argc; i++) {
        for (j = 0; j < NR_ARG; j++) {
            if      (!strcmp(arg_table[j].abbr, argv[i])) { Todo = arg_table[j].handler; break; }
            else if (!strcmp(arg_table[j].name, argv[i])) { Todo = arg_table[j].handler; break; }
            else if (          0 < (tmp = atoi(argv[i]))) {                 Times = tmp; break; }
        }
        if (j == NR_ARG) return 2;
    }
    return 0;
}

int main(int argc, char **argv) {
    Times = 1;  
    int res = arg_parser(argc, argv);
    switch (res) {
        case 0 : Todo(); break;
        case 1 : help(); break;
        case 2 : printf("Unknown argument.\n"); help(); break;
        default :;
    }
   /* Also, for undefined details, use default.                    *
    * We are also free to have a conifguration file for the future */ 
    return 0;
}

inline int help() {
    printf("Usage: wt [LANG] [CASE#]\n");
    for (int i = 0; i < NR_ARG; i++) 
        printf("%4s%10s              %s\n", arg_table[i].abbr, arg_table[i].name, arg_table[i].description);
    return 0;
}