#include <DirectC.h>
#include <conio.h>

struct Player {
	DirectC::Position p = { 0,0 };
};

void main() {
	DirectC::Screen s(0, 0, "DirectC Example 2");
	const DirectC::ConsoleSizeData size = s.GetConsoleSizeData();
	Player p;

	while (_getch() != 'x') {
		if (s.WasKeyPressed(DirectC::Key::D) && p.p.x < size.rows - 1) {
			p.p.AddX(1);
		}
		else if (s.WasKeyPressed(DirectC::Key::S) && p.p.y < size.cols - 1) {
			p.p.AddY(1);
		}
		else if (s.WasKeyPressed(DirectC::Key::A) && p.p.x > 0) {
			p.p.AddX(-1);
		}
		else if (s.WasKeyPressed(DirectC::Key::W) && p.p.y > 0) {
			p.p.AddY(-1);
		}
		s.Write("@", p.p, false, FOREGROUND_RED);
		s.RenderNextFrame();
		s.ClearBuffer();
	}
}