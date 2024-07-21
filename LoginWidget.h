
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "LoginWidget.generated.h"

/**
 * Goal is to accept input of username and password and compare to database
 */
UCLASS()
class CAPSTONEPROJECT_API ULoginWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

protected:
    UPROPERTY(meta = (BindWidget))
    class UEditableTextBox* UsernameTextBox;

    UPROPERTY(meta = (BindWidget))
    class UEditableTextBox* PasswordTextBox;

    UPROPERTY(meta = (BindWidget))
    class UButton* LoginButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ErrorMessage;

private:
    UFUNCTION()
    void OnLoginButtonClicked();

};
