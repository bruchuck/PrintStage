// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameViewportClient.h"
#include "ImageUtils.h"
#include "MyGameViewportClient.generated.h"


/**
 * 
 */
UCLASS()
class PRINTSTAGE_API UMyGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
	
public:
	
	
	void SaveScreenshotToDisk(FString TheFileName);
	bool DoScreenShot = false;

	int ElapsedFrames = 0;
	int32 everyFrame = 60;

	
	float BMP_Width, BMP_Height;
	TArray<FColor> ColorBuffer;
	void TakeScreenShot();

	void ResetScreenshotActor(FString actorName, FString Path);

protected:
	void Draw(FViewport * viewport, FCanvas * sceneCanvas) override;
	
private:
	int32 screenshotID = 0;
	FString screenshotName;
	FString screenshotPath;
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
};
