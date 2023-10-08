// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建弹簧臂组件
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	//使用Pawn的旋转控制
	SpringArmComp->bUsePawnControlRotation = true;
	//将弹簧臂组件绑定到根组件
	SpringArmComp->SetupAttachment(RootComponent);
	
	// 创建相机组件
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CamaraComp");
	//将相机组件绑定到弹簧臂组件
	CameraComp->SetupAttachment(SpringArmComp);

	// 将角色朝向向加速度方向旋转，用RotationRate作为旋转改变速率
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 调用将运动功能绑定到用户输入
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 将角色移动绑定到轴输入
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	
	// 将角色旋转绑定到轴输入
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this, &APawn::AddControllerPitchInput);

	// 将角色的攻击绑定到动作输入
	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&ASCharacter::PrimaryAttack);
	
	// 将角色的跳跃绑定到动作输入
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
}

//
void ASCharacter::MoveForward(float Value)
{
	// 获取控制器当前的朝向（获取旋转，将除Yaw之外的角度设置为0）
	FRotator RotatorRotation = GetControlRotation();
	RotatorRotation.Pitch = 0.0f;
	RotatorRotation.Roll = 0.0f;
	
	// 将朝向设置为角色运动方向
	AddMovementInput(RotatorRotation.Vector(),Value);
}

void ASCharacter::MoveRight(float Value)
{
	//获取控制器当前的朝向（获取旋转，将除Yaw之外的角度设置为0）
	FRotator RotatorRotation = GetControlRotation();
	RotatorRotation.Pitch = 0.0f;
	RotatorRotation.Roll = 0.0f;
	
	 // x = 前方		红色
	 // y = 右方		绿色
	 // z = 上方		蓝色
	
	// 将Y轴朝向转换为方向向量
	FVector RightVector = FRotationMatrix(RotatorRotation).GetScaledAxis(EAxis::Y);
	
	// 将角色运动方向设置为方向向量（Y轴朝向）
	AddMovementInput(RightVector, Value);
}

void ASCharacter::PrimaryAttack()
{
	// 获取角色的武器位置
	FVector SwordLoc = GetMesh()->GetSocketLocation("Sword");
	
	// 将弹体生成位置设置为武器位置
	FTransform SpawnTrans = FTransform(GetActorRotation(),SwordLoc);
	//设定生成参数，即使碰撞也始终生成
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//在武器位置生成弹体
	GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTrans,SpawnParams);
}
