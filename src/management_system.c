#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// ���� ����
FILE* outf;

// ��¥ ����ü
typedef struct {
    char year[5];   // ����
    char month[3];  // ��
    char day[3];    // ��
} _stDate;

// ���� ���� ���� ����Ʈ ���
typedef struct _node {
    int roomno;           // ��ѹ�
    char name[20];        // �̸�
    char phone[40];       // ��ȭ��ȣ
    double price;         // ���
    char address[40];     // �ּ�
    _stDate enter_date;   // �Խ� ��¥
    _stDate exit_date;    // ��� ��¥
    struct _node* prev;   // ���� ������
    struct _node* next;   // ���� ������  
} t_node;

// ���� ���� ����Ʈ ����ü
typedef struct double_linked {
    t_node* head;  // ����Ʈ�� ù ��° ���
    t_node* tail;  // ����Ʈ�� ������ ���
    t_node* curr;  // ���� ���
    int num_of_data; // ������ ����
} t_list;
void resort(t_list* t);
// ��带 �Է� ������� �߰��ϴ� �Լ�
void add0(t_node* new_node, t_list* t) {
    new_node->prev = NULL;
    new_node->next = NULL;

    if (t->head == NULL) {
        t->head = t->tail = t->curr = new_node;  // ù ��° ���
    }
    else {
        t->tail->next = new_node;  // ���� tail�� ���� ���� �߰�
        new_node->prev = t->tail;  // ���ο� ����� prev�� ���� tail
        t->tail = new_node;        // tail�� �� ���� ������Ʈ
    }

    t->num_of_data++;  // ������ �� ����
    resort(t);  // ���� �߰��� ������ ����
}

// ���� ����Ʈ�� roomno �������� �����ϴ� �Լ�
void resort(t_list* t) {
    if (t->head == NULL || t->head->next == NULL) {
        return;
    }

    t_node* i = t->head;
    while (i != NULL) {
        t_node* j = i->next;
        while (j != NULL) {
            if (i->roomno > j->roomno) {
                // i�� j(i->next)�� roomno�� ���ؼ�, i�� �� ũ�� ���� ��ȯ
                int temp_roomno = i->roomno;
                char temp_name[20];
                char temp_phone[40];
                double temp_price = i->price;
                char temp_address[40];
                _stDate temp_enter_date = i->enter_date;
                _stDate temp_exit_date = i->exit_date;

                strcpy(temp_name, i->name);
                strcpy(temp_phone, i->phone);
                strcpy(temp_address, i->address);
                temp_enter_date = i->enter_date;
                temp_exit_date = i->exit_date;

                // i�� j�� ������ ��ȯ
                i->roomno = j->roomno;
                strcpy(i->name, j->name);
                strcpy(i->phone, j->phone);
                i->price = j->price;
                strcpy(i->address, j->address);
                i->enter_date = j->enter_date;
                i->exit_date = j->exit_date;

                j->roomno = temp_roomno;
                strcpy(j->name, temp_name);
                strcpy(j->phone, temp_phone);
                j->price = temp_price;
                strcpy(j->address, temp_address);
                j->enter_date = temp_enter_date;
                j->exit_date = temp_exit_date;
            }
            j = j->next;
        }
        i = i->next;
    }
}

// �޴� ��� �Լ�
void show_menu(void) {
    char* reservation[] = {
        "-----<�Է� ����>------\n",
        "1. ��    ��\n",      // ����
        "2. ��    ��\n",      // ���
        "3. ��    ��\n",      // ���� ���� ����
        "4. ���� ��ȸ\n",      // ���� ��ȸ
        "5. ��ü��ȸ\n",      // ��ü ��ȸ
        "9. ����\n"       // ����
    };
    for (int i = 0; i < 7; i++)  // �޴� �׸� ������ 6���� ����
        printf("%s", reservation[i]);
}

