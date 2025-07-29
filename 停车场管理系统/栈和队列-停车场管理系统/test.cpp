//#define _CRT_SECURE_NO_WARNINGS 1
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//
//#define MAX_PARK 5  // 停车场最大容量
//#define PRICE_PER_HOUR 10  // 每小时停车费用
//
//typedef struct {
//    int number;     // 车牌号
//    int arriveTime; // 到达时间(小时)
//} Car;
//
//typedef struct {
//    Car data[MAX_PARK];
//    int top;        // 栈顶指针
//} ParkStack;        // 停车场栈
//
//typedef struct WaitNode {
//    Car car;
//    struct WaitNode* next;
//} WaitNode;
//
//typedef struct {
//    WaitNode* front, * rear;
//} WaitQueue;        // 等待便道队列
//
//// 初始化停车场栈
//void InitPark(ParkStack* s) {
//    s->top = -1;
//}
//
//// 初始化等待队列
//void InitWaitQueue(WaitQueue* q) {
//    q->front = q->rear = NULL;
//}
//
//// 车辆到达处理
//void Arrival(ParkStack* park, WaitQueue* wait, int number, int time) {
//    if (park->top < MAX_PARK - 1) {  // 停车场未满
//        park->top++;
//        park->data[park->top].number = number;
//        park->data[park->top].arriveTime = time;
//        printf("车牌%d的车辆已停入停车场，位置%d\n", number, park->top + 1);
//    }
//    else {  // 停车场已满，进入便道
//        WaitNode* node = (WaitNode*)malloc(sizeof(WaitNode));
//        node->car.number = number;
//        node->car.arriveTime = time;
//        node->next = NULL;
//
//        if (wait->rear == NULL) {
//            wait->front = wait->rear = node;
//        }
//        else {
//            wait->rear->next = node;
//            wait->rear = node;
//        }
//        printf("车牌%d的车辆停在便道上等待\n", number);
//    }
//}
//
//// 车辆离开处理
//void Leave(ParkStack* park, ParkStack* temp, WaitQueue* wait, int number, int leaveTime) {
//    int i, found = 0;
//    Car movedCar;
//
//    // 在停车场中查找要离开的车
//    for (i = park->top; i >= 0; i--) {
//        if (park->data[i].number == number) {
//            found = 1;
//            break;
//        }
//    }
//
//    if (found) {
//        // 计算停留时间和费用
//        int parkTime = leaveTime - park->data[i].arriveTime;
//        int fee = parkTime * PRICE_PER_HOUR;
//
//        printf("车牌%d的车辆离开停车场，停留时间%d小时，应收费%d元\n",
//            number, parkTime, fee);
//
//        // 将该车之后进入的车移到临时栈
//        while (park->top > i) {
//            movedCar = park->data[park->top--];
//            temp->data[++temp->top] = movedCar;
//        }
//
//        // 弹出要离开的车
//        park->top--;
//
//        // 将临时栈的车移回停车场
//        while (temp->top >= 0) {
//            movedCar = temp->data[temp->top--];
//            park->data[++park->top] = movedCar;
//        }
//
//        // 检查便道是否有车等待，有则进入停车场
//        if (wait->front != NULL) {
//            movedCar = wait->front->car;
//            wait->front = wait->front->next;
//            if (wait->front == NULL) wait->rear = NULL;
//
//            park->top++;
//            park->data[park->top] = movedCar;
//            printf("车牌%d的车辆从便道进入停车场，位置%d\n",
//                movedCar.number, park->top + 1);
//        }
//    }
//    else {
//        // 检查车辆是否在便道上
//        WaitNode* prev = NULL, * current = wait->front;
//        found = 0;
//
//        while (current != NULL) {
//            if (current->car.number == number) {
//                found = 1;
//                break;
//            }
//            prev = current;
//            current = current->next;
//        }
//
//        if (found) {
//            if (prev == NULL) {
//                wait->front = current->next;
//                if (wait->front == NULL) wait->rear = NULL;
//            }
//            else {
//                prev->next = current->next;
//                if (current->next == NULL) wait->rear = prev;
//            }
//            printf("车牌%d的车辆从便道离开，未收费\n", number);
//            free(current);
//        }
//        else {
//            printf("未找到车牌%d的车辆\n", number);
//        }
//    }
//}
//
//// 显示停车场和便道状态
//void ShowStatus(ParkStack* park, WaitQueue* wait) {
//    int i;
//    printf("\n====== 当前状态 ======\n");
//    printf("停车场（容量%d/%d）：\n", park->top + 1, MAX_PARK);
//    for (i = 0; i <= park->top; i++) {
//        printf("位置%d - 车牌%d，到达时间%d:00\n",
//            i + 1, park->data[i].number, park->data[i].arriveTime);
//    }
//
//    printf("\n便道等待车辆：");
//    WaitNode* current = wait->front;
//    if (current == NULL) {
//        printf("无\n");
//    }
//    else {
//        printf("\n");
//        while (current != NULL) {
//            printf("车牌%d，到达时间%d:00\n",
//                current->car.number, current->car.arriveTime);
//            current = current->next;
//        }
//    }
//    printf("====================\n\n");
//}
//
//int main() {
//    ParkStack park, temp;  // 停车场栈和临时栈
//    WaitQueue wait;        // 等待便道队列
//    char action;
//    int number, time;
//
//    InitPark(&park);
//    InitPark(&temp);
//    InitWaitQueue(&wait);
//
//    printf("停车场管理系统\n");
//    printf("操作说明：\n");
//    printf("A - 车辆到达\n");
//    printf("D - 车辆离开\n");
//    printf("S - 显示状态\n");
//    printf("E - 退出系统\n");
//
//    while (1) {
//        printf("\n请输入操作(A/D/S/E): ");
//        scanf(" %c", &action);
//
//        switch (toupper(action)) {
//        case 'A':
//            printf("请输入车牌号: ");
//            scanf("%d", &number);
//            printf("请输入到达时间(小时): ");
//            scanf("%d", &time);
//            Arrival(&park, &wait, number, time);
//            break;
//
//        case 'D':
//            printf("请输入车牌号: ");
//            scanf("%d", &number);
//            printf("请输入离开时间(小时): ");
//            scanf("%d", &time);
//            Leave(&park, &temp, &wait, number, time);
//            break;
//
//        case 'S':
//            ShowStatus(&park, &wait);
//            break;
//
//        case 'E':
//            printf("系统退出\n");
//            return 0;
//
//        default:
//            printf("无效操作，请重新输入\n");
//        }
//    }
//}
