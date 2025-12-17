#pragma once

#include "CoreMinimal.h"
#include "ImHighlightable.generated.h"

UINTERFACE(BlueprintType)
class FPINTERACTMOVECOMP_API UImHighlightable : public UInterface
{
	GENERATED_BODY()
};

class FPINTERACTMOVECOMP_API IImHighlightable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Highlight")
	void Highlight();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Highlight")
	void Unhighlight();
};