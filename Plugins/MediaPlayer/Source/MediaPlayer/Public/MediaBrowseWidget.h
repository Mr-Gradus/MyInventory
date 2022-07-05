#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "MediaBrowseWidget.generated.h"

UCLASS()
class MEDIAPLAYER_API UMediaBrowseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstanceDynamic;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMediaPlayer* MediaPlayer;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* Material;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* BrowseButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CloseButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* RenderImage;

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnCloseButtonReleased();
	
	UFUNCTION()
	void OnBrowseButtonReleased();

	UFUNCTION()
	void OnMediaOpened(FString Path);
};
