// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingProgress.h"


ULoadingProgress* ULoadingProgress::Get()
{
	ULoadingProgress* This = Cast<ULoadingProgress>(GEngine->AssetManager);
	if (This)
	{
		return This;
	}
	else
	{
		return NewObject<ULoadingProgress>(); // never calls this
	}
}

FString ULoadingProgress::AsyncLoadObject(FSoftObjectPath Path, FOnPackageLoaded OnPackageLoaded)
{
	FString result;
	result += FString::Printf(TEXT("StartLoad:\t%s\n"), *Path.ToString());

	CurrentLoadPackage = Path.ToString();
	LoadPackageAsync(
		CurrentLoadPackage,
		FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
			{
				if (Result == EAsyncLoadingResult::Succeeded)
				{
					//可执行通知进行地图切换，即openlevel
					OnPackageLoaded.ExecuteIfBound();
				}
			}), 0, PKG_ContainsMap);
	return result;
}
// 获取当前加载进度，并返回百分比
float ULoadingProgress::GetCurrentLoadProgress(int32& LoadedCount, int32& RequestedCount) const
{
	return GetAsyncLoadPercentage(*CurrentLoadPackage);
}
