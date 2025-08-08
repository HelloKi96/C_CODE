#define _CRT_SECURE_NO_WARNINGS 1

 /** 停车场管理系统 - 使用栈和队列实现
 * 功能：
 * 1. 模拟停车场（栈结构）和等待便道（队列结构）
 * 2. 处理车辆到达/离开事件
 * 3. 计算停车费用（每小时10元）
 * 4. 实时显示停车场和便道状态*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARK 5      // 停车场最大容量
#define PRICE_PER_HOUR 10 // 每小时停车费用

 /* 车辆信息结构体 */
typedef struct {
    int number;         // 车牌号（唯一标识）
    int arriveTime;     // 到达时间（24小时制整数小时）
} Car;

/* 停车场栈结构 - 后进先出 */
typedef struct {
    Car data[MAX_PARK]; // 停车场车位数组
    int top;            // 栈顶指针（-1表示空栈）
} ParkStack;

/* 等待队列节点 - 链表实现 */
typedef struct WaitNode {
    Car car;            // 车辆信息
    struct WaitNode* next; // 下一个节点指针
} WaitNode;

/* 等待队列结构 - 先进先出 */
typedef struct {
    WaitNode* front;    // 队首指针
    WaitNode* rear;     // 队尾指针
} WaitQueue;


 //* 函数名称：InitPark
 //* 功能描述：初始化停车场栈
 //* 输入参数：s - 指向ParkStack结构的指针
 //* 返回值：无

void InitPark(ParkStack* s) {
    s->top = -1;  // 初始化栈顶指针为空栈状态
}


 //* 函数名称：InitWaitQueue
 //* 功能描述：初始化等待便道队列
 //* 输入参数：q - 指向WaitQueue结构的指针
 //* 返回值：无

void InitWaitQueue(WaitQueue* q) {
    q->front = q->rear = NULL;  // 初始化队列头尾指针为空
}


 //* 功能描述：将小写字母转换为大写字母
 //* 输入参数：c - 待转换的字符
 //* 返回值：转换后的大写字母或原字符

char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';  // ASCII码转换
    }
    return c;
}


 //* 函数名称：Arrival
 //* 功能描述：处理车辆到达事件
 //* 输入参数：
 //*   park  - 指向停车场栈的指针
 //*   wait  - 指向等待队列的指针
 //*   number - 到达车辆车牌号
 //*   time   - 到达时间（整数小时）
 //* 返回值：无
 
void Arrival(ParkStack* park, WaitQueue* wait, int number, int time) {
    // 检查停车场是否已满
    if (park->top < MAX_PARK - 1) {
        // 停车场未满，直接停入
        park->top++;
        park->data[park->top].number = number;
        park->data[park->top].arriveTime = time;
        printf("车牌%d的车辆已停入停车场，位置%d\n", number, park->top + 1);
    }
    else {
        // 停车场已满，进入便道等待
        WaitNode* node = (WaitNode*)malloc(sizeof(WaitNode));
        node->car.number = number;
        node->car.arriveTime = time;
        node->next = NULL;

        if (wait->rear == NULL) {
            // 便道为空，初始化队列
            wait->front = wait->rear = node;
        }
        else {
            // 添加到队尾
            wait->rear->next = node;
            wait->rear = node;
        }
        printf("车牌%d的车辆停在便道上等待\n", number);
    }
}