// ���� �Լ�
void make_reservation(t_list* t) {
    t_node* new_node = (t_node*)malloc(sizeof(t_node));
    if (new_node == NULL) {
        printf("�޸� �Ҵ� ����\n");
        return;
    }

    // ���� ���� �Է�
    printf("--------------< �Է� ���� >---------------------\n");
    printf("roomno: ");
    if (scanf("%d", &new_node->roomno) != 1) {
        printf("�Է� ����: �߸��� roomno ��\n");
        free(new_node);
        return;
    }

    // ���� ��ȣ �ߺ� Ȯ��
    t_node* current = t->head;
    while (current != NULL) {
        if (current->roomno == new_node->roomno) {
            printf("�ش� ������ �̹� ����Ǿ����ϴ�. �ٸ� ���� ��ȣ�� �������ּ���.\n");
            free(new_node);
            return;  // ���� ���
        }
        current = current->next;
    }

    printf("name: ");
    scanf("%19s", new_node->name);  // �̸� �Է� �� �ִ� 19�ڱ��� �Է¹���
    printf("phone: ");
    scanf("%39s", new_node->phone); // ��ȭ��ȣ �Է� �� �ִ� 39�ڱ��� �Է¹���
    printf("���: ");
    if (scanf("%lf", &new_node->price) != 1) {
        printf("�Է� ����: �߸��� ��� ��\n");
        free(new_node);
        return;
    }
    printf("�ּ�: ");
    scanf("%39s", new_node->address); // �ּ� �Է� �� �ִ� 39�ڱ��� �Է¹���
    printf("�Խ� ��¥ (YYYY-MM-DD): ");
    scanf("%4s-%2s-%2s", new_node->enter_date.year, new_node->enter_date.month, new_node->enter_date.day);
    printf("��� ��¥ (YYYY-MM-DD): ");
    scanf("%4s-%2s-%2s", new_node->exit_date.year, new_node->exit_date.month, new_node->exit_date.day);

    add0(new_node, t);  // ��� �߰� Ȯ��
}
//����Ʈ ���� �Լ�
void del0(t_list* t, int roomno, char* name, char* phone)
{
    t_node* current = t->head;    // ����Ʈ ó������ ����

    while (current != NULL)         // ��ã�� �� ���� �ݺ�
    {
        if (current->roomno == roomno && strcmp(current->name, name) == 0 && strcmp(current->phone, phone) == 0)  // ã��
        {
            // ������ ��尡 head�� ���
            if (current->prev == NULL)
            {
                t->head = current->next;
                if (t->head != NULL)        // ������ ��� �ڿ� �ٸ� ��尡 �����ϴ� ���
                {
                    t->head->prev = NULL; // ���Ӱ� ���۵ȴ� ����Ʈ / ���ϸ� ���ο� head�� ���� head�� ����� �� ����
                }
            }
            // ������ ��尡 tail�� ���
            if (current->next == NULL)
            {
                t->tail = current->prev;
                if (t->tail != NULL)
                {
                    t->tail->next = NULL;
                }
            }
            //������ ��尡 �߰��� ���
            else
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            printf("���ó�� �Ǿ����ϴ�.\n");
            return;
        }
        current = current->next;
    }
    printf("���� �����Դϴ�.");
}
void check_out(t_list* t)
{
    int roomno;
    char name[40], phone[40], confirm;

    printf("--------------< ����(���) >---------------------\n");
    printf("roomno: ");
    if (scanf("%d", &roomno) != 1) {
        printf("�Է� ����: �߸��� roomno ��\n");
        return;
    }
    printf("name: ");
    scanf("%19s", name);  // �̸� �Է� �� �ִ� 19�ڱ��� �Է¹���
    printf("phone: ");
    scanf("%39s", phone);

    // �Է� ���ۿ� ���� �ִ� ���� ���� ó��
    getchar();

    while (1) {
        printf("Ȯ�� (y/n): ");
        scanf("%c", &confirm);  // y �Ǵ� n �Է� �ޱ�

        if (confirm == 'y' || confirm == 'Y') {
            del0(t, roomno, name, phone);  // ��� ó�� �Լ� ȣ��
            break;
        }
        else if (confirm == 'n' || confirm == 'N') {
            printf("��� ���\n");
            break;
        }
        else {
            printf("�ùٸ� ���� �Է����ּ���.\n");  // �߸��� �Է� ó��
            getchar();  // ���ۿ� ���� �ִ� ���� ���� ó��
        }
    }
    return;
}
//����Ʈ ���� �Լ�
void change_res(t_list* t)
{
    int roomno;
    char name[40], phone[40], confirm;
    t_node* current;

    printf("--------------< ���� ���� >---------------------\n");
    printf("roomno: ");
    if (scanf("%d", &roomno) != 1) {
        printf("�Է� ����: �߸��� roomno ��\n");
        return;
    }
    printf("name: ");
    scanf("%19s", name);  // �̸� �Է� �� �ִ� 19�ڱ��� �Է¹���
    printf("phone: ");
    scanf("%39s", phone);

    current = t->head;
    while (current != NULL) {
        // �Էµ� roomno, name, phone�� ��ġ�ϴ� ������ ã��
        if (current->roomno == roomno && strcmp(current->name, name) == 0 && strcmp(current->phone, phone) == 0) {
            printf("������ ã�ҽ��ϴ�: \n");
            printf("���� ����: roomno: %d, name: %s, phone: %s, ���: %.2lf, �ּ�: %s, �Խ�: %s-%s-%s, ���: %s-%s-%s\n",
                current->roomno, current->name, current->phone, current->price, current->address,
                current->enter_date.year, current->enter_date.month, current->enter_date.day,
                current->exit_date.year, current->exit_date.month, current->exit_date.day);

            // ���� ����
            while (1) {
                printf("������ �׸��� �����ϼ���: \n");
                printf("1. ���\n");
                printf("2. �ּ�\n");
                printf("3. �Խ� ��¥\n");
                printf("4. ��� ��¥\n");
                printf("5. ���� ���\n");
                printf("����: ");
                if (scanf("%d", &confirm) != 1) {
                    printf("�Է� ����: ���ڸ� �Է��ϼ���.\n");
                    getchar(); // �Է� ���� ����
                    continue;
                }

                switch (confirm) {
                case 1:
                    printf("�� ���: ");
                    if (scanf("%lf", &current->price) != 1) {
                        printf("�Է� ����: �߸��� ��� ��\n");
                        return;
                    }
                    break;
                case 2:
                    printf("�� �ּ�: ");
                    scanf("%39s", current->address);
                    break;
                case 3:
                    printf("�� �Խ� ��¥ (YYYY-MM-DD): ");
                    scanf("%4s-%2s-%2s", current->enter_date.year, current->enter_date.month, current->enter_date.day);
                    break;
                case 4:
                    printf("�� ��� ��¥ (YYYY-MM-DD): ");
                    scanf("%4s-%2s-%2s", current->exit_date.year, current->exit_date.month, current->exit_date.day);
                    break;
                case 5:
                    printf("���� ���\n");
                    return;
                default:
                    printf("�߸��� �����Դϴ�.\n");
                    continue;
                }

                // ������ ���� ���� Ȯ��
                printf("������ ���� ����: roomno: %d, name: %s, phone: %s, ���: %.2lf, �ּ�: %s, �Խ�: %s-%s-%s, ���: %s-%s-%s\n",
                    current->roomno, current->name, current->phone, current->price, current->address,
                    current->enter_date.year, current->enter_date.month, current->enter_date.day,
                    current->exit_date.year, current->exit_date.month, current->exit_date.day);

                // ���� Ȯ��
                while (1) {
                    printf("������ ������ �����Ͻðڽ��ϱ�? (y/n): ");
                    getchar();  // ���� �Է��� ���� ���� ó��
                    scanf("%c", &confirm);

                    if (confirm == 'y' || confirm == 'Y') {
                        printf("������ �Ϸ�Ǿ����ϴ�.\n");
                        return;
                    }
                    else if (confirm == 'n' || confirm == 'N') {
                        printf("������ ��ҵǾ����ϴ�.\n");
                        return;
                    }
                    else {
                        printf("�ùٸ� ���� �Է����ּ���.\n");  // �߸��� �Է� ó��
                    }
                }
            }
        }
        current = current->next;
    }
    printf("������ ã�� �� �����ϴ�.\n");
}
// ���� ��ȸ �Լ�
void print_one(t_list* t) {
    int input;
    printf("roomno �Է�: ");
    scanf("%d", &input);

    t_node* temp = t->head;

    while (temp != NULL) {
        if (temp->roomno == input) {
            printf("  %d          %s       %s      %.2lf     %s      %s-%s-%s   %s-%s-%s\n",
                temp->roomno, temp->name, temp->phone, temp->price, temp->address,
                temp->enter_date.year, temp->enter_date.month, temp->enter_date.day,
                temp->exit_date.year, temp->exit_date.month, temp->exit_date.day);
            return;
        }
        temp = temp->next;
    }

    printf("������ �������� �ʽ��ϴ�.\n");
}

