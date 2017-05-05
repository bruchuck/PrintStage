// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "MyGameViewportClient.h"
#include "PrintStageGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class PRINTSTAGE_API APrintStageGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void HandleStartingNewPlayer_Implementation(APlayerController *controller) override;

	UFUNCTION(BlueprintCallable, Category = "ScreenshotControl")
	void ChangeScreenshotName(FString NewName, FString Path);


	UFUNCTION(BlueprintCallable, Category = "ScreenshotControl")
	void ToggleScreenshot(bool enabled = true);

	UPROPERTY(EditAnywhere)
		int32 frameDelay;
	
};
