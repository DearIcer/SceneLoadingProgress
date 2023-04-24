// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LoadingProgress.generated.h"

//异步加载资源完成后回调通知。
DECLARE_DYNAMIC_DELEGATE(FOnPackageLoaded);
/**
 * 
 */
UCLASS()
class SCENELOADINGPROGRESS_API ULoadingProgress : public UAssetManager
{
	GENERATED_BODY()
public:
	FString CurrentLoadPackage;

	/**
	 * @brief 用于获取唯一的 ULoadingProgress 实例。
	 * @return 
	 */
	UFUNCTION(BlueprintPure, CallInEditor,DisplayName = "LoadingProgress")
	static  ULoadingProgress* Get();

	/**
	 * @brief 异步加载指定路径的资源，并注册回调函数。
	 * @param Path 
	 * @param OnPackageLoaded 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, CallInEditor)
	FString AsyncLoadObject(FSoftObjectPath Path, FOnPackageLoaded  OnPackageLoaded);
	
	/**
	 * @brief 获取当前加载进度。
	 * @param LoadedCount 
	 * @param RequestedCount 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, CallInEditor)
	float GetCurrentLoadProgress(int32& LoadedCount, int32& RequestedCount) const;
};
