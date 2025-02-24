// Copyright by FK


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	const bool bLogNotFound) const
{
	for (const auto& [InputAction, InputTag] : AbilityInputActions)
	{
		if (InputAction && InputTag == InputTag)
		{
			return InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
