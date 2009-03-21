//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include <UnitTest++.h>
#include <iostream>  // for cout

#include "astyle.h"

//----------------------------------------------------------------------------
// declarations
//----------------------------------------------------------------------------

// AStyleMain callback function declarations
void  STDCALL errorHandler(int errorNumber, char* errorMessage);
char* STDCALL memoryAlloc(unsigned long memoryNeeded);


//----------------------------------------------------------------------------
// AStyle Indent Options
//----------------------------------------------------------------------------


//-------------------------------------------------------------------------
// AStyle Indent Classes
// Additional tests are in the Brackets tests
//-------------------------------------------------------------------------

TEST(IndentClasses)
{
	// test indent class blocks
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"class FooClass\n"
		"{\n"
		"    private:\n"
		"        bool var1;\n"
		"        void func1();\n"
		"    protected:\n"
		"        bool var2;\n"
		"        void func2();\n"
		"};\n"
		"\n"
		"void FooClass::Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        bar();\n"
		"    }\n"
		"    else\n"
		"    {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentClassesShort)
{
	// test indent class blocks short option
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"class FooClass\n"
		"{\n"
		"    private:\n"
		"        bool var1;\n"
		"        void func1();\n"
		"    protected:\n"
		"        bool var2;\n"
		"        void func2();\n"
		"};\n"
		"\n"
		"void FooClass::Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        bar();\n"
		"    }\n"
		"    else\n"
		"    {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "-C";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}


//-------------------------------------------------------------------------
// AStyle Indent Switches
//-------------------------------------------------------------------------

TEST(IndentSwitchesNone)
{
	// test without indent switch blocks
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    switch (foo)\n"
		"    {\n"
		"    case 1:\n"
		"        a += 1;\n"
		"        break;\n"
		"\n"
		"    case 2:\n"
		"    {\n"
		"        a += 2;\n"
		"        break;\n"
		"    }\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches)
{
	// test indent switch blocks
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    switch (foo)\n"
		"    {\n"
		"        case 1:\n"
		"            a += 1;\n"
		"            break;\n"
		"\n"
		"        case 2:\n"
		"        {\n"
		"            a += 2;\n"
		"            break;\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "indent-switches";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitchesShort)
{
	// test indent switch blocks short option
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    switch (foo)\n"
		"    {\n"
		"        case 1:\n"
		"            a += 1;\n"
		"            break;\n"
		"\n"
		"        case 2:\n"
		"        {\n"
		"            a += 2;\n"
		"            break;\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "-S";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Indent Cases
//-------------------------------------------------------------------------

TEST(IndentCases)
{
	// test indent case blocks
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    switch (foo)\n"
		"    {\n"
		"    case 1:\n"
		"        a += 1;\n"
		"        break;\n"
		"\n"
		"    case 2:\n"
		"        {\n"
		"            a += 2;\n"
		"            break;\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "indent-cases";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentCasesShort)
{
	// test indent case blocks
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    switch (foo)\n"
		"    {\n"
		"    case 1:\n"
		"        a += 1;\n"
		"        break;\n"
		"\n"
		"    case 2:\n"
		"        {\n"
		"            a += 2;\n"
		"            break;\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "-K";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentCasesSans1)
{
	// test without indent case blocks
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    switch (foo)\n"
		"    {\n"
		"    case 1:\n"
		"        a += 1;\n"
		"        break;\n"
		"\n"
		"    case 2:\n"
		"    {\n"
		"        a += 2;\n"
		"        break;\n"
		"    }\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentCasesMultiple1)
{
	// test multiple case statements per line, with keep one line statements
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    switch (foo)\n"
		"    {\n"
		"    case 1:case 2:\n"
		"        a += 1;\n"
		"        break;\n"
		"\n"
		"    case 3:case 4:\n"
		"    {\n"
		"        a += 2;\n"
		"        break;\n"
		"    }\n"
		"    }\n"
		"}\n";
	char options[] = "keep-one-line-statements";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentCasesMultiple2)
{
	// test multiple case statements per line, with break one line statements
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    switch (foo)\n"
		"    {\n"
		"    case 1:case 2:\n"
		"        a += 1;\n"
		"        break;\n"
		"\n"
		"    case 3:case 4:\n"
		"    {\n"
		"        a += 2;\n"
		"        break;\n"
		"    }\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    switch (foo)\n"
		"    {\n"
		"    case 1:\n"
		"    case 2:\n"
		"        a += 1;\n"
		"        break;\n"
		"\n"
		"    case 3:\n"
		"    case 4:\n"
		"    {\n"
		"        a += 2;\n"
		"        break;\n"
		"    }\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitchesCases)
{
	// test indent case blocks, with indent switch blocks
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    switch (foo)\n"
		"    {\n"
		"        case 1:\n"
		"            a += 1;\n"
		"            break;\n"
		"\n"
		"        case 2:\n"
		"            {\n"
		"                a += 2;\n"
		"                break;\n"
		"            }\n"
		"    }\n"
		"}\n";
	char options[] = "indent-switches, indent-cases";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Indent Blocks
// Additional tests are in the Brackets tests
//-------------------------------------------------------------------------

TEST(IndentBlocks)
{
	// test indent blocks
	// per GNU standards the only extra indent is within function blocks
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"class FooClass\n"
		"{\n"
		"private:\n"
		"    bool var1;\n"
		"    void func1();\n"
		"protected:\n"
		"    bool var2;\n"
		"    void inlineFunc()\n"
		"    {\n"
		"        if (isBar)\n"
		"            {\n"
		"                bar();\n"
		"                if (isAnotherBar)\n"
		"                    {\n"
		"                        anotherBar();\n"
		"                        if (isXtraBar)\n"
		"                            {\n"
		"                                xtraBar();\n"
		"                            }\n"
		"                    }\n"
		"            }\n"
		"    }\n"
		"};\n"
		"\n"
		"void FooClass::Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"        {\n"
		"            bar();\n"
		"        }\n"
		"    else\n"
		"        anotherBar();\n"
		"\n"
		"    if (isBar)\n"
		"        {\n"
		"            bar();\n"
		"            if (isAnotherBar)\n"
		"                {\n"
		"                    anotherBar();\n"
		"                    if (isXtraBar)\n"
		"                        {\n"
		"                            xtraBar();\n"
		"                        }\n"
		"                }\n"
		"        }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "indent-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentBlocksShort)
{
	// test indent blocks short option
	// per GNU standards the only extra indent is within function blocks
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"class FooClass\n"
		"{\n"
		"private:\n"
		"    bool var1;\n"
		"    void func1();\n"
		"protected:\n"
		"    bool var2;\n"
		"    void inlineFunc()\n"
		"    {\n"
		"        if (isBar)\n"
		"            {\n"
		"                bar();\n"
		"                if (isAnotherBar)\n"
		"                    {\n"
		"                        anotherBar();\n"
		"                        if (isXtraBar)\n"
		"                            {\n"
		"                                xtraBar();\n"
		"                            }\n"
		"                    }\n"
		"            }\n"
		"    }\n"
		"};\n"
		"\n"
		"void FooClass::Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"        {\n"
		"            bar();\n"
		"        }\n"
		"    else\n"
		"        anotherBar();\n"
		"\n"
		"    if (isBar)\n"
		"        {\n"
		"            bar();\n"
		"            if (isAnotherBar)\n"
		"                {\n"
		"                    anotherBar();\n"
		"                    if (isXtraBar)\n"
		"                        {\n"
		"                            xtraBar();\n"
		"                        }\n"
		"                }\n"
		"        }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "-G";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentBlocksBrackets)
{
	// test indent blocks and brackets
	// these are mutually exclusive - indent blocks will be used
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"class FooClass\n"
		"{\n"
		"private:\n"
		"    bool var1;\n"
		"    void func1();\n"
		"protected:\n"
		"    bool var2;\n"
		"    void func2();\n"
		"};\n"
		"\n"
		"void FooClass::Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"        {\n"
		"            bar();\n"
		"        }\n"
		"    else\n"
		"        {\n"
		"            anotherBar();\n"
		"        }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "indent-brackets, indent-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentBlocksStruct)
{
	// test indent blocks with structs and unions
	// the opening bracket should NOT be indented
	char text[] =
		"\nstruct b_type\n"
		"{\n"
		"    int i;\n"
		"    int j;\n"
		"};\n"
		"\n"
		"struct a_type {\n"
		"    int i;\n"
		"    int j;\n"
		"};\n"
		"\n"
		"union b_type\n"
		"{\n"
		"    int i;\n"
		"    int j;\n"
		"};\n"
		"\n"
		"union a_type {\n"
		"    int i;\n"
		"    int j;\n"
		"};\n"
		"\n"
		"// struct with inheritence and method\n"
		"struct b_fooStruct : public bar\n"
		"{\n"
		"    Foobar(bool isBar)\n"
		"    {\n"
		"        if (isBar)\n"
		"            {\n"
		"                Foo();\n"
		"            }\n"
		"        else\n"
		"            bar();\n"
		"        index = i;\n"
		"    }\n"
		"    long index;\n"
		"};\n"
		"\n"
		"// struct with inheritence and method\n"
		"struct a_fooStruct : public bar {\n"
		"    Foobar(bool isBar) {\n"
		"        if (isBar) {\n"
		"                Foo();\n"
		"            }\n"
		"        else\n"
		"            bar();\n"
		"        index = i;\n"
		"    }\n"
		"    long index;\n"
		"};\n";
	char options[] = "indent-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Indent Brackets
// Additional tests are in the Brackets tests
//-------------------------------------------------------------------------

TEST(IndentBrackets)
{
	// test indent brackets
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"class FooClass\n"
		"    {\n"
		"private:\n"
		"    bool var1;\n"
		"    void func1();\n"
		"protected:\n"
		"    bool var2;\n"
		"    void func2();\n"
		"    };\n"
		"\n"
		"void FooClass::Foo(bool isFoo)\n"
		"    {\n"
		"    if (isFoo)\n"
		"        {\n"
		"        bar();\n"
		"        }\n"
		"    else\n"
		"        {\n"
		"        anotherBar();\n"
		"        }\n"
		"    }\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "indent-brackets";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}
TEST(IndentBracketsShort)
{
	// test indent brackets short option
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"class FooClass\n"
		"    {\n"
		"private:\n"
		"    bool var1;\n"
		"    void func1();\n"
		"protected:\n"
		"    bool var2;\n"
		"    void func2();\n"
		"    };\n"
		"\n"
		"void FooClass::Foo(bool isFoo)\n"
		"    {\n"
		"    if (isFoo)\n"
		"        {\n"
		"        bar();\n"
		"        }\n"
		"    else\n"
		"        {\n"
		"        anotherBar();\n"
		"        }\n"
		"    }\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "-B";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentBracketsBlocks)
{
	// test indent brackets and blocks
	// these are mutually exclusive - indent blocks will be used
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"class FooClass\n"
		"{\n"
		"private:\n"
		"    bool var1;\n"
		"    void func1();\n"
		"protected:\n"
		"    bool var2;\n"
		"    void func2();\n"
		"};\n"
		"\n"
		"void FooClass::Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"        {\n"
		"            bar();\n"
		"        }\n"
		"    else\n"
		"        {\n"
		"            anotherBar();\n"
		"        }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "indent-blocks, indent-brackets";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Indent Namespaces
// Additional tests are in the Brackets tests
//-------------------------------------------------------------------------

TEST(IndentNamespaces)
{
	// test indent namespaces
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"    class FooClass\n"
		"    {\n"
		"    private:\n"
		"        bool var1;\n"
		"        void func1();\n"
		"    protected:\n"
		"        bool var2;\n"
		"        void func2();\n"
		"    };\n"
		"\n"
		"    void FooClass::Foo(bool isFoo)\n"
		"    {\n"
		"        if (isFoo)\n"
		"        {\n"
		"            bar();\n"
		"        }\n"
		"        else\n"
		"        {\n"
		"            anotherBar();\n"
		"        }\n"
		"    }\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(IndentNamespacesShort)
{
	// test indent namespaces short option
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"    class FooClass\n"
		"    {\n"
		"    private:\n"
		"        bool var1;\n"
		"        void func1();\n"
		"    protected:\n"
		"        bool var2;\n"
		"        void func2();\n"
		"    };\n"
		"\n"
		"    void FooClass::Foo(bool isFoo)\n"
		"    {\n"
		"        if (isFoo)\n"
		"        {\n"
		"            bar();\n"
		"        }\n"
		"        else\n"
		"        {\n"
		"            anotherBar();\n"
		"        }\n"
		"    }\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "-N";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Indent Misc
// Additional tests that are not specific options
//-------------------------------------------------------------------------

TEST(IndentMiscIndentableHeaders)
{
	// test indentable headers (return, cout, cin, cerr)
	// these headers use InStatementIndent like an operator
	char text[] =
		"\nint foo () {\n"
		"    if (foo1 == bar1)\n"
		"        return xxx +\n"
		"               yyy -\n"
		"               zzz;\n"
		"\n"
		"    return (xxx +\n"
		"            yyy -\n"
		"            zzz);\n"
		"\n"
		"    cout << xxx << xxx\n"
		"         << xxx << xxx << xxx;\n"
		"    cin >> xxx >> xxx\n"
		"        >> xxx >> xxx >> xxx;\n"
		"    cerr << xxx << xxx\n"
		"         << xxx << xxx << xxx;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

// TODO: test indent-labels
// TODO: test indent-preprocessor
// TODO: test max-instatement-indent
// TODO: test min-conditional-indent