#pragma once
#include "DynamicCommandHelper.hpp"

namespace LLNET::DynamicCommand {
	using System::AttributeUsageAttribute;
	using System::AttributeTargets;
	using System::Attribute;

	[AttributeUsage(AttributeTargets::Class)]
	public ref class CommandAttribute :Attribute
	{
	public:
		CommandAttribute(String^ name)
			:Name(name)
		{
		}
		String^ Name;
		String^ Description = "";
		MC::CommandPermissionLevel Permission = MC::CommandPermissionLevel::GameMasters;
		String^ Alia = "";
		MC::CommandFlagValue Flag1 = MC::CommandFlagValue(0x80);
		MC::CommandFlagValue Flag2 = MC::CommandFlagValue(0);
	};

	[AttributeUsage(AttributeTargets::Class, AllowMultiple = true)]
	public ref class CommandAliasAttribute :Attribute
	{
	public:
		CommandAliasAttribute(String^ alia)
			:Alia(alia)
		{
		}
		String^ Alia = "";
	};

	[AttributeUsage(AttributeTargets::Enum)]
	public ref class CommandEnumAttribute :Attribute
	{
	public:
		//String^ Name = nullptr;
	};

	[AttributeUsage(AttributeTargets::Field | AttributeTargets::Property)]
	public ref class CommandParameterAttribute :Attribute
	{
	public:
		CommandParameterAttribute(DynamicCommand::ParameterType paramType)
			:Type(paramType) {}

		DynamicCommand::ParameterType Type;
		bool IsMandatory = true;
		String^ Identifier = "";
		MC::CommandParameterOption Option = MC::CommandParameterOption::None;
		property int OverloadId {int get() { return overloadId; } void set(int value) { isSet = true; overloadId = value; }}

	internal:
		int overloadId = 0;
		bool isSet = false;
	};

	[AttributeUsage(AttributeTargets::Field | AttributeTargets::Property)]
	public ref class CommandParameterOverloadAttribute :Attribute
	{
	public:
		CommandParameterOverloadAttribute(int id)
			:OverloadId(id) {}

		int OverloadId;
	};
}