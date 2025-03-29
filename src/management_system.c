#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// 파일 저장
FILE* outf;

// 날짜 구조체
typedef struct {
    char year[5];   // 연도
    char month[3];  // 월
    char day[3];    // 일
} _stDate;

// 예약 이중 연결 리스트 노드
typedef struct _node {
    int roomno;           // 룸넘버
    char name[20];        // 이름
    char phone[40];       // 전화번호
    double price;         // 요금
    char address[40];     // 주소
    _stDate enter_date;   // 입실 날짜
    _stDate exit_date;    // 퇴실 날짜
    struct _node* prev;   // 이전 포인터
    struct _node* next;   // 다음 포인터  
} t_node;

// 이중 연결 리스트 구조체
typedef struct double_linked {
    t_node* head;  // 리스트의 첫 번째 노드
    t_node* tail;  // 리스트의 마지막 노드
    t_node* curr;  // 현재 노드
    int num_of_data; // 데이터 개수
} t_list;
void resort(t_list* t);
// 노드를 입력 순서대로 추가하는 함수
void add0(t_node* new_node, t_list* t) {
    new_node->prev = NULL;
    new_node->next = NULL;

    if (t->head == NULL) {
        t->head = t->tail = t->curr = new_node;  // 첫 번째 노드
    }
    else {
        t->tail->next = new_node;  // 기존 tail의 다음 노드로 추가
        new_node->prev = t->tail;  // 새로운 노드의 prev는 기존 tail
        t->tail = new_node;        // tail을 새 노드로 업데이트
    }

    t->num_of_data++;  // 데이터 수 증가
    resort(t);  // 새로 추가된 예약을 정렬
}

