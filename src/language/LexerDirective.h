#ifndef __GOTO_FRONTEND_LANGUAGE_LEXER_DIRECTIVE_H__
#define __GOTO_FRONTEND_LANGUAGE_LEXER_DIRECTIVE_H__

namespace
{

enum class DirectiveType
{
    DT_DEFINE  = 0x01,
    DT_ERROR   = 0x02,
    DT_UNDEF   = 0x03,
    DT_ELSE_IF = 0x04,
    DT_IF      = 0x05,
    DT_INCLUDE = 0x06,
    DT_ELSE    = 0x07,
    DT_IFDEF   = 0x08,
    DT_LINE    = 0x09,
    DT_ENDIF   = 0x0A,
    DT_IFNDEF  = 0x0B,
    DT_PRAGMA  = 0x0C
};

class Directive
{
    DirectiveType dtType;

public:

};

} // namespace

#endif