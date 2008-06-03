#include "tod/core/method.h"

#include "boost/tokenizer.hpp"
#include "tod/core/node.h"

using namespace tod;

//-----------------------------------------------------------------------------
Method::Method()
{
    // empty
}


//-----------------------------------------------------------------------------
Method::~Method()
{
    // empty
}


//-----------------------------------------------------------------------------
void Method::setPrototype(const char_t* proto)
{
    prototype_ = proto;

    typedef boost::tokenizer<
        boost::char_separator<char_t>,
        String::const_iterator, String> Tokenizer;
    Tokenizer tok(prototype_);
    Tokenizer::iterator i = tok.begin();
    String out_arg = *i;
    ++i; ++i;
    name_ = *i;
    ++i; ++i;
    String in_arg = *i;

    build_paramter(out_arg, parameter_.out());
    build_paramter(in_arg, parameter_.in());
}


//-----------------------------------------------------------------------------
const String& Method::getPrototype() const
{
    return prototype_;
}


//-----------------------------------------------------------------------------
void Method::build_paramter(const String& s, Variables* v)
{
    for (size_t i = 0; i < s.size(); ++i)
    {
        switch (s[i])
        {
        case 'v':
            continue;
        case 'b':
            v->add<bool>(false);
            break;
        case 'i':
            v->add<int>(0);
            break;
        case 'L':
            v->add<__int64>(0);
            break;
        case 'f':
            v->add<float>(0);
            break;
        case 'd':
            v->add<double>(0);
            break;
        case 's':
            v->add<String>(STRING(""));
            break;
        case 'o':
            v->add<Node*>(0);
            break;
        case 'l':
            v->setForceList(true);
            break;
        }
    }
}
