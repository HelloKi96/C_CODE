//#define _CRT_SECURE_NO_WARNINGS 1
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//
//#define MAX_PARK 5  // ͣ�����������
//#define PRICE_PER_HOUR 10  // ÿСʱͣ������
//
//typedef struct {
//    int number;     // ���ƺ�
//    int arriveTime; // ����ʱ��(Сʱ)
//} Car;
//
//typedef struct {
//    Car data[MAX_PARK];
//    int top;        // ջ��ָ��
//} ParkStack;        // ͣ����ջ
//
//typedef struct WaitNode {
//    Car car;
//    struct WaitNode* next;
//} WaitNode;
//
//typedef struct {
//    WaitNode* front, * rear;
//} WaitQueue;        // �ȴ��������
//
//// ��ʼ��ͣ����ջ
//void InitPark(ParkStack* s) {
//    s->top = -1;
//}
//
//// ��ʼ���ȴ�����
//void InitWaitQueue(WaitQueue* q) {
//    q->front = q->rear = NULL;
//}
//
//// �������ﴦ��
//void Arrival(ParkStack* park, WaitQueue* wait, int number, int time) {
//    if (park->top < MAX_PARK - 1) {  // ͣ����δ��
//        park->top++;
//        park->data[park->top].number = number;
//        park->data[park->top].arriveTime = time;
//        printf("����%d�ĳ�����ͣ��ͣ������λ��%d\n", number, park->top + 1);
//    }
//    else {  // ͣ����������������
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
//        printf("����%d�ĳ���ͣ�ڱ���ϵȴ�\n", number);
//    }
//}
//
//// �����뿪����
//void Leave(ParkStack* park, ParkStack* temp, WaitQueue* wait, int number, int leaveTime) {
//    int i, found = 0;
//    Car movedCar;
//
//    // ��ͣ�����в���Ҫ�뿪�ĳ�
//    for (i = park->top; i >= 0; i--) {
//        if (park->data[i].number == number) {
//            found = 1;
//            break;
//        }
//    }
//
//    if (found) {
//        // ����ͣ��ʱ��ͷ���
//        int parkTime = leaveTime - park->data[i].arriveTime;
//        int fee = parkTime * PRICE_PER_HOUR;
//
//        printf("����%d�ĳ����뿪ͣ������ͣ��ʱ��%dСʱ��Ӧ�շ�%dԪ\n",
//            number, parkTime, fee);
//
//        // ���ó�֮�����ĳ��Ƶ���ʱջ
//        while (park->top > i) {
//            movedCar = park->data[park->top--];
//            temp->data[++temp->top] = movedCar;
//        }
//
//        // ����Ҫ�뿪�ĳ�
//        park->top--;
//
//        // ����ʱջ�ĳ��ƻ�ͣ����
//        while (temp->top >= 0) {
//            movedCar = temp->data[temp->top--];
//            park->data[++park->top] = movedCar;
//        }
//
//        // ������Ƿ��г��ȴ����������ͣ����
//        if (wait->front != NULL) {
//            movedCar = wait->front->car;
//            wait->front = wait->front->next;
//            if (wait->front == NULL) wait->rear = NULL;
//
//            park->top++;
//            park->data[park->top] = movedCar;
//            printf("����%d�ĳ����ӱ������ͣ������λ��%d\n",
//                movedCar.number, park->top + 1);
//        }
//    }
//    else {
//        // ��鳵���Ƿ��ڱ����
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
//            printf("����%d�ĳ����ӱ���뿪��δ�շ�\n", number);
//            free(current);
//        }
//        else {
//            printf("δ�ҵ�����%d�ĳ���\n", number);
//        }
//    }
//}
//
//// ��ʾͣ�����ͱ��״̬
//void ShowStatus(ParkStack* park, WaitQueue* wait) {
//    int i;
//    printf("\n====== ��ǰ״̬ ======\n");
//    printf("ͣ����������%d/%d����\n", park->top + 1, MAX_PARK);
//    for (i = 0; i <= park->top; i++) {
//        printf("λ��%d - ����%d������ʱ��%d:00\n",
//            i + 1, park->data[i].number, park->data[i].arriveTime);
//    }
//
//    printf("\n����ȴ�������");
//    WaitNode* current = wait->front;
//    if (current == NULL) {
//        printf("��\n");
//    }
//    else {
//        printf("\n");
//        while (current != NULL) {
//            printf("����%d������ʱ��%d:00\n",
//                current->car.number, current->car.arriveTime);
//            current = current->next;
//        }
//    }
//    printf("====================\n\n");
//}
//
//int main() {
//    ParkStack park, temp;  // ͣ����ջ����ʱջ
//    WaitQueue wait;        // �ȴ��������
//    char action;
//    int number, time;
//
//    InitPark(&park);
//    InitPark(&temp);
//    InitWaitQueue(&wait);
//
//    printf("ͣ��������ϵͳ\n");
//    printf("����˵����\n");
//    printf("A - ��������\n");
//    printf("D - �����뿪\n");
//    printf("S - ��ʾ״̬\n");
//    printf("E - �˳�ϵͳ\n");
//
//    while (1) {
//        printf("\n���������(A/D/S/E): ");
//        scanf(" %c", &action);
//
//        switch (toupper(action)) {
//        case 'A':
//            printf("�����복�ƺ�: ");
//            scanf("%d", &number);
//            printf("�����뵽��ʱ��(Сʱ): ");
//            scanf("%d", &time);
//            Arrival(&park, &wait, number, time);
//            break;
//
//        case 'D':
//            printf("�����복�ƺ�: ");
//            scanf("%d", &number);
//            printf("�������뿪ʱ��(Сʱ): ");
//            scanf("%d", &time);
//            Leave(&park, &temp, &wait, number, time);
//            break;
//
//        case 'S':
//            ShowStatus(&park, &wait);
//            break;
//
//        case 'E':
//            printf("ϵͳ�˳�\n");
//            return 0;
//
//        default:
//            printf("��Ч����������������\n");
//        }
//    }
//}
