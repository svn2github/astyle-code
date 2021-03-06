// AStyleTest_Tabs.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {
//
//-----------------------------------------------------------------------------
// AStyle Tab Options
//-----------------------------------------------------------------------------

TEST(Tabs, DefaultNone)
{
	// test default indent of 4 spaces per tab
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, Default)
{
	// test default indent of 4 spaces per tab
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char options[] = "indent=spaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, DefaultShort)
{
	// test default indent of 4 spaces per tab
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char options[] = "-s";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, Spaces_8)
{
	// test indent of 8 spaces per tab
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "        if (isFoo)\n"
	    "        {\n"
	    "                bar();\n"
	    "        }\n"
	    "        else\n"
	    "                anotherBar();\n"
	    "}\n";
	char options[] = "indent=spaces=8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, Spaces_Short8)
{
	// test indent of 8 spaces per tab
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "        if (isFoo)\n"
	    "        {\n"
	    "                bar();\n"
	    "        }\n"
	    "        else\n"
	    "                anotherBar();\n"
	    "}\n";
	char options[] = "s8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, Spaces_Invalid1)
{
	// test with an invalid indent
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "}\n";
	char options[] = "indent=spaces=x";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(Tabs, Spaces_Invalid2)
{
	// test with an indent that is below minimum
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "}\n";
	char options[] = "indent=spaces=1";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(Tabs, Spaces_Invalid3)
{
	// test with an indent that is above maximum
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "}\n";
	char options[] = "indent=spaces=21";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(Tabs, Spaces_CSharpLambda)
{
	// test C# with a lambda indent
	// TODO: doesn't work, should be indented like textIn
	char textIn[] =
	    "\nvoid UpdateErrorList(IEnumerable<CompilerError> errors)\n"
	    "{\n"
	    "    Dispatcher.Invoke(\n"
	    "        (Action)(\n"
	    "            () =>\n"
	    "            {\n"
	    "                var tasks = errors.Select(error => new Task()).ToList();\n"
	    "                if (tasks.Count > 0)\n"
	    "                {\n"
	    "                    TaskService.ClearExceptCommentTasks();\n"
	    "                    TaskService.AddRange(tasks);\n"
	    "                }\n"
	    "            }\n"
	    "        )\n"
	    "    );\n"
	    "}\n";
	char text[] =
	    "\nvoid UpdateErrorList(IEnumerable<CompilerError> errors)\n"
	    "{\n"
	    "    Dispatcher.Invoke(\n"
	    "        (Action)(\n"
	    "            () =>\n"
	    "    {\n"
	    "        var tasks = errors.Select(error => new Task()).ToList();\n"
	    "        if (tasks.Count > 0)\n"
	    "        {\n"
	    "            TaskService.ClearExceptCommentTasks();\n"
	    "            TaskService.AddRange(tasks);\n"
	    "        }\n"
	    "    }\n"
	    "        )\n"
	    "    );\n"
	    "}\n";
	char options[] = "indent=spaces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, Tab_Default)
{
	// test default tab indent of 4 spaces per tab
	// the '&& isBar' line will be indented with 2 tab widths or 8 spaces
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "	        && isBar)\n"
	    "	{\n"
	    "		bar();\n"
	    "	}\n"
	    "	else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, Tab_DefaultShort)
{
	// test default tab indent of 4 spaces per tab
	// the '&& isBar' line will be indented with 2 tab widths or 8 spaces
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "	        && isBar)\n"
	    "	{\n"
	    "		bar();\n"
	    "	}\n"
	    "	else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "t";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, Tab_8)
{
	// test tab indent of 8 spaces per tab
	// the '&& isBar' line will be indented with 2 tab widths or 16 spaces
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "	                && isBar)\n"
	    "	{\n"
	    "		bar();\n"
	    "	}\n"
	    "	else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "indent=tab=8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, Tab_Short8)
{
	// test tab indent of 8 spaces per tab
	// the '&& isBar' line will be indented with 2 tab widths or 16 spaces
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "	                && isBar)\n"
	    "	{\n"
	    "		bar();\n"
	    "	}\n"
	    "	else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "t8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, Tab_Invalid1)
{
	// test with an invalid indent
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "}\n";
	char options[] = "indent=tab=x";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(Tabs, Tab_Invalid2)
{
	// test with an indent that is below minimum
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "}\n";
	char options[] = "indent=tab=1";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(Tabs, Tab_Invalid3)
{
	// test with an indent that is above maximum
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "}\n";
	char options[] = "indent=tab=21";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(Tabs, Tab_CSharpLambda)
{
	// test C# with a lambda indent
	// TODO: doesn't work, should be indented like textIn
	char textIn[] =
	    "\nvoid UpdateErrorList(IEnumerable<CompilerError> errors)\n"
	    "{\n"
	    "	Dispatcher.Invoke(\n"
	    "	    (Action)(\n"
	    "	        () =>\n"
	    "	        {\n"
	    "		        var tasks = errors.Select(error => new Task()).ToList();\n"
	    "		        if (tasks.Count > 0)\n"
	    "		        {\n"
	    "			        TaskService.ClearExceptCommentTasks();\n"
	    "			        TaskService.AddRange(tasks);\n"
	    "		        }\n"
	    "	        }\n"
	    "	    )\n"
	    "	);\n"
	    "}\n";
	char text[] =
	    "\nvoid UpdateErrorList(IEnumerable<CompilerError> errors)\n"
	    "{\n"
	    "	Dispatcher.Invoke(\n"
	    "	    (Action)(\n"
	    "	        () =>\n"
	    "	{\n"
	    "		var tasks = errors.Select(error => new Task()).ToList();\n"
	    "		if (tasks.Count > 0)\n"
	    "		{\n"
	    "			TaskService.ClearExceptCommentTasks();\n"
	    "			TaskService.AddRange(tasks);\n"
	    "		}\n"
	    "	}\n"
	    "	    )\n"
	    "	);\n"
	    "}\n";
	char options[] = "indent=tab, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTab_Default)
{
	// test default force tab indent of 4 spaces per tab
	// the '&& isBar' line will be indented with 2 tabs instead of 8 spaces
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "			&& isBar)\n"
	    "	{\n"
	    "		bar();\n"
	    "	}\n"
	    "	else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "indent=force-tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTab_DefaultShort)
{
	// test default force tab indent of 4 spaces per tab
	// the '&& isBar' line will be indented with 2 tabs instead of 8 spaces
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "			&& isBar)\n"
	    "	{\n"
	    "		bar();\n"
	    "	}\n"
	    "	else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "-T";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTab_8)
{
	// test default force tab indent of 8 spaces per tab
	// the result of this test is the same as the default option
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "			&& isBar)\n"
	    "	{\n"
	    "		bar();\n"
	    "	}\n"
	    "	else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "indent=force-tab=8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTab_Short8)
{
	// test default force tab indent of 8 spaces per tab
	// the result of this test is the same as the default option
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "			&& isBar)\n"
	    "	{\n"
	    "		bar();\n"
	    "	}\n"
	    "	else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "T8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTab_Invalid1)
{
	// test with an invalid indent
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "}\n";
	char options[] = "indent=force-tab=x";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(Tabs, ForceTab_Invalid2)
{
	// test with an indent that is below minimum
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "}\n";
	char options[] = "indent=force-tab=1";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(Tabs, ForceTab_Invalid3)
{
	// test with an indent that is above maximum
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "}\n";
	char options[] = "indent=force-tab=21";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(Tabs, ForceTab_CSharpLambda)
{
	// test C# with a lambda indent
	// TODO: doesn't work, should be indented like textIn
	char textIn[] =
	    "\nvoid UpdateErrorList(IEnumerable<CompilerError> errors)\n"
	    "{\n"
	    "	Dispatcher.Invoke(\n"
	    "		(Action)(\n"
	    "			() =>\n"
	    "			{\n"
	    "				var tasks = errors.Select(error => new Task()).ToList();\n"
	    "				if (tasks.Count > 0)\n"
	    "				{\n"
	    "					TaskService.ClearExceptCommentTasks();\n"
	    "					TaskService.AddRange(tasks);\n"
	    "				}\n"
	    "			}\n"
	    "		)\n"
	    "	);\n"
	    "}\n";
	char text[] =
	    "\nvoid UpdateErrorList(IEnumerable<CompilerError> errors)\n"
	    "{\n"
	    "	Dispatcher.Invoke(\n"
	    "		(Action)(\n"
	    "			() =>\n"
	    "	{\n"
	    "		var tasks = errors.Select(error => new Task()).ToList();\n"
	    "		if (tasks.Count > 0)\n"
	    "		{\n"
	    "			TaskService.ClearExceptCommentTasks();\n"
	    "			TaskService.AddRange(tasks);\n"
	    "		}\n"
	    "	}\n"
	    "		)\n"
	    "	);\n"
	    "}\n";
	char options[] = "indent=force-tab, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTabX_Default)
{
	// Test force-tab with the default tab-size of 8 spaces
	// and the default indent of 4 spaces.
	// The indents will be mixed tabs and spaces.
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "	    && isBar)\n"
	    "    {\n"
	    "	bar();\n"
	    "    }\n"
	    "    else\n"
	    "	anotherBar();\n"
	    "}\n";
	char options[] = "indent=force-tab-x";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTabX_DefaultShort)
{
	// Test force-tab short option with the default tab-size of 8 spaces
	// and the default indent of 4 spaces.
	// The indents will be mixed tabs and spaces.
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "	    && isBar)\n"
	    "    {\n"
	    "	bar();\n"
	    "    }\n"
	    "    else\n"
	    "	anotherBar();\n"
	    "}\n";
	char options[] = "-xT";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTabX_6)
{
	// Test option with a tab length of 6 spaces
	// and a default indentof 3 spaces.
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "   if (isFoo\n"
	    "	   && isBar)\n"
	    "   {\n"
	    "	bar();\n"
	    "   }\n"
	    "   else\n"
	    "	anotherBar();\n"
	    "}\n";
	char options[] = "indent=force-tab-x=6, indent=force-tab=3";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTabX_Short6)
{
	// Test short option with a tab length of 6 spaces
	// and a default indent of 3 spaces.
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "   if (isFoo\n"
	    "	   && isBar)\n"
	    "   {\n"
	    "	bar();\n"
	    "   }\n"
	    "   else\n"
	    "	anotherBar();\n"
	    "}\n";
	char options[] = "xT6, T3";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTabX_Indent1)
{
	// Test force-tab with tab-size of 4 spaces
	// and an indent size of 8 spaces.
	// There will be two tabs per indent.
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "		if (isFoo\n"
	    "						&& isBar)\n"
	    "		{\n"
	    "				bar();\n"
	    "		}\n"
	    "		else\n"
	    "				anotherBar();\n"
	    "}\n";
	char options[] = "indent=force-tab-x=4, indent=force-tab=8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTabX_Indent2)
{
	// Test force-tab with tab-size of 4 spaces
	// and an indent size of 8 spaces.
	// There will be two tabs per indent.
	// The options are reversed from above. Should still work.
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "		if (isFoo\n"
	    "						&& isBar)\n"
	    "		{\n"
	    "				bar();\n"
	    "		}\n"
	    "		else\n"
	    "				anotherBar();\n"
	    "}\n";
	char options[] = ", indent=force-tab=8, indent=force-tab-x=4";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTabX_Indent3)
{
	// Test force-tab with tab-size of 6 spaces
	// and an indent size of 4 spaces.
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "		&& isBar)\n"
	    "    {\n"
	    "	  bar();\n"
	    "    }\n"
	    "    else\n"
	    "	  anotherBar();\n"
	    "}\n";
	char options[] = "indent=force-tab-x=6, indent=force-tab=4";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTabX_Indent4)
{
	// Test force-tab with tab-size of 4 spaces
	// and an indent size of 6 spaces.
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	  if (isFoo\n"
	    "				  && isBar)\n"
	    "	  {\n"
	    "			bar();\n"
	    "	  }\n"
	    "	  else\n"
	    "			anotherBar();\n"
	    "}\n";
	char options[] = "indent=force-tab-x=4, indent=force-tab=6";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTabX_Horstmann1)
{
	// Test force-tab option with Horstmann braces.
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo\n"
	    "	    && isBar)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "	anotherBar();\n"
	    "}\n";
	char options[] = "indent=force-tab-x, style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTabX_Horstmann2)
{
	// Test force-tab option with Horstmann braces.
	// A Comment in a switch statement requires 2 indents.
	char text[] =
	    "\nvoid Foo()\n"
	    "{   switch (foo)\n"
	    "    {   // comment1\n"
	    "	case 1:\n"
	    "	    a += 1;\n"
	    "	    break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-switches, indent=force-tab-x, style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTabX_Horstmann3)
{
	// Test force-tab option with Horstmann braces
	// with a tab-size of 4 spaces and an indent size of 8 spaces.
	// There will be two tabs per indent.
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{		if (isFoo\n"
	    "						&& isBar)\n"
	    "		{		bar();\n"
	    "		}\n"
	    "		else\n"
	    "				anotherBar();\n"
	    "}\n";
	char options[] = "style=horstmann, indent=force-tab-x=4, indent=force-tab=8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Tabs, ForceTabX_Horstmann4)
{
	// Test force-tab option with Horstmann braces
	// with a tab-size of 6 spaces and an indent size of 4 spaces.
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo\n"
	    "		&& isBar)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "	  anotherBar();\n"
	    "}\n";
	char options[] = "style=horstmann, indent=force-tab-x=6, indent=force-tab=4";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-----------------------------------------------------------------------------
// AStyle Attach Extern "C" Option
//-----------------------------------------------------------------------------

TEST(AttachExternC, LongOption)
{
	// test attach extern C long option
	char textIn[] =
	    "\nextern \"C\"\n"
	    "{\n"
	    "    void foo2() {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nextern \"C\" {\n"
	    "    void foo2() {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "attach-extern-c";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachExternC, ShortOption)
{
	// test attach extern C short option
	char textIn[] =
	    "\nextern \"C\"\n"
	    "{\n"
	    "    void foo2() {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nextern \"C\" {\n"
	    "    void foo2() {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "-xk";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachExternC, BreakBraces)
{
	// test attach extern C with break braces
	char textIn[] =
	    "\nextern \"C\"\n"
	    "{\n"
	    "    void foo2() {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nextern \"C\" {\n"
	    "    void foo2()\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "attach-extern-c, style=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachExternC, AttachBraces)
{
	// test attach extern C with attach braces
	char textIn[] =
	    "\nextern \"C\"\n"
	    "{\n"
	    "    void foo2()\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nextern \"C\" {\n"
	    "    void foo2() {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "attach-extern-c, style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachExternC, LinuxBraces)
{
	// test attach extern C with linux braces
	char textIn[] =
	    "\nextern \"C\"\n"
	    "{\n"
	    "    void foo2()\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nextern \"C\" {\n"
	    "    void foo2()\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "attach-extern-c, style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachExternC, StroustrupBraces)
{
	// test attach extern C with stroustrup braces
	char textIn[] =
	    "\nextern \"C\"\n"
	    "{\n"
	    "    void foo2()\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nextern \"C\" {\n"
	    "    void foo2()\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "attach-extern-c, style=stroustrup";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachExternC, RunInBraces)
{
	// test attach extern C with run-in braces
	char textIn[] =
	    "\nextern \"C\"\n"
	    "{\n"
	    "    void foo2()\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nextern \"C\" {\n"
	    "    void foo2()\n"
	    "    {   bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "attach-extern-c, style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachExternC, CPlusPlus)
{
	// test attach extern C in __cplusplus preprocessor
	char textIn[] =
	    "\n#ifdef __cplusplus\n"
	    "extern \"C\"\n"
	    "{\n"
	    "#endif\n"
	    "\n"
	    "#ifdef __cplusplus\n"
	    "}\n"
	    "#endif";
	char text[] =
	    "\n#ifdef __cplusplus\n"
	    "extern \"C\" {\n"
	    "#endif\n"
	    "\n"
	    "#ifdef __cplusplus\n"
	    "}\n"
	    "#endif";
	char options[] = "attach-extern-c";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-----------------------------------------------------------------------------
// AStyle Attach Namespaces Option
//-----------------------------------------------------------------------------

TEST(AttachNamespaces, LongOption)
{
	// test attach namespaces long option
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "}";
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "}";
	char options[] = "attach-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachNamespaces, ShortOption)
{
	// test attach namespaces short option
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "}";
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "}";
	char options[] = "-xn";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachNamespaces, BreakBraces)
{
	// test attach namespaces with break braces
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "}";
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "}";
	char options[] = "attach-namespaces, style=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachNamespaces, AttachBraces)
{
	// test attach namespaces with attach braces
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "}";
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "}";
	char options[] = "attach-namespaces, style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachNamespaces, LinuxBraces)
{
	// test attach namespaces with linux braces
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "}";
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "}";
	char options[] = "attach-namespaces, style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachNamespaces, StroustrupBraces)
{
	// test attach namespaces with stroustrup braces
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "}";
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "}";
	char options[] = "attach-namespaces, style=stroustrup";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachNamespaces, RunInBraces)
{
	// test attach namespaces with run-in braces
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "}";
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "}";
	char options[] = "attach-namespaces, style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachNamespaces, NestedNamespace)
{
	// test attach namespaces with nested namespaces
	char textIn[] =
	    "\nnamespace A\n"
	    "{\n"
	    "namespace B\n"
	    "{\n"
	    "namespace C\n"
	    "{\n"
	    "}\n"
	    "}\n"
	    "}\n";
	char text[] =
	    "\nnamespace A {\n"
	    "namespace B {\n"
	    "namespace C {\n"
	    "}\n"
	    "}\n"
	    "}\n";
	char options[] = "attach-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachNamespaces, SharpNamespace)
{
	// test attach namespaces with nested namespaces
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "}";
	char text[] =
	    "\nnamespace FooName {\n"
	    "}";
	char options[] = "attach-namespaces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

//-----------------------------------------------------------------------------
// AStyle Attach Classes Option
//-----------------------------------------------------------------------------

TEST(AttachClasses, LongOption)
{
	// test attach classes long option
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "};";
	char text[] =
	    "\nclass FooClass {\n"
	    "};";
	char options[] = "attach-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClasses, ShortOption)
{
	// test attach classes short option
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "};";
	char text[] =
	    "\nclass FooClass {\n"
	    "};";
	char options[] = "-xc";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClasses, BreakBraces)
{
	// test attach classes with break braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "};";
	char text[] =
	    "\nclass FooClass {\n"
	    "};";
	char options[] = "attach-classes, style=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClasses, AttachBraces)
{
	// test attach classes with attach braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "};";
	char text[] =
	    "\nclass FooClass {\n"
	    "};";
	char options[] = "attach-classes, style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClasses, LinuxBraces)
{
	// test attach classes with linux braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "};";
	char text[] =
	    "\nclass FooClass {\n"
	    "};";
	char options[] = "attach-classes, style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClasses, StroustrupBraces)
{
	// test attach classes with stroustrup braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "};";
	char text[] =
	    "\nclass FooClass {\n"
	    "};";
	char options[] = "attach-classes, style=stroustrup";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClasses, RunInBraces)
{
	// test attach classes with run-in braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "};";
	char text[] =
	    "\nclass FooClass {\n"
	    "};";
	char options[] = "attach-classes, style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClasses, NestedClasses)
{
	// test attach classes with nested classes
	char textIn[] =
	    "\nclass A\n"
	    "{\n"
	    "class B\n"
	    "{\n"
	    "class C\n"
	    "{\n"
	    "};\n"
	    "};\n"
	    "};\n";
	char text[] =
	    "\nclass A {\n"
	    "    class B {\n"
	    "        class C {\n"
	    "        };\n"
	    "    };\n"
	    "};\n";
	char options[] = "attach-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClasses, AttachNamespaces)
{
	// test attach classes with attach namespaces
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "class  FooClass\n"
	    "{\n"
	    "};\n"
	    "};\n";
	char text[] =
	    "\nnamespace FooName {\n"
	    "class  FooClass {\n"
	    "};\n"
	    "};\n";
	char options[] = "attach-classes, attach-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClasses, JavaClass)
{
	// test attach classes with a Java class
	char textIn[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "}\n";
	char text[] =
	    "\npublic class FooClass {\n"
	    "}\n";
	char options[] = "attach-classes, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClasses, SharpClass)
{
	// test attach classes with a C# class
	char textIn[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "}\n";
	char text[] =
	    "\npublic class FooClass {\n"
	    "}\n";
	char options[] = "attach-classes, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClasses, SharpInterface)
{
	// test attach classes with a C# interface
	char textIn[] =
	    "public interface FooInterface\n"
	    "{\n"
	    "}";
	char text[] =
	    "public interface FooInterface {\n"
	    "}";
	char options[] = "attach-classes, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

//-----------------------------------------------------------------------------
// AStyle Attach Inlines Option
//-----------------------------------------------------------------------------

TEST(AttachInlines, LongOption)
{
	// test attach inlines long option
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch)\n"
	    "    {\n"
	    "        if (isFoo1(ch))\n"
	    "        {\n"
	    "            if (isFoo2(ch))\n"
	    "            {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch) {\n"
	    "        if (isFoo1(ch)) {\n"
	    "            if (isFoo2(ch)) {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char options[] = "attach-inlines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, ShortOption)
{
	// test attach inlines short option
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch)\n"
	    "    {\n"
	    "        if (isFoo1(ch))\n"
	    "        {\n"
	    "            if (isFoo2(ch))\n"
	    "            {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch) {\n"
	    "        if (isFoo1(ch)) {\n"
	    "            if (isFoo2(ch)) {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char options[] = "-xl";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, NoneBraces1)
{
	// test attach inlines with no brace style
	// start with broken braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch)\n"
	    "    {\n"
	    "        if (isFoo1(ch))\n"
	    "        {\n"
	    "            if (isFoo2(ch))\n"
	    "            {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch) {\n"
	    "        if (isFoo1(ch)) {\n"
	    "            if (isFoo2(ch)) {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char options[] = "attach-inlines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, NoneBraces2)
{
	// test attach inlines with no brace style
	// start with run-in braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch)\n"
	    "    {   if (isFoo1(ch))\n"
	    "        {   if (isFoo2(ch))\n"
	    "            {   return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch) {\n"
	    "        if (isFoo1(ch)) {\n"
	    "            if (isFoo2(ch)) {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char options[] = "attach-inlines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, NoneBraces3)
{
	// test attach inlines with no brace style
	// start with one-line braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch)\n"
	    "    {   if (isFoo1(ch))\n"
	    "        { return false; }\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch) {\n"
	    "        if (isFoo1(ch)) {\n"
	    "            return false;\n"
	    "        }\n"
	    "    }\n"
	    "};";
	char options[] = "attach-inlines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, NoneBraces4)
{
	// test attach inlines with no brace style
	// with keep-one-line-blocks
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch)\n"
	    "    {   if (isFoo1(ch))\n"
	    "        { return false; }\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch) {\n"
	    "        if (isFoo1(ch))\n"
	    "        { return false; }\n"
	    "    }\n"
	    "};";
	char options[] = "attach-inlines, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, BreakBraces)
{
	// test attach inlines with break braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch)\n"
	    "    {\n"
	    "        if (isFoo1(ch))\n"
	    "        {\n"
	    "            if (isFoo2(ch))\n"
	    "            {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch) {\n"
	    "        if (isFoo1(ch)) {\n"
	    "            if (isFoo2(ch)) {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char options[] = "attach-inlines, style=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, AttachBraces)
{
	// test attach inlines with attach braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch)\n"
	    "    {\n"
	    "        if (isFoo1(ch))\n"
	    "        {\n"
	    "            if (isFoo2(ch))\n"
	    "            {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nclass FooClass {\n"
	    "    bool Foo(char ch) {\n"
	    "        if (isFoo1(ch)) {\n"
	    "            if (isFoo2(ch)) {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char options[] = "attach-inlines, style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, LinuxBraces)
{
	// test attach inlines with linux braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch)\n"
	    "    {\n"
	    "        if (isFoo1(ch))\n"
	    "        {\n"
	    "            if (isFoo2(ch))\n"
	    "            {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch) {\n"
	    "        if (isFoo1(ch)) {\n"
	    "            if (isFoo2(ch)) {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char options[] = "attach-inlines, style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, StroustrupBraces)
{
	// test attach inlines with stroustrup braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch)\n"
	    "    {\n"
	    "        if (isFoo1(ch))\n"
	    "        {\n"
	    "            if (isFoo2(ch))\n"
	    "            {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nclass FooClass {\n"
	    "    bool Foo(char ch) {\n"
	    "        if (isFoo1(ch)) {\n"
	    "            if (isFoo2(ch)) {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char options[] = "attach-inlines, style=stroustrup";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, RunInBraces)
{
	// test attach inlines with run-in braces
	// run-in braces should NOT be attached
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    bool Foo(char ch)\n"
	    "    {\n"
	    "        if (isFoo1(ch))\n"
	    "        {\n"
	    "            if (isFoo2(ch))\n"
	    "            {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{   bool Foo(char ch)\n"
	    "    {   if (isFoo1(ch))\n"
	    "        {   if (isFoo2(ch))\n"
	    "            {   return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "};";
	char options[] = "attach-inlines, style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, StructInClass)
{
	// test attach inlines with a struct in a class
	// the braces are attached
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    struct switchVariables\n"
	    "    {\n"
	    "        int  switchBraceCount;\n"
	    "        int  Foo()\n"
	    "        {\n"
	    "            bool unindentCase;\n"
	    "        }\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    struct switchVariables\n"
	    "    {\n"
	    "        int  switchBraceCount;\n"
	    "        int  Foo() {\n"
	    "            bool unindentCase;\n"
	    "        }\n"
	    "    }\n"
	    "};";
	char options[] = "attach-inlines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, JavaClass)
{
	// test attach inlines with a Java class
	// Java class should NOT be changed
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    public bool Foo(char ch)\n"
	    "    {\n"
	    "        if (isFoo1(ch))\n"
	    "        {\n"
	    "            if (isFoo2(ch))\n"
	    "            {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "}";
	char options[] = "attach-inlines, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, SharpClass)
{
	// test attach inlines with a C# class
	// C# class should NOT be changed
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    public bool Foo(char ch)\n"
	    "    {\n"
	    "        if (isFoo1(ch))\n"
	    "        {\n"
	    "            if (isFoo2(ch))\n"
	    "            {\n"
	    "                return false;\n"
	    "            }\n"
	    "            return true;\n"
	    "        }\n"
	    "        return false;\n"
	    "    }\n"
	    "}";
	char options[] = "attach-inlines, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachInlines, RunInComment)
{
	// test attach inlines followed by a run-in comment
	// brace should NOT be attached
	char textIn[] =
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "    int Foo () \n"
	    "    {\n"
	    "        if (not rc)\n"
	    "        {   // comment\n"
	    "            return 0;\n"
	    "        }\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "    int Foo () {\n"
	    "        if (not rc)\n"
	    "        {   // comment\n"
	    "            return 0;\n"
	    "        }\n"
	    "    }\n"
	    "};\n";
	char options[] = "attach-inlines, remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-----------------------------------------------------------------------------
// AStyle Attach Closing While
//-----------------------------------------------------------------------------

TEST(AttachClosingWhile, LongOption)
{
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    do\n"
	    "    {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } \n"
	    "    while (x == 1);    // comment\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    do\n"
	    "    {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } while (x == 1);  // comment\n"
	    "}";
	char options[] = "attach-closing-while";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, ShortOption)
{
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    do\n"
	    "    {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } \n"
	    "    while (x == 1);    // comment\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    do\n"
	    "    {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } while (x == 1);  // comment\n"
	    "}";
	char options[] = "-xV";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, BreakStyle)
{
	// test BREAK_MODE braces with attach closing while
	char textIn[] =
	    "\n"
	    "void Foo() {\n"
	    "     do {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    }\n"
	    "    while (x == 1);    // comment\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    do\n"
	    "    {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } while (x == 1);  // comment\n"
	    "}";
	char options[] = "style=break, attach-closing-while";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, AttachStyle)
{
	// test ATTACH_MODE braces with attach closing while
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    do\n"
	    "    {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    }\n"
	    "    while (x == 1);    // comment\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo() {\n"
	    "    do {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } while (x == 1);  // comment\n"
	    "}";
	char options[] = "style=java, attach-closing-while";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, LinuxStyle)
{
	// test LINUX_MODE braces with attach closing while
	char textIn[] =
	    "\n"
	    "void Foo() {\n"
	    "     do {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    }\n"
	    "    while (x == 1);    // comment\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    do {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } while (x == 1);  // comment\n"
	    "}";
	char options[] = "style=kr, attach-closing-while";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, RunInStyle)
{
	// test RUN_IN_MODE braces with attach closing while
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    do {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    }\n"
	    "    while (x == 1);    // comment\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{   do\n"
	    "    {   bar();\n"
	    "        ++x;\n"
	    "    } while (x == 1);  // comment\n"
	    "}";
	char options[] = "style=run-in, attach-closing-while";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, BreakStyleSans)
{
	// test BREAK_MODE braces without attach closing while
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    do\n"
	    "    {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    }\n"
	    "    while (x == 1);  // comment\n"
	    "}";
	char options[] = "style=break";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, AttachStyleSans)
{
	// test ATTACH_MODE braces without attach closing while
	char text[] =
	    "\n"
	    "void Foo() {\n"
	    "    do {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } while (x == 1);  // comment\n"
	    "}";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, LinuxStyleSans)
{
	// test LINUX_MODE braces without attach closing while
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    do {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } while (x == 1);  // comment\n"
	    "}";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, RunInStyleSans)
{
	// test RUN_IN_MODE braces without attach closing while
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{   do\n"
	    "    {   bar();\n"
	    "        ++x;\n"
	    "    }\n"
	    "    while (x == 1);  // comment\n"
	    "}";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, BreakBlocks)
{
	// test spacing with break blocks
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    bar1();\n"
	    "    do\n"
	    "    {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } \n"
	    "    while (x == 1);    // comment\n"
	    "    bar2();\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    bar1();\n"
	    "\n"
	    "    do\n"
	    "    {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } while (x == 1);  // comment\n"
	    "\n"
	    "    bar2();\n"
	    "}";
	char options[] = "attach-closing-while, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, BreakBlocksAll)
{
	// test spacing with break blocks all
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    bar1();\n"
	    "    do\n"
	    "    {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } \n"
	    "    while (x == 1);    // comment\n"
	    "    bar2();\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    bar1();\n"
	    "\n"
	    "    do\n"
	    "    {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    } while (x == 1);  // comment\n"
	    "\n"
	    "    bar2();\n"
	    "}";
	char options[] = "attach-closing-while, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, PreceedingEmptyLine)
{
	// do not attach closing while to a preceeding empty line
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    do\n"
	    "    {\n"
	    "        bar();\n"
	    "        ++x;\n"
	    "    }\n"
	    "\n"
	    "    while (x == 1);    // comment\n"
	    "}";
	char options[] = "attach-closing-while";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachClosingWhile, KeepOneLineBlocks)
{
	// do not attach closing while to a one line block
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    do\n"
	    "    { bar(); ++x; }\n"
	    "    while (x == 1);    // comment\n"
	    "}";
	char options[] = "attach-closing-while, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}


//----------------------------------------------------------------------------

}  // namespace
