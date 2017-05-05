// Fill out your copyright notice in the Description page of Project Settings.

#include "PrintStage.h"
#include "PrintStageGameModeBase.h"



void APrintStageGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController *controller) {


	Super::HandleStartingNewPlayer_Implementation(controller);

	UMyGameViewportClient *viewport = Cast<UMyGameViewportClient>(GetWorld()->GetGameViewport());
	viewport->everyFrame = frameDelay;

	//ACameraActor *camera;

	for (TActorIterator<ACameraActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ActorItr->GetName());
	}
}

void APrintStageGameModeBase::ChangeScreenshotName(FString NewName, FString Path) {


	UMyGameViewportClient *viewport = Cast<UMyGameViewportClient>(GetWorld()->GetGameViewport());
	viewport->ResetScreenshotActor(NewName, Path);


}

void APrintStageGameModeBase::ToggleScreenshot(bool enabled)
{

	
	if(!UGameplayStatics::IsGamePaused(GetWorld())){
		UMyGameViewportClient *viewport = Cast<UMyGameViewportClient>(GetWorld()->GetGameViewport());
		viewport->DoScreenShot = enabled;
	}
	
}