// Based on:
//	https://wiki.gnome.org/Projects/Vala/CairoSample

using Gtk;
using Gdk;
using Cairo;

// Exports from C-code.
extern int *w_board;
extern int e_win;
extern int e_lose;
extern int e_score;
extern uint w_color_board;
extern uint w_color_final;
extern uint w_color_text;
extern uint w_color_overlay;
extern int w_line_size;
extern void e_init(int esc_keycode, int left_keycode, int right_keycode, int up_keycode, int down_keycode);
extern void e_key(int keycode);
extern uint e_foreground(int val);
extern uint e_background(int val);
extern double w_R(uint rgb);
extern double w_G(uint rgb);
extern double w_B(uint rgb);

public class Vala2048 : Gtk.Window {
	private const int TILE_SIZE   = 64;
	private const int TILE_MARGIN = 16;

	private DrawingArea drawing_area;

	public Vala2048() {
		e_init((int) Key.Escape, (int) Key.Left, (int) Key.Right, (int) Key.Up, (int) Key.Down);
		title = "2048-Vala";
		set_default_size(340, 400);
		set_resizable(false);
		init_widgets();
	}

	private void init_widgets() {
		destroy.connect(main_quit);
		key_press_event.connect((event) => {
			e_key((int) event.keyval);
			drawing_area.queue_draw();
			return true;
		});

		drawing_area = new DrawingArea();
		drawing_area.draw.connect((drawing_area, context) => {
			context.set_source_rgb(w_R(w_color_board), w_G(w_color_board), w_B(w_color_board));
			context.paint();
			for (int y = 0; y < w_line_size; ++y)
				for (int x = 0; x < w_line_size; ++x)
					draw_tile(context, w_board[x + y * w_line_size], x, y);
			draw_final(context);
			return false;
		});
		add(drawing_area);
	}

	private void draw_tile(Context context, int val, int x, int y) {
		uint bkg = e_background(val), frg = e_foreground(val);
		int xOffset = offset_coords(x), yOffset = offset_coords(y);
		context.set_source_rgb(w_R(bkg), w_G(bkg), w_B(bkg));
		draw_rounded_rectangle(context, xOffset, yOffset, TILE_SIZE, TILE_SIZE, 6);
		context.select_font_face("Sans", FontSlant.NORMAL, FontWeight.BOLD);
		if (val > 0) {
			int size = (val < 100) ? 26 : (val < 1000) ? 22 : 16;
			string strValue = val.to_string();
			context.set_source_rgb(w_R(frg), w_G(frg), w_B(frg));
			context.select_font_face("Sans", FontSlant.NORMAL, FontWeight.BOLD);
			context.set_font_size(size);
			TextExtents extents;
			context.text_extents(strValue, out extents);
			int w = (int) (extents.width) + 2, h = size;
			context.move_to(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2);
			context.show_text(strValue);
		}
	}

	private void draw_final(Context context) {
		int width = drawing_area.get_allocated_width(), height = drawing_area.get_allocated_height();
		int size = 26;
		if (e_win > 0 || e_lose > 0) {
			context.set_source_rgba(w_R(w_color_overlay), w_G(w_color_overlay), w_B(w_color_overlay), 0.5);
			context.paint();
			context.set_source_rgb(w_R(w_color_final), w_G(w_color_final), w_B(w_color_final));
			context.set_font_size(size);
			string strCenter = (e_win > 0) ? "You won!" : "Game Over!";
			TextExtents extents;
			context.text_extents(strCenter, out extents);
			context.move_to(width / 2 - (int) (extents.width) / 2, height / 2);
			context.show_text(strCenter);
		}
		size = 18;
		context.set_source_rgb(w_R(w_color_text), w_G(w_color_text), w_B(w_color_text));
		context.select_font_face("Sans", FontSlant.NORMAL, FontWeight.NORMAL);
		context.set_font_size(size);
		string strScore = "Score: " + e_score.to_string();
		TextExtents extents;
		context.text_extents(strScore, out extents);
		context.move_to(TILE_MARGIN, height - size);
		context.show_text("ESC to Restart!");
		context.move_to(width - (int) (extents.width) - TILE_MARGIN, height - size);
		context.show_text(strScore);
	}

	private void draw_rounded_rectangle(Context context, double x, double y, double w, double h, double r) {
		const double d = Math.PI / 180.0;
		context.new_sub_path();
		context.arc(x + w - r, y + r, r, -90 * d, 0 * d);
		context.arc(x + w - r, y + h - r, r, 0 * d, 90 * d);
		context.arc(x + r, y + h - r, r, 90 * d, 180 * d);
		context.arc(x + r, y + r, r, 180 * d, 270 * d);
		context.close_path();
		context.fill();
	}

	private inline int offset_coords(int coord) {
		return coord * (TILE_SIZE + TILE_MARGIN) + TILE_MARGIN;
	}

	static int main(string[] args) {
		Gtk.init(ref args);
		new Vala2048().show_all();
		Gtk.main();
		return 0;
	}
}

