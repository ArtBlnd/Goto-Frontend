#include "pch.h"

#include "driver/CommandLine.h"
#include "parser/TokenVerifier.h"
#include "parser/Parser.h"

#include <filesystem>

namespace GTFW
{
    // TryParseInScope
    //   Try parse everything in the current scope for specal scope token,
    //   such as quote(", '), braces((, ), [, ], <, >) etcs. 
    std::string TryParseInScope(const std::string& argsLine, size_t& index, char scopeToken)
    {
        std::string Records = "";

        ++index;
        for (; index < argsLine.length(); ++index)
        {
            char c = argsLine[index];

            if (c == scopeToken)
            {
                return Records;
            }

            Records += c;
        }

        throw std::exception("End of qoute is unreachable.");
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

    void SetOptionValue(std::string& Key, std::vector<std::string>& Val, Driver::DriverOption* Option)
    {
        if (Val.empty())
        {
            // Defining just an key should be enabling
            // So replacing it with boolean true/false

            Option->SetValue(true);
            return;
        }

        if (Val.size() == 1)
        {
            std::string& strVal = Val[0];

            if (Parser::tvIsInteger(strVal))
            {
                Option->SetValue(Parser::psStr2IntegerTransform(strVal));
                return;
            }

            if (Parser::tvIsBoolean(strVal))
            {
                Option->SetValue(Parser::psStr2BoolTransform(strVal));
                return;
            }

            // Seems its raw string
            // We are just putting value into Option.
            Option->SetValue(strVal);
        }
    }

    void ParseArgsImpl(const std::string& argsLine, Driver::CommandLineContext* context)
    {
        std::string              Key = "";
        std::string              Val = "";
        std::vector<std::string> Vals;
        bool                     isOnKeyScope = false;
        bool                     isOnValScope = false;

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
                if (isOnKeyScope || isOnValScope)
                {
                    Key += c;
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

                    continue;
                }

                EmitArgumentParseException(i, c);
            }

            if (Parser::tvIsComma(c) || Parser::tvIsSemicolon(c))
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
                if (!Val.empty())
                {
                    Vals.push_back(std::move(Val));
                }

                if (!Key.empty())
                {
                    isOnKeyScope = false;
                    isOnValScope = false;
                    
                    SetOptionValue(Key, Vals, context->m_clcOptionTable.Lookup(Key));
                }

                continue;
            }

            // General Capturing.
            // TODO : Only capures that supported languages.
            if (isOnKeyScope)
            {
                Key += c;
            }
            if (isOnValScope)
            {
                Val += c;
            }
        }
    }

    // Generate inlined arguments line from space splited argv
    std::string TransformArgvIntoInlinedString(const char** argv, size_t args)
    {
        std::string Args = "";

        // We are string index with 2
        // First index if argv is program name it-self and second is target source file name.
        for (unsigned int i = 2; i < args; ++i)
        {
            const char* arg = argv[i];
            for (unsigned int j = 0; arg[j] != '\0'; ++j)
            {
                Args += arg[j];
            }

            Args += " ";
        }

        return Args;
    }

    bool TryParseCommandLine(Driver::CommandLineContext* context, size_t args, const char** argv, const char** envp)
    {
        if (args == 1)
        {
            // There is no source code target found.
            return false;
        }

        // First of argv is should be source file.
        context->m_clcTargetSourceFile = argv[1];

        // Generating inlined arguments and environments.
        try
        {
            std::string InlinedArgs = TransformArgvIntoInlinedString(argv, args);
            if (InlinedArgs.empty())
            {
                return true;
            }

            ParseArgsImpl(InlinedArgs, context);
        }
        catch (std::exception e)
        {
            return false;
        }

        return true;
    }


    // InitCommandLineContext
    // Information:
    //   Create and initlaize CommandLineContext
    // Behavior:
    //   - Create CommandLineContext
    //   - Returns false if some kind of failure.
    //       1. If failed to create CommandLineContext
    //       2. If failed to find target source file
    //       3. If failed to find end of argv line.
    bool Driver::InitCommandLineContext(CommandLineContext** ppContext, size_t args, const char** argv, const char** envp)
    {
        CommandLineContext* CLIContext = new CommandLineContext();

        if (!TryParseCommandLine(CLIContext, args, argv, envp))
        {
            FreeCommandLineContext(CLIContext);
            return false;
        }

        *ppContext = CLIContext;
        return true;
    }


    void Driver::FreeCommandLineContext(CommandLineContext* pContext)
    {
        if (pContext == nullptr)
        {
            return;
        }

        delete pContext;
    }
}