#pragma once
#include <src/Main/ClassTemplate.hpp>

#include <RemoteCallAPI.h>

namespace RemoteCall
{
    struct ItemType;
}

namespace MC
{
    ref class ItemStack;
}

namespace LiteLoader::RemoteCall
{
    public ref class ItemType : ClassTemplate<ItemType, ::RemoteCall::ItemType>/*, IValue*/
    {
    public:
        __ctor_all(ItemType, ::RemoteCall::ItemType);
        __ctor_default(ItemType, ::RemoteCall::ItemType);
    public:
        ItemType(MC::ItemStack^ item);

        MC::ItemStack^ Get();

    public:
        static operator ItemType ^ (MC::ItemStack^ v);
        static operator MC::ItemStack ^ (ItemType^ v);
    internal:
        ItemType(::RemoteCall::ItemType const& v);
    public:
        virtual String^ ToString() override;
    };
}