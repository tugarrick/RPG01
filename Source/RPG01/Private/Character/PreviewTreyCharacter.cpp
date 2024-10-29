

#include "Character/PreviewTreyCharacter.h"
#include "Struct/ItemInfomation.h"


APreviewTreyCharacter::APreviewTreyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	if (GetMesh())
	{
		MeshComponent = GetMesh();

		ChestComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Chest"));
		ChestComponent->SetupAttachment(MeshComponent);
		ChestComponent->SetLeaderPoseComponent(MeshComponent);

		HandsComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hands"));
		HandsComponent->SetupAttachment(MeshComponent);
		HandsComponent->SetLeaderPoseComponent(MeshComponent);

		LegsComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs"));
		LegsComponent->SetupAttachment(MeshComponent);
		LegsComponent->SetLeaderPoseComponent(MeshComponent);

		FeetComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Feet"));
		FeetComponent->SetupAttachment(MeshComponent);
		FeetComponent->SetLeaderPoseComponent(MeshComponent);
	}
}

void APreviewTreyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

//void APreviewTreyCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}


void APreviewTreyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APreviewTreyCharacter::AttachItem(int EquipmentIndex, FItemInfomation& ItemInfo)
{
	if (ItemInfo.ItemClass)
	{
		FName SocketName = FName(UEnum::GetDisplayValueAsText(ItemInfo.ItemType).ToString());
		auto SocketTransform = MeshComponent->GetSocketTransform(SocketName);

		if (GetWorld() && MeshComponent) {

			auto AttachedActor = GetWorld()->SpawnActor(ItemInfo.ItemClass, &SocketTransform);
			AttachedActors.Add(EquipmentIndex, AttachedActor);
			switch (EquipmentIndex)
			{
			case 3:
				ChestComponent->SetSkeletalMesh(ItemInfo.SkeletalMesh);
				break;
			case 4:
				HandsComponent->SetSkeletalMesh(ItemInfo.SkeletalMesh);
				break;
			case 5:
				LegsComponent->SetSkeletalMesh(ItemInfo.SkeletalMesh);
				break;
			case 6:
				FeetComponent->SetSkeletalMesh(ItemInfo.SkeletalMesh);
				break;
			default:
				AttachedActor->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
				break;
			}
		}
	}
}

void APreviewTreyCharacter::DetachItem(int EquipmentIndex)
{
	if (auto AttachedActor = AttachedActors.Find(EquipmentIndex))
	{
		AttachedActors.Remove(EquipmentIndex);
		(*AttachedActor)->Destroy();
		switch (EquipmentIndex)
		{
		case 3:
			ChestComponent->SetSkeletalMesh(nullptr);
			break;
		case 4:
			HandsComponent->SetSkeletalMesh(nullptr);
			break;
		case 5:
			LegsComponent->SetSkeletalMesh(nullptr);
			break;
		case 6:
			FeetComponent->SetSkeletalMesh(nullptr);
			break;
		}
	}
}

