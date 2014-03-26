#pragma once

#include "BsMonoPrerequisites.h"
#include <mono/jit/jit.h>

namespace BansheeEngine
{
	class BS_MONO_EXPORT MonoClass
	{
		struct MethodId
		{
			struct Hash
			{
				inline size_t operator()(const MethodId& v) const;
			};
			
			struct Equals
			{
				inline bool operator()(const MethodId &a, const MethodId &b) const;
			};

			MethodId(const CM::String& name, CM::UINT32 numParams);

			CM::String name;
			CM::UINT32 numParams;
		};

	public:
		~MonoClass();

		const CM::String& getNamespace() const { return mNamespace; }
		const CM::String& getTypeName() const { return mTypeName; }
		const CM::String& getFullName() const { return mFullName; }

		MonoMethod& getMethod(const CM::String& name, CM::UINT32 numParams = 0);
		MonoField* getField(const CM::String& name) const;
		MonoProperty& getProperty(const CM::String& name);
		MonoObject* getAttribute(MonoClass* monoClass) const;
		MonoClass* getBaseClass() const;

		/**
		 * @brief	Retrieves a method, expects exact method name with parameters.
		 *
		 * @note	Example: Name = "CreateInstance", Signature = "type,int[]"
		 */
		MonoMethod* getMethodExact(const CM::String& name, const CM::String& signature);

		/**
		 * @brief	Returns all fields belonging to this class.
		 *
		 * @note	Be aware this will not include the fields of any base classes.
		 */
		const CM::Vector<MonoField*>::type getAllFields() const;

		bool hasAttribute(MonoClass* monoClass) const;
		bool hasField(const CM::String& name) const;
		bool isSubClassOf(const BS::MonoClass* monoClass) const;
		bool isInstanceOfType(MonoObject* object) const;

		MonoObject* invokeMethod(const CM::String& name, MonoObject* instance = nullptr, void** params = nullptr, CM::UINT32 numParams = 0);
		void addInternalCall(const CM::String& name, const void* method);

		::MonoClass* _getInternalClass() const { return mClass; }

		MonoObject* createInstance(bool construct = true) const;
		MonoObject* createInstance(void** params, CM::UINT32 numParams);
	private:
		friend class MonoAssembly;

		MonoClass(const CM::String& ns, const CM::String& type, ::MonoClass* monoClass, const MonoAssembly* parentAssembly);

		const MonoAssembly* mParentAssembly;
		::MonoClass* mClass;
		CM::String mNamespace;
		CM::String mTypeName;
		CM::String mFullName;

		CM::UnorderedMap<MethodId, MonoMethod*, MethodId::Hash, MethodId::Equals>::type mMethods; 
		mutable CM::UnorderedMap<CM::String, MonoField*>::type mFields; 
		CM::UnorderedMap<CM::String, MonoProperty*>::type mProperties;

		mutable bool mHasCachedFields;
		mutable CM::Vector<MonoField*>::type mCachedFieldList;
	};
}