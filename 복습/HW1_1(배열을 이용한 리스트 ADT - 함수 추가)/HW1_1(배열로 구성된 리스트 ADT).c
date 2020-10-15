#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 5

typedef int element;
typedef struct {
    element array[MAX_LIST_SIZE];
    int size; // 현재 리스트에 저장된 항목의 개수
} ArrayListType;

//오류 처리 함수
void error(char *message)
{ 
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// 리스트 초기화
void init(ArrayListType *L)
{
    L->size = 0;
}
// 리스트가 비어있으면 1 반환, 그렇지 않으면 0 반환
int is_empty(ArrayListType *L)
{
    return L->size == 0;
}
// 리스트가 가득 차 있으면 1 반환, 그렇지 않으면 0 반환
int is_full(ArrayListType *L)
{
    return L->size == MAX_LIST_SIZE;
}
// 인덱스가 pos인 값 반환
element get_entry(ArrayListType *L, int pos)
{
    if (pos < 0 || pos >= L->size)
        error("위치 오류");
    return L->array[pos];
}
// 리스트 출력
void print_list(ArrayListType *L)
{
    int i;
    for (i = 0; i < L->size; i++)
        printf("%d->", L->array[i]);
    printf("리스트끝\n");
}
// 끝에 삽입
void insert_last(ArrayListType *L, element item)
{
    if (is_full(L)) // L->size >= MAX_LIST_SIZE
        error("리스트 오버플로우");
    L->array[L->size++] = item;
}
// pos 위치에 삽입
void insert_pos(ArrayListType *L, int pos, element item)
{
    int i;
    if (!is_full(L) && (pos >= 0 && pos <= L->size)) {
        for (i = L->size - 1; i >= pos; i--)
            L->array[i + 1] = L->array[i];
        L->array[pos] = item;
        L->size++;
    }
	else
		printf("리스트 오버플로우");
}
// pos 위치 값 삭제, 반환
element delete_pos(ArrayListType *L, int pos)
{
    int i;
	element item;
    if (pos < 0 || pos >= L->size)
        error("위치 오류");
    item = L->array[pos];
    for (i = pos; i < L->size - 1; i++)
        L->array[i] = L->array[i + 1];
    L->size--;
    return item;
}

// 여기서부터 새로 작성한 함수들

// 리스트 비우기
void clear(ArrayListType *L) 
{
	L->size = 0;
}
// item을 리스트의 첫 번째 항목에 추가
void insert_first(ArrayListType *L, element item)
{
	int i;
	if (is_full(L)) 
		printf("리스트 오버플로우\n");
	else {
		for (i = L->size - 1; i >= 0; i--)
			L->array[i + 1] = L->array[i];
		L->array[0] = item;
		L->size++;
	}
}
// 리스트의 항목 수 반환
int get_length(ArrayListType *L)
{
	return L->size;
}
// pos번째 항목을 item으로 바꾼다
void replace(ArrayListType *L, int pos, element item)
{
	if (pos < 0 || pos >= L->size) 
		printf("위치 오류\n");
	else
		L->array[pos] = item;
}
// item이 리스트에 있으면 1을 아니면 0을 반환
int is_in_list(ArrayListType *L, element item)
{
	int i;
	for (i = 0; i < L->size; i++)
		if (L->array[i] == item)
			return 1;
	return 0;
}
// 리스트에서 key값 검색 후 삭제
void delete_by_key(ArrayListType *L, element key)
{
	int i;
	for (i = 0; i < L->size; i++)
		if (L->array[i] == key) {
			delete_pos(L, i);
			return;
		}
	printf("삭제하려는 key값 %d은 리스트에 없습니다\n", key);
}

int main(void)
{
	ArrayListType list;

	init(&list);
	insert_pos(&list, 0, 20);
	insert_pos(&list, 0, 10); print_list(&list); 
	clear(&list); print_list(&list);

	insert_last(&list, 90); print_list(&list); 

	insert_pos(&list, 0, 30);
	insert_pos(&list, 0, 20);
	insert_pos(&list, 0, 10);

	delete_pos(&list, 2); print_list(&list); 
	
	printf("\n추가 함수 테스트\n"); 
	insert_first(&list, 9); print_list(&list); 
	insert_last(&list, 99); print_list(&list);

	insert_first(&list, 1); print_list(&list); // 리스트 꽉 찬 상태

	printf("길이는 %d\n", get_length(&list));
	printf("3번째 데이터는 %d\n", get_entry(&list, 2));

	replace(&list, 3, 40); print_list(&list); 
	printf("20은 리스트에 %s\n", is_in_list(&list, 20) ? "있습니다" : "없습니다");
	printf("22은 리스트에 %s\n", is_in_list(&list, 22) ? "있습니다" : "없습니다");

	delete_by_key(&list, 20); print_list(&list);
	delete_by_key(&list, 22); print_list(&list);
} 