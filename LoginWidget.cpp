
#include "LoginWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Widget.h"


void ULoginWidget::NativeConstruct()
{

    if (LoginButton)
    {
        LoginButton->OnClicked.__Internal_AddDynamic(this, &ULoginWidget::OnLoginButtonClicked, UE::Delegates::Private::GetTrimmedMemberFunctionName(L"&ULoginUserWidget::OnLoginButtonClicked"));
    }
}

   
void ULoginWidget::OnLoginButtonClicked()
{
    if (!UsernameTextBox || !PasswordTextBox || !ErrorMessage) return;

    FString Username = UsernameTextBox->GetText().ToString();
    FString Password = PasswordTextBox->GetText().ToString();

    // Hardcoded credentials for testing purposes
    FString CorrectUsername = TEXT("admin");
    FString CorrectPassword = TEXT("password");

    if (Username == CorrectUsername && Password == CorrectPassword)
    {
        UE_LOG(LogTemp, Log, TEXT("Login Successful"));
        ErrorMessage->SetText(FText::FromString(TEXT("Login Successful")));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Username or Password"));
        ErrorMessage->SetText(FText::FromString(TEXT("Invalid Username or Password")));
    }
}

