// Copyright 2021-2021 by Martin Moene
//
// https://github.com/martinmoene/string-non-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#ifndef TEST_STRING_NON_LITE_H_INCLUDED
#define TEST_STRING_NON_LITE_H_INCLUDED

#include string_STRING_HEADER

// Compiler warning suppression for usage of lest:

#ifdef __clang__
# pragma clang diagnostic ignored "-Wstring-conversion"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-template"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-member-function"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
# pragma GCC   diagnostic ignored "-Wunused-function"
#endif

// Limit C++ Core Guidelines checking to GSL Lite:

#if string_COMPILER_MSVC_VER >= 1910
# include <CppCoreCheck/Warnings.h>
# pragma warning(disable: ALL_CPPCORECHECK_WARNINGS)
#endif

#include <iostream>

// String to use with iterators:

inline std::string & text()
{
    static std::string text_("abc123mno123xyz");
    return text_;
}

inline std::string::const_iterator text_end()
{
    return text().end();
}

#if string_CONFIG_SELECT_STRING_VIEW == string_CONFIG_SELECT_STRING_VIEW_STD

inline std::string_view text_view()
{
    return { text().c_str(), text().length() };
}

inline std::string_view::const_iterator text_view_end()
{
    return text_view().end();
}

#else

inline nonstd::string::string_view text_view()
{
    return nonstd::string::string_view( text().c_str(), text().length() );
}

inline nonstd::string::string_view::const_iterator text_view_end()
{
    return text_view().end();
}

#endif // string_HAVE_STD_STRING_VIEW

// Provide CsString with C++17 and later:

#define string_HAS_CSSTRING string_CPP17_140

#if string_HAS_CSSTRING

#include "cs_string/cs_string.h"
#include "cs_string/cs_string_view.h"

// String to use with iterators:

inline CsString::CsString & cstext()
{
    static CsString::CsString text_("αβγ123χψω");
    return text_;
}

inline CsString::CsString::const_iterator cstext_end()
{
    return cstext().end();
}

inline CsString::CsStringView::const_iterator cstext_view_end()
{
    return CsString::CsStringView( cstext() ).end();
}

namespace nonstd {

// use oparator<< instead of to_string() overload;
// see  http://stackoverflow.com/a/10651752/437272

template< typename CharT, typename AllocT >
inline std::ostream & operator<<( std::ostream & os, CsString::CsBasicString<CharT,AllocT> const & s )
{
    return os << s.constData();
}

template< typename CharT, typename AllocT >
inline std::ostream & operator<<( std::ostream & os, typename CsString::CsBasicString<CharT,AllocT>::CsStringIterator pos )
{
    return os << "[CsStringIterator]";

    if ( pos == cstext_end() )
        return os << "[end]";

    os << "\"";
    for ( ; pos != cstext_end(); ++pos )
    {
        os << (*pos).unicode();
    }
    return os << "\"";
}

} // namespace nonstd

#endif // string_HAS_CSSTRING

namespace nonstd {

inline std::ostream & operator<<( std::ostream & os, std::string::const_iterator pos )
{
    // return os << "[it]";

    if ( pos == text_end() )
        return os << "[end]";

    os << "\"";
    for ( ; pos != text_end(); ++pos )
    {
        os << *pos;
    }
    return os << "\"";
}

namespace string {

#if string_CONFIG_SELECT_STRING_VIEW == string_CONFIG_SELECT_STRING_VIEW_INTERNAL

inline std::ostream & operator<<( std::ostream & os, string_view sv )
{
    return os << to_string(sv);
}
#else
// using nonstd::operator<<;
#endif

// inline std::ostream & operator<<( std::ostream & os, string_view::const_iterator pos )
// {
//     // return os << "[it-sv]";

//     if ( pos == text_view_end() )
//         return os << "[end-sv]";

//     os << "\"";
//     for ( ; pos != text_view_end(); ++pos )
//     {
//         os << *pos;
//     }
//     return os << "\"";
// }

inline bool operator==( string_view const & a, std::string const & b )
{
    return std::string(a.begin(), a.end()) == b;
}

inline bool operator==( std::vector<string_view> const & a, std::vector<std::string> const & b )
{
    return std::equal( a.begin(), a.end(), b.begin() );
}

inline bool operator==( std::vector<std::string> const & a, std::vector<string_view> const & b )
{
    return b == a;
}

} // namespace string

#if _MSC_VER && string_CONFIG_SELECT_STRING_VIEW == string_CONFIG_SELECT_STRING_VIEW_STD

inline std::ostream & operator<<( std::ostream & os, std::string_view::const_iterator pos )
{
    // return os << "[it-sv]";

    if ( pos == text_view_end() )
        return os << "[end-sv]";

    os << "\"";
    for ( ; pos != text_view_end(); ++pos )
    {
        os << *pos;
    }
    return os << "\"";
}
#endif

template< typename T >
inline std::ostream & operator<<( std::ostream & os, std::vector<T> vec )
{
    os << "[vector:";

    for ( typename std::vector<T>::const_iterator pos = vec.begin(); pos != vec.end(); ++pos )
    {
        os << " '" << *pos << "'";
    }
    return os << "]";
}

template< typename T >
inline bool operator==( std::vector<T> const & a, std::vector<T> const & b )
{
    return std::equal( a.begin(), a.end(), b.begin() );
}

// inline bool operator==( std::vector<std::string> const & a, std::vector<std::string> const & b )
// {
//     return false;
// }

} // namespace nonstd

namespace lest {

using ::nonstd::operator<<;
// using ::nonstd::operator==;

#if string_CONFIG_SELECT_STRING_VIEW == string_CONFIG_SELECT_STRING_VIEW_INTERNAL
using ::nonstd::string::operator<<;
#endif

using ::nonstd::string::operator==;

} // namespace lest

namespace std {

using ::nonstd::operator<<;
// using ::nonstd::string::operator<<;

}

#include "lest_cpp03.hpp"

extern lest::tests & specification();

#define CASE( name ) lest_CASE( specification(), name )

#endif // TEST_STRING_NON_LITE_H_INCLUDED

// end of file
