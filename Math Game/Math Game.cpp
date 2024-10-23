#include <iostream>
#include <cstdlib>
using namespace std;

enum enQuizLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enQuizOperators { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuizInfo
{
    short QuizNumber;
    double Num1;
    double Num2;
    double Result;
    double UserResult;
};

struct stQuizResults
{
    short NumberOfQustions = 0;
    enQuizLevel QuizLevel = enQuizLevel::Easy;
    enQuizOperators OpType = enQuizOperators::Add;
    short RightAnswer = 0;
    short WrongAnswer = 0;
};

int RandomNumber(int From, int To) {
    // Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

int ReadNumber()
{
    int number;

    cout << "How many Question you wanna play ? ";
    cin >> number;
    return number;
}

enQuizLevel ReadQuizLevel()
{
    int Choice = 1;
    do
    {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> Choice;

    } while (Choice < 1 || Choice > 4);

    return (enQuizLevel)Choice;
}

enQuizOperators ReadQuizOperationType()
{
    int Choice = 1;
    do
    {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 5);

    return (enQuizOperators)Choice;
}

void RandomNumberAccordingToLevel(double& num1, double& num2, enQuizLevel& QuizLevel)
{
    if (QuizLevel == enQuizLevel::MixLevel)
        QuizLevel = (enQuizLevel)RandomNumber(1, 3);

    switch (QuizLevel)
    {
    case Easy:
        num1 = RandomNumber(1, 10);
        num2 = RandomNumber(1, 10);
        break;
    case Med:
        num1 = RandomNumber(10, 50);
        num2 = RandomNumber(10, 50);
        break;
    case Hard:
        num1 = RandomNumber(50, 100);
        num2 = RandomNumber(50, 100);
        break;
    }
}

double Result(double Num1, double Num2, enQuizOperators& OpType)
{
    if (OpType == enQuizOperators::MixOp)
        OpType = (enQuizOperators)RandomNumber(1, 4);

    switch (OpType)
    {
    case Add:
        return Num1 + Num2;

    case Sub:
        return Num1 - Num2;

    case Mul:
        return Num1 * Num2;

    case Div:
        return Num1 / Num2;
    }
}

char CharOperationType(enQuizOperators& Op)
{
    if (Op == enQuizOperators::MixOp)
        Op = (enQuizOperators)RandomNumber(1, 4);

    switch (Op)
    {
    case Add:
        return '+';
        break;
    case Sub:
        return '-';
    case Mul:
        return '*';
    case Div:
        return '/';

    }
}

void UserResultCheck(double UserNumber, double Result)
{
    if (UserNumber == Result)
    {
        cout << "\nThe answer is right.\n";
        system("color 2F");// colorize Screen to red
    }
    else
    {
        system("color 4F"); // colorize Screen to red
        cout << "\a";
        cout << "\nThe answer is wrong.\n";
        cout << "The Right answer = " << Result << endl;
    }
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void FillQuizResult(stQuizInfo QuizInfo, stQuizResults& QuizResults)
{
    if (QuizInfo.UserResult == QuizInfo.Result)
        QuizResults.RightAnswer++;
    else
        QuizResults.WrongAnswer++;
}

stQuizInfo PlayGame(short NumberOfQuestion, enQuizLevel QuizLevel, enQuizOperators Op, stQuizResults& QuizResults)
{
    stQuizInfo QuizInfo;

    QuizResults.NumberOfQustions = NumberOfQuestion;
    QuizResults.OpType = Op;
    QuizResults.QuizLevel = QuizLevel;

    for (int i = 1; i <= NumberOfQuestion; i++)
    {
        QuizLevel = QuizResults.QuizLevel;
        Op = QuizResults.OpType;

        QuizInfo.QuizNumber = i;
        cout << "\nQuestion [" << i << "/" << NumberOfQuestion << "]\n\n";

        RandomNumberAccordingToLevel(QuizInfo.Num1, QuizInfo.Num2, QuizLevel);

        QuizInfo.Result = Result(QuizInfo.Num1, QuizInfo.Num2, Op);

        cout << QuizInfo.Num1 << "\n";
        cout << QuizInfo.Num2 << "  " << CharOperationType(Op);
        cout << "\n-------------------\n";
        cin >> QuizInfo.UserResult;

        UserResultCheck(QuizInfo.UserResult, QuizInfo.Result);
        FillQuizResult(QuizInfo, QuizResults);
    }
    return QuizInfo;
}

void ShowQuizHead(stQuizResults QuizResults)
{
    cout << "\n\n-------------------------------------\n\n";
    cout << "\tFinal Result is ";

    if (QuizResults.RightAnswer >= QuizResults.WrongAnswer)
    {
        cout << "Pass";
        system("color 2F");
    }
    else
    {
        cout << "Failed";
        system("color 4F");
    }

    cout << "\n\n-------------------------------------\n\n";
}

void ShowQuizResults(stQuizResults QuizResults)
{
    ShowQuizHead(QuizResults);
    cout << "\nNumber of Question: " << QuizResults.NumberOfQustions;
    cout << "\nQuestions Level   : " << QuizResults.QuizLevel;
    cout << "\nOperation Type    : " << QuizResults.OpType;
    cout << "\nRight Answers     : " << QuizResults.RightAnswer;
    cout << "\nWrong Answers     : " << QuizResults.WrongAnswer << endl;
    cout << "---------------------------------------------------------" << endl;

}

void StartQuiz()
{
    char PlayAgain = 'y';
    stQuizInfo QuizInfo;
    do
    {
        ResetScreen();

        int NumberOfQuestion = ReadNumber();
        enQuizLevel QuizLevel = ReadQuizLevel();
        enQuizOperators OP = ReadQuizOperationType();

        stQuizResults QuizResults;

        QuizInfo = PlayGame(NumberOfQuestion, QuizLevel, OP, QuizResults);

        ShowQuizResults(QuizResults);

        cout << "Do you wand to play again ? (y/n): ";
        cin >> PlayAgain;

        cout << endl;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartQuiz();
    return 0;
}

