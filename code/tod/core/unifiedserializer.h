#ifndef TOD_CORE_SERIALIZER_UNIFIEDSERIALIZER_H
#define TOD_CORE_SERIALIZER_UNIFIEDSERIALIZER_H
/**
    @ingroup TodCoreSerializer
    @class tod::UnifiedSerializer
    @brief
*/

#include <map>
#include "tod/core/define.h"
#include "tod/core/string.h"
#include "tod/core/serializer.h"

namespace tod
{
    class Object;
    class UnifiedSerializer : public Serializer
    {
    public:
        override bool serialize(const Uri& uri, Object* object);
        override Object* deserialize(Node* parent, const Uri& uri, const char_t* name);

    private:
        typedef std::map<String, Serializer*> Serializers;

    private:
        Serializers serializers_;

    };
}

#endif // TOD_CORE_SERIALIZER_UNIFIEDSERIALIZER_H
