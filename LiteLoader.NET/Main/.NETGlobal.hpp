#pragma once
#include <msclr/marshal_cppstd.h>
#include <stdint.h>

#include "Global.hpp"
#include "../Header/Core/Pair.hpp"

#define LLNET_DEFAULT_EXCEPTION_MESSAGE "Uncaught {0} detected!"

#define CATCH                                                                                   \
    catch (System::Exception ^ ex)                                                              \
    {                                                                                           \
        System::Console::WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, ex->GetType()->ToString()); \
        System::Console::WriteLine(ex->ToString());                                             \
    }                                                                                           \
    catch (const std::exception& ex)                                                            \
    {                                                                                           \
        System::Console::WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, "std::exception");          \
        System::Console::WriteLine(marshalString(ex.what()));                                   \
    }                                                                                           \
    catch (...)                                                                                 \
    {                                                                                           \
        System::Console::WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, "exception");               \
    }

#define NULL_ARG_CHEEK(arg)           \
    if (ReferenceEquals(arg, nullptr)) \
        throw gcnew ::System::ArgumentNullException(#arg, "Cannot be null.");

#define CLASS \
public        \
    ref class

using System::Console;
using System::GC;
using System::IntPtr;
using System::String;
using System::Collections::Generic::Dictionary;
using System::Collections::Generic::List;
using System::Reflection::Assembly;
using System::Reflection::AssemblyName;
using System::Runtime::InteropServices::FieldOffsetAttribute;
using System::Runtime::InteropServices::GCHandle;
using System::Runtime::InteropServices::LayoutKind;
using System::Runtime::InteropServices::Marshal;
using System::Runtime::InteropServices::StructLayoutAttribute;
using LLNET::Core::Pair;

#include "../Tools/clix.hpp"
using namespace clix;

inline String^ marshalString(std::string const& str) {
    return marshalString<Encoding::E_UTF8>(str);
};

inline std::string marshalString(String^ str)
{
    return marshalString<Encoding::E_UTF8>(str);
}

inline uint64_t do_Hash(String^ str)
{
    uint64_t rval = 0;
    for (int i = 0; i < str->Length; ++i)
    {
        if (i & 1)
        {
            rval ^= (~((rval << 11) ^ str[i] ^ (rval >> 5)));
        }
        else
        {
            rval ^= (~((rval << 7) ^ str[i] ^ (rval >> 3)));
        }
    }
    return rval;
}