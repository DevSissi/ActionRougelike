// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建一个球体组件
	SphereComp =  CreateDefaultSubobject<USphereComponent>("SphereComp");
	// 设置球体半径
	SphereComp->SetSphereRadius(1);
	// 将碰撞组件的碰撞文件默认为Projectile
	SphereComp->SetCollisionProfileName("Projectile");
	// 将球体组件设置为根组件
	RootComponent = SphereComp;
	// 将 SphereComp 的 OnComponentBeginOverlap 事件添加一个动态监听器，当发生时调用 OnOverlapBegin 函数
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnOverlapBegin);

	// 创建粒子系统组件
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	// 将粒子组件绑定到球体组件下
	EffectComp->SetupAttachment(SphereComp);

	// 创建弹体运动组件
	MovementComp =  CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	// 初始化弹体速度默认值为1000
	MovementComp->InitialSpeed = 1000.0f;
	// 让粒子系统跟随射弹的速度
	MovementComp->bRotationFollowsVelocity = true;
	// 将初始速度设置为本地空间
	MovementComp->bInitialVelocityInLocalSpace = true;
	// 关闭重力影响（值设置为0）
	MovementComp->ProjectileGravityScale = 0.0f;
	

}

void ASMagicProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 如果其他 Actor 不为空
	if (ensure(OtherActor && OtherActor != GetInstigator()))
	{
		// 尝试将其他 Actor 转换为 USAttributeComponent
		USAttributeComponent* AtrributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));

		// 改变其他物体的血量
		AtrributeComp->isChangeHealth(Damage);

		Destroy();
	}
}