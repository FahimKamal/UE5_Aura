// Copyright by FK


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/*
	 * Line trace from cursor. There are several scenarios.
	 *  A. LastActor is null && ThisActor is null.
	 *		- Do nothing
	 *  B. LastActor is null && ThisActor is valid.
	 *		- Highlight ThisActor
	 *	C. LastActor is valid && ThisActor is null.
	 *		- UnHighlight LastActor
	 *	D. Both actors are valid, but LastActor != ThisActor.
	 *		- Unhighlight LastActor and Highlight ThisActor
	 *	E. Both actors are valid, and are the same actor
	 *		- Do nothing. 
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Base B
			ThisActor-> HighlightActor();
		}
		else
		{
			// Case A - both are null, do nothing.
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else // both actors are valid 
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor-> UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E: Do nothing.
			}
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Set EnhancedInputSubsystems for player inputs with UInputMappingContext.
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem-> AddMappingContext(AuraContext, 0);

	// Set mouse behaviour in game and UI.
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const struct FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	// (Y, Z, X)
	// (Pitch=-76.000000,Yaw=98.000000,Roll=36.000000)
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}

	// (X=1210.000000,Y=1339.000000,Z=87.500100)
}