// 예약 리스트를 roomno 기준으로 정렬하는 함수
void resort(t_list* t) {
    if (t->head == NULL || t->head->next == NULL) {
        return;
    }

    t_node* i = t->head;
    while (i != NULL) {
        t_node* j = i->next;
        while (j != NULL) {
            if (i->roomno > j->roomno) {
                // i와 j(i->next)의 roomno를 비교해서, i가 더 크면 둘을 교환
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

                // i와 j의 값들을 교환
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

// 메뉴 출력 함수
void show_menu(void) {
    char* reservation[] = {
        "-----<입력 예약>------\n",
        "1. 예    약\n",      // 예약
        "2. 퇴    실\n",      // 퇴실
        "3. 수    정\n",      // 예약 내역 수정
        "4. 개별 조회\n",      // 개별 조회
        "5. 전체조회\n",      // 전체 조회
        "9. 종료\n"       // 종료
    };
    for (int i = 0; i < 7; i++)  // 메뉴 항목 개수를 6으로 수정
        printf("%s", reservation[i]);
}

// 예약 함수
void make_reservation(t_list* t) {
    t_node* new_node = (t_node*)malloc(sizeof(t_node));
    if (new_node == NULL) {
        printf("메모리 할당 실패\n");
        return;
    }

    // 예약 정보 입력
    printf("--------------< 입력 예약 >---------------------\n");
    printf("roomno: ");
    if (scanf("%d", &new_node->roomno) != 1) {
        printf("입력 오류: 잘못된 roomno 값\n");
        free(new_node);
        return;
    }

    // 객실 번호 중복 확인
    t_node* current = t->head;
    while (current != NULL) {
        if (current->roomno == new_node->roomno) {
            printf("해당 객실은 이미 예약되었습니다. 다른 객실 번호를 선택해주세요.\n");
            free(new_node);
            return;  // 예약 취소
        }
        current = current->next;
    }

    printf("name: ");
    scanf("%19s", new_node->name);  // 이름 입력 시 최대 19자까지 입력받음
    printf("phone: ");
    scanf("%39s", new_node->phone); // 전화번호 입력 시 최대 39자까지 입력받음
    printf("요금: ");
    if (scanf("%lf", &new_node->price) != 1) {
        printf("입력 오류: 잘못된 요금 값\n");
        free(new_node);
        return;
    }
    printf("주소: ");
    scanf("%39s", new_node->address); // 주소 입력 시 최대 39자까지 입력받음
    printf("입실 날짜 (YYYY-MM-DD): ");
    scanf("%4s-%2s-%2s", new_node->enter_date.year, new_node->enter_date.month, new_node->enter_date.day);
    printf("퇴실 날짜 (YYYY-MM-DD): ");
    scanf("%4s-%2s-%2s", new_node->exit_date.year, new_node->exit_date.month, new_node->exit_date.day);

    add0(new_node, t);  // 노드 추가 확인
}
//리스트 삭제 함수
void del0(t_list* t, int roomno, char* name, char* phone)
{
    t_node* current = t->head;    // 리스트 처음부터 시작

    while (current != NULL)         // 못찾을 떄 까지 반복
    {
        if (current->roomno == roomno && strcmp(current->name, name) == 0 && strcmp(current->phone, phone) == 0)  // 찾기
        {
            // 삭제할 노드가 head인 경우
            if (current->prev == NULL)
            {
                t->head = current->next;
                if (t->head != NULL)        // 삭제할 노드 뒤에 다른 노드가 존재하는 경우
                {
                    t->head->prev = NULL; // 새롭게 시작된는 리스트 / 안하면 새로운 head가 이전 head와 연결될 수 있음
                }
            }
            // 삭제할 노드가 tail인 경우
            if (current->next == NULL)
            {
                t->tail = current->prev;
                if (t->tail != NULL)
                {
                    t->tail->next = NULL;
                }
            }
            //삭제할 노드가 중간인 경우
            else
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            printf("퇴실처리 되었습니다.\n");
            return;
        }
        current = current->next;
    }
    printf("없는 객실입니다.");
}
void check_out(t_list* t)
{
    int roomno;
    char name[40], phone[40], confirm;

    printf("--------------< 삭제(퇴실) >---------------------\n");
    printf("roomno: ");
    if (scanf("%d", &roomno) != 1) {
        printf("입력 오류: 잘못된 roomno 값\n");
        return;
    }
    printf("name: ");
    scanf("%19s", name);  // 이름 입력 시 최대 19자까지 입력받음
    printf("phone: ");
    scanf("%39s", phone);

    // 입력 버퍼에 남아 있는 개행 문자 처리
    getchar();

    while (1) {
        printf("확인 (y/n): ");
        scanf("%c", &confirm);  // y 또는 n 입력 받기

        if (confirm == 'y' || confirm == 'Y') {
            del0(t, roomno, name, phone);  // 퇴실 처리 함수 호출
            break;
        }
        else if (confirm == 'n' || confirm == 'N') {
            printf("퇴실 취소\n");
            break;
        }
        else {
            printf("올바른 값을 입력해주세요.\n");  // 잘못된 입력 처리
            getchar();  // 버퍼에 남아 있는 개행 문자 처리
        }
    }
    return;
}
//리스트 수정 함수
void change_res(t_list* t)
{
    int roomno;
    char name[40], phone[40], confirm;
    t_node* current;

    printf("--------------< 수정 예약 >---------------------\n");
    printf("roomno: ");
    if (scanf("%d", &roomno) != 1) {
        printf("입력 오류: 잘못된 roomno 값\n");
        return;
    }
    printf("name: ");
    scanf("%19s", name);  // 이름 입력 시 최대 19자까지 입력받음
    printf("phone: ");
    scanf("%39s", phone);

    current = t->head;
    while (current != NULL) {
        // 입력된 roomno, name, phone과 일치하는 예약을 찾기
        if (current->roomno == roomno && strcmp(current->name, name) == 0 && strcmp(current->phone, phone) == 0) {
            printf("예약을 찾았습니다: \n");
            printf("현재 정보: roomno: %d, name: %s, phone: %s, 요금: %.2lf, 주소: %s, 입실: %s-%s-%s, 퇴실: %s-%s-%s\n",
                current->roomno, current->name, current->phone, current->price, current->address,
                current->enter_date.year, current->enter_date.month, current->enter_date.day,
                current->exit_date.year, current->exit_date.month, current->exit_date.day);

            // 예약 수정
            while (1) {
                printf("수정할 항목을 선택하세요: \n");
                printf("1. 요금\n");
                printf("2. 주소\n");
                printf("3. 입실 날짜\n");
                printf("4. 퇴실 날짜\n");
                printf("5. 수정 취소\n");
                printf("선택: ");
                if (scanf("%d", &confirm) != 1) {
                    printf("입력 오류: 숫자를 입력하세요.\n");
                    getchar(); // 입력 버퍼 비우기
                    continue;
                }

                switch (confirm) {
                case 1:
                    printf("새 요금: ");
                    if (scanf("%lf", &current->price) != 1) {
                        printf("입력 오류: 잘못된 요금 값\n");
                        return;
                    }
                    break;
                case 2:
                    printf("새 주소: ");
                    scanf("%39s", current->address);
                    break;
                case 3:
                    printf("새 입실 날짜 (YYYY-MM-DD): ");
                    scanf("%4s-%2s-%2s", current->enter_date.year, current->enter_date.month, current->enter_date.day);
                    break;
                case 4:
                    printf("새 퇴실 날짜 (YYYY-MM-DD): ");
                    scanf("%4s-%2s-%2s", current->exit_date.year, current->exit_date.month, current->exit_date.day);
                    break;
                case 5:
                    printf("수정 취소\n");
                    return;
                default:
                    printf("잘못된 선택입니다.\n");
                    continue;
                }

                // 수정된 예약 정보 확인
                printf("수정된 예약 정보: roomno: %d, name: %s, phone: %s, 요금: %.2lf, 주소: %s, 입실: %s-%s-%s, 퇴실: %s-%s-%s\n",
                    current->roomno, current->name, current->phone, current->price, current->address,
                    current->enter_date.year, current->enter_date.month, current->enter_date.day,
                    current->exit_date.year, current->exit_date.month, current->exit_date.day);

                // 수정 확인
                while (1) {
                    printf("수정된 내용을 저장하시겠습니까? (y/n): ");
                    getchar();  // 이전 입력의 개행 문자 처리
                    scanf("%c", &confirm);

                    if (confirm == 'y' || confirm == 'Y') {
                        printf("수정이 완료되었습니다.\n");
                        return;
                    }
                    else if (confirm == 'n' || confirm == 'N') {
                        printf("수정이 취소되었습니다.\n");
                        return;
                    }
                    else {
                        printf("올바른 값을 입력해주세요.\n");  // 잘못된 입력 처리
                    }
                }
            }
        }
        current = current->next;
    }
    printf("예약을 찾을 수 없습니다.\n");
}
// 개별 조회 함수
void print_one(t_list* t) {
    int input;
    printf("roomno 입력: ");
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

    printf("예약이 존재하지 않습니다.\n");
}

// 전체 예약 정보를 출력하는 함수
void show_all(t_list* t) {
    printf("----------------------------------< 전체조회(예약자 전체조회) >--------------------------------\n");
    printf("  roomno       name     phoneno          요금      주소          입실                퇴실\n");
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

// 예약 정보를 파일에 저장하는 함수
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
    printf("예약 정보가 파일에 저장되었습니다.\n");
}
//종료 함수 
void exit_program(t_list* t) {
    char confirm;
    printf("종료하시겠습니까? (y/n): ");
    scanf(" %c", &confirm);  // 공백 문자를 처리하기 위해 앞에 공백 추가

    if (confirm == 'y' || confirm == 'Y') {
        save_reservations_to_file(t);  // 예약 정보를 파일에 저장
        printf("프로그램을 종료합니다.\n");
        fclose(outf);
        exit(0);  // 프로그램 종료
    }
    else {
        printf("종료가 취소되었습니다.\n");
    }
}
// main 함수
int main(void) {
    t_list reservation_list = { NULL, NULL, NULL, 0 };  // 예약 리스트 초기화
    if ((outf = fopen("reservation.txt", "w")) == NULL) {
        fprintf(stderr, "Can't Open reservation.txt...\n");
        exit(-1);
    }


    while (1) {
        int choice = 0;
        t_node new_node;  // 새 예약 노드

        show_menu();
        printf("선택: ");
        scanf("%d", &choice);



        switch (choice) {
        case 1:
            make_reservation(&reservation_list);  // 예  약 
            break;
        case 2:
            check_out(&reservation_list);         //삭   제
            break;
        case 3:
            change_res(&reservation_list);        //수   정
            break;
        case 4:
            print_one(&reservation_list);         // 개별 예약 조회
            break;

        case 5:
            show_all(&reservation_list);          // 전체 예약 조회
            break;
        case 9:
            exit_program(&reservation_list);      // 종료 + 저장
            break;

        default:
            printf("잘못된 선택입니다.\n");
        }
    }

    fclose(outf);
    return 0;
}

#endif