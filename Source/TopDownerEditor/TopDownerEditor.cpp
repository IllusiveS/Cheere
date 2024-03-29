// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownerEditor.h"

#include "TopDownerEditorStyle.h"
#include "ToolMenus.h"
#include "Modules/ModuleManager.h"
#include "TopDownerToolbarCommands.h"
#include "Misc/MessageDialog.h"

//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, TopDownerEditor, "TopDownerEditor" );
static const FName TestToolbarTabName("TestToolbar");

#define LOCTEXT_NAMESPACE "FTestToolbarModule"

IMPLEMENT_MODULE(FTopDownerEditorModule, TopDownerEditor)

void FTopDownerEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTopDownerEditorStyle::Initialize();
	FTopDownerEditorStyle::ReloadTextures();

	FTopDownerEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTopDownerEditorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FTopDownerEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTopDownerEditorModule::RegisterMenus));
}

void FTopDownerEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTopDownerEditorStyle::Shutdown();

	FTopDownerEditorCommands::Unregister();
}

void FTopDownerEditorModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FTestToolbarModule::PluginButtonClicked()")),
							FText::FromString(TEXT("TestToolbar.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FTopDownerEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTopDownerEditorCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTopDownerEditorCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

DEFINE_LOG_CATEGORY(LogTopDownerEditor)
 