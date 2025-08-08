#define _CRT_SECURE_NO_WARNINGS 1

 /** ͣ��������ϵͳ - ʹ��ջ�Ͷ���ʵ��
 * ���ܣ�
 * 1. ģ��ͣ������ջ�ṹ���͵ȴ���������нṹ��
 * 2. ����������/�뿪�¼�
 * 3. ����ͣ�����ã�ÿСʱ10Ԫ��
 * 4. ʵʱ��ʾͣ�����ͱ��״̬*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARK 5      // ͣ�����������
#define PRICE_PER_HOUR 10 // ÿСʱͣ������

 /* ������Ϣ�ṹ�� */
typedef struct {
    int number;         // ���ƺţ�Ψһ��ʶ��
    int arriveTime;     // ����ʱ�䣨24Сʱ������Сʱ��
} Car;

/* ͣ����ջ�ṹ - ����ȳ� */
typedef struct {
    Car data[MAX_PARK]; // ͣ������λ����
    int top;            // ջ��ָ�루-1��ʾ��ջ��
} ParkStack;

/* �ȴ����нڵ� - ����ʵ�� */
typedef struct WaitNode {
    Car car;            // ������Ϣ
    struct WaitNode* next; // ��һ���ڵ�ָ��
} WaitNode;

/* �ȴ����нṹ - �Ƚ��ȳ� */
typedef struct {
    WaitNode* front;    // ����ָ��
    WaitNode* rear;     // ��βָ��
} WaitQueue;


 //* �������ƣ�InitPark
 //* ������������ʼ��ͣ����ջ
 //* ���������s - ָ��ParkStack�ṹ��ָ��
 //* ����ֵ����

void InitPark(ParkStack* s) {
    s->top = -1;  // ��ʼ��ջ��ָ��Ϊ��ջ״̬
}


 //* �������ƣ�InitWaitQueue
 //* ������������ʼ���ȴ��������
 //* ���������q - ָ��WaitQueue�ṹ��ָ��
 //* ����ֵ����

void InitWaitQueue(WaitQueue* q) {
    q->front = q->rear = NULL;  // ��ʼ������ͷβָ��Ϊ��
}


 //* ������������Сд��ĸת��Ϊ��д��ĸ
 //* ���������c - ��ת�����ַ�
 //* ����ֵ��ת����Ĵ�д��ĸ��ԭ�ַ�

char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';  // ASCII��ת��
    }
    return c;
}


 //* �������ƣ�Arrival
 //* ���������������������¼�
 //* ���������
 //*   park  - ָ��ͣ����ջ��ָ��
 //*   wait  - ָ��ȴ����е�ָ��
 //*   number - ���ﳵ�����ƺ�
 //*   time   - ����ʱ�䣨����Сʱ��
 //* ����ֵ����
 
void Arrival(ParkStack* park, WaitQueue* wait, int number, int time) {
    // ���ͣ�����Ƿ�����
    if (park->top < MAX_PARK - 1) {
        // ͣ����δ����ֱ��ͣ��
        park->top++;
        park->data[park->top].number = number;
        park->data[park->top].arriveTime = time;
        printf("����%d�ĳ�����ͣ��ͣ������λ��%d\n", number, park->top + 1);
    }
    else {
        // ͣ�����������������ȴ�
        WaitNode* node = (WaitNode*)malloc(sizeof(WaitNode));
        node->car.number = number;
        node->car.arriveTime = time;
        node->next = NULL;

        if (wait->rear == NULL) {
            // ���Ϊ�գ���ʼ������
            wait->front = wait->rear = node;
        }
        else {
            // ��ӵ���β
            wait->rear->next = node;
            wait->rear = node;
        }
        printf("����%d�ĳ���ͣ�ڱ���ϵȴ�\n", number);
    }
}

