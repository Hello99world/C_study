#include <time.h>


int add_space(char *num);
int change_space(char *num, int status);
int delete_space(char *num);
int add_monthly(char *card, char *num, char *start, char *end);
int change_monthly(char *card, char *num, char *start, char *end);
int delete_monthly(char *card);
int add_year(char *card, char *num);
int change_year(char *card,char *num);
int delete_year(char *card);
int car_run(char *card, int type);
int car_out(char *card);