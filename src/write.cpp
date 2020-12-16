#include <stdio.h>
#include <stdlib.h>
extern int Times;
const char *lang_compiler[] = {
    (char *)"gcc",
    (char *)"g++"
};
const char *lang_fmt[] = {
    (char *)"c",
    (char *)"cpp"
};

static int write_template(const int times, const int lang) {
    printf("Start Writing bash script...\n");
    system("touch run.sh");
    FILE *fp = fopen("./run.sh", "w");
    fprintf(fp, "%s ./main.%s -ggdb3 -Wall -Werror -O2\n", lang_compiler[lang], lang_fmt[lang]);
    for (int i = 1; i <= times; i++) {
        fprintf(fp, "echo test%d\n", i);    
        fprintf(fp, "./a.out < %d.in\n", i);
    }
    fclose(fp);
    printf("Done.\n");
    return 0;
}

int write_c_template() {
    write_template(Times, 0);
    return 0;
}

int write_cpp_template() {
    write_template(Times, 1);
    return 0;
}