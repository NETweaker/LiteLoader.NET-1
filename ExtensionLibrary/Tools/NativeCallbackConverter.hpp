#include <Utils/Hash.h>
#include "Global.hpp"
#pragma once

constexpr size_t do_hash()
{
    return 0;
}

using CHash = size_t;

public
interface class NativeCallbackHandler : System::IDisposable
{
};

/**
 * .Net-Native�ص�ת������
 *
 * class_name          : ����   �������
 * callback_delegate   : .Netί������
 * ret                 : Native�ص�������������
 * ...                 : Native�ص����������б�
 *
 * ====================API======================
 *
 * class_name::Create(dlegate^ callback) :���ذ���Native����ָ����ת����ʵ����Pair
 * class_name:
 *    GCHandle gch:��ֹ����.Net�ص�ί�е�handle
 *    callback_delegate^ delfunc:.Net�ص�ί��
 *
 * Ps:
 * �ȶ���δ֪����ת����ʵ���Ļ��ջᵼ��.Netί��ʵ�����ͷ���Native����ָ���ʧЧ
 * �ȴ��ȶ��Բ���.jpg
 */
#define DelegateToNativeHelper(class_name, callback_delegate, ret, ...)                                                                             \
                                                                                                                                                    \
    template <CHash, CHash>                                                                                                                         \
    ref class NativeCallbackTemplate;                                                                                                               \
                                                                                                                                                    \
    template <>                                                                                                                                     \
    ref class NativeCallbackTemplate<do_hash(#class_name) ^ do_hash(#ret), do_hash(#callback_delegate) ^ do_hash(#__VA_ARGS__)>                     \
        : public NativeCallbackHandler                                                                                                              \
    {                                                                                                                                               \
    public:                                                                                                                                         \
        typedef ret (*pCallback)(__VA_ARGS__);                                                                                                      \
        delegate ret delCallback(__VA_ARGS__);                                                                                                      \
                                                                                                                                                    \
    public:                                                                                                                                         \
        GCHandle gch;                                                                                                                               \
        callback_delegate ^ delfunc;                                                                                                                \
                                                                                                                                                    \
    public:                                                                                                                                         \
        value class __Pair                                                                                                                          \
        {                                                                                                                                           \
        public:                                                                                                                                     \
            pCallback pCallbackFn;                                                                                                                  \
            NativeCallbackTemplate ^ converter;                                                                                                     \
            __Pair(pCallback p, NativeCallbackTemplate ^ obj)                                                                                       \
                : pCallbackFn(p)                                                                                                                    \
                , converter(obj)                                                                                                                    \
            {                                                                                                                                       \
            }                                                                                                                                       \
        };                                                                                                                                          \
                                                                                                                                                    \
    protected:                                                                                                                                      \
        NativeCallbackTemplate()                                                                                                                    \
            : delfunc(nullptr)                                                                                                                      \
        {                                                                                                                                           \
        }                                                                                                                                           \
        NativeCallbackTemplate(callback_delegate ^ callback)                                                                                        \
            : delfunc(callback)                                                                                                                     \
        {                                                                                                                                           \
        }                                                                                                                                           \
        ~NativeCallbackTemplate()                                                                                                                   \
        {                                                                                                                                           \
            this->!NativeCallbackTemplate();                                                                                                        \
            GC::SuppressFinalize(this);                                                                                                             \
        }                                                                                                                                           \
        !NativeCallbackTemplate()                                                                                                                   \
        {                                                                                                                                           \
            if (gch.IsAllocated)                                                                                                                    \
                gch.Free();                                                                                                                         \
        }                                                                                                                                           \
                                                                                                                                                    \
    private:                                                                                                                                        \
        ret NATIVECALLBACK NativeCallbackFunc(__VA_ARGS__);                                                                                         \
                                                                                                                                                    \
    public:                                                                                                                                         \
        static __Pair Create(callback_delegate ^ callback)                                                                                          \
        {                                                                                                                                           \
            auto instance = gcnew NativeCallbackTemplate(callback);                                                                                 \
            delCallback ^ del = gcnew delCallback(instance, &NativeCallbackFunc);                                                                   \
            instance->gch = GCHandle::Alloc(del);                                                                                                   \
            auto p = static_cast<pCallback>((void*)Marshal::GetFunctionPointerForDelegate(del));                                                    \
            return __Pair(p, instance);                                                                                                             \
        }                                                                                                                                           \
    };                                                                                                                                              \
                                                                                                                                                    \
    ref class class_name : public NativeCallbackTemplate<do_hash(#class_name) ^ do_hash(#ret), do_hash(#callback_delegate) ^ do_hash(#__VA_ARGS__)> \
    {                                                                                                                                               \
    };                                                                                                                                              \
                                                                                                                                                    \
    ret NativeCallbackTemplate<do_hash(#class_name) ^ do_hash(#ret), do_hash(#callback_delegate) ^ do_hash(#__VA_ARGS__)>::NativeCallbackFunc(__VA_ARGS__)