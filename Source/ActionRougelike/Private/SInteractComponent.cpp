// 在项目设置的描述页面填写您的版权声明。


#include "SInteractComponent.h"

#include <ocidl.h>

#include "SCharacter.h"
#include "SGameplayInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/GameSession.h"
#include "HAL/ExceptionHandling.h"
#include "Physics/PhysicsFiltering.h"


// 设置该组件属性的默认值
USInteractComponent::USInteractComponent()
{
	// 设置该组件在游戏开始时初始化，并且每帧都被勾选。如果不需要这些功能，您可以关闭它们以提高性能。
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
}


// 游戏开始时调用
void USInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// 每一帧调用
void USInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractComponent::DefaultInteract()
{
	// 创建一个碰撞对象查询参数，用于检测可检测的对象
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	QueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	
	// 获取玩家的眼睛视点
	FVector EyeLoc;
	FRotator EyeRot;
	FVector StartLoc;
	FVector EndLoc;

	//GetOwner() 返回的是AActor*类型 后续根据需求转换
	AActor* CompOwnerActor = GetOwner();
	CompOwnerActor->GetActorEyesViewPoint(EyeLoc,EyeRot);

	StartLoc = EyeLoc;
	// 计算射线的终点
	EndLoc = EyeLoc + EyeRot.Vector() * 100;

	// 射线检测，LineTraceSingle 检测范围太窄
	//FHitResult HitResult;
	//GetWorld()->LineTraceSingleByObjectType(HitResult,EyeLoc,EndLoc,QueryParams);

	// 使用多重扫描检测
	TArray<FHitResult> HitResult;
	FCollisionShape HitShape;
	float Radius = 10.0f;
	HitShape.SetSphere(Radius);

	//使用角色的摄像机作为射线检测起点，防止移动相机后实际检测位置与视觉不符
	if (UCameraComponent* CameraComp = GetOwner()->FindComponentByClass<UCameraComponent>())
	{
		StartLoc = CameraComp->GetComponentLocation();
		EndLoc = StartLoc + CameraComp->GetForwardVector() * 100;
	}
	
	// 将扫描结果存入bIsHit中
	bool bIsHit = GetWorld()->SweepMultiByObjectType(HitResult,StartLoc,EndLoc,FQuat::Identity,QueryParams,HitShape);

	// 遍历所有检测到的碰撞对象
	for (FHitResult Hits : HitResult)
	{
		// 获取碰撞对象
		AActor* HitActor = Hits.GetActor();
		if (HitActor)
		{
			// 尝试将碰撞对象转换为Pawn
			APawn* CompOwnerPawn = Cast<APawn>(CompOwnerActor);
			// 如果碰撞对象实现接口，则执行交互
			if (HitActor->Implements<USGameplayInterface>())
			{
				ISGameplayInterface::Execute_Interact(HitActor,CompOwnerPawn);
				//如果执行了互动就跳出循环，保证每次仅互动一个物品
				break;
			}
		}

		// 绘制调试 sphere
		//FColor DebugColor = bIsHit ? FColor::Green : FColor::Red;
		//DrawDebugSphere(GetWorld(),Hits.ImpactPoint,Radius,16,DebugColor,false,2.f);
		
	}

	// 绘制调试 line
	//FColor DebugLineColor = bIsHit ? FColor::Green : FColor::Red;
	//DrawDebugLine(GetWorld(),StartLoc,EndLoc,DebugLineColor,false,20.0f,0,1.0f);
	
}