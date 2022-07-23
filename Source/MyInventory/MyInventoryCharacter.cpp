// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyInventoryCharacter.h"

#include "EquipInventoryComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AMyInventoryCharacter::AMyInventoryCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	EquipmentInventoryComponent = CreateDefaultSubobject<UEquipInventoryComponent>("EquipInventory");
	InventoryManagerComponent = CreateDefaultSubobject<UInventoryManagerComponent>("InventoryManager");
                         

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMyInventoryCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void AMyInventoryCharacter::BeginPlay()
{
	Super::BeginPlay();

if(InventoryManagerComponent && EquipmentInventoryComponent)
{
	InventoryManagerComponent->InitEquipment(EquipmentInventoryComponent);
}


	//	if(InventoryManagerComponent && InventoryComponent)
//	{
//		InventoryManagerComponent->Init(InventoryComponent);
//	}
	
	
}

void AMyInventoryCharacter::Interact_Implementation(AActor* ActorInteractedWithObject)
{
	if (ActorInteractedWithObject)
	{
		// check if actor has QuestList and can accept quests
		UActorComponent * ActorQuestListComp = ActorInteractedWithObject->GetComponentByClass(UQuestListComponent::StaticClass());
		if (ActorQuestListComp)
		{
			UQuestListComponent * ActorQuestList = Cast<UQuestListComponent>(ActorQuestListComp);
			// past any limitations and quest choosing logic
			TArray<AActor*> AttachedActors;
			GetAttachedActors(AttachedActors);
			bool HadQuestsAvailable = false;
			for (AActor * Actor : AttachedActors)
			{
				if (AQuest * Quest = Cast<AQuest>(Actor))
				{
					if (Quest->IsAlreadyTaken() || (Quest->GetPrerquisedQuest() && !Quest->GetPrerquisedQuest()->IsCompleted()))
					{
						continue;
					}
					if (QuestDialogClass)
					{
						UQuestDialog * QuestDialog = CreateWidget<UQuestDialog>(GetWorld(), QuestDialogClass);
						QuestDialog->Init(Quest);
						QuestDialog->OnQuestAccepted.BindUObject(ActorQuestList, &UQuestListComponent::AddQuest, Quest);
						
                        QuestDialog->OnQuestQuited.BindLambda([this, ActorInteractedWithObject]()
                        {
							NotifyInteractionFinished(this, ActorInteractedWithObject);
                        });

						QuestDialog->AddToViewport();
                    }
                        HadQuestsAvailable = true;
                }
            }

			if (!HadQuestsAvailable)
            {
				NotifyInteractionFinished(this, ActorInteractedWithObject);
            }
        }
    }
}

void AMyInventoryCharacter::ChangeClassCharacter(UDataTable* ClassDataTable) const
{
	if(InventoryManagerComponent && InventoryComponent)
	{
		InventoryComponent->InventoryClass = ClassDataTable;
		InventoryManagerComponent->Init(InventoryComponent);
		
	}
}

void AMyInventoryCharacter::EquipItem(EEquipSlot Slot, FName ItemID)
{
	UStaticMeshComponent * EquipComponent = GetEquipComponent(Slot);
	if (EquipComponent)
	{
		FInventoryItemInfo * ItemInfoPtr = InventoryManagerComponent->GetItemData(ItemID);
		if (ItemInfoPtr)
		{
			EquipComponent->SetStaticMesh(ItemInfoPtr->Mesh.LoadSynchronous());
			/*DamageStat += ItemInfoPtr->Damage;
			ArmorStat += ItemInfoPtr->Armor;
			IntelligenceStat += ItemInfoPtr->Intelligence;*/
		}
	}
}

void AMyInventoryCharacter::UnequipItem(EEquipSlot Slot, FName ItemID)
{
	UStaticMeshComponent * EquipComponent = GetEquipComponent(Slot);
	if (EquipComponent)
	{
		EquipComponent->SetStaticMesh(nullptr);
		FInventoryItemInfo * ItemInfoPtr = InventoryManagerComponent->GetItemData(ItemID);
	/*	if (ItemInfoPtr)
		{
			DamageStat -= ItemInfoPtr->Damage;
			ArmorStat -= ItemInfoPtr->Armor;
			IntelligenceStat -= ItemInfoPtr->Intelligence;
		}*/
	}
}

UStaticMeshComponent * AMyInventoryCharacter::GetEquipComponent(EEquipSlot Slot) const
{
	FName EquipTag = "";
	switch (Slot)
	{
	case EEquipSlot::ES_None:
		break;
	case EEquipSlot::ES_Head:
		EquipTag = "Equip_Head";
		break;
	case EEquipSlot::ES_Body:
		EquipTag = "Equip_Body";
		break;
	case EEquipSlot::ES_RightHand:
		EquipTag = "Equip_RightHand";
		break;
	case EEquipSlot::ES_LeftHand:
		EquipTag = "Equip_LeftHand";
		break;
	case EEquipSlot::ES_Finger:
		EquipTag = "Equip_Finger";
		break;
	case EEquipSlot::ES_Slot1:
		EquipTag = "Equip_Slot1";
		break;
	case EEquipSlot::ES_Slot2:
		EquipTag = "Equip_Slot2";
		break;
	default:
		break;
	}
	TArray<UActorComponent*> Components = GetComponentsByTag(UStaticMeshComponent::StaticClass(), EquipTag);
	return Components.Num() > 0 ? Cast<UStaticMeshComponent>(Components[0]) : nullptr;
}
