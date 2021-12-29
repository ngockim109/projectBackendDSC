#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct student
{
    int id;
    char name[50];
    char sex[5];
    int age;
    float mark1;
    float mark2;
    float mark3;
    float gpa;
    char rank[10];
}ST;
struct listStudents
{
	ST list[100];
	int countStudent = 0;
};
//xoa dau xuong dong;
void delLineBreaks(char x[])
{
	size_t len = strlen(x); //len = do dai chuoi;
	if(x[len-1]=='\n')
	{
		x[len-1]='\0';
	}
}
void inputStudent(ST &st)
{
	do{
		printf("\nID: ");
		scanf("%d", &st.id);
	}while(st.id < 0);
	getchar();
	printf("\nName: ");
	fflush(stdin);
	fgets(st.name, sizeof(st.name), stdin);
	delLineBreaks(st.name);
	printf("\nSex: ");
	fflush(stdin);
	fgets(st.sex, sizeof(st.sex), stdin);
	delLineBreaks(st.sex);
	do{
		printf("\nAge: ");
		scanf("%d", &st.age);
		if (st.age < 0 || st.age > 123) 
        {printf("\nAge must be 0->123\n");}
	}while(st.age < 0 || st.age > 123);
	do{
		printf("\nMark 1: ");
		scanf("%f", &st.mark1);
		if (st.mark1 < 0 || st.mark1 > 10) 
        {printf("\nScore must be 0->10\n");}
	}while(st.mark1 < 0 || st.mark1 > 10);
	do{
		printf("\nMark 2: ");
		scanf("%f", &st.mark2);
		if (st.mark2 < 0 || st.mark2 > 10) 
        {printf("\nScore must be 0->10\n");}
	}while(st.mark2 < 0 || st.mark2 > 10);
	do{
		printf("\nMark 3: ");
		scanf("%f", &st.mark3);
		if (st.mark3 < 0 || st.mark3 > 10) 
        {printf("\nScore must be 0->10\n");}
	}while(st.mark3 < 0 || st.mark3 > 10);
}
void gpa(ST &st)
{
	st.gpa = (st.mark1 + st.mark2 + st.mark3) / 3;
}
void rank(ST &st)
{
		if ((st.gpa) >= 9)
		{strcpy(st.rank, "Excellent");}
		else if ((st.gpa) >= 8)
		{strcpy(st.rank, "Very Good");} 
		else if ((st.gpa) >= 7)
		{strcpy(st.rank, "Good");} 
		else if ((st.gpa) >= 5)
		{strcpy(st.rank, "Average");} 
		else if ((st.gpa) < 5)
		{strcpy(st.rank, "Below Average");}
}
void updateStudent(ST &st)
{
	inputStudent(st);
	gpa(st);
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
		printf("\nEnter Student %d", i+1);
		updateStudent(list[i]);
	}
}
void print()
{
	printf("\n%5s \t %20s \t %10s \t %4s \t %7s \t %6s \t %6s \t %5s \t %13s", "ID", "Name", "Sex", "Age", "Mark 1", "Mark 2", "Mark 3", "GPA", "Rank");
}
void outputStudent(ST &st)
{
	printf("\n%5d \t %20s \t %10s \t %4d \t %6g \t %6g \t %6g \t %6.2g \t %4s", st.id, st.name, st.sex,st.age, st.mark1, st.mark2, st.mark3, st.gpa, st.rank);
}
void outputListStudents(ST list[], int countStudent)
{
	printf("***********************************************************************************************************************************");
	printf("\nTotal: %d\n", countStudent);
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
	printf("\nEnter file path or file name: ");
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
	printf("\nEnter file path or file name: ");
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
	printf("**              PROGRAM STUDENTS MANAGEMENT                     **\n");
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
			printf("Please type again!!!");
			break;
		}
	} while(1 <= choice <= 12);
    return 0;
}
