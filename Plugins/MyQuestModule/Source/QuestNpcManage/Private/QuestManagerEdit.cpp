#include "QuestManagerEdit.h"
#include "QuestNpcManagerEditorTool.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"
#include "Engine/Selection.h"

const FEditorModeID FQuestManagerEdit::EM_QuestNpcManageEdModeId = TEXT("EM_QuestNpcManageEdMode");

FQuestManagerEdit::FQuestManagerEdit()
{

}

FQuestManagerEdit::~FQuestManagerEdit()
{

}

void FQuestManagerEdit::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FQuestNpcManagerEditorTool);
		Toolkit->Init(Owner->GetToolkitHost());
	}

	UpdateSelectedActors();
}

void FQuestManagerEdit::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	FEdMode::Exit();
}

void FQuestManagerEdit::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	for (AActor* BoundedActor : SelectedActors)
	{
		DrawWireBox( PDI, BoundedActor->GetComponentsBoundingBox(true), DebugColor, 1);
	}

	FEdMode::Render(View, Viewport, PDI);
}

void FQuestManagerEdit::DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas)
{
	FEdMode::DrawHUD(ViewportClient, Viewport, View, Canvas);

	for (const AActor* SelectedActor : SelectedActors)
	{
		if (Canvas)
		{
			FBox Bounds = SelectedActor->GetComponentsBoundingBox(true);
;
			FVector DrawPos = Bounds.GetCenter() + FVector(0.f, 0.f, Bounds.GetExtent().Z);
			FVector2D PixelLocation;

			View->ScreenToPixel(View->WorldToScreen(DrawPos), PixelLocation);
			PixelLocation /= ViewportClient->GetDPIScale();
			const UFont* RenderFont = GEngine->GetSmallFont();
			Canvas->DrawShadowedText(PixelLocation.X, PixelLocation.Y,
				FText::FromString(SelectedActor->GetName()),
				RenderFont, DebugColor);
		}
	}
}

void FQuestManagerEdit::ActorSelectionChangeNotify()
{
	FEdMode::ActorSelectionChangeNotify();

	UpdateSelectedActors();
}

bool FQuestManagerEdit::UsesToolkits() const
{
	return true;
}

void FQuestManagerEdit::UpdateSelectedActors()
{
	SelectedActors.Empty();

	USelection* SelectedActorSet = GEditor->GetSelectedActors();
	for (FSelectionIterator Iter(*SelectedActorSet); Iter; ++Iter)
	{
		AActor* LevelActor = Cast<AActor>(*Iter);
		if (LevelActor && !SelectedActors.Contains(LevelActor))
		{
			SelectedActors.Add(LevelActor);
		}
	}


}



