#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct
{
	int M, C; //선교사, 식인종
	int Answer_Count; //해 카운트
	int boat; //보트
	void * pNode;
}typedef Node;
Node Value, Queue[999999], Result[50];

int Rear = 0, Front = 0;
int Mis_Count = 0, Can_Count = 0;
int Result_Count = 0;
int Boat_Count = 0;

void InputData(Node *input);	// 사용자 입력 함수
void Solution(Node *input);	// 목표 찾는 함수
int Deduplication(Node *value);	// 중복 제거 함수
int Condition(Node *value);		// 조건 검사 함수
void AnswerPrint();				// 해 카운트 결과 출력
void MovePrint(Node *value);	// 히스토리 출력

int main() {
	int input = 1;

	while (1)
	{
		// 구조체 초기화
		memset(&Value, 0, sizeof(Value));
		memset(&Queue, 0, sizeof(Node) * 999999);
		memset(&Result, 0, sizeof(Node) * 50);

		InputData(&Value);
		Solution(&Value);
		AnswerPrint();

		while (1) {
			printf("계속 진행(1), 종료(2) >> ");
			scanf_s("%d", &input);
			if (input == 1) {
				Rear = 0;
				Front = 0;
				Result_Count = 0;
				break;
			}
			else if (input == 2) {
				return 0;
			}
			else {
				printf("'Y'또는 'N'을 입력해주세요.\n");
				return 0;
			}
		}
	}
}

void InputData(Node *input)
{
	while (1)
	{
		system("cls");
		printf("\n  선 교 사 의 수 >> ");
		scanf_s("%d", &input->M);

		if (input->M < 0)
		{
			printf("\n선교사가 존재하지 않습니다.\n");
			return;
		}

		printf("\n  식 인 종 의 수 >> ");
		scanf_s("%d", &input->C);

		if (input->C < 0)
		{
			printf("\n식인종이 존재하지 않습니다.\n");
			return;
		}

		printf("\n  보트 좌석의 수 >> ");
		scanf_s("%d", &Boat_Count);

		if (Boat_Count < 2)
		{
			printf("\n보트 좌석수는 최소 2칸이상 이여야합니다.\n");
			return;
		}
		break;
	}

	Can_Count = input->C;
	Mis_Count = input->M;

	input->Answer_Count++;
}

void Solution(Node *input)
{
	int Solution = 0;
	int Solution_Count = 0;
	int FirstSolution = 0;

	Queue[Rear++] = *input;

	while (Rear != Front && !Solution_Count)
	{
		if (Rear > 999999 || Front > 999999)
		{
			printf("\n\tOverflow\n");
			break;
		}

		Value = Queue[Front++];

		if (Deduplication(&Value))
		{
			if (FirstSolution)
			{
				if (Value.Answer_Count <= Solution)
				{
					Result[Result_Count++] = Value;
				}
				else
				{
					Solution_Count = 1;
				}
			}
			else
			{
				FirstSolution = 1;
				Solution = Value.Answer_Count;
				Result[Result_Count++] = Value;
			}
		}
		else
		{
			if (FirstSolution && Value.Answer_Count > Solution)
			{
				Solution_Count = 1;
				continue;
			}

			for (int i = 0; i <= Boat_Count; i++)
			{
				for (int j = 0; j <= Boat_Count; j++)
				{
					if (i == 0 && j == 0)
						continue;
					if (i + j > Boat_Count)
						break;

					Node Value_Sum;
					memset(&Value_Sum, 0, sizeof(Node));

					int nBoatDirection = Value.boat ? 1 : -1;

					Value_Sum.pNode = malloc(sizeof(Node));

					memcpy(Value_Sum.pNode, &Value, sizeof(Node));

					Value_Sum.M = Value.M + i * nBoatDirection;
					Value_Sum.C = Value.C + j * nBoatDirection;
					Value_Sum.boat = !Value.boat;
					Value_Sum.Answer_Count = Value.Answer_Count + 1;

					if (Condition(&Value_Sum) == 0)
						Queue[Rear++] = Value_Sum;
				}
			}
		}
	}
}

int Deduplication(Node *value)
{
	int bResult = 0;

	if (value->C == 0 && value->M == 0 && value->boat == 1) {
		bResult = 1;
	}

	return bResult;
}

int Condition(Node *value)
{
	if (value->M < 0 || value->C < 0 || value->M > Mis_Count || value->C > Can_Count)
		return 1;

	if (value->M < value->C && value->M > 0)
		return 1;

	if ((Mis_Count - value->M < Can_Count - value->C) && (Mis_Count - value->M > 0))
		return 1;

	return 0;
}

void AnswerPrint()
{
	if (Result_Count == 0)
	{
		printf("\n  해를 찾지 못했습니다.\n\n");
	}
	else
	{
		int Solfound = 1;
		system("cls");
		for (int i = 0; i < Result_Count; i++)
		{
			Value = Result[i];
			printf("\t    %02d번 해[%d회]\n", Solfound++, Value.Answer_Count);
			printf("   START   |    BOAT     |    GOAL\n");
			MovePrint(&Value);

			printf("\n");
		}
	}
}

void MovePrint(Node *value)
{
	const char *boat;

	if (value->pNode != NULL)
		MovePrint(value->pNode);

	if (value->boat)
		boat = "R";
	else
		boat = "L";

	printf("%dMIS  %dCAN |      %s      | %dMIS  %dCAN\n", value->M, value->C, boat,
		Mis_Count - value->M, Can_Count - value->C);
}