// ��ü ���� ������ ����ϴ� �Լ�
void show_all(t_list* t) {
    printf("----------------------------------< ��ü��ȸ(������ ��ü��ȸ) >--------------------------------\n");
    printf("  roomno       name     phoneno          ���      �ּ�          �Խ�                ���\n");
    printf("---------   ----------   -----------        ---------  ---------- ------------- -------------------------\n");

    t_node* temp = t->head;
    while (temp != NULL) {
        printf("  %d          %s       %s      %.2lf     %s      %s-%s-%s   %s-%s-%s\n",
            temp->roomno, temp->name, temp->phone, temp->price, temp->address,
            temp->enter_date.year, temp->enter_date.month, temp->enter_date.day,
            temp->exit_date.year, temp->exit_date.month, temp->exit_date.day);
        temp = temp->next;
    }
}

// ���� ������ ���Ͽ� �����ϴ� �Լ�
void save_reservations_to_file(t_list* t) {

    t_node* temp = t->head;
    while (temp != NULL) {
        fprintf(outf, "%d          %s   %s    %.2lf    %s    %s-%s-%s %s-%s-%s\n",
            temp->roomno, temp->name, temp->phone, temp->price, temp->address,
            temp->enter_date.year, temp->enter_date.month, temp->enter_date.day,
            temp->exit_date.year, temp->exit_date.month, temp->exit_date.day);
        temp = temp->next;
    }

    fclose(outf);
    printf("���� ������ ���Ͽ� ����Ǿ����ϴ�.\n");
}
//���� �Լ� 
void exit_program(t_list* t) {
    char confirm;
    printf("�����Ͻðڽ��ϱ�? (y/n): ");
    scanf(" %c", &confirm);  // ���� ���ڸ� ó���ϱ� ���� �տ� ���� �߰�

    if (confirm == 'y' || confirm == 'Y') {
        save_reservations_to_file(t);  // ���� ������ ���Ͽ� ����
        printf("���α׷��� �����մϴ�.\n");
        fclose(outf);
        exit(0);  // ���α׷� ����
    }
    else {
        printf("���ᰡ ��ҵǾ����ϴ�.\n");
    }
}
// main �Լ�
int main(void) {
    t_list reservation_list = { NULL, NULL, NULL, 0 };  // ���� ����Ʈ �ʱ�ȭ
    if ((outf = fopen("reservation.txt", "w")) == NULL) {
        fprintf(stderr, "Can't Open reservation.txt...\n");
        exit(-1);
    }


    while (1) {
        int choice = 0;
        t_node new_node;  // �� ���� ���

        show_menu();
        printf("����: ");
        scanf("%d", &choice);



        switch (choice) {
        case 1:
            make_reservation(&reservation_list);  // ��  �� 
            break;
        case 2:
            check_out(&reservation_list);         //��   ��
            break;
        case 3:
            change_res(&reservation_list);        //��   ��
            break;
        case 4:
            print_one(&reservation_list);         // ���� ���� ��ȸ
            break;

        case 5:
            show_all(&reservation_list);          // ��ü ���� ��ȸ
            break;
        case 9:
            exit_program(&reservation_list);      // ���� + ����
            break;

        default:
            printf("�߸��� �����Դϴ�.\n");
        }
    }

    fclose(outf);
    return 0;
}

#endif