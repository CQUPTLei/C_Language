
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<string.h>
struct Book {
    char ID[20];
    char Name[10];
    char Author[30];
    char Press[30];
    int Total;
}books[1000];
int num = 0;
void Copy(struct Book* arr, int i, int j)
{
    strcpy(arr[i].ID, arr[j].ID);
    strcpy(arr[i].Name, arr[j].Name);
    strcpy(arr[i].Author, arr[j].Author);
    strcpy(arr[i].Press, arr[j].Press);
    arr[i].Total = arr[j].Total;
}

int Book_SearchByName(char name[])
{
    int i;
    for (i = 0; i < num; i++)
    {
        if (strcmp(books[i].Name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}
int Book_SearchByIndex(char id[])
{
    int i;
    for (i = 0; i < num; i++)
    {
        if (strcmp(books[i].ID, id) == 0)
        {
            return i;
        }
    }
    return -1;
}
void Book_DisplaySingle(int index)
{
    printf("%10s%10s%10s%10s%10s\n", "序号", "书名", "作者", "出版社", "数量");
    printf("-------------------------------------------------------------\n");
    printf("%10s%10s%10s%10s%10.2d\n", books[index].ID, books[index].Name, books[index].Author, books[index].Press, books[index].Total);
}
void inputt()
{
    while (1)
    {
        printf("请输入序号:");
        scanf("%s", &books[num].ID);
        getchar();
        printf("请输入书名;");
        scanf("%s", &books[num].Name);
        getchar();
        printf("请输入作者:");
        scanf("%s", &books[num].Author);
        getchar();
        printf("请输入出版社:");
        scanf("%s", &books[num].Press);
        getchar();
        printf("请输入数量:");
        scanf("%d", &books[num].Total);
        getchar();
        if (Book_SearchByIndex(books[num].ID) == -1)
        {
            num++;
        }
        else
        {
            printf("序号重复，输入数据无效 !!!\n");
        }

        printf("是否继续?(y/n)");
        if (getchar() == 'n')
        {
            break;
        }
    }
}
void modify()
{
    while (1)
    {
        char id[20];
        int index;
        printf("请输入要修改的图书的序号:");
        scanf("%s", &id);
        getchar();
        index = Book_SearchByIndex(id);
        if (index == -1)
        {
            printf("图书不存在!\n");
        }
        else
        {
            printf("你要修改的图书信息为:\n");
            Book_DisplaySingle(index);
            printf("请输入新值\n");
            printf("请输入序号:");
            scanf("%s", &books[num].ID);
            getchar();
            printf("请输入书名;");
            scanf("%s", &books[num].Name);
            getchar();
            printf("请输入作者:");
            scanf("%s", &books[num].Author);
            getchar();
            printf("请输入出版社:");
            scanf("%s", &books[num].Press);
            getchar();
            printf("请输入数量:");
            scanf("%d", &books[num].Total);
            getchar();
        }
        printf("是否继续?(y/n)");
        if (getchar() == 'n')
        {
            break;
        }
    }
}
void deletee()
{
    int i;
    while (1)
    {
        char id[20];
        int index;
        printf("请输入要删除的图书的序号:");
        scanf("%s", &id);
        getchar();
        index = Book_SearchByIndex(id);
        if (index == -1)
        {
            printf("书本不存在!\n");
        }
        else
        {
            printf("你要删除的书本信息为:\n");
            Book_DisplaySingle(index);
            printf("是否真的要删除?(y/n)");
            if (getchar() == 'y')
            {
                for (i = index; i < num - 1; i++)
                {
                    Copy(books, i, i + 1);
                    books[i] = books[i + 1];
                }
                num--;
            }
            getchar();
        }

        printf("是否继续?(y/n)");
        if (getchar() == 'n')
        {
            break;
        }
    }
}
void display()
{
    int a;
    printf("%10s%10s%10s%10s%10s\n", "序号", "书名", "作者", "出版社", "数量");
    printf("-------------------------------------------------------------\n");
    for (a = 0; a < num; a++)
    {
        printf("%10s%10s%10s%10s%10.2d\n", books[a].ID, books[a].Name,
            books[a].Author, books[a].Press, books[a].Total);
    }
}
void insert()
{
    int a, b, c;
    printf("请输入你要插入的位置");
    scanf("%d", &a);
    if (a > num) {
        printf("输入的位置有误，请重新输入,当前共%d条数据\n", num);
        scanf("%d", &a);
    }
    for (b = num - 1; b >= a - 1; b--)
    {
        strcpy(books[b + 1].ID, books[b].ID);
        strcpy(books[b + 1].Name, books[b].Name);
        strcpy(books[b + 1].Author, books[b].Author);
        strcpy(books[b + 1].Press, books[b].Press);
        books[b + 1].Total = books[b].Total;
        Copy(books, b + 1, b);
    }
    num++;
    printf("请输入序号:");
    scanf("%s", &books[a - 1].ID);
    getchar();
    printf("请输入姓名:");
    scanf("%s", &books[a - 1].Name);
    getchar();
    printf("请输入作者:");
    scanf("%f", &books[a - 1].Author);
    getchar();
    printf("请输入出版社:");
    scanf("%f", &books[a - 1].Press);
    getchar();
    printf("请输入数量:");
    scanf("%d", &books[a - 1].Total);
    getchar();
}
void search()
{
    while (1)
    {
        char name[20];
        int index;
        printf("请输入要查询的书本的书名:");
        scanf("%s", &name);
        getchar();
        index = Book_SearchByName(name);
        if (index == -1)
        {
            printf("图书不存在!\n");
        }
        else
        {
            printf("你要查询的书本信息为:\n");
            Book_DisplaySingle(index);
        }
        printf("是否继续?(y/n)");
        if (getchar() == 'n')
        {
            break;
        }
    }
}
void Save()
{
    FILE* fp = fopen("temp.txt", "w+");
    fprintf(fp, "%d\n", num);
    for (int i = 0; i < num; i++)
    {
        fprintf(fp, "%s %s %s %s %d\n", books[i].ID, books[i].Name, books[i].Author, books[i].Press, books[i].Total);
    }
    fclose(fp);
}
void Load()
{
    FILE* fp = fopen("temp.txt", "r");
    fscanf(fp, "%d", &num);
    for (int i = 0; i < num; i++)
    {
        fscanf(fp, "%s %s %s %s %d\n", books[i].ID, books[i].Name, books[i].Author, books[i].Press,&books[i].Total);
    }
    fclose(fp);
}
int main() {
    char i;
    while (1) {
        Load();
        printf("\t\t\t\t\t-------- 图书管理系统-------\n\n\n\n");
        printf("\t\t\t\t\t1. 添加图书记录\n\n");
        printf("\t\t\t\t\t2. 修改图书记录\n\n");
        printf("\t\t\t\t\t3. 删除图书记录\n\n");
        printf("\t\t\t\t\t4. 插入图书记录\n\n");
        printf("\t\t\t\t\t5. 显示图书记录\n\n");
        printf("\t\t\t\t\t6. 查询图书记录\n\n");
        printf("\t\t\t\t\t0. 退出\n\n\n");
        printf("请选择(0-6):");
        scanf("%c", &i);
        switch (i) {
        case 1:inputt(); break;
        case 2:modify(); break;
        case 3:deletee(); break;
        case 4:insert(); break;
        case 5:display(); break;
        case 6:search(); break;
        case 0:exit(0);
        default:;
        }
        Save();
    }
    return 0;
}