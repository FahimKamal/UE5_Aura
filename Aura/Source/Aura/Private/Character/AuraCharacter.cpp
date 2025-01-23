// Copyright by FK


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()-> bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	/**
	 * Set AbilitySystemComponent from player state.
	 * Set AttrubuteSet from player state.
	 */
	//======================================================================
	APlayerState* PlayerState = GetPlayerState();
	MPlayerState = Cast<AAuraPlayerState>(PlayerState);

	AbilitySystemComponent = MPlayerState->GetAbilitySystemComponent();
	AttributeSet = MPlayerState->GetAttributeSet();
	//=======================================================================
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(MPlayerState, this);
}
