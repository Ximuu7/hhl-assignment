// assigment 11.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct E{
    char name[64];
    float damage;
    float magic;
    struct E* next;
}Enemy;

typedef struct {
    int num;
    Enemy* next;
}EnemyLinkedList;

void AddNewEnemy(EnemyLinkedList* head, Enemy *newenemy){
    newenemy->next = head->next;
    head->next = newenemy;
    head->num++;
}

void RemoveEnemy(EnemyLinkedList* head, Enemy* enemy) {
    Enemy *ee = head->next;
    if (ee == enemy)
    {
        head->next = ee->next;
        head->num--;
        free(ee);
        return;
    }
    while (ee->next != enemy && ee->next == NULL)
    {
        ee = ee->next;
    }
    if (ee->next == enemy)
    {
        Enemy* temp = ee->next;
        ee->next = ee->next->next;
        free(temp);
        head->num--;
    }

}

Enemy* FindEnemy_Name(EnemyLinkedList* head, char* name) {
    Enemy* e = head->next;
    while (e != NULL && strcmp(name,e->name)!=0) {
        e = e -> next;
    }
        return e;
    
}

void SortEnemy_damage(EnemyLinkedList* head) {
    if (head->next == NULL)
        return;
    Enemy* e1 = head->next;
    Enemy* e2 = NULL;
    if (head->next->next == NULL && e1->damage > e1->next->damage) {
        e2 = e1->next;
        e2->next = e1;
        head->next = e2;
        return;
    }
    loop:e1 = head->next;
    e2 = e1->next;
    if (e1->damage < e2->damage){
        head->next = e2;
        e1->next = e2->next;
        e2->next = e1;
        
    }


    int check = 1;
    while (e2->next != NULL&&check==1)
    {        
        if (e2->next->damage > e2->damage) {
            e1->next = e2->next;
            e2->next = e2->next->next;
            e1->next->next = e2;
            check = 0;
        }
        e1 = e1->next;
        e2 = e1->next;     

    }
    if (check == 0)
        goto loop;
    
    

    return;
}

void Print(EnemyLinkedList* head) {
    Enemy* e = head->next;
    while (e != NULL) {
        printf("%s,%.0f,%.0f\t", e->name, e->damage, e->magic);
        e = e->next;
    }
    printf("\n");
}

void Destory(EnemyLinkedList* head) {
    Enemy* e = head->next;
    Enemy* ee = e->next;
    while (ee != NULL) {
        ee = e->next;
        free(e);
        e = ee;
    }
    free(head);
}

int main()
{
    srand(time(NULL));
    EnemyLinkedList* head = (EnemyLinkedList*)malloc((unsigned)sizeof(EnemyLinkedList));
    head->next = NULL;
    head->num = 0;
    int nCand = rand() % 20;
    char* find = NULL;
    for (int i = 0; i < 20; i++) {
        Enemy* e = (Enemy*)malloc((unsigned)sizeof(Enemy));
        e->damage = (rand() % 10/1.0f);
        e->magic = (rand() % 10/1.0f);
        e->name[0] = 'A' + rand() % 26;
        e->name[1] = 'A' + rand() % 26;
        e->name[2] = 'A' + rand() % 26;
        e->name[3] = '\0';
        AddNewEnemy(head, e);
        if (nCand == i)
            find = e->name;
    }
    printf("%d\n", nCand);
    Print(head);
    Enemy* e = FindEnemy_Name(head, find);
    printf("The Enemy found name:%s,damage:%.0f,magic:%.0f\n", e->name, e->damage, e->magic);
    RemoveEnemy(head, e);
    printf("Remove it from the list\n");
    Print(head);
    printf("sort the list by damage\n");
    SortEnemy_damage(head);
    Print(head);
    Destory(head);
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
