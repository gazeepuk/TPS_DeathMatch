// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "AnnouncementWidget.h"

#include "Components/TextBlock.h"

void UAnnouncementWidget::SetCountdownText(const FText& CountdownText) const
{
	WarmupCountdownTextBlock->SetText(CountdownText);
}

void UAnnouncementWidget::SetCountdownText(float CountdownTime) const
{
	CountdownTime = FMath::Max(CountdownTime, 0.f);
	const int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
	const int32 Seconds = CountdownTime - Minutes * 60;
	const FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	WarmupCountdownTextBlock->SetText(FText::FromString(CountdownText));
}

void UAnnouncementWidget::SetAnnouncementText(const FText& AnnouncementText) const
{
	if(AnnouncementTextBlock)
	{
		AnnouncementTextBlock->SetText(AnnouncementText);
	}
}
