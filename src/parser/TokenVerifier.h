#ifndef __GFWK_C_FRONTEND_PARSER_TOKEN_VERIFIER_H__
#define __GFWK_C_FRONTEND_PARSER_TOKEN_VERIFIER_H__

namespace GTFW
{
	namespace Parser
	{
		// Token Verifier
		// Type: '\"' (DOUBLE_QUOTE)
		inline bool tvIsDoubleQuote(const char c)
		{
			return c == '\"';
		}

		// Token Verifier
		// Type: '\'' (SINGLE_QUOTE)
		inline bool tvIsSingleQuote(const char c)
		{
			return c == '\'';
		}

		// Token Verifier
		// Type : '-' (DASH)
		inline bool tvIsDash(const char c)
		{
			return c == '-';
		}

		// Token Verifier
		// Type : ';' (SEMI_COLON)
		inline bool tvIsSemicolon(const char c)
		{
			return c == ';';
		}

		// Token Verifier
		// Type : ',' (COMMA)
		inline bool tvIsComma(const char c)
		{
			return c == ',';
		}

		// Token Verifier
		// Type : '.' (DOT)
		inline bool tvIsDot(const char c)
		{
			return c == '.';
		}

		// Token Verifier
		// Type : ' ' (SPACE)
		inline bool tvIsSpace(const char c)
		{
			return c == ' ';
		}

		// Token Verifier
		// Type : '=' (Equal)
		inline bool tvIsEqualSym(const char c)
		{
			return c == '=';
		}
	}
}


#endif