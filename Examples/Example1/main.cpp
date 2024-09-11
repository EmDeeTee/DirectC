#include <DirectC.h>
#include <conio.h>

void main() {
	DirectC::Screen s(0, 0, "DirectC Example 1");

	while (_getch() != 'x') {
		s.DisplayConsoleInfo();
	}
}