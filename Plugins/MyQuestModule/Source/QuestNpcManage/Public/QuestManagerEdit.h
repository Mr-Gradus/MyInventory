#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"

class FQuestManagerEdit : public FEdMode
{
public:
	const static FEditorModeID EM_QuestNpcManageEdModeId;
public:
	FQuestManagerEdit();

	virtual ~FQuestManagerEdit() override;

	virtual void Enter() override;

	virtual void Exit() override;
	
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;

	virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;

	virtual void ActorSelectionChangeNotify() override;

	virtual bool UsesToolkits() const override;

	void ChangeDebugColors(const FLinearColor NewColor) {
		DebugColor = NewColor;
	}

	FLinearColor GetDebugColor() const { return DebugColor; }

protected:
	TArray<AActor*> SelectedActors;

	void UpdateSelectedActors();	
	
private:
	FLinearColor DebugColor = FColor::Yellow;

};
