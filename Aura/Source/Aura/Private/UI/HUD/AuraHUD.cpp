// Copyright by FK


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"


void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
