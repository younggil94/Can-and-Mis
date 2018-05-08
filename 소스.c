#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct
{
	int M, C; //������, ������
	int Answer_Count; //�� ī��Ʈ
	int boat; //��Ʈ
	void * pNode;
}typedef Node;
Node Value, Queue[999999], Result[50];

int Rear = 0, Front = 0;
int Mis_Count = 0, Can_Count = 0;
int Result_Count = 0;
int Boat_Count = 0;

void InputData(Node *input);	// ����� �Է� �Լ�
void Solution(Node *input);	// ��ǥ ã�� �Լ�
int Deduplication(Node *value);	// �ߺ� ���� �Լ�
int Condition(Node *value);		// ���� �˻� �Լ�
void AnswerPrint();				// �� ī��Ʈ ��� ���
void MovePrint(Node *value);	// �����丮 ���

int main() {
	int input = 1;

	while (1)
	{
		// ����ü �ʱ�ȭ
		memset(&Value, 0, sizeof(Value));
		memset(&Queue, 0, sizeof(Node) * 999999);
		memset(&Result, 0, sizeof(Node) * 50);

		InputData(&Value);
		Solution(&Value);
		AnswerPrint();

		while (1) {
			printf("��� ����(1), ����(2) >> ");
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
				printf("'Y'�Ǵ� 'N'�� �Է����ּ���.\n");
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
		printf("\n  �� �� �� �� �� >> ");
		scanf_s("%d", &input->M);

		if (input->M < 0)
		{
			printf("\n�����簡 �������� �ʽ��ϴ�.\n");
			return;
		}

		printf("\n  �� �� �� �� �� >> ");
		scanf_s("%d", &input->C);

		if (input->C < 0)
		{
			printf("\n�������� �������� �ʽ��ϴ�.\n");
			return;
		}

		printf("\n  ��Ʈ �¼��� �� >> ");
		scanf_s("%d", &Boat_Count);

		if (Boat_Count < 2)
		{
			printf("\n��Ʈ �¼����� �ּ� 2ĭ�̻� �̿����մϴ�.\n");
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
		printf("\n  �ظ� ã�� ���߽��ϴ�.\n\n");
	}
	else
	{
		int Solfound = 1;
		system("cls");
		for (int i = 0; i < Result_Count; i++)
		{
			Value = Result[i];
			printf("\t    %02d�� ��[%dȸ]\n", Solfound++, Value.Answer_Count);
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