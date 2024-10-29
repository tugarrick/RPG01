// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TreyCharacter.h"
#include "Character/PreviewTreyCharacter.h"
#include "Components/SphereComponent.h"
#include "Actor/InteractableItems.h"
#include "Enum/ItemType.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "DataAsset/TreyCharacterData.h"
#include "DataAsset/EnhancedInputData.h"
#include "Widget/NotifyBoxWidget.h"
#include "Widget/NotifyWidget.h"
#include "Component/StatComponent.h"
#include "Component/InventorySystemComponent.h"



// Sets default values
ATreyCharacter::ATreyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetSphereRadius(128.0);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATreyCharacter::SphereComponentBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ATreyCharacter::SphereComponentEndOverlap);

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
		
	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("Stat Component"));

	InventorySystem = CreateDefaultSubobject<UInventorySystemComponent>(TEXT("Inventory System"));
	InventorySystem->Inventory.SetNum(InventorySize);
}

void ATreyCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	
	if (InventorySystem && PlayerController)
	{
		InventorySystem->Init(PlayerController);
	}	
	
	if (TreyCharacterData == nullptr) return;

	if (TreyCharacterData->NotifyBoxWidgetClass && PlayerController)
	{
		UNotifyBoxWidget::InitInstance(PlayerController, TreyCharacterData->NotifyBoxWidgetClass);
		UNotifyBoxWidget::Get()->AddToViewport(1);
	}
}

void ATreyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATreyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	SetupInputMappingContext();

	auto EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInput && EnhancedInputData)
	{
		EnhancedInput->BindAction(EnhancedInputData->IA_Pickup, ETriggerEvent::Triggered, this, &ATreyCharacter::Pickup);
		EnhancedInput->BindAction(EnhancedInputData->IA_ToggleInventory, ETriggerEvent::Triggered, this, &ATreyCharacter::ToggleInventory);
	}
}

void ATreyCharacter::SphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag(FName(TEXT("Interactable"))))
	{
		InteractableActors.AddUnique(Cast<AInteractableItems>(OtherActor));
		if (auto InteractInterface = TScriptInterface<IInteractInterface>(InteractableActors[0]))
		{
			InteractInterface->I_InRange();
		}

	}
}

void ATreyCharacter::SphereComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag(FName(TEXT("Interactable"))))
	{
		auto InteractableActor = Cast<AInteractableItems>(OtherActor);
		InteractableActors.Remove(InteractableActor);
		if (auto InteractInterface = TScriptInterface<IInteractInterface>(InteractableActor))
		{
			InteractInterface->I_OutOfRange();
		}
	}
}

void ATreyCharacter::SetupInputMappingContext()
{
	if (auto Local_PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Local_PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(EnhancedInputData->IMC_Trey, 0);
		}
	}
}

void ATreyCharacter::Pickup()
{
	if (!InventorySystem) return;

	if (!InteractableActors.IsEmpty() && InventorySystem->InterfaceWidget == nullptr)
	{
		if (auto InteractInterface = TScriptInterface<IInteractInterface>(InteractableActors[0]))
		{
			InteractableActors.RemoveAt(0);
			InteractInterface->I_Interact(this);
		}
	}
	if (!InteractableActors.IsEmpty() && InventorySystem->InterfaceWidget == nullptr)
	{
		if (auto InteractInterface = TScriptInterface<IInteractInterface>(InteractableActors[0]))
		{
			InteractInterface->I_InRange();
		}
	}
}

void ATreyCharacter::ToggleInventory()
{	
	if (!InventorySystem) return;

	if (InventorySystem->InterfaceWidget == nullptr)
	{
		InventorySystem->OpenInventory();
		bCanMove = false;
	}
	else
	{
		InventorySystem->CloseInventory();
		bCanMove = true;
	}
}

void ATreyCharacter::PickupItem(FItemInfomation& ItemInfo)
{
	if (!InventorySystem) return;

	InventorySystem->AddItem(ItemInfo);
	
	if (TreyCharacterData->NotifyWidgetClass)
	{
		UNotifyBoxWidget::Get()->AddNotify(ItemInfo, TreyCharacterData->NotifyWidgetClass);
	}
}

