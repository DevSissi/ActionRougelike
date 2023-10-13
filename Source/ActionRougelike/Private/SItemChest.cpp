// 在项目设置的描述页面填写您的版权声明。


#include "SItemChest.h"



// 设置默认值
ASItemChest::ASItemChest()
{
	// 设置该 actor 每帧调用 Tick()。如果不需要，您可以将其关闭以提高性能。
	PrimaryActorTick.bCanEverTick = true;
	
	// 创建基座网格组件
	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	// 创建盖子网格组件
	LidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");

	// 设置基座为根组件
	RootComponent = BaseMeshComp;
	// 将盖子网格组件附加到基座网格组件上
	LidMeshComp->SetupAttachment(BaseMeshComp);

	// 设置盖子旋转角度
	OpenedRotation = FRotator(0, 0, 0);

}

// 玩家与该物品交互时调用
void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	// 设置盖子网格组件的相对旋转角度
	LidMeshComp->SetRelativeRotation(OpenedRotation);
}

// 游戏开始或生成时调用
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// 在每一帧调用
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

