#pragma once

#include "CoreMinimal.h"
#include "Toolkits/BaseToolkit.h"

class FQuestNpcManagerEditorTool : public FModeToolkit
{
public:

	FQuestNpcManagerEditorTool();
	
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

	virtual FName GetToolkitFName() const override;

	virtual FText GetBaseToolkitName() const override;

	virtual FEdMode* GetEditorMode() const override;

	virtual TSharedPtr<SWidget> GetInlineContent() const override { return ToolkitWidget; }

	void UpdateColor(FLinearColor NewColor);
	
	
	

private:

	FLinearColor GetColor() const;

	FReply SelectNewColor(const FGeometry&, const FPointerEvent&);

	FReply OnQuestSelection();

	FReply OnButtonClick(FVector InOffset);

	TSharedRef<SWidget> MakeButton(FText InLabel, const FVector InOffset);

	TSharedRef<SWidget> MakeQuestControlButton(FText InLabel);

	TSharedPtr<SWidget> ToolkitWidget;

};
