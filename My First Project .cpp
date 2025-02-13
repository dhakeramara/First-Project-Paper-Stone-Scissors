#include<cmath>
#include <iostream>
#include<string>
#include<cstdlib>

using namespace std;

int RandomNumber(int From, int To)
{
    int RandomNumber = rand() % (To - From + 1) + From;
    return RandomNumber;
}

enum enGameChoise{Paper = 1 , Stone = 2 , Scissors = 3};
enum enWinner{Player = 1 , Computer = 2 , Draw = 3};

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoise PlayerChoise;
    enGameChoise ComputerChoise;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

short ReadHowManyRound()
{
    short GameRound = 1;
    do
    {
        cout << "How Many Round Do You Want To Play 1 To 10 ? " << endl;
        cin >> GameRound;
        cout << endl;
    } while (GameRound < 1 || GameRound >10);
    return GameRound;
    
    
}

enGameChoise ReadPlayerChoise()
{
    short Choise = 1;
    do
    {
        cout << "Your Choise : [1]:Paper , [2]:Stone , [3]:Scissors ?" << endl;
        cin >> Choise;
    } while (Choise < 1 || Choise > 3);

    return (enGameChoise)Choise;
}

enGameChoise GetComputerChoise()
{
    return (enGameChoise)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoise == RoundInfo.ComputerChoise)
    {
        return enWinner::Draw;
    }

    switch (RoundInfo.PlayerChoise)
    {
    case enGameChoise::Stone:
        if (RoundInfo.ComputerChoise == enGameChoise::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoise::Paper:
        if (RoundInfo.ComputerChoise == enGameChoise::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoise::Scissors:
        if (RoundInfo.ComputerChoise == enGameChoise::Stone)
        {
            return enWinner::Computer;
        }
        break;
    }

    // If the Computer is Not The winner that is mean the Player is the winner
    return enWinner::Player;
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
    if (PlayerWinTimes > ComputerWinTimes)
        return enWinner::Player;
    else if (ComputerWinTimes > PlayerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player" , "Computer" , "No Winner" };
    return arrWinnerName[Winner - 1];
}

string ChoiseName(enGameChoise Choise)
{
    string arrChoiseName[3] = { "Stone" , "Paper" , "Scissors" };
    return arrChoiseName[Choise - 1];
}

void PrintRoundWinner(stRoundInfo RoundInfo)
{
    cout << "\n-----------Round [" << RoundInfo.RoundNumber << "] -----------\n\n";
    cout << "Player Choise    : " << ChoiseName(RoundInfo.PlayerChoise) << endl;
    cout << "Computer Choise  : " << ChoiseName(RoundInfo.ComputerChoise) << endl;
    cout << "Round Winner is  :[" << RoundInfo.WinnerName << "]" << endl;
    cout << "---------------------------------\n" << endl;

}

string Tabs(short NumberOfTabs)
{
    string t = "";

    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "__________________________________________________\n\n";
    cout << Tabs(2) << "            +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "__________________________________________________\n\n";

}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F"); // Color Green
        break;
    case enWinner::Computer:
        system("color 4F"); // Color Red
        cout << "\a";
        break;
    default:
        system("color 6F"); // Color yellow
        break;
    }
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "---------------------- [Game Results ] ---------------------\n\n";
    cout << Tabs(2) << "Game Rounds         : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player Won Times    : " << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer Won Times  : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw Times          : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner is     : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "------------------------------------------------------------\n\n";

    SetWinnerScreenColor(GameResults.GameWinner);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

stGameResults FillGameResults(short GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.PlayerWinTimes = PlayerWinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

stGameResults PlayGame(short HowManyRound)
{
    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRound; GameRound++)
    {
        cout << "Round [" << GameRound << "] Begin :\n\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoise = ReadPlayerChoise();
        RoundInfo.ComputerChoise = GetComputerChoise();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

     //Increae Win / Draw Counters :
        if (RoundInfo.Winner == enWinner::Player)
        {
            PlayerWinTimes++;
        }
        else if (RoundInfo.Winner == enWinner::Computer)
        {
            ComputerWinTimes++;
        }
        else
        {
            DrawTimes++;
        }

        PrintRoundWinner(RoundInfo);
    }

    return FillGameResults(HowManyRound, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}




void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRound());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do You Want To Play Agin ? Y/N ?";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{
    srand((unsigned)time(NULL));
    StartGame();

}

