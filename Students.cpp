#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct student
{
    int id;
    char name[50];
    char sex[5];
    int age;
    float gpa;
    char rank[10];
}ST;
struct listStudents
{
	ST list[100];
	int countStudent;
};
void delLineBreaks(char x[])
{
	size_t len = strlen(x);
	if(x[len-1]=='\n')
	{
		x[len-1]='\0';
	}
}
void inputStudent(ST &st)
{
	printf("\nID: ");
	scanf("%d", &st.id);
	getchar();
	printf("\nName: ");
	fflush(stdin);
	fgets(st.name, sizeof(st.name), stdin);
	delLineBreaks(st.name);
	printf("\nSex: ");
	fflush(stdin);
	fgets(st.sex, sizeof(st.sex), stdin);
	delLineBreaks(st.sex);
	printf("\nAge: ");
	scanf("%d", &st.age);
	printf("\nGPA: ");
	scanf("%f", &st.gpa);
}
void rank(ST &st)
{
	if ((st.gpa) > 9)
	{
		strcpy(st.rank, "Excellent");
	} else if ((st.gpa) > 8)
	{
		strcpy(st.rank, "Good");
	} else if ((st.gpa) > 5)
	{
		strcpy(st.rank, "Average");
	} else if ((st.gpa) < 5)
	{
		strcpy(st.rank, "Below Average");
	}
}
void updateStudent(ST &st)
{
	inputStudent(st);
	rank(st);
}
void inputListStudents(ST list[], int &countStudent)
{
	do
	{
		printf("\nEnter the number of Student: ");
		scanf("%d", &countStudent);
	} while (countStudent <= 0);
	int i;
	for (i = 0; i < countStudent; i++)
	{
		printf("\nEnter Student %d", i);
		updateStudent(list[i]);
	}
}
void print()
{
	printf("\n%5s \t %20s \t %10s \t %4s \t %5s \t %10s", "ID", "Name", "Sex", "Age", "GPA", "Rank");
}
void outputStudent(ST &st)
{
	printf("\n%5d \t %20s \t %10s \t %4d \t %5g \t %10s", st.id, st.name, st.sex,st.age, st.gpa, st.rank);
}
void outputListStudents(ST list[], int countStudent)
{
	print();
	printf("\n");
	int i;
	if (countStudent == 0)
	{
		printf("No one in class!");
	}
	else
	{
		for (i = 0; i < countStudent; i++)
		{
			outputStudent(list[i]);
			printf("\n");
		}
	}
}
void findStudentByName(struct student* list, int countStudent)
{
	char name[20];
	printf("\nEnter name of Student: "); fflush(stdin);
	fgets(name, sizeof(name), stdin); delLineBreaks(name);
	print();
	int i, findName = 0;
	for (i = 0; i < countStudent; i++)
	{
		if (strstr(strupr(list[i].name), strupr(name))) //strstr = find string in string; strupr: in hoa;
		{
			outputStudent(list[i]);
			findName = 1;
		}
	} 
	if(findName == 0)
	{
		printf("\nNo one have name: %s in list!\n", name);
	}
}
void findStudentById(struct student* list, int countStudent, int id)
{
	print();
	int i, findId = 0;
	for (i = 0; i < countStudent; i++)
	{
		if (list[i].id == id)
		{
			outputStudent(list[i]);
			findId = 1;
		}
	}
	if(findId == 0)
	{
		printf("\nNo one have id: %d in list!\n", id);
	}
}
void delStudentById(ST list[], int &countStudent, int id)
{
	int i, j;
	int countDel;
	for (i = 0; i < countStudent; i++)
	{
		if (list[i].id == id)
		{
			for (j = i; j < countStudent; j++)
			{
				list[j] = list[j+1];
			}
			countStudent--;
		}
	}
}
void sortUpByGpa(ST list[], int countStudent)
{
	int i, j;
	for (i = 0; i < countStudent - 1; i++)
	{
		for (j = i +1; j < countStudent; j++)
		{
			if(list[i].gpa > list[j].gpa)
			{
				ST tmp;
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
		}
	}
}
void sortDescendByGpa(ST list[], int countStudent)
{
	int i, j;
	for (i = 0; i < countStudent - 1; i++)
	{
		for (j = i +1; j < countStudent; j++)
		{
			if(list[i].gpa < list[j].gpa)
			{
				ST tmp;
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
		}
	}
}
void sortUpByName(ST list[], int countStudent)
{
	int i, j;
	for (i = 0; i < countStudent - 1; i++)
	{
		for (j = i + 1; j < countStudent; j++)
		{
			if(strcmp(strupr(list[i].name), strupr(list[j].name)) > 0) //strupr la ham in hoa; //strcmp la so sanh hai chuoi;
			{
				ST tmp;
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
		}
	}
}
void addNewStudent(listStudents *listAdd, int add, ST &st)
{
	int i;
	for(i = (*listAdd).countStudent; i > add; i--)
	{
		(*listAdd).list[i] = (*listAdd).list[i-1];
	}
	rank(st);
	(*listAdd).list[add] = st;
	(*listAdd).countStudent += 1;
}
void inputFile(ST list[], int countStudent) //ghi du lieu vao file dang nhi phan;
{
	char fileName[100];
	printf("\nEnter file path and file name: ");
	fflush(stdin);
	fgets(fileName, sizeof(fileName), stdin);
	delLineBreaks(fileName);
	FILE *f;
	f = fopen(fileName, "wb");
	if (f == NULL)
	{
		printf("\nError!!!");
		return;
	}
	fwrite(&countStudent, sizeof(countStudent), 1, f);
	int i;
	for (i = 0; i < countStudent; i++)
	{
		fwrite(&list[i], sizeof(ST), 1, f);
	}
	printf("\nSuccess!");
	fclose(f);
}
void takeFromFile(ST list[], int &countStudent) //lay du lieu tu file dang nhi phan;
{
	char fileName[100];
	printf("\nEnter file path and file name: ");
	fflush(stdin);
	fgets(fileName, sizeof(fileName), stdin);
	delLineBreaks(fileName);
	FILE *f;
	f = fopen(fileName, "rb");
	if (f == NULL)
	{
		printf("\nError!!!");
		return;
	}
	fread(&countStudent, sizeof(countStudent), 1, f);
	int i;
	for (i = 0; i < countStudent; i++)
	{
		fread(&list[i], sizeof(ST), 1, f);
	}
	printf("\nSuccess!");
	fclose(f);
}
void printToScreen()
{
	printf("\n******************************************************************\n");
	printf("**              PROGRAM MANAGEMENT STUDENTS                     **\n");
	printf("**              1.Input List Student                            **\n");
	printf("**              2.Output List Student                           **\n");
	printf("**              3.Find Student By ID                            **\n");
	printf("**              4.Find Student By Name                          **\n");
	printf("**              5.Add New Student                               **\n");
	printf("**              6.Delete Student By ID                          **\n");
	printf("**              7.Sort Up Student By GPA                        **\n");
	printf("**              8.Sort Descending Student By GPA                **\n");
	printf("**              9.Sort Up Student By Name                       **\n");
	printf("**              10.Input In File                                **\n");
	printf("**              11.Take Data From File                          **\n");
	printf("**              12.Exit                                         **\n");
	printf("******************************************************************\n");
	printf("**               Your choice is:                                **\n");	
}
void nextStep() //de dung man hinh
{
	printf("\nPress Any Key To Continue!");
	getchar();
}
int main()
{
	int id, add;
	ST st;
	listStudents listAdd;
	char name[20];
	int choice;
	do{
		printToScreen();
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				inputListStudents(listAdd.list, listAdd.countStudent);
				nextStep();
				break;
			case 2:
				outputListStudents(listAdd.list, listAdd.countStudent);
				nextStep();
				break;
			case 3:
				printf("\nEnter ID of Student: "); 
				scanf("%d", &id);
				findStudentById(listAdd.list, listAdd.countStudent, id);
				nextStep();
				break;
			case 4:
				findStudentByName(listAdd.list, listAdd.countStudent);
				nextStep();
				break;
			case 5:
				printf("\nEnter position you want to add: ");
				scanf("%d", &add);
				inputStudent(st);
				addNewStudent(&listAdd, add, st);
				printf("\nList of Students after adding:");
				outputListStudents(listAdd.list, listAdd.countStudent);
				nextStep();
				break;				
			case 6:
				int id;
				printf("\nEnter id of Student: ");
				scanf("%d", &id);
				delStudentById(listAdd.list, listAdd.countStudent, id);
				nextStep();
				break;
			case 7:
				sortUpByGpa(listAdd.list, listAdd.countStudent);
				outputListStudents(listAdd.list, listAdd.countStudent);
				nextStep();
				break;
			case 8:
				sortDescendByGpa(listAdd.list, listAdd.countStudent);
				outputListStudents(listAdd.list, listAdd.countStudent);
				nextStep();
				break;
			case 9:
				sortUpByName(listAdd.list, listAdd.countStudent);
				outputListStudents(listAdd.list, listAdd.countStudent);
				nextStep();
				break;
			case 10:
				inputFile(listAdd.list, listAdd.countStudent);
				nextStep();
				break;
			case 11:
				takeFromFile(listAdd.list, listAdd.countStudent);
				nextStep();
				break;
			case 12:
				printf("Exit!");
				return 0;
				break;
			default:
			printf("Please type agian!!!");
			break;
		}
	} while(choice != 0);
    return 0;
}
