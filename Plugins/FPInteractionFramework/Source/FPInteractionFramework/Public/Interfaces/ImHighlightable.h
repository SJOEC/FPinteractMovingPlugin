#pragma once

#include "CoreMinimal.h"
#include "ImHighlightable.generated.h"

UINTERFACE(BlueprintType)
class FPINTERACTIONFRAMEWORK_API UImHighlightable : public UInterface
{
	GENERATED_BODY()
};

class FPINTERACTIONFRAMEWORK_API IImHighlightable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Highlight")
	void Highlight();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Highlight")
	void Unhighlight();
};