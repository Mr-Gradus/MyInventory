#include "Npc.h"

#include "QuestListComponent.h"
#include "Components/WidgetComponent.h"

ANpc::ANpc()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComp;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));	
	Body->SetupAttachment(SceneComp);
	
	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(Body);
	
	NotifyWidget = CreateDefaultSubobject<UWidgetComponent>("NotifyWidget");
	NotifyWidget->SetWidgetClass(NotifyWidgetClass);
	NotifyWidget->SetupAttachment(RootComponent);
	NotifyWidget->SetHiddenInGame(true);
}

void ANpc::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANpc::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANpc::Interact_Implementation(AActor* InteractInstigator)
{
	if (InteractInstigator == nullptr)
	{
		return;
	}		

	UQuestListComponent* QuestList = Cast<UQuestListComponent>(InteractInstigator->GetComponentByClass(UQuestListComponent::StaticClass()));
	
	if (QuestList == nullptr)
	{
		return;
	}

	TArray<AActor*> AttachedActors;
	
	GetAttachedActors(AttachedActors);
	
	for (AActor* Actor: AttachedActors)
	{
		AQuest* Quest = Cast<AQuest>(Actor);
		
		Quest->OnNotifyStatus.AddUObject(this, &ThisClass::GetAcceptableQuest);

		if (Quest == nullptr || Quest->Objectives.Num() <= 0)
		{
			continue;
		}

		if (Quest->bIsTaken || (Quest->PrerequisitedQuest && !Quest->PrerequisitedQuest->IsCompleted()))
		{
			continue;
		}
		
		if (QuestDialogClass)
		{
			UQuestDialog* QuestDialog = CreateWidget<UQuestDialog>(GetWorld(), QuestDialogClass);
			
			QuestDialog->Init(Quest);

			QuestDialog->OnQuestAccepted.AddUObject(QuestList, &UQuestListComponent::AddQuest, Quest);

			QuestDialog->OnQuestAccepted.AddUObject(this, &ThisClass::SetHiddenNotificationWidget, true);
			
			QuestDialog->OnQuestQuited.BindLambda([this, InteractInstigator]()
			{
				NotifyInteractionFinished(this, InteractInstigator);
			});
			
			QuestDialog->AddToViewport();
			
			return;
		}
	}
	
	NotifyInteractionFinished(this, InteractInstigator);
}

TArray<AQuest*> ANpc::GetQuests() const
{
	TArray<AActor*> AttachedActors;
	TArray<AQuest*> QuestList;
	GetAttachedActors(AttachedActors);
	for (AActor* Actor : AttachedActors)
	{
		AQuest* Quest = Cast<AQuest>(Actor);
		if (Quest == nullptr)
		{
			continue;
		};

		QuestList.Add(Quest);
	}

	return QuestList;
}

TArray<AActor*> ANpc::GetAllObjectiveComps() const
{
	TArray<AActor*> ObjectiveComponents;
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (auto& Actor : AttachedActors)
	{
		AQuest* Quest = Cast<AQuest>(Actor);
		if (Quest == nullptr)
		{
			continue;
		};

		ObjectiveComponents.Append(Quest->GetObjectiveComponents());
	}

	return ObjectiveComponents;
}

bool ANpc::HasQuests() const
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	return (AttachedActors.Num() > 0);
}

void ANpc::GetAcceptableQuest()
{
	TArray<AActor*> AttachedActors;
	
	GetAttachedActors(AttachedActors);

	bool bAcceptableQuest = false;
	
	for (auto& Actor: AttachedActors)
	{
		AQuest* Quest = Cast<AQuest>(Actor);

		if (Quest == nullptr)
		{
			continue;
		}

		if (Quest->bIsTaken || (Quest->PrerequisitedQuest && !Quest->PrerequisitedQuest->IsCompleted()))
		{
			continue;
		}

		bAcceptableQuest = true;
	}

	SetHiddenNotificationWidget(!bAcceptableQuest);
}

void ANpc::SetHiddenNotificationWidget(bool bSetHidden) const
{
	if (NotifyWidget)
	{
		NotifyWidget->SetHiddenInGame(bSetHidden);
	}
}

