#ifndef SDeviceSignature_HPP
#define SDeviceSignature_HPP

#include <vector>
#include <functional>

namespace boo
{

class CDeviceToken;
class CDeviceBase;

struct SDeviceSignature
{
    typedef std::vector<const SDeviceSignature*> TDeviceSignatureSet;
    typedef std::function<CDeviceBase*(CDeviceToken*)> TFactoryLambda;
    const char* m_name;
    unsigned m_vid, m_pid;
    bool m_lowLevel;
    TFactoryLambda m_factory;
    SDeviceSignature() : m_name(NULL) {} /* Sentinel constructor */
    SDeviceSignature(const char* name, unsigned vid, unsigned pid, bool lowLevel, TFactoryLambda&& factory)
        : m_name(name), m_vid(vid), m_pid(pid), m_lowLevel(lowLevel), m_factory(factory) {}
    static bool DeviceMatchToken(const CDeviceToken& token, const TDeviceSignatureSet& sigSet);
    static CDeviceBase* DeviceNew(CDeviceToken& token);
};

#define DEVICE_SIG(name, vid, pid, lowLevel) \
    SDeviceSignature(#name, vid, pid, lowLevel, [](CDeviceToken* tok) -> CDeviceBase* {return new name(tok);})
#define DEVICE_SIG_SENTINEL() SDeviceSignature()

extern const SDeviceSignature BOO_DEVICE_SIGS[];

}

#endif // SDeviceSignature_HPP

