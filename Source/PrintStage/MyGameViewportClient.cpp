// Fill out your copyright notice in the Description page of Project Settings.

#include "PrintStage.h"
#include "MyGameViewportClient.h"




void UMyGameViewportClient::Draw(FViewport * viewport, FCanvas * sceneCanvas) {

	Super::Draw(viewport, sceneCanvas);



	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(" Viewport screenshot %s"), DoScreenShot ? TEXT("True") : TEXT("False")));

	if (DoScreenShot && ElapsedFrames > everyFrame){

		TakeScreenShot();
		ElapsedFrames = 0;
	}

	ElapsedFrames++;

}

void UMyGameViewportClient::ResetScreenshotActor(FString actorName, FString Path) {

	screenshotID = 0;
	screenshotName = actorName;

	if (Path != "null"){
		screenshotPath = FPaths::GameDir() + "\\Dataset\\" + Path + "\\";
		if(!FPaths::DirectoryExists(screenshotPath))
			PlatformFile.CreateDirectory(*screenshotPath);
	}else
		DoScreenShot = false;
	
}

void UMyGameViewportClient::TakeScreenShot() {

	//get viewport size
	FVector2D viewportSize;
	GetViewportSize(viewportSize);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(viewportSize.X) + FString::FromInt(viewportSize.Y));

	//~~~ Invalid View Port Size ~~~
	if (viewportSize.X <= 0 || viewportSize.Y <= 0) return;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//Section of Viewport to capture
	//        entire buffer invalidated if going larger than viewport size
	//        during readpixels

	viewportSize.X--;
	viewportSize.Y--;

	//Adjusted Image Size
	BMP_Width = viewportSize.X -1 ;
	BMP_Height = viewportSize.Y - 1;

	ColorBuffer.Empty();

	int32 viewportTotalSize = (viewportSize.X-1) * (viewportSize.Y-1);
	ColorBuffer.AddDefaulted(viewportTotalSize);


	//Get Screen Shot!
	if (!Viewport->ReadPixels(
		ColorBuffer,
		FReadSurfaceDataFlags(),
		FIntRect(1, 1, viewportSize.X, viewportSize.Y)

	)) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Faield to Read Pixels"));
		return;
	}


	//fill alpha = 1.0
	for (int32 i = 0; i < viewportTotalSize; i++) {
		ColorBuffer[i].A = 255;
	}

	
	//Start Processing Image
	//if(!FPaths::DirectoryExists(FPaths::GameDir() + "\\Dataset\\"))
	//	PlatformFile.CreateDirectory(FPaths::GameDir() + "\\Dataset\\");
	
	SaveScreenshotToDisk(screenshotName + "_" + FString::FromInt(screenshotID) + ".png");
	++screenshotID;
}

void UMyGameViewportClient::SaveScreenshotToDisk(FString TheFileName) {


	TArray<uint8> PNG_Compressed_ImageData;
	PNG_Compressed_ImageData.Empty();
	//PNG_Compressed_ImageData.AddZeroed(BMP_Width * BMP_Height);
	FImageUtils::CompressImageArray(BMP_Width, BMP_Height, ColorBuffer, PNG_Compressed_ImageData);

	if(FFileHelper::SaveArrayToFile(PNG_Compressed_ImageData, *(screenshotPath+TheFileName))) {
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TheFileName);
		// UE_LOG(LogTemp, Warning, TEXT("screenshot saved sucess!!!!!!!!"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("saved error"));
	
	}

	PNG_Compressed_ImageData.Empty();
}

