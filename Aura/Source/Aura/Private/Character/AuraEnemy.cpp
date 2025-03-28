// Copyright by FK


#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	

	AttributeSet =CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::HighlightActor()
{
	bool bHighlighted = true;
	SetHighLightValues(bHighlighted,*GetMesh());
	// GetMesh()->SetRenderCustomDepth(true);
	// GetMesh()->SetCustomDepthStencilValue(250);

	SetHighLightValues(bHighlighted, *Weapon);
}

void AAuraEnemy::UnHighlightActor()
{
	bool bHighlighted = false;
	SetHighLightValues(bHighlighted,*GetMesh());
	SetHighLightValues(bHighlighted, *Weapon);
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	
}

void AAuraEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}


void AAuraEnemy::SetHighLightValues(bool bValue, USkeletalMeshComponent& MeshComponent)
{
	MeshComponent.SetRenderCustomDepth(bValue);
	if (bValue)
	{
		MeshComponent.SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}


