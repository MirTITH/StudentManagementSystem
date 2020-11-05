/*
 学生管理系统
 创建人学号：200320620
 2020/11/2
 V 2.1
 亮点：
	输入数据功能：
		姓名支持中文、空格、特殊符号
		支持非整数分数
		已经存在数据时：
			让用户选择：1、添加新数据 2、删除现有数据 3、返回
			用户选择删除现有数据时提示用户再次确认
		存在相同学号时，提示用户是否覆盖（可用来修改之前的数据）
		达到最大学生数时，进入修改模式，用户只可修改之前的数据，不能增加数据
	排序功能：
		支持中文名排序
	显示功能：
		打印列表时可根据姓名长度自动列对齐
    使用enum枚举使程序代码易读

注：可在主菜单输入10086，随机输入学生数据，方便测试
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_STUDENT_NUM 30//最大学生数
#define MAX_NAME_LENGTH 200//最大名字长度

void PrintMenu();//打印菜单
int InputData(void* (*Data)(int));//手动输入数据，返回0
int FindByNumber(void* (*Data)(int), int);//按学号查找，如果找到，返回次序，否则返回-1
double GetScore(void* (*Data)(int), int);//返回分数
int GetRank(void* (*Data)(int), int);//返回排名
void* GetData(int);//获取数据
void PrintTotalAverageScore(void* (*Data)(int));//打印总分和平均分
int GetTotalStudentNum(void* (*Data)(int));//返回学生总数
void Sort(void* (*Data)(int), int, int (*Compare)(void* (*)(int), int, int, int));//排序
void Swap(void* (*Data)(int), int, int);//交换
int CompareDescending(void* (*Data)(int), int, int, int);//从高到低
int CompareAscending(void* (*Data)(int), int, int, int);//从低到高
void PrintListAll(void* (*Data)(int));//列举所有学生信息
void PrintStatisticAnalysis(void* (*Data)(int));//打印数据分析
void PrintListOne(void* (*Data)(int), int);//列出一个学生的信息
int FindByName(void* (*Data)(int), char*);//按姓名查找，打印找到的学生信息，返回找到的学生数
void TestInputData(void* (*Data)(int));//（测试用途）随机输入数据

enum TYPE {Initialize, Number, Name, Score} type;

int main()
{

    int iUserInput = 0;//用户输入值

    int iFindByNumber_Result = 0;
    int iFindByNumber_NumberToFind = 0;

	int iFindByName_Result = 0;
	char iFindByName_NameToFind[MAX_NAME_LENGTH] = {0};

    GetData(Initialize);//初始化数据

    PrintMenu();

    do
    {
        iUserInput = -1;//初始化输入值
        scanf("%d", &iUserInput);

        while (getchar() != '\n');//清除键盘缓冲区

        switch (iUserInput)
        {
        case 11://退出
            exit(0);
            break;
        case 1://Input record
            printf("\n----------------------------\n");
            InputData(GetData);
            printf("\n----------------------------\n");
            PrintMenu();
            break;
        case 2://Calculate total and average score of course
            printf("\n----------------------------\n");
            PrintTotalAverageScore(GetData);
			printf("\n---Press any key to continue---");
			getch();
			printf("\n----------------------------\n");
			PrintMenu();
            break;
        case 3://Sort in descending order by score
            printf("\n----------------------------\n");
            Sort(GetData, Score, CompareDescending);
			PrintListAll(GetData);
			printf("\n---Press any key to continue---");
			getch();
			printf("\n----------------------------\n");
			PrintMenu();
            break;
        case 4://Sort in ascending order by score
            printf("\n----------------------------\n");
            Sort(GetData, Score, CompareAscending);
            PrintListAll(GetData);
			printf("\n---Press any key to continue---");
			getch();
			printf("\n----------------------------\n");
			PrintMenu();
            break;
        case 5://Sort in ascending order by number
            printf("\n----------------------------\n");
            Sort(GetData, Number, CompareAscending);
            PrintListAll(GetData);
			printf("\n---Press any key to continue---");
			getch();
			printf("\n----------------------------\n");
			PrintMenu();
            break;
		case 6://Sort in dictionary order by name
            printf("\n----------------------------\n");
            Sort(GetData, Name, CompareAscending);
            PrintListAll(GetData);
			printf("\n---Press any key to continue---");
			getch();
			printf("\n----------------------------\n");
			PrintMenu();
            break;
        case 7://Search by number
            printf("\n----------------------------\n");
            printf("Input number to search.");
            do
            {
                printf("\nPlease input the number(Input 0 to exit):");
                iFindByNumber_NumberToFind = -1;//初始化输入值
                scanf("%d", &iFindByNumber_NumberToFind);
                while (getchar() != '\n');//清除键盘缓冲区

                if(iFindByNumber_NumberToFind > 0)
                {
                    iFindByNumber_Result = FindByNumber(GetData, iFindByNumber_NumberToFind);

                    if(iFindByNumber_Result == -1)
                    {
                        printf("---Number %d does not exist. ---", iFindByNumber_NumberToFind);
                    }
                    else
                    {
						PrintListOne(GetData, iFindByNumber_Result);
                    }
                }
                else if(iFindByNumber_NumberToFind != 0)
                {
                    printf("---Invalid input.---\n");
                }

            } while (iFindByNumber_NumberToFind != 0);
            printf("\n----------------------------\n");
            PrintMenu();
            break;
		case 8://Search by name
			printf("\n----------------------------\n");
			printf("Please input the name:");
			scanf("%[^\n]", &iFindByName_NameToFind);//使用%[^\n]表示除了回车，其它的字符都读入
			while (getchar() != '\n');//清除键盘缓冲区
			iFindByName_Result = FindByName(GetData, iFindByName_NameToFind);
			printf("---%d found---", iFindByName_Result);
			printf("\n---Press any key to continue---");
			getch();
			printf("\n----------------------------\n");
			PrintMenu();
            break;
        case 9://Statistic analysis
            printf("\n----------------------------\n");
            PrintStatisticAnalysis(GetData);
			printf("\n---Press any key to continue---");
			getch();
			printf("\n----------------------------\n");
			PrintMenu();
            break;
        case 10://List record
            printf("\n----------------------------\n");
            PrintListAll(GetData);
            PrintTotalAverageScore(GetData);
			printf("\n---Press any key to continue---");
			getch();
			printf("\n----------------------------\n");
			PrintMenu();
            break;
		case 10086://随机写入学生数据
			TestInputData(GetData);
			break;
        default:
            printf("---Invalid input.---\n");
            break;
        }

    } while (1);
}

void PrintMenu()//打印菜单
{
    printf(" 1.Input record\n");
    printf(" 2.Calculate total and average score of course\n");
    printf(" 3.Sort in descending order by score\n");
    printf(" 4.Sort in ascending order by score\n");
    printf(" 5.Sort in ascending order by number\n");
    printf(" 6.Sort in dictionary order by name\n");
    printf(" 7.Search by number\n");
    printf(" 8.Search by name\n");
    printf(" 9.Statistic analysis\n");
    printf("10.List record\n");
    printf("11.Exit\n");
	printf("Please enter your choice:");
}

int InputData(void* (*Data)(int))
{
    int *iNumberData = (int*)Data(Number);
    char *cNameData = (char*)Data(Name);
    double *dScoreData = (double*)Data(Score);

    int iInputNumber = 0;//输入的Number
    double dInputScore = 0;//输入的成绩
    char cInputName[MAX_NAME_LENGTH] = {0};//输入的名字

    int iInputStatus = 0;
    int iErrStatus = 0;
    char cInput = 0;

	int iStartNum = 1;
	int iNumberOrder = 0;

	int iReachedMaxPrintMode = 0;


    if((iNumberData)[0] != 0)//判断学生数据是否已经存在
    {
        printf("---Student data already exist. What would you want to do? ---\n");
        printf(" 1. Add new data\n");
        printf(" 2. Clean all data and input\n");
        printf(" 0. Exit\n");
        do
        {
            printf("Please enter your choice:");
            iInputStatus = scanf("%d", &iInputNumber);
            while (getchar() != '\n'); //清除键盘缓冲区
        } while (iInputStatus != 1 || iInputNumber < 0 || iInputNumber > 2);

        switch (iInputNumber)
            {
            case 0: //退出
                return 0;
                break;
            case 1://新增数据
                iStartNum = GetTotalStudentNum(Data) + 1;
                break;
            case 2://清除所有数据
				printf("\n---Warning! This will erase all the data. Are you sure? ---\n");
				do
				{
					printf("---Input n for No, y for Yes: ");
					iInputStatus = scanf("%c", &cInput);
					while (cInput != '\n' && getchar() != '\n');//清除键盘缓冲区（当输入值不为回车时）
				} while (iInputStatus != 1 || (cInput != 'n' && cInput != 'N' && cInput != 'y' && cInput != 'Y')); //当输入合法时结束循环

				if (cInput == 'y' || cInput == 'Y') //清除
				{
					for (int i = 0; i < MAX_STUDENT_NUM; i++)
					{
						iNumberData[i] = 0;
						dScoreData[i] = 0;
						for (int j = 0; j < MAX_NAME_LENGTH; j++)
						{
							cNameData[i * MAX_NAME_LENGTH + j] = 0;
						}
					}
				}
				else //不清除
				{
					return 0;
				}
				break;
            }
		printf("\n");
    }


	//开始输入数据
	if (iStartNum <= MAX_STUDENT_NUM)
	{
		printf("Please input the student's number, score and name. (Max capacity is %d)\n", MAX_STUDENT_NUM);
		printf("Format:number,score,name\n");
		printf("---You can input 0 to save and exit.---\n");
	}

    for(int iOrder = iStartNum; iOrder <= MAX_STUDENT_NUM + 1; iOrder++)
	//从第1个学生循环输入到第MAX_STUDENT_NUM + 1个学生
	//（当学生数到达MAX_STUDENT_NUM + 1时，提示用户人数到达最大值
    {
		if (iOrder <= MAX_STUDENT_NUM)
		{
			printf("Student %d:", iOrder);
		}
		else if (iReachedMaxPrintMode == 0)
		{
			printf("\n---Reached the max num. (You can still modify the data or input 0 to exit)---\n");
			printf("Format:number to modify,score,name)\n");
			printf("Modify mode>");
			iReachedMaxPrintMode++;
		}
		else
		{
			printf("Modify mode>");
		}


        iInputStatus = scanf("%d,%lf,%[^\n]", &iInputNumber, &dInputScore, cInputName);//使用%[^\n]表示除了回车，其它的字符都读入
        while (getchar() != '\n');//清除键盘缓冲区

        if (iInputStatus == 1 && iInputNumber == 0)//只输入0，退出
        {
            return 0;
        }
        else if (iInputStatus != 3)//判断非法输入
        {
            printf("---Invalid input.---\n");
			printf("---You can input 0 to save and exit.---\n");
            iOrder--;//实现重新输入当前学生
            continue;
        }

		iNumberOrder = FindByNumber(Data, iInputNumber);//判断学号是否已经存在
		if (iInputNumber <= 0) //学号不允许小于0
		{
			printf("---Wrong. Invalid number.---\n");
			iErrStatus = 1;
		}
		else if (iNumberOrder != -1)
		{
			printf("\n---The number alreary exists. Do you want to overwright it?---\n");
			do
			{
				printf("---Input n for No, y for Yes: ");
				iInputStatus = scanf("%c", &cInput);
				while (cInput != '\n' && getchar() != '\n');//清除键盘缓冲区（当输入值不为回车时）
			} while (iInputStatus != 1 || (cInput != 'n' && cInput != 'N' && cInput != 'y' && cInput != 'Y')); //当输入合法时结束循环

			printf("\n");

			if (cInput == 'y' || cInput == 'Y') //覆盖
			{
				dScoreData[iNumberOrder] = dInputScore;
				strcpy(cNameData + (iNumberOrder)*MAX_NAME_LENGTH, cInputName);
				iErrStatus = 1;
			}
			else //不覆盖
			{
				iErrStatus = 1;
			}
		}

		else if (iReachedMaxPrintMode)
		{
			printf("---The number does not exist. (Input 0 to exit)---\n");
		}

		if (iErrStatus == 0)//正常写入数据
        {
			if (iOrder >= MAX_STUDENT_NUM + 1)//达到最大学生数时防止跳出循环
			{
				iOrder--;
			}
			else
			{
				iNumberData[iOrder - 1] = iInputNumber;
            	dScoreData[iOrder - 1] = dInputScore;
            	strcpy(cNameData + (iOrder - 1) * MAX_NAME_LENGTH, cInputName);
			}
        }
        else if (iErrStatus == 1)//异常时重新此次循环，不在此处写入数据
        {
            iOrder--;
            iErrStatus = 0;
            continue;
        }
        else//其他情况跳过此次循环，不在此写入数据
        {
            iErrStatus = 0;
            continue;
        }
    }
    return 0;
}

int FindByNumber(void* (*Data)(int), int iNumberToFind)
{
    int *iNumberData = (int*)Data(Number);


    for(int iOrder = 0; iOrder < MAX_STUDENT_NUM; iOrder++)
    {
        if(iNumberToFind == iNumberData[iOrder])
        {
            return iOrder;
        }
    }
    return -1;
}

double GetScore(void* (*Data)(int), int iOrder)
{
    double *dScoreData = (double*)Data(Score);
    return dScoreData[iOrder];
}

int GetRank(void* (*Data)(int), int iOrder)
{
    double *dScoreData = (double*)Data(Score);

    double dScore = dScoreData[iOrder];
    int iRank = 1;
    for(int i = 0; i < MAX_STUDENT_NUM; i++)
    {
        if (dScoreData[i] > dScore)
        {
            iRank++;
        }
    }
    return iRank;
}

void* GetData(int iType)//iType 0 初始化，1 学号，2 姓名，3 成绩
{
    static int iNumberData[MAX_STUDENT_NUM] = {0};//学生学号
    static double dScoreData[MAX_STUDENT_NUM] = {0};//学生成绩
    static char cNameData[MAX_STUDENT_NUM][MAX_NAME_LENGTH] = {0};//学生姓名

    switch (iType)
    {
    case Number://学号
        return iNumberData;
        break;
    case Name://姓名
        return cNameData;
        break;
    case Score://分数
        return dScoreData;
        break;
    case Initialize://初始化
		return NULL;
        break;
    default:
		return NULL;
        break;
    }
}

void PrintTotalAverageScore(void* (*Data)(int))
{
    double *dScoreData = (double*)Data(Score);
    double dTotalScore = 0;
    int iTotalStudent = GetTotalStudentNum(Data);
    for (int i = 0; i < MAX_STUDENT_NUM; i++)
    {
        dTotalScore += dScoreData[i];
    }
    printf("Total score: %lf \n", dTotalScore);
    printf("Average score: %lf \n", dTotalScore / iTotalStudent);
}

int GetTotalStudentNum(void* (*Data)(int))
{
    char *cNameData = (char*)Data(Name);
    int iTotalStudentNum = 0;
    for (int i = 0; i < MAX_STUDENT_NUM; i++)
    {
        if(cNameData[i * MAX_NAME_LENGTH] != '\0')
        {
            iTotalStudentNum++;
        }
    }
    return iTotalStudentNum;
}

void Swap(void* (*Data)(int), int iOrderA, int iOrderB)
{
    int *iNumberData = (int*)Data(Number);
    char *cNameData = (char*)Data(Name);
    double *dScoreData = (double*)Data(Score);

    int iTemp = 0;
    char cTemp[MAX_NAME_LENGTH] = {0};
    double dTemp = 0;

    iTemp = iNumberData[iOrderA];
    iNumberData[iOrderA] = iNumberData[iOrderB];
    iNumberData[iOrderB] = iTemp;

    dTemp = dScoreData[iOrderA];
    dScoreData[iOrderA] = dScoreData[iOrderB];
    dScoreData[iOrderB] = dTemp;

    strcpy(cTemp, cNameData + iOrderA * MAX_NAME_LENGTH);
    strcpy(cNameData + iOrderA * MAX_NAME_LENGTH, cNameData + iOrderB * MAX_NAME_LENGTH);
    strcpy(cNameData + iOrderB * MAX_NAME_LENGTH, cTemp);
}

void Sort(void* (*Data)(int), int iType, int (*Compare)(void* (*)(int), int, int, int))
{
	int iTotalStudentNum = GetTotalStudentNum(Data);
    int iIsDone = 0;

    do
    {
		iIsDone = 0;
        for (int i = 0; i < iTotalStudentNum - 1; i++)
        {
            if(Compare(Data, iType, i, i + 1))
            {
                Swap(Data, i, i + 1);
				iIsDone = 1;
            }
        }
    } while (iIsDone);
}

int CompareDescending(void *(*Data)(int), int iType, int iOrder1, int iOrder2)
{
	switch (iType)
	{
	case Number:
		return *((int *)Data(Number) + iOrder1) < *((int *)Data(Number) + iOrder2);
		break;
	case Score:
		return *((double *)Data(Score) + iOrder1) < *((double *)Data(Score) + iOrder2);
		break;
	case Name:
		return strcmp((char *)Data(Name) + iOrder1 * MAX_NAME_LENGTH, (char *)Data(Name) + iOrder2 * MAX_NAME_LENGTH) < 0;
	default:
		exit(iType);
		break;
	}
}

int CompareAscending(void *(*Data)(int), int iType, int iOrder1, int iOrder2)
{
	switch (iType)
	{
	case Number:
		return *((int *)Data(Number) + iOrder1) > *((int *)Data(Number) + iOrder2);
		break;
	case Score:
		return *((double *)Data(Score) + iOrder1) > *((double *)Data(Score) + iOrder2);
		break;
	case Name:
		return strcmp((char *)Data(Name) + iOrder1 * MAX_NAME_LENGTH, (char *)Data(Name) + iOrder2 * MAX_NAME_LENGTH) > 0;
	default:
		exit(iType);
		break;
	}
}

void PrintListOne(void* (*Data)(int), int iOrder)
{
	int *iNumberData = (int*)Data(Number);
    char *cNameData = (char*)Data(Name);
    double *dScoreData = (double*)Data(Score);

	int iMaxNameLength = 0;

    for(int i = 0; i < MAX_STUDENT_NUM; i++)//获取最大姓名长度
    {
        if (cNameData[i * MAX_NAME_LENGTH] != '\0')
        {
			if(strlen(cNameData + i * MAX_NAME_LENGTH) > iMaxNameLength)
			{
				iMaxNameLength = strlen(cNameData + i * MAX_NAME_LENGTH);
			}
        }
	}

	printf("Number:%8.d  Name:%s", iNumberData[iOrder], cNameData + iOrder * MAX_NAME_LENGTH);
	for (int j = 0; j <= iMaxNameLength - strlen(cNameData + iOrder * MAX_NAME_LENGTH) + 1; j++)
	{
		printf(" ");
	}
	printf("Rank:%3.d	Score:%lf\n", GetRank(Data, iOrder), dScoreData[iOrder]);
}

void PrintListAll(void* (*Data)(int))
{
	char *cNameData = (char*)Data(Name);

	for(int i = 0; i < MAX_STUDENT_NUM; i++)
	{
		if (cNameData[i * MAX_NAME_LENGTH] != '\0')
        {
			PrintListOne(Data, i);
        }

    }
}

void PrintStatisticAnalysis(void* (*Data)(int))
{
    char *cNameData = (char*)Data(Name);

    int iTotalStudent = GetTotalStudentNum(Data);

    int iExcellentNum = 0;//90-100
    int iGoodNum = 0;//80-89
    int iMediumNum = 0;//70-79
    int iPassNum = 0;//60-69
    int iFailNum = 0;//0-59

    double dScoreNum = 0;

    for (int i = 0; i < MAX_STUDENT_NUM; i++)
    {
        if (cNameData[i * MAX_NAME_LENGTH] != '\0')
        {
            dScoreNum = GetScore(Data, i);
            if (dScoreNum >= 90)
            {
                iExcellentNum++;
            }
            else if (dScoreNum >= 80)
            {
                iGoodNum++;
            }
            else if (dScoreNum >= 70)
            {
                iMediumNum++;
            }
            else if (dScoreNum >= 60)
            {
                iPassNum++;
            }
            else
            {
                iFailNum++;
            }
        }
    }

    printf("Excellent:	%d, %.2lf%%\n", iExcellentNum, (double)iExcellentNum / iTotalStudent * 100);
    printf("Good:		%d, %.2lf%%\n", iGoodNum, (double)iGoodNum / iTotalStudent * 100);
    printf("Medium:		%d, %.2lf%%\n", iMediumNum, (double)iMediumNum / iTotalStudent * 100);
    printf("Pass:		%d, %.2lf%%\n", iPassNum, (double)iPassNum / iTotalStudent * 100);
    printf("Fail:		%d, %.2lf%%\n", iFailNum, (double)iFailNum / iTotalStudent * 100);
}

void TestInputData(void* (*Data)(int))
{
	int iInputStatus = 0;
	char cInput = 0;
	printf("\n---Warning! This will erase all the existed data. Are you sure? ---\n");
	do
	{
		printf("---Input n for No, y for Yes: ");
		iInputStatus = scanf("%c", &cInput);
		while (cInput != '\n' && getchar() != '\n');//清除键盘缓冲区（当输入值不为回车时）
	} while (iInputStatus != 1 || (cInput != 'n' && cInput != 'N' && cInput != 'y' && cInput != 'Y')); //当输入合法时结束循环

	if (cInput == 'y' || cInput == 'Y') //确定
	{
		int iSeed = 0;
		printf("Please input a seed\n");
		scanf("%d", &iSeed);
		srand(iSeed);

		int *iNumberData = (int *)Data(Number);
		char(*cNameData)[MAX_NAME_LENGTH] = Data(Name);
		double *dScoreData = (double *)Data(Score);

		for (int i = 0; i < MAX_STUDENT_NUM; i++)
		{
			iNumberData[i] = rand() % 1000 + 1;
			dScoreData[i] = rand() % 101;
			for (int j = 0; j < rand() % 20 + 1; j++)
			{
				cNameData[i][j] = rand() % 75 + 48;
			}
		}
		printf("Done\n");
		PrintMenu();
	}
	else
	{
		PrintMenu();
	}
}

int FindByName(void* (*Data)(int), char* cNameToFind)
{
	char (*cNameData)[MAX_NAME_LENGTH] = Data(Name);
	int iTotalStudentNumber = GetTotalStudentNum(Data);
	int iFound = 0;
	for (int i = 0; i < iTotalStudentNumber; i++)
	{
		if (strstr(cNameData[i], cNameToFind))
		{
			PrintListOne(Data, i);
			iFound++;
		}
	}
	return iFound;
}
