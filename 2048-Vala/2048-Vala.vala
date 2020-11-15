using Gtk;
using Gdk;
using Cairo;

extern int e_win;
extern int e_lose;
extern int e_score;
extern int w_line_size;
extern int w_board_size;
extern int *w_board;

extern void e_init(int esc_keycode, int left_keycode, int right_keycode, int up_keycode, int down_keycode);
extern void e_key(int keycode);

extern uint e_foreground(int value);
extern uint e_background(int value);

public class Vala2048 : Gtk.Window {
	public Vala2048() {
		e_init(
			(int) Gdk.Key.Escape,
			(int) Gdk.Key.Left,
			(int) Gdk.Key.Right,
			(int) Gdk.Key.Up,
			(int) Gdk.Key.Down
		);
		title = "2048-Vala";
		destroy.connect(Gtk.main_quit);
		set_default_size(340, 400);

		for (int i = 0; i < w_board_size; ++i)
			stderr.printf("%d", w_board[i]);
	}

	static int main(string[] args) {
		Gtk.init(ref args);
		new Vala2048().show_all();
		Gtk.main();
		return 0;
	}
}

