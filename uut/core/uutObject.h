#pragma once
#include "core/uutDefine.h"
#include "core/uutPtr.h"
#include "container/uutHashString.h"

namespace uut
{
	class Context;

#define OBJECT(typeName) \
public: \
	virtual const uut::HashString& GetType() const { return GetTypeStatic(); } \
	virtual const uut::HashString& GetBaseType() const { return GetBaseTypeStatic(); } \
	static const uut::HashString& GetTypeStatic() { static const uut::HashString typeStatic(#typeName); return typeStatic; } \

#define BASEOBJECT(typeName) \
public: \
	static const uut::HashString& GetBaseTypeStatic() { static const uut::HashString baseTypeStatic(#typeName); return baseTypeStatic; } \

	class UUT_API Object : public RefCounted
	{
		BASEOBJECT(Object)
	public:
		Object(Context* context);

		virtual const HashString& GetType() const = 0;
		virtual const HashString& GetBaseType() const = 0;

		Context* GetContext() const { return _context; }

	protected:
		Context* _context;
	};

	class IObjectFactory : public RefCounted
	{
	public:
		IObjectFactory(Context* context) : _context(context) {}

		virtual Object* Create() = 0;
		virtual const HashString& GetType() const = 0;

		Context* GetContext() const { return _context; }

	protected:
		Context* _context;
	};

	template<class T>
	class ObjectFactory : public IObjectFactory
	{
	public:
		ObjectFactory(Context* context) : IObjectFactory(context) {}

		virtual Object* Create() { return new T(_context); }
		virtual const HashString& GetType() const { return T::GetTypeStatic(); }
	};
}