#include "cli/CommandLine.h"

#include "parser/TokenVerifier.h"

#include <iostream>
#include <string>
#include <exception>

namespace GTFW
{
	// TryParseInScope
	//   Try parse everything in the current scope for specal scope token,
	//   such as quote(", '), braces((, ), [, ], <, >) etcs. 
	std::string& TryParseInScope(const std::string& argsLine, size_t index, char scopeToken)
	{
		std::string Records = "";

		for (; index < argsLine.length(); ++index)
		{
			char c = argsLine[index];
			Records += c;

			if (c == scopeToken)
			{
				return Records;
			}
		}

		throw std::exception("End of qoute is unreachable.");
	}

	CLI::KVInfo* GenerateKVWithAndClear(std::string& Key, std::vector<std::string>& Val)
	{
		CLI::KVInfo* info = new CLI::KVInfo();

		info->m_Key = std::move(Key);
		info->m_Val = std::move(Val);
	}
	
	void EmitArgumentParseException(size_t index, char c)
	{
		std::string exceptionMessage = "";

		exceptionMessage += "unknown charactor ";
		exceptionMessage += c;
		exceptionMessage += " has been found at index=";
		exceptionMessage += index;

		throw std::exception(exceptionMessage.c_str());
	}

	void GenerateKVInformationsFrom(const std::string& argsLine, std::vector<CLI::KVInfo*>& KVArgs)
	{
		std::string				 Key = "";
		std::string			     Val = "";
		std::vector<std::string> Vals;
		bool					 isOnKeyScope = false;
		bool					 isOnValScope = false;

		for (size_t i = 0; i < argsLine.length(); ++i)
		{
			char c = argsLine[i];

			if (Parser::tvIsDoubleQuote(c) || Parser::tvIsSingleQuote(c))
			{
				if (isOnValScope)
				{
					Val += TryParseInScope(argsLine, i, c);
					continue;
				}

				EmitArgumentParseException(i, c);
			}

			if (Parser::tvIsDash(c))
			{
				if (isOnKeyScope)
				{
					Key += c;
					continue;
				}

				if (isOnValScope)
				{
					Val += c;
					continue;
				}

				isOnKeyScope = true;
				continue;
			}

			if (Parser::tvIsEqualSym(c))
			{
				if (isOnKeyScope)
				{
					std::swap(isOnKeyScope, isOnValScope);
				}
			}

			if (Parser::tvIsComma(c))
			{
				if (isOnValScope)
				{
					if (!Val.empty())
					{
						Vals.emplace_back(std::move(Val));
					}

					continue;
				}

				EmitArgumentParseException(i, c);
			}

			if (Parser::tvIsSpace(c))
			{
				if (!Key.empty())
				{
					KVArgs.push_back(GenerateKVWithAndClear(Key, Vals));
				}
			}
		}
	}

	// Generate inlined arguments line from space splited argv
	std::string& TransformArgvIntoInlinedString(char** argv, size_t args)
	{
		std::string Args = "";

		for (unsigned int i = 0; i < args; ++i)
		{
			char* arg = argv[i];
			for (unsigned int j = 0; arg[j] != '\0'; ++j)
			{
				Args += arg[j];
			}
		}

		return Args;
	}

    bool TryParseCommandLine(CLI::CommandLineContext* context, size_t args, char** argv, char** envp)
    {
        std::vector<CLI::KVInfo*> argsInfo;
        std::vector<CLI::KVInfo*> envsInfo;

		// Generating inlined arguments and environments.
		try 
		{
			GenerateKVInformationsFrom(TransformArgvIntoInlinedString(argv, args), argsInfo);
		}
		catch (std::exception e)
		{
			return false;
		}

		context->m_clcArgs = std::move(argsInfo);
		context->m_clcEnvs = std::move(envsInfo);

		return true;
    }

    bool CLI::CreateCommandLineContextWith(CommandLineContext** ppContext, size_t args, char** argv, char** envp)
    {
        *ppContext = new CommandLineContext();
        return TryParseCommandLine(*ppContext, args, argv, envp);
    }

	void CLI::FreeCommandLineContext(CommandLineContext* pContext)
	{
		for (CLI::KVInfo* infoArgs : pContext->m_clcArgs)
		{
			delete infoArgs;
		}

		for (CLI::KVInfo* infoEnvs : pContext->m_clcEnvs)
		{
			delete infoEnvs;
		}

		delete pContext;
	}
}