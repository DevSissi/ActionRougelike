// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveActor.h"

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
}

void ASExplosiveActor::PostInitializeComponents()
{
	// 调用父类 AExplosiveActor 的 PostInitializeComponents 函数
	Super::PostInitializeComponents();
	// 将 StaticMeshComp 的 OnComponentHit 事件添加一个动态监听器，当有碰撞发生时调用 OnActorHit 函数
	StaticMeshComp->OnComponentHit.AddDynamic(this,&ASExplosiveActor::OnActorHit);
}

void ASExplosiveActor::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 发生碰撞时发出脉冲
	RadialForceComp->FireImpulse();
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