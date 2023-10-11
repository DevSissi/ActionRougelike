// 在项目设置的描述页面填写您的版权声明。

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGELIKE_API USInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void DefaultInteract();

public:	
	// 设置该组件属性的默认值
	USInteractComponent();

protected:
	// 游戏开始时调用
	virtual void BeginPlay() override;

public:	
	// 每一帧调用
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
