#pragma once
#include "../../tools/memory.h"


struct Model
{
	char name[255];
};


struct IModelInfo
{
	Model* GetModel(int32_t modelIndex)
	{
		return memory::CallVmtFn<Model*, int32_t>(this, 1, modelIndex);
	}

	int32_t GetModelIndex(const char* modelName)
	{
		return memory::CallVmtFn<int32_t, const char*>(this, 2, modelName);
	}

	const char* GetModelName(const Model* model)
	{
		return memory::CallVmtFn<const char*, const Model*>(this, 3, model);
	}
};