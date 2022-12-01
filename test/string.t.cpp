// Copyright 2021-2021 Martin Moene
//
// https://github.com/martinmoene/string-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "string-main.t.hpp"

#ifdef _WIN32
# define string_strdup  _strdup
#else
# define string_strdup   strdup
#endif

namespace {

using namespace nonstd::string;

struct scoped_str
{
    char * p;

    scoped_str( char const * s ) : p ( string_strdup(s) ) {}

    ~scoped_str() { delete p; }

    operator char const *() { return p; }

    char * get() { return p; }
};

inline char const * lstr() { return "a b c d e f g h i j k l m n o p q r s t u v w x y z"; }
inline char const * ustr() { return "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"; }

struct stringy : std::string
{
    stringy( char const * text )
        : std::string( text ) {}

    // std::string::iterator begin() { return }
};

// Tests:

CASE( "string: Setting Windows console to print utf8 characters" "[unicode][windows]" )
{
#if defined(_WIN32) && _WIN32
    // enable display of utf8, https://stackoverflow.com/a/19071749/437272
    EXPECT( SetConsoleOutputCP(65001) != 0 );
#else
    EXPECT( !!"string: skipping (non-Windows)" );
#endif
}

// Observers:

// is_empty():

CASE( "is_empty: true if string is empty - char *" )
{
    EXPECT(     is_empty("") );
    EXPECT_NOT( is_empty("a") );
}

CASE( "is_empty: true if string is empty - string" )
{
    EXPECT(     is_empty(std::string()) );
    EXPECT_NOT( is_empty(std::string("x")) );
}

// contains():

CASE( "contains: true if string contains sub string - string-char" )
{
    EXPECT(     contains(std::string("abc123mno123xyz"), '1') );
    EXPECT_NOT( contains(std::string("abc123mno123xyz"), '7') );
}

CASE( "contains: true if string contains sub string - string-char*" )
{
    EXPECT(     contains(std::string("abc123mno123xyz"), "123") );
    EXPECT_NOT( contains(std::string("abc123mno123xyz"), "789") );
}

CASE( "contains: true if string contains sub string - string-string" )
{
    EXPECT(     contains(std::string("abc123mno123xyz"), std::string("123")) );
    EXPECT_NOT( contains(std::string("abc123mno123xyz"), std::string("789")) );
}

CASE( "contains: true if string contains sub string - string-string_view" )
{
    EXPECT(     contains(std::string("abc123mno123xyz"), string_view("123")) );
    EXPECT_NOT( contains(std::string("abc123mno123xyz"), string_view("789")) );
}

CASE( "contains: true if string contains sub string - string_view-string_view" )
{
    EXPECT(     contains(string_view("abc123mno123xyz"), string_view("123")) );
    EXPECT_NOT( contains(string_view("abc123mno123xyz"), string_view("789")) );
}

CASE( "contains: true if string contains regular expression - string-std::regexp" )
{
#if string_HAVE_REGEX
    EXPECT(     contains(std::string("abc123mno123xyz"), std::regex("[0-9]+")) );
    EXPECT_NOT( contains(std::string("abc123mno123xyz"), std::regex("[4-9]+")) );
#else
    EXPECT( !!"contains_re is not available (pre C++11)." );
#endif
}

CASE( "contains_re: true if string contains regular expression - string-char*" )
{
#if string_HAVE_REGEX
    EXPECT(     contains_re(std::string("abc123mno123xyz"), "[0-9]+") );
    EXPECT_NOT( contains_re(std::string("abc123mno123xyz"), "[4-9]+") );
#else
    EXPECT( !!"contains_re is not available (pre C++11)." );
#endif
}

CASE( "contains_re: true if string contains regular expression - string-string" )
{
#if string_HAVE_REGEX
    EXPECT(     contains_re(std::string("abc123mno123xyz"), std::string("[0-9]+")) );
    EXPECT_NOT( contains_re(std::string("abc123mno123xyz"), std::string("[4-9]+")) );
#else
    EXPECT( !!"contains_re is not available (pre C++11)." );
#endif
}

// ends_with():

CASE( "starts_with: true if string starts with sub string - string-char" )
{
    EXPECT(     starts_with(std::string("abc123mno123xyz"), 'a') );
    EXPECT_NOT( starts_with(std::string("abc123mno123xyz"), 'b') );
}

CASE( "starts_with: true if string starts with sub string - string-char*" )
{
    EXPECT(     starts_with(std::string("abc123mno123xyz"), "a") );
    EXPECT_NOT( starts_with(std::string("abc123mno123xyz"), "b") );
}

CASE( "starts_with: true if string starts with sub string - string-string" )
{
    EXPECT(     starts_with(std::string("abc123mno123xyz"), std::string("a")) );
    EXPECT_NOT( starts_with(std::string("abc123mno123xyz"), std::string("b")) );
}

CASE( "starts_with: true if string starts with sub string - string-string_view" )
{
    EXPECT(     starts_with(std::string("abc123mno123xyz"), string_view("a")) );
    EXPECT_NOT( starts_with(std::string("abc123mno123xyz"), string_view("b")) );
}

CASE( "starts_with: true if string starts with sub string - string_view-string_view" )
{
    EXPECT(     starts_with(string_view("abc123mno123xyz"), string_view("a")) );
    EXPECT_NOT( starts_with(string_view("abc123mno123xyz"), string_view("b")) );
}

// ends_with():

CASE( "ends_with: true if string ends with sub string - string-char" )
{
    EXPECT(     ends_with(std::string("abc123mno123xyz"), 'z') );
    EXPECT_NOT( ends_with(std::string("abc123mno123xyz"), 'y') );
}

CASE( "ends_with: true if string ends with sub string - string-char*" )
{
    EXPECT(     ends_with(std::string("abc123mno123xyz"), "z") );
    EXPECT_NOT( ends_with(std::string("abc123mno123xyz"), "y") );
}

CASE( "ends_with: true if string ends with sub string - string-string" )
{
    EXPECT(     ends_with(std::string("abc123mno123xyz"), std::string("z")) );
    EXPECT_NOT( ends_with(std::string("abc123mno123xyz"), std::string("y")) );
}

CASE( "ends_with: true if string ends with sub string - string-string_view" )
{
    EXPECT(     ends_with(std::string("abc123mno123xyz"), string_view("z")) );
    EXPECT_NOT( ends_with(std::string("abc123mno123xyz"), string_view("y")) );
}

CASE( "ends_with: true if string ends with sub string - string_view-string_view" )
{
    EXPECT(     ends_with(string_view("abc123mno123xyz"), string_view("z")) );
    EXPECT_NOT( ends_with(string_view("abc123mno123xyz"), string_view("y")) );
}

// find_last():

CASE( "find_first: iterator to sub string in string - string-char*" )
{
    // text((): "abc123mno123xyz"

    EXPECT( text_end() != find_first(text(), "123") );
    EXPECT( text_end() == find_first(text(), "789") );
}

CASE( "find_first: iterator to sub string in string - string-string" )
{
    // text((): "abc123mno123xyz"

    EXPECT( text_end() != find_first(text(), std::string("123")) );
    EXPECT( text_end() == find_first(text(), std::string("789")) );
}

CASE( "find_first: iterator to sub string in string - string-string_view" )
{
    // text((): "abc123mno123xyz"

    EXPECT( text_end() != find_first(text(), string_view("123")) );
    EXPECT( text_end() == find_first(text(), string_view("789")) );
}

CASE( "find_first: iterator to sub string in string_view - string_view-string_view" )
{
    // text((): "abc123mno123xyz"

    EXPECT( text_view_end() != find_first(text_view(), string_view("123")) );
    EXPECT( text_view_end() == find_first(text_view(), string_view("789")) );
}

// find_last():

CASE( "find_last: iterator to sub string in string - string-char*" )
{
    // text((): "abc123mno123xyz"

    EXPECT( text_end() != find_last(text(), "123") );
    EXPECT( text_end() == find_last(text(), "789") );
}

CASE( "find_last: iterator to sub string in string - string-string" )
{
    // text((): "abc123mno123xyz"

    EXPECT( text_end() != find_last(text(), std::string("123")) );
    EXPECT( text_end() == find_last(text(), std::string("789")) );
}

CASE( "find_last: iterator to sub string in string - string-string_view" )
{
    // text((): "abc123mno123xyz"

    EXPECT( text_end() != find_last(text(), string_view("123")) );
    EXPECT( text_end() == find_last(text(), string_view("789")) );
}

CASE( "find_last: iterator to sub string in string_view - string_view-string_view" )
{
    // text((): "abc123mno123xyz"

    EXPECT( text_view_end() != find_last(text_view(), string_view("123")) );
    EXPECT( text_view_end() == find_last(text_view(), string_view("789")) );
}

// Modifiers:

// clear():

CASE( "clear: Makes string empty - char *" )
{
    scoped_str s( lstr() );

    clear( s.get() );

    EXPECT( *s == '\0' );
}

CASE( "clear: Makes string empty - string" )
{
    std::string s(lstr());

    clear( s );

    EXPECT( s  == "" );
    EXPECT( s.length() == 0u );
}

// replace_all():

CASE( "replace_all: Change all occurrences of sub string - string-char*" )
{
    std::string result( "abc123mno123xyz" );

    (void) replace_all( result, "123", "789");

    EXPECT( result == std::string("abc789mno789xyz") );
}

CASE( "replace_all: Change all occurrences of sub string - string-string" )
{
    std::string result( "abc123mno123xyz" );

    (void) replace_all( result, std::string("123"), std::string("789"));

    EXPECT( result == std::string("abc789mno789xyz") );
}

CASE( "replace_all: Change all occurrences of sub string - string-string_view" )
{
    std::string result( "abc123mno123xyz" );

    (void) replace_all( result, std::string("123"), string_view("789"));

    EXPECT( result == std::string("abc789mno789xyz") );
}

// replaced_all():

CASE( "replaced_all: Return new string with all occurrences of sub string changed - char*-char*" )
{
    EXPECT( replaced_all( "abc123mno123xyz", "123", "789") == std::string("abc789mno789xyz") );
}

CASE( "replaced_all: Return new string with all occurrences of sub string changed - string-string" )
{
    EXPECT( replaced_all( std::string("abc123mno123xyz"), std::string("123"), std::string("789") ) == std::string("abc789mno789xyz") );
}

CASE( "replaced_all: Return new string with all occurrences of sub string changed - string-string_view" )
{
    EXPECT( replaced_all( std::string("abc123mno123xyz"), "123", "789") == std::string("abc789mno789xyz") );
}

CASE( "replaced_all: Return new string with all occurrences of sub string changed - string_view-string_view" " [TODO]" )
{
// TODO : implement detail::replace_all(it...)
    // EXPECT( replaced_all( string_view("abc123mno123xyz"), "123", "789") == std::string("abc789mno789xyz") );
}

// replace_first():

CASE( "replace_first: Change the first occurrence of sub string - char*-char*" "[TODO]" )
{
// TODO : implement detail::replace_first(...)
    // char result[] = "abc123mno123xyz";

    // (void) replace_first( result, "123", "789");

    // EXPECT( result == std::string("abc789mno123xyz") );
}

CASE( "replace_first: Change the first occurrence of sub string - string-char*" )
{
    std::string result( "abc123mno123xyz" );

    (void) replace_first( result, "123", "789");

    EXPECT( result == std::string("abc789mno123xyz") );
}

CASE( "replace_first: Change the first occurrence of sub string - string-string" )
{
    std::string result( "abc123mno123xyz" );

    (void) replace_first( result, std::string("123"), std::string("789"));

    EXPECT( result == std::string("abc789mno123xyz") );
}

CASE( "replace_first: Change the first occurrence of sub string - string-string_view" )
{
    std::string result( "abc123mno123xyz" );

    (void) replace_first( result, string_view("123"), string_view("789"));

    EXPECT( result == std::string("abc789mno123xyz") );
}

CASE( "replace_first: Change the first occurrence of sub string - string_view-string_view" )
{
    std::string result( "abc123mno123xyz" );

    (void) replace_first( result, string_view("123"), string_view("789"));

    EXPECT( result == std::string("abc789mno123xyz") );
}

// replaced_first():

CASE( "replaced_first: Return new string with first occurrence of sub string changed - char*-char*" )
{
    EXPECT( replaced_first( "abc123mno123xyz", "123", "789") == std::string("abc789mno123xyz") );
}

CASE( "replaced_first: Return new string with first occurrence of sub string changed - string-string" )
{
    EXPECT( replaced_first( std::string("abc123mno123xyz"), std::string("123"), std::string("789") ) == std::string("abc789mno123xyz") );
}

CASE( "replaced_first: Return new string with first occurrence of sub string changed - string-string_view" )
{
    EXPECT( replaced_first( std::string("abc123mno123xyz"), "123", "789") == std::string("abc789mno123xyz") );
}

CASE( "replaced_first: Return new string with first occurrence of sub string changed - string_view-string_view" " [TODO]" )
{
// TODO : implement detail::replaced_first(it...)
    // EXPECT( replaced_first( string_view("abc123mno123xyz"), "123", "789") == std::string("abc789mno789xyz") );
}

// replace_last():

CASE( "replace_last: Change the first occurrence of sub string - char*-char*" "[TODO]" )
{
// TODO : implement detail::replace_last(...)
    // char result[] = "abc123mno123xyz";

    // (void) replace_last( result, "123", "789");

    // EXPECT( result == std::string("abc789mno123xyz") );
}

CASE( "replace_last: Change the last occurrence of sub string - string-char*" )
{
    std::string result( "abc123mno123xyz" );

    (void) replace_last( result, "123", "789");

    EXPECT( result == std::string("abc123mno789xyz") );
}

CASE( "replace_last: Change the last occurrence of sub string - string-string" )
{
    std::string result( "abc123mno123xyz" );

    (void) replace_last( result, std::string("123"), std::string("789"));

    EXPECT( result == std::string("abc123mno789xyz") );
}

CASE( "replace_last: Change the last occurrence of sub string - string-string_view" )
{
    std::string result( "abc123mno123xyz" );

    (void) replace_last( result, string_view("123"), std::string("789"));

    EXPECT( result == std::string("abc123mno789xyz") );
}

CASE( "replace_last: Change the last occurrence of sub string - string_view-string_view" )
{
    // TODO : replace_last
}

// replaced_last():

CASE( "replaced_last: Return new string with last occurrence of sub string changed - char*-char*" )
{
    EXPECT( replaced_last( "abc123mno123xyz", "123", "789") == std::string("abc123mno789xyz") );
}

CASE( "replaced_last: Return new string with last occurrence of sub string changed - string-string" )
{
    EXPECT( replaced_last( std::string("abc123mno123xyz"), std::string("123"), std::string("789") ) == std::string("abc123mno789xyz") );
}

CASE( "replaced_last: Return new string with last occurrence of sub string changed - string-string_view" )
{
    EXPECT( replaced_last( std::string("abc123mno123xyz"), "123", "789") == std::string("abc123mno789xyz") );
}

CASE( "replaced_last: Return new string with last occurrence of sub string changed - string_view-string_view" " [TODO]" )
{
// TODO : implement detail::replaced_last(it...)
    // EXPECT( replaced_last( string_view("abc123mno123xyz"), "123", "789") == std::string("abc789mno789xyz") );
}

// to_lowercase(), to_uppercase:

CASE( "to_lowercase: Makes string lowercase - char *" )
{
    scoped_str s( ustr() );

    to_lowercase( s.get() );

    EXPECT( std::strcmp(s, lstr()) == 0 );
}

CASE( "to_uppercase: Makes string uppercase - char *" )
{
    scoped_str s( lstr() );

    to_uppercase( s.get() );

    EXPECT( std::strcmp(s, ustr()) == 0 );
}

CASE( "to_lowercase: Makes string lowercase - string" )
{
    std::string ls( lstr() );
    std::string  s( ustr() );

    to_lowercase( s );

    EXPECT( s == ls );
}

CASE( "to_uppercase: Makes string uppercase - string" )
{
    std::string us( ustr() );
    std::string  s( lstr() );

    to_uppercase( s );

    EXPECT( s == us );
}

// as_lowercase(), as_uppercase:

CASE( "as_lowercase: Return new string in lowercase - string" )
{
    std::string ls( lstr() );
    std::string us( ustr() );

    EXPECT( as_lowercase(us) == ls );
}

CASE( "as_uppercase: Return new string in uppercase - string" )
{
    std::string ls( lstr() );
    std::string us( ustr() );

    EXPECT( as_uppercase(ls) == us );
}

// append():

CASE( "append: Append a string to a string in-place - char*-char* - Note: be careful!" )
{
    char pa[] = "abc\x00xxx";
    char pb[] = "xyz";

    EXPECT( std::string(append(pa, pb)) == std::string("abcxyz") );
}

CASE( "append: Append a string to a string in-place - string-char*" )
{
    std::string text("abc");

    EXPECT( append(text, "xyz") == std::string("abcxyz") );
}

CASE( "append: Append a string to a string in-place - string-string" )
{
    std::string text("abc");

    EXPECT( append(text, std::string("xyz")) == std::string("abcxyz") );
}

CASE( "append: Append a string to a string in-place - string-string_view" )
{
    std::string text("abc");

    EXPECT( append(text, string_view("xyz")) == std::string("abcxyz") );
}

// appended():

CASE( "appended: Return new string with second string appended to first string - string-char*" )
{
    EXPECT( appended(std::string("abc"), "xyz") == std::string("abcxyz") );
}

CASE( "appended: Return new string with second string appended to first string - string-string" )
{
    EXPECT( appended(std::string("abc"), std::string("xyz")) == std::string("abcxyz") );
}

CASE( "appended: Return new string with second string appended to first string - string-string_view" )
{
    EXPECT( appended(std::string("abc"), string_view("xyz")) == std::string("abcxyz") );
}

CASE( "trim_left: Remove characters in set from left of string [\" \\t\\n\"] - in-place - C-string" )
{
    char s1[] = " \t\nabc";
    char s2[] = " #$%&abc";

    EXPECT( trim_left(s1) == std::string("abc") );
    EXPECT( trim_left(s2, " #$%&") == std::string("abc") );
}

CASE( "trim_left: Remove characters in set from left of string [\" \\t\\n\"] - in-place - std::string" )
{
    std::string s1(" \t\nabc");
    std::string s2(" #$%&abc");

    EXPECT( trim_left(s1) == std::string("abc") );
    EXPECT( trim_left(s2, " #$%&") == std::string("abc") );
}

// TODO trim_left: other - implement

CASE( "trim_left: Remove characters in set from left of string [\" \\t\\n\"] - in-place - other" "[.TODO]")
{
    stringy s1(" \t\nabc");
    stringy s2(" #$%&abc");

    EXPECT( trim_left(s1) == std::string("abc") );
    EXPECT( trim_left(s2, " #$%&") == std::string("abc") );
}

CASE( "trim_right: Remove characters in set from right of string [\" \\t\\n\"] - in-place - char*" )
{
    char s1[] = "abc \t\n";
    char s2[] = "abc #$%&";

    EXPECT( trim_right(s1) == std::string("abc") );
    EXPECT( trim_right(s2, " #$%&") == std::string("abc") );
}

CASE( "trim_right: Remove characters in set from right of string [\" \\t\\n\"] - in-place - string" )
{
    std::string s1("abc \t\n");
    std::string s2("abc #$%&");

    EXPECT( trim_right(s1) == std::string("abc") );
    EXPECT( trim_right(s2, " #$%&") == std::string("abc") );
}

// TODO trim_right: other - implement

CASE( "trim_right: Remove characters in set from left of string [\" \\t\\n\"] - in-place - other" "[.TODO]")
{
    stringy s1("abc \t\n");
    stringy s2("abc #$%&");

    EXPECT( trim_right(s1) == std::string("abc") );
    EXPECT( trim_right(s2, " #$%&") == std::string("abc") );
}

CASE( "trim: Remove characters in set from left and right of string [\" \\t\\n\"] - in-place - char*" )
{
    char s1[] = " \t\nabc \t\n";
    char s2[] = " #$%&abc #$%&";

    EXPECT( trim(s1) == std::string("abc") );
    EXPECT( trim(s2, " #$%&") == std::string("abc") );
}

CASE( "trim: Remove characters in set from left and right of string [\" \\t\\n\"] - in-place - string" )
{
    std::string s1(" \t\nabc \t\n");
    std::string s2(" #$%&abc #$%&");

    EXPECT( trim(s1) == std::string("abc") );
    EXPECT( trim(s2, " #$%&") == std::string("abc") );
}

// TODO trim: other

CASE( "trim: Remove characters in set from left and right of string [\" \\t\\n\"] - in-place - other" "[.TODO]")
{
    stringy s1(" \t\nabc \t\n");
    stringy s2(" #$%&abc #$%&");

    EXPECT( trim(s1) == std::string("abc") );
    EXPECT( trim(s2, " #$%&") == std::string("abc") );
}

CASE( "trimmed_left: Remove characters in set from left of string [\" \\t\\n\"] - copy - string" )
{
    EXPECT( trimmed_left(std::string(" \t\nabc")) == std::string("abc") );
    EXPECT( trimmed_left(std::string(" #$%&abc"), " #$%&") == std::string("abc") );
}

CASE( "trimmed_left: Remove characters in set from left of string [\" \\t\\n\"] - copy - other" "[.TODO]")
{
    char s1[] = " \t\nabc";
    char s2[] = " #$%&abc";

    EXPECT( trimmed_left(string_view(begin(s1), end(s1))) == std::string("abc") );
    EXPECT( trimmed_left(string_view(begin(s2), end(s2)), " #$%&") == std::string("abc") );
}

CASE( "trimmed_right: Remove characters in set from right of string [\" \\t\\n\"] - copy - string" )
{
    EXPECT( trimmed_right(std::string("abc \t\n")) == std::string("abc") );
    EXPECT( trimmed_right(std::string("abc #$%&"), " #$%&") == std::string("abc") );
}

CASE( "trimmed_right: Remove characters in set from left of string [\" \\t\\n\"] - copy - other" "[.TODO]")
{
    EXPECT( trimmed_right(stringy("abc \t\n")) == std::string("abc") );
    EXPECT( trimmed_right(stringy("abc #$%&"), " #$%&") == std::string("abc") );

    char s1[] = "abc \t\n";
    char s2[] = "abc #$%&";

    EXPECT( trimmed_right(string_view(begin(s1), end(s1))) == std::string("abc") );
    EXPECT( trimmed_right(string_view(begin(s2), end(s2)), " #$%&") == std::string("abc") );
}

CASE( "trimmed: Remove characters in set from left and right of string [\" \\t\\n\"] - copy - string" )
{
    EXPECT( trimmed(std::string(" \t\nabc \t\n")) == std::string("abc") );
    EXPECT( trimmed(std::string(" #$%&abc #$%&"), " #$%&") == std::string("abc") );
}

CASE( "trimmed: Remove characters in set from left and right of string [\" \\t\\n\"] - copy - other" "[.TODO]")
{
    EXPECT( trimmed(stringy(" \t\nabc \t\n")) == std::string("abc") );
    EXPECT( trimmed(stringy(" #$%&abc #$%&"), " #$%&") == std::string("abc") );

    // char s1[] = " \t\nabc";
    // char s2[] = " #$%&abc";

    // EXPECT( trimmed(string_view(begin(s1), end(s1))) == std::string("abc") );
    // EXPECT( trimmed(string_view(begin(s2), end(s2)), " #$%&") == std::string("abc") );
}

// TODO Add tests for string_view:

CASE( "string_view: ..." "[TODO]" )
{
}

// join(), split():

std::vector<std::string>
make_vec_of_strings( char const * p="abc", char const * q="def", char const * r="ghi")
{
    std::vector<std::string> result;
    result.push_back(p);
    result.push_back(q);
    result.push_back(r);
    return result;
}

// join():

CASE( "join: Join strings from collection into a string separated by given separator" )
{
    std::vector<std::string> coll = make_vec_of_strings();

    EXPECT( join( coll, "..") == "abc..def..ghi" );
}

// split():
//
// - literal_delimiter - a single string delimiter
// - any_of_delimiter - any of given characters as delimiter
// - fixed_delimiter - fixed length delimiter
// - limit_delimiter - not implemented
// - regex_delimiter - regular expression delimiter
// - char_delimiter - single-char delimiter
// - above as empty limiters

CASE( "split: Split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings() );

    EXPECT( split("abc..def..ghi", "..") == golden );
    EXPECT( split("abc..def..ghi", literal_delimiter("..")) == golden );
}

CASE( "split: Split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("", "abc", "def") );

    EXPECT( split("-abc-def", "-") == golden );
}

CASE( "split: Split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("abc", "", "def") );

    EXPECT( split("abc--def", "-") == golden );
}

CASE( "split: Split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("abc", "def", "") );

    EXPECT( split("abc-def-", "-") == golden );
}

// TODO split case

CASE( "split: Split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("", "abc", "") );

    EXPECT( split("-abc-", "-") == golden );
}

CASE( "split: Split string into vector of string_view given delimiter - any_of_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings() );

    EXPECT( split("abc+def-ghi", any_of_delimiter("+-")) == golden );
}

CASE( "split: Split string into vector of string_view given delimiter - fixed_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings() );

    EXPECT( split("abcdefghi", fixed_delimiter(3)) == golden );
}

CASE( "split: Split string into vector of string_view given delimiter - limit_delimiter" "[.TODO]" )
{
    std::vector<std::string> golden( make_vec_of_strings() );
}

CASE( "split: Split string into vector of string_view given delimiter - regex_delimiter" )
{
#if string_HAVE_REGEX
    std::vector<std::string> golden( make_vec_of_strings() );

    EXPECT( split("abc+-def-+ghi", regex_delimiter("[+-]+")) == golden );
#else
    EXPECT( !!"regex_delimiter is not available (pre C++11)." );
#endif
}

CASE( "split: Split string into vector of string_view given delimiter - char_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("&", "&", "&") );

    EXPECT( split("abc&def&ghi&jkl", char_delimiter('&')) == golden );
}

CASE( "split: Split string into single characters given empty delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("a", "b", "c") );

    EXPECT( split("abc", "") == golden );
    EXPECT( split("abc", literal_delimiter("")) == golden );
    EXPECT( split("abc", any_of_delimiter("")) == golden );
    EXPECT( split("abc", fixed_delimiter(1)) == golden );

#if string_HAVE_REGEX
    EXPECT( split("abc", regex_delimiter("")) == golden );
#endif
    // Not eligible:
    // EXPECT( split("abc", limit_delimiter("")) == golden );
    // EXPECT( split("abc", char_delimiter('x')) == golden );
}

// TODO Unicode:

// clear():

CASE( "clear: Makes string empty - string " "[unicode]" )
{
#if string_HAS_CSSTRING
    CsString::CsString s( "α β γ δ ε ζ η θ ι κ λ μ ν ξ ο π ρ ς σ τ υ φ χ ψ ω" );

    EXPECT( s  == s );

    clear( s );

    EXPECT( s  == "" );
    EXPECT( s.length() == 0u );
#else
    EXPECT( !!"Unicode via CsString is not available (pre C++17)." );
#endif
}

CASE( "to_lowercase: Makes string lowercase - string " "[unicode][.todo]" )
{
#if string_HAS_CSSTRING
    // el_EU ISO-8859-7x   Greek language locale for Europe (Euro symbol added)
    // el_GR ISO-8859-7    Greek language locale for Greece

    // std::locale::global(std::locale("el_GR"));

    CsString::CsString ls( "α β γ δ ε ζ η θ ι κ λ μ ν ξ ο π ρ σ τ υ φ χ ψ ω" );
    CsString::CsString us( "Α Β Γ Δ Ε Ζ Η Θ Ι Κ Λ Μ Ν Ξ Ο Π Ρ Σ Τ Υ Φ Χ Ψ Ω" );
    CsString::CsString  s( us );

    // to_lowercase( s );

    EXPECT( s == ls );
#else
    EXPECT( !!"Unicode via CsString is not available (pre C++17)." );
#endif
}

CASE( "to_uppercase: Makes string uppercase - string " "[unicode][.todo]" )
{
#if string_HAS_CSSTRING
    // el_EU ISO-8859-7x   Greek language locale for Europe (Euro symbol added)
    // el_GR ISO-8859-7    Greek language locale for Greece

    // std::locale::global(std::locale("el_GR"));

    CsString::CsString ls( "α β γ δ ε ζ η θ ι κ λ μ ν ξ ο π ρ σ τ υ φ χ ψ ω" );
    CsString::CsString us( "Α Β Γ Δ Ε Ζ Η Θ Ι Κ Λ Μ Ν Ξ Ο Π Ρ Σ Τ Υ Φ Χ Ψ Ω" );
    CsString::CsString  s( ls );

    // to_uppercase( s );

    EXPECT( s == us );
#else
    EXPECT( !!"Unicode via CsString is not available (pre C++17)." );
#endif
}

CASE( "tweak header: Reads tweak header if supported " "[tweak]" )
{
#if string_HAVE_TWEAK_HEADER
    EXPECT( string_TWEAK_VALUE == 42 );
#else
    EXPECT( !!"Tweak header is not available (string_HAVE_TWEAK_HEADER: 0)." );
#endif
}
} // anonymous namespace
