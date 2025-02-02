// Copyright by FK


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50);
	InitMaxHealth(100);
	InitMana(50);
	InitMaxMana(100);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
	FEffectProperties& PropsOut)
{
	/**
	 * Source = Causer of the effect.
	 * Target = Target of the effect (Owner of this AS)
	 */

	PropsOut.EffectContextHandle = Data.EffectSpec.GetContext();
	PropsOut.SourceASC = PropsOut.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(PropsOut.SourceASC) && PropsOut.SourceASC->AbilityActorInfo.IsValid() && PropsOut.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		PropsOut.SourceAvatarActor = PropsOut.SourceASC->AbilityActorInfo->AvatarActor.Get();
		PropsOut.SourceController = PropsOut.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (PropsOut.SourceController == nullptr && PropsOut.SourceAvatarActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(PropsOut.SourceAvatarActor))
			{
				PropsOut.SourceController = Pawn->GetController();
			}
		}
		if (PropsOut.SourceController)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(PropsOut.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		PropsOut.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		PropsOut.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		PropsOut.TargetCharacter = Cast<ACharacter>(PropsOut.TargetAvatarActor);
		PropsOut.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PropsOut.TargetAvatarActor);
	}
}


void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}