// 车辆离开处理
//park停车场栈指针，temp临时栈指针，wait等待队列指针，number车牌号，leaveTime离开时间
void Leave(ParkStack* park, ParkStack* temp, WaitQueue* wait, int number, int leaveTime) {
    int i, found = 0;
    Car movedCar;

    // 在停车场中查找车辆
    for (i = park->top; i >= 0; i--) {
        if (park->data[i].number == number) {
            found = 1;
            break;
        }
    }

    if (found) {
        int parkTime = leaveTime - park->data[i].arriveTime;
        int fee = parkTime * PRICE_PER_HOUR;

        printf("车牌%d的车辆离开停车场，停留时间%d小时，应收费%d元\n",
            number, parkTime, fee);

        // 移动阻挡车辆到临时栈
        while (park->top > i) {
            movedCar = park->data[park->top--];
            temp->data[++temp->top] = movedCar;
        }

        // 弹出目标车辆
        park->top--;

        // 将临时栈车辆移回
        while (temp->top >= 0) {
            movedCar = temp->data[temp->top--];
            park->data[++park->top] = movedCar;
        }

        // 从便道移入一辆车
        if (wait->front != NULL) {
            movedCar = wait->front->car;
            wait->front = wait->front->next;
            if (wait->front == NULL) wait->rear = NULL;

            park->top++;
            park->data[park->top] = movedCar;
            printf("车牌%d的车辆从便道进入停车场，位置%d\n",
                movedCar.number, park->top + 1);
        }
    }
    else {
        // 检查便道上是否有该车
        WaitNode* prev = NULL, * current = wait->front;
        found = 0;

        while (current != NULL) {
            if (current->car.number == number) {
                found = 1;
                break;
            }
            prev = current;
            current = current->next;
        }

        if (found) {
            if (prev == NULL) {
                wait->front = current->next;
                if (wait->front == NULL) wait->rear = NULL;
            }
            else {
                prev->next = current->next;
                if (current->next == NULL) wait->rear = prev;
            }
            printf("车牌%d的车辆从便道离开，未收费\n", number);
            free(current);
        }
        else {
            printf("未找到车牌%d的车辆\n", number);
        }
    }
}

// 显示系统当前状态
void ShowStatus(ParkStack* park, WaitQueue* wait) {
    int i;
    printf("\n====== 当前状态 ======\n");
    printf("停车场（容量%d/%d）：\n", park->top + 1, MAX_PARK);
    for (i = 0; i <= park->top; i++) {
        printf("位置%d - 车牌%d，到达时间%d:00\n",
            i + 1, park->data[i].number, park->data[i].arriveTime);
    }

    printf("\n便道等待车辆：");
    WaitNode* current = wait->front;
    if (current == NULL) {
        printf("无\n");
    }
    else {
        printf("\n");
        while (current != NULL) {
            printf("车牌%d，到达时间%d:00\n",
                current->car.number, current->car.arriveTime);
            current = current->next;
        }
    }
    printf("====================\n\n");
}

int main() {
    ParkStack park, temp;  // 停车场栈和临时栈（用于倒车）
    WaitQueue wait;        // 等待便道队列
    char action;           // 用户操作命令
    int number, time;      // 车牌号和到达/离开时间

    // 初始化数据结构
    InitPark(&park);
    InitPark(&temp);
    InitWaitQueue(&wait);

    // 打印操作说明
    printf("停车场管理系统\n");
    printf("操作说明：\n");
    printf("A - 车辆到达\n");
    printf("D - 车辆离开\n");
    printf("S - 显示状态\n");
    printf("E - 退出系统\n");

    // 主循环
    while (1) {
        printf("\n请输入操作(A/D/S/E): ");
        scanf(" %c", &action);
        action = toUpper(action);  // 统一转换为大写

        switch (action) {
        case 'A':
            printf("请输入车牌号: ");
            scanf("%d", &number);
            printf("请输入到达时间(小时): ");
            scanf("%d", &time);
            Arrival(&park, &wait, number, time);
            break;

        case 'D':
            printf("请输入车牌号: ");
            scanf("%d", &number);
            printf("请输入离开时间(小时): ");
            scanf("%d", &time);
            Leave(&park, &temp, &wait, number, time);
            break;

        case 'S':
            ShowStatus(&park, &wait);
            break;

        case 'E':
            printf("系统退出\n");
            return 0;

        default:
            printf("无效操作，请重新输入\n");
        }
    }
}