// �����뿪����
//parkͣ����ջָ�룬temp��ʱջָ�룬wait�ȴ�����ָ�룬number���ƺţ�leaveTime�뿪ʱ��
void Leave(ParkStack* park, ParkStack* temp, WaitQueue* wait, int number, int leaveTime) {
    int i, found = 0;
    Car movedCar;

    // ��ͣ�����в��ҳ���
    for (i = park->top; i >= 0; i--) {
        if (park->data[i].number == number) {
            found = 1;
            break;
        }
    }

    if (found) {
        int parkTime = leaveTime - park->data[i].arriveTime;
        int fee = parkTime * PRICE_PER_HOUR;

        printf("����%d�ĳ����뿪ͣ������ͣ��ʱ��%dСʱ��Ӧ�շ�%dԪ\n",
            number, parkTime, fee);

        // �ƶ��赲��������ʱջ
        while (park->top > i) {
            movedCar = park->data[park->top--];
            temp->data[++temp->top] = movedCar;
        }

        // ����Ŀ�공��
        park->top--;

        // ����ʱջ�����ƻ�
        while (temp->top >= 0) {
            movedCar = temp->data[temp->top--];
            park->data[++park->top] = movedCar;
        }

        // �ӱ������һ����
        if (wait->front != NULL) {
            movedCar = wait->front->car;
            wait->front = wait->front->next;
            if (wait->front == NULL) wait->rear = NULL;

            park->top++;
            park->data[park->top] = movedCar;
            printf("����%d�ĳ����ӱ������ͣ������λ��%d\n",
                movedCar.number, park->top + 1);
        }
    }
    else {
        // ��������Ƿ��иó�
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
            printf("����%d�ĳ����ӱ���뿪��δ�շ�\n", number);
            free(current);
        }
        else {
            printf("δ�ҵ�����%d�ĳ���\n", number);
        }
    }
}

// ��ʾϵͳ��ǰ״̬
void ShowStatus(ParkStack* park, WaitQueue* wait) {
    int i;
    printf("\n====== ��ǰ״̬ ======\n");
    printf("ͣ����������%d/%d����\n", park->top + 1, MAX_PARK);
    for (i = 0; i <= park->top; i++) {
        printf("λ��%d - ����%d������ʱ��%d:00\n",
            i + 1, park->data[i].number, park->data[i].arriveTime);
    }

    printf("\n����ȴ�������");
    WaitNode* current = wait->front;
    if (current == NULL) {
        printf("��\n");
    }
    else {
        printf("\n");
        while (current != NULL) {
            printf("����%d������ʱ��%d:00\n",
                current->car.number, current->car.arriveTime);
            current = current->next;
        }
    }
    printf("====================\n\n");
}

int main() {
    ParkStack park, temp;  // ͣ����ջ����ʱջ�����ڵ�����
    WaitQueue wait;        // �ȴ��������
    char action;           // �û���������
    int number, time;      // ���ƺź͵���/�뿪ʱ��

    // ��ʼ�����ݽṹ
    InitPark(&park);
    InitPark(&temp);
    InitWaitQueue(&wait);

    // ��ӡ����˵��
    printf("ͣ��������ϵͳ\n");
    printf("����˵����\n");
    printf("A - ��������\n");
    printf("D - �����뿪\n");
    printf("S - ��ʾ״̬\n");
    printf("E - �˳�ϵͳ\n");

    // ��ѭ��
    while (1) {
        printf("\n���������(A/D/S/E): ");
        scanf(" %c", &action);
        action = toUpper(action);  // ͳһת��Ϊ��д

        switch (action) {
        case 'A':
            printf("�����복�ƺ�: ");
            scanf("%d", &number);
            printf("�����뵽��ʱ��(Сʱ): ");
            scanf("%d", &time);
            Arrival(&park, &wait, number, time);
            break;

        case 'D':
            printf("�����복�ƺ�: ");
            scanf("%d", &number);
            printf("�������뿪ʱ��(Сʱ): ");
            scanf("%d", &time);
            Leave(&park, &temp, &wait, number, time);
            break;

        case 'S':
            ShowStatus(&park, &wait);
            break;

        case 'E':
            printf("ϵͳ�˳�\n");
            return 0;

        default:
            printf("��Ч����������������\n");
        }
    }
}
