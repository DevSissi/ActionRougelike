// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveActor.h"

#include "SAttributeComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveActor::ASExplosiveActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建静态网格组件
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	// 将碰撞配置文件设置为PhysicsActor
	StaticMeshComp->SetCollisionProfileName("PhysicsActor");
	//将静态网格组件设置为根组件
	RootComponent = StaticMeshComp;
	// 启用物理模拟
	StaticMeshComp->SetSimulatePhysics(true);
	// 添加碰撞事件监听器
	StaticMeshComp->OnComponentHit;

	// 创建径向力（RadialForce）组件
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	// 将径向力组件附加到静态网格体组件
	RadialForceComp->SetupAttachment(StaticMeshComp);

	// 初始化设置径向力组件
	RadialForceComp->Radius = 500.0f;
	RadialForceComp->ImpulseStrength = 400.0f;
	RadialForceComp->bImpulseVelChange = true;
	//关闭自动启用
	RadialForceComp->SetAutoActivate(false);
	
	// 将 StaticMeshComp 的 OnComponentHit 事件添加一个动态监听器，当有碰撞发生时调用 OnActorHit 函数
	// 在构造函数和下面的 PostInitializeComponents() 中调用都可以
	StaticMeshComp->OnComponentHit.AddDynamic(this,&ASExplosiveActor::OnActorHit);

	//初始化爆炸伤害
	Damage = 50.f;
}

void ASExplosiveActor::PostInitializeComponents()
{
	// 调用父类 AExplosiveActor 的 PostInitializeComponents 函数
	Super::PostInitializeComponents();
}

/** 
 * @brief 当 Actor 被击中时
 * @param HitComp		表示被碰撞的组件，可能是角色本身的一个组件，也可能是其他物体碰撞到该组件上。
 * @param OtherActor	表示碰撞的Actor。
 * @param OtherComp		表示碰撞的组件。
 * @param NormalImpulse	表示碰撞的 impulse（ impulse 是一种碰撞效果，通常用于模拟物理碰撞）。
 * @param Hit			表示碰撞结果的数据结构，包括碰撞的点、碰撞的向量等信息。
 */
void ASExplosiveActor::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 发生碰撞时发出脉冲
	RadialForceComp->FireImpulse();

	if (OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()))
	{
		USAttributeComponent* AffectComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		
		AffectComp->isChangeHealth(-Damage);
	}

	// Debug入门
	// 通过UE的Debug系统记录日志
	// 这段代码的目的是在Unreal Engine 5中使用UE_LOG函数记录一条日志。LogTemp是一个日志类别，Log是一个日志级别。TEXT是一个格式化字符串的宏，用于将其他参数插入到字符串中。
	//UE_LOG(LogTemp,Log,TEXT("其他Actor: %s, 游戏内时间: %f"),*OtherActor->GetName(),GetWorld()->TimeSeconds);
}

// Called when the game starts or when spawned
void ASExplosiveActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASExplosiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}