// Based on: https://wiki.gnome.org/Projects/Vala/CairoSample

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
	// TODO: Delete this.
	private bool check = true;
	private DrawingArea drawing_area;

	public Vala2048() {
		e_init(
			(int) Gdk.Key.Escape,
			(int) Gdk.Key.Left,
			(int) Gdk.Key.Right,
			(int) Gdk.Key.Up,
			(int) Gdk.Key.Down
		);
		title = "2048-Vala";
		set_default_size(340, 400);
		set_resizable(false);
		create_widgets_and_connects();
		// TODO: Remove this check
		for (int i = 0; i < w_board_size; ++i)
			stderr.printf("%d", w_board[i]);
	}

	private void create_widgets_and_connects() {
		destroy.connect(Gtk.main_quit);

		drawing_area = new DrawingArea();
		drawing_area.draw.connect(on_draw);
		add(drawing_area);

		key_press_event.connect((event) => {
			stderr.printf("%u\n", event.keyval);
			check = false;
			drawing_area.queue_draw();
			return true;
		});
	}

	private bool on_draw(Widget drawing_area, Context context) {
		if (check)
			context.set_source_rgb(1, 0, 0);
			else context.set_source_rgb(1, 0, 1);
		context.paint();
		return false;
	}

	static int main(string[] args) {
		Gtk.init(ref args);
		new Vala2048().show_all();
		Gtk.main();
		return 0;
	}
}

