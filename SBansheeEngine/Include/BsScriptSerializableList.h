#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "CmIReflectable.h"
#include <mono/jit/jit.h>

namespace BansheeEngine
{
	class BS_SCR_BE_EXPORT ScriptSerializableList : public CM::IReflectable
	{
	private:
		struct ConstructPrivately {};

	public:
		ScriptSerializableList(const ConstructPrivately& dummy, const ScriptSerializableTypeInfoListPtr& typeInfo, MonoObject* managedInstance);
		ScriptSerializableList(const ConstructPrivately& dummy);

		MonoObject* getManagedInstance() const { return mManagedInstance; }

		static ScriptSerializableListPtr create(MonoObject* managedInstance, const ScriptSerializableTypeInfoListPtr& typeInfo);

	protected:
		MonoObject* mManagedInstance;

		ScriptSerializableTypeInfoListPtr mListTypeInfo;
		CM::Vector<ScriptSerializableFieldDataPtr>::type mListEntries;
		
		CM::UINT32 mNumElements;

		/**
		 * @brief	Populates internal field data based on currently active managed instance.
		 */
		void serializeManagedInstance();

		/**
		 * @brief	Creates a new managed instance and populates it with stored field data.
		 */
		void deserializeManagedInstance();

		void setFieldData(CM::UINT32 arrayIdx, const ScriptSerializableFieldDataPtr& val);
		ScriptSerializableFieldDataPtr getFieldData(CM::UINT32 arrayIdx);

		void setValue(CM::UINT32 arrayIdx, void* val);
		void* getValue(CM::UINT32 arrayIdx);

		CM::UINT32 getLength() const;
		void setLength(CM::UINT32 length);

		/************************************************************************/
		/* 								RTTI		                     		*/
		/************************************************************************/
		
		static ScriptSerializableListPtr createEmpty();

	public:
		friend class ScriptSerializableListRTTI;
		static CM::RTTITypeBase* getRTTIStatic();
		virtual CM::RTTITypeBase* getRTTI() const;
	};
}