// 在项目设置的描述页面填写您的版权声明。

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SItemChest.generated.h"

UCLASS()
class ACTIONROUGELIKE_API ASItemChest : public AActor,public ISGameplayInterface
{
	GENERATED_BODY()

	// 重写 ISGameplayInterface::Interact 方法
	void Interact_Implementation(APawn* InstigatorPawn) override;
	
public:	
	// 设置该 actor 属性的默认值
	ASItemChest();

	// 设置物品打开时的网格体角度
	UPROPERTY(EditAnywhere)
	FRotator OpenedRotation;

protected:

	// 物品的基座
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMeshComp;

	// 物品的盖子
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMeshComp;
	
	// 游戏开始或生成时调用
	virtual void BeginPlay() override;

public:	
	// 在每一帧调用
	virtual void Tick(float DeltaTime) override;

};