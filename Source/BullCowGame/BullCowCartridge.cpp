// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    LoadResources();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    if (Lives <= 0)
    {
        EndGame();
    }

    if (IsGameOver)
    {
        ClearScreen();
        SetupGame();
        return;
    }

    ProcessGuess(Input);
}

void UBullCowCartridge::ProcessGuess(const FString &Input)
{
    if (HiddenWord == Input)
    {
        PrintLine(TEXT("Correct!"));
        EndGame();
        return;
    }

    ProcessWrongGuess(Input);
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    IsGameOver = false;

    Introduction();
}

void UBullCowCartridge::Introduction() const
{
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Press Enter continue..."));
}

void UBullCowCartridge::EndGame()
{
    IsGameOver = true;
    ClearScreen();

    if (Lives <= 0)
    {
        PrintLine(TEXT("You have no lives left."));
        PrintLine(TEXT("The Hidden Word was %s"), *HiddenWord);
    }

    PrintLine(TEXT("Press Enter to play again"));
}

void UBullCowCartridge::ProcessWrongGuess(const FString &Input)
{
    if (Lives > 0)
    {
        VerifyGuess(Input);
    }

    if (Lives <= 0)
    {
        EndGame();
    }
}

void UBullCowCartridge::VerifyGuess(const FString &Input)
{
    if (HiddenWord.Len() != Input.Len())
    {
        PrintLine(TEXT("Its a %i letter word!"), HiddenWord.Len());
    }
    else if (!IsIsogram(Input))
    {
        PrintLine(TEXT("No repeating letters, guess again"));
    }
    else
    {
        PrintLine(TEXT("Sorry, Try guessing again!\nYou have %i lives remaining"), --Lives);
    }
}

bool UBullCowCartridge::IsIsogram(const FString &Input) const
{
    for (int i = 0; i < Input.Len(); i++)
    {
        for (int j = 0; j < Input.Len(); j++)
        {
            if (i != j && Input[i] == Input[j])
            {
                return false;
            }
        }
    }

    return true;
}

void UBullCowCartridge::LoadResources()
{
    const FString WordListhPath = FPaths::ProjectContentDir() / TEXT("HiddenWords/words_parsed.txt");
    FFileHelper::LoadFileToStringArray(Isograms, *WordListhPath);
}