UInventorySystemComponent* ATreyCharacter::GetInventorySystem()
{
	if (IsValid(InventorySystem))
	{
		return InventorySystem;
	}
	return nullptr;
}

void ATreyCharacter::AddAttachedItem(int EquipmentIndex, FItemInfomation& ItemInfo)
{
	if (!ItemInfo.ItemClass || !StatComponent) return;
	if (!InventorySystem) return;

	for (auto StatData : ItemInfo.Stats)
	{
		switch (StatData.Key)
		{
		case EStat::AttackSpeed:
			StatComponent->SetMaxStat(StatData.Key,
				StatComponent->GetMaxStat(StatData.Key) + StatComponent->GetBaseStat(StatData.Key) * StatData.Value / 100.0f,
				true);
			break;
		default:
			StatComponent->SetMaxStat(StatData.Key,
				StatComponent->GetMaxStat(StatData.Key) + StatData.Value,
				true);
			break;
		}
	}

	InventorySystem->AttachedEquipment.Add({ EquipmentIndex, ItemInfo });
	AttachItem(EquipmentIndex, ItemInfo);
}

void ATreyCharacter::AttachItem(int EquipmentIndex, FItemInfomation& ItemInfo)
{
	if (!ItemInfo.ItemClass) return;
	if (!InventorySystem) return;

	FName SocketName = FName(UEnum::GetDisplayValueAsText(ItemInfo.ItemType).ToString());
	auto SocketTransform = MeshComponent->GetSocketTransform(SocketName);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			3.0f,
			FColor::Blue,
			SocketName.ToString()
		);
	}

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
	
	if (InventorySystem->PreviewTreyCharacter)
	{
		InventorySystem->PreviewTreyCharacter->AttachItem(EquipmentIndex, ItemInfo);
	}
}


void ATreyCharacter::RemoveAttachedItem(int EquipmentIndex, FItemInfomation& ItemInfo, bool bChangeCurrentStats)
{
	if (!ItemInfo.ItemClass || !StatComponent) return;
	if (!InventorySystem) return;
	 
	for (auto StatData : ItemInfo.Stats)
	{
		switch (StatData.Key)
		{
		case EStat::AttackSpeed:
			StatComponent->SetMaxStat(StatData.Key,
				StatComponent->GetMaxStat(StatData.Key) - StatComponent->GetBaseStat(StatData.Key) * StatData.Value / 100.0f,
				bChangeCurrentStats);
			break;
		default:
			StatComponent->SetMaxStat(StatData.Key,
				StatComponent->GetMaxStat(StatData.Key) - StatData.Value,
				bChangeCurrentStats);
			break;
		}
	}

	InventorySystem->AttachedEquipment.Remove(EquipmentIndex);
	DetachItem(EquipmentIndex);
}

float ATreyCharacter::GetCurrentStat(const EStat& Stat)
{
	if (StatComponent)
	{
		return StatComponent->GetCurrentStat(Stat);
	}
	return 0.0f;
}

float ATreyCharacter::GetMaxStat(const EStat& Stat)
{
	if (StatComponent)
	{
		return StatComponent->GetMaxStat(Stat);
	}
	return 0.0f;
}

float ATreyCharacter::GetBaseStat(const EStat& Stat)
{
	if (StatComponent)
	{
		return StatComponent->GetBaseStat(Stat);
	}
	return 0.0f;
}

void ATreyCharacter::DetachItem(int EquipmentIndex)
{
	if (!InventorySystem) return;

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

	if (InventorySystem->PreviewTreyCharacter)
	{
		InventorySystem->PreviewTreyCharacter->DetachItem(EquipmentIndex);
	}
}

void ATreyCharacter::I_Interact(AActor* InActor)
{
	if (auto InteractableItem = Cast<AInteractableItems>(InActor))
	{
		PickupItem(InteractableItem->ItemInfo);
	}
}





