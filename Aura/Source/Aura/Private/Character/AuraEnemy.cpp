// Copyright by FK


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	bHighlighted = true;
	SetHighLightValues(bHighlighted,*GetMesh());
	// GetMesh()->SetRenderCustomDepth(true);
	// GetMesh()->SetCustomDepthStencilValue(250);

	SetHighLightValues(bHighlighted, *Weapon);
}

void AAuraEnemy::UnHighlightActor()
{
	bHighlighted = false;
	SetHighLightValues(bHighlighted,*GetMesh());
	SetHighLightValues(bHighlighted, *Weapon);
}


void AAuraEnemy::SetHighLightValues(bool bValue, USkeletalMeshComponent& MeshComponent)
{
	MeshComponent.SetRenderCustomDepth(bValue);
	if (bValue)
	{
		MeshComponent.SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}


