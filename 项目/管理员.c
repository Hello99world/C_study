#include "工具.h"
#include "业务.h"

// 添加车位
void add_space_admin()
{
    char num[8];
    printf("输入车位号: ");
    scanf("%s", num);
    if (add_space(num) == 0)
    {
        printf("添加成功\n");
        char log[100];
        sprintf(log, "管理员增加车位：%s", num);
        add_logs(log);
    }
    else
    {
        printf("添加失败\n");
    }
}

// 修改车位
void change_space_admin()
{
    char num[8];
    int status;
    printf("输入车位号: ");
    scanf("%s", num);
    printf("输入状态(0空闲/1占用): ");
    scanf("%d", &status);
    if (change_space(num, status) == 0)
    {
        printf("修改成功\n");
        char log[100];
        sprintf(log, "管理员修改车位：%s", num);
        add_logs(log);
    }
    else
    {
        printf("修改失败\n");
    }
}

// 删除车位
void delete_space_admin()
{
    char num[8];
    printf("输入车位号: ");
    scanf("%s", num);
    int ret = delete_space(num);
    if (ret == 0)
    {
        printf("删除成功\n");
        char log[100];
        sprintf(log, "管理员删除车位：%s", num);
        add_logs(log);
    }
    else if (ret == -2)
    {
        printf("车位有车，不能删除\n");
    }
    else
    {
        printf("删除失败\n");
    }
}

// 添加月租车
void add_monthly_admin()
{
    char card[16], num[8], start[12], end[12];
    printf("输入车牌号: ");
    scanf("%s", card);
    printf("输入车位号: ");
    scanf("%s", num);
    printf("输入起始日期(YYYY-MM-DD): ");
    scanf("%s", start);
    printf("输入结束日期(YYYY-MM-DD): ");
    scanf("%s", end);
    if (add_monthly(card, num, start, end) == 0)
    {
        printf("添加成功\n");
        char log[100];
        sprintf(log, "管理员增加月租车：%s", card);
        add_logs(log);
    }
    else
    {
        printf("添加失败\n");
    }
}

// 修改月租车
void change_monthly_admin()
{
    char card[16], num[8], start[12], end[12];
    printf("输入车牌号: ");
    scanf("%s", card);
    printf("输入车位号: ");
    scanf("%s", num);
    printf("输入新起始日期(YYYY-MM-DD): ");
    scanf("%s", start);
    printf("输入新的结束日期(YYYY-MM-DD): ");
    scanf("%s", end);
    if (change_monthly(card, num, start, end) == 0)
    {
        printf("修改成功\n");
        char log[100];
        sprintf(log, "管理员修改月租车：%s", card);
        add_logs(log);
    }
    else
    {
        printf("修改失败\n");
    }
}

// 删除月租车
void delete_monthly_admin()
{
    char card[16];
    printf("输入车牌号: ");
    scanf("%s", card);
    if (delete_monthly(card) == 0)
    {
        printf("删除成功\n");
        char log[100];
        sprintf(log, "管理员删除月租车：%s", card);
        add_logs(log);
    }
    else
    {
        printf("删除失败\n");
    }
}

// 查询月租车
void query_monthly_admin()
{
    print("月租车辆.txt");
    char log[100];
    strcpy(log, "管理员查询月租车");
    add_logs(log);
}

// 添加长期车
void add_year_admin()
{
    char card[16], num[8];
    printf("输入车牌号: ");
    scanf("%s", card);
    printf("输入车位号: ");
    scanf("%s", num);
    if (add_year(card, num) == 0)
    {
        printf("添加成功\n");
        char log[100];
        sprintf(log, "管理员增加长期车：%s", card);
        add_logs(log);
    }
    else
    {
        printf("添加失败\n");
    }
}

// 修改长期车
void change_year_admin()
{
    char card[16], num[8];
    printf("输入车牌号: ");
    scanf("%s", card);
    printf("输入新车位号: ");
    scanf("%s", num);
    if (change_year(card, num) == 0)
    {
        printf("修改成功\n");
        char log[100];
        sprintf(log, "管理员修改长期车：%s", card);
        add_logs(log);
    }
    else
    {
        printf("修改失败\n");
    }
}

// 查询长期车
void query_year_admin()
{
    print("长期车辆.txt");
    char log[100];
    strcpy(log, "管理员查询长期车");
    add_logs(log);
}

// 删除长期车
void delete_year_admin()
{
    char card[16];
    printf("输入车牌号: ");
    scanf("%s", card);
    if (delete_year(card) == 0)
    {
        printf("删除成功\n");
        char log[100];
        sprintf(log, "管理员删除长期车：%s", card);
        add_logs(log);
    }
    else
    {
        printf("删除失败\n");
    }
}

// 查询当前车辆
void cars_now_admin()
{
    print("cars_now.txt");
    char log[100];
    strcpy(log, "管理员查询当前入场车辆");
    add_logs(log);
}

int main()
{
    int opt;
    void (*admin_func[])() = {
        add_space_admin,
        change_space_admin,
        delete_space_admin,
        cars_now_admin,
        add_monthly_admin,
        change_monthly_admin,
        delete_monthly_admin,
        query_monthly_admin,
        add_year_admin,
        change_year_admin,
        delete_year_admin,
        query_year_admin};
    printf("管理员登录成功\n");
    while (1)
    {
        printf("\n-------------------- 后台管理 ---------------------\n");
        printf("1. 添加车位   2. 修改车位   3. 删除车位  4. 查看入场车辆\n");
        printf("5. 添加月租车 6. 修改月租车 7. 删除月租车 8. 查看月租车\n");
        printf("9. 添加长期车 10. 修改长期车 11. 删除长期车 12.查看长期车\n");
        printf("0. 退出\n");
        printf("选择: ");
        scanf("%d", &opt);
        if (opt == 0)
        {
            break;
        }
        if (opt >= 1 && opt <= 12)
        {
            admin_func[opt - 1]();
        }
        else
        {
            printf("无效选择\n");
        }
    }
    return 0;
}
