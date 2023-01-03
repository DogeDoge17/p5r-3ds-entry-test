#pragma once
#include <iostream>
#include <string.h>

PrintConsole topConsole, bottomConsole;

namespace Debug
{
	PrintConsole debugConsole;

	int x = 20;
	int	y = 1;
	int	w = 29;
	int	h = 28;

	bool visible;

	std::string *input;

	void init()
	{
		consoleInit(GFX_BOTTOM, &debugConsole);
		consoleSetWindow(&debugConsole, x, y, w, h);
	}

	/*void Write(std::string input)
	{
		std::cout<<
	}*/

	void Clear()
	{
		consoleSelect(&debugConsole);
		printf("\x1b[2J");
		consoleSelect(&topConsole);
	}

	/*void WriteLine() {
		std::cout<<"\n";
		consoleSelect(&topConsole);
	}

	template<typename First, typename ... Strings>
	void WriteLine(First arg, const Strings&... rest) {
		consoleSelect(&debugConsole);
		printf(arg,rest...);
		WriteLine(rest...);
	}*/


	void Hide()
	{
		Clear();
		consoleSetWindow(&debugConsole, -100, -100, 0, 0);
		visible = false;
	}

	void Show()
	{
		Clear();
		consoleSetWindow(&debugConsole, x, y, w, h);
		visible = true;
	}

	void ToggleVisibility()
	{	
		if(visible)
			Hide();
		else
			Show();
	}

	int WriteLine(const char *format, ...)
	{
		consoleSelect(&debugConsole);
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
		std::cout << "\n";
		consoleSelect(&topConsole);

		return 0;
	}

	int Error(const char *format, ...)
	{
		consoleSelect(&debugConsole);
		va_list args;
		fprintf(stderr, "\x1b[31mError: " );
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
		fprintf( stderr, "\x1b[0m\n" );
		consoleSelect(&topConsole);

		return 0;
	}

	int Warn(const char *format, ...)
	{
		consoleSelect(&debugConsole);
		va_list args;
		fprintf(stderr, "\x1b[33mWarning: " );
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
		fprintf(stderr, "\x1b[0m\n" );
		consoleSelect(&topConsole);

		return 0;
	}
};