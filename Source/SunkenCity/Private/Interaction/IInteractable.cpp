#include "Interaction/IInteractable.h"

void IInteractable::OnInteract_Implementation(APawn* Interactor)
{
}

FText IInteractable::GetInteractionPrompt_Implementation() const
{
	return FText::GetEmpty();
}
