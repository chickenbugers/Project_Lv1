// Fill out your copyright notice in the Description page of Project Settings.


#include "Room/RoomListWidget.h"
#include "RoomItemWidget.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"

bool URoomListWidget::Initialize()
{
	if(Super::Initialize() == false)
		return false;

	SetInfo();

	return true;
}

void URoomListWidget::SetInfo()
{
	Rooms.Empty();

	for (int32 i = 0; i < 50; i++)
	{
		if(RoomItemWidgetClass == nullptr)
			continue;

		URoomItemWidget* ChildWidget = CreateWidget<URoomItemWidget>(GetWorld(), RoomItemWidgetClass);
		if(ChildWidget == nullptr)
			continue;

		RoomList->AddChildToWrapBox(ChildWidget);

		Rooms.Add(ChildWidget);
	}

	RefreshUI();
}

void URoomListWidget::RefreshUI()
{
	const int32 SessionLength = SessionInfos.Num();

	for (int32 i = 0; i < Rooms.Num(); i++)
	{
		const int32 Index = i;

		if (Index < SessionLength)
		{
			Rooms[Index]->SetVisibility(ESlateVisibility::Visible);

			FBlueprintSessionResult Result = SessionInfos[Index];
			Rooms[Index]->SetInfo(Result);
		}
		else
		{
			Rooms[Index]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}