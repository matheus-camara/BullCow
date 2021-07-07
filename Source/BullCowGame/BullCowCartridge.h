// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString &Input) override;
	void SetupGame();
	void Introduction() const;
	void EndGame();
	void ProcessGuess(const FString &Input);
	void VerifyGuess(const FString &Input);
	void ProcessWrongGuess(const FString &Input);
	bool IsIsogram(const FString &Input) const;

	// Your declarations go below!
private:
	FString HiddenWord;
	int32 Lives;
	bool IsGameOver;
};
