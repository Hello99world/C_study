#include "./f29_门禁V3_工具.h"
extern Node *head;
extern mlog *mylog;
extern Node *current;
extern char login_status;
void login(Node *head);
void add();
void reset_passwd();
void user_list();
void user_detail();
void del_user();
void modify_status();
void unlock();
void reset_passwd();
void modify_phone();
void modify_address();
void logout();