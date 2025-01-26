// Copyright by FK


#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemComponent.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttribute& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}
