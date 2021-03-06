#include "2048.h"

#include <LibGfx/Font.h>
#include <LibGfx/Path.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/Palette.h>

#include <LibGUI/Menu.h>
#include <LibGUI/Action.h>
#include <LibGUI/Widget.h>
#include <LibGUI/Window.h>
#include <LibGUI/Painter.h>
#include <LibGUI/MenuBar.h>
#include <LibGUI/MessageBox.h>
#include <LibGUI/Application.h>
#include <LibGUI/FontDatabase.h>

static const int TILE_SIZE = 64;
static const int TILE_MARGIN = 16;

class Widget final : public GUI::Widget {
	C_OBJECT(Widget)

	bool q_tiles_rounded;
	bool q_show_background;

	inline int offset_coords(int coord, int size, int offset) {
		const int start = (size / 2) - (((TILE_SIZE * LINE_SIZE) + (TILE_MARGIN * (LINE_SIZE - 1))) / 2);
		return coord * (TILE_MARGIN + TILE_SIZE) + start - offset;
	}

	// There are some HACKS for properly rounded rectangles.
	// See this method with clean code and additional information here:
	// https://github.com/SerenityOS/serenity/issues/2582
	void fill_rounded_rect(GUI::Painter &painter, const Gfx::IntRect &rect, const Gfx::Color &color) {
		auto path = Gfx::Path();
		const float left = rect.left(), right = rect.right() - 1, top = rect.top(), bottom = rect.bottom() - 1, rad = 5;
		path.move_to({ left + rad * 2, top });
		path.line_to({ right - rad * 2, top });
		path.quadratic_bezier_curve_to({ right, top }, { right, top + rad });
		path.line_to({ right, bottom - rad });
		path.quadratic_bezier_curve_to({ right, bottom }, { right - rad, bottom });
		path.line_to({ left + rad, bottom });
		path.quadratic_bezier_curve_to({ left, bottom }, { left, bottom - (rad * 2) });
		path.line_to({ left, top + rad * 2 });
		path.quadratic_bezier_curve_to({ left, top }, { left + rad * 2, top });
		path.close();
		painter.fill_path(path, color, Gfx::Painter::WindingRule::EvenOdd);
	}
	void draw_tile(GUI::Painter &painter, const Gfx::IntRect &rect, int value, int x, int y) {
		const int xOffset = offset_coords(x, rect.width(), 0), yOffset = offset_coords(y, rect.height(), TILE_MARGIN * 2);
		if (q_tiles_rounded) {
			// HACK: draw rounded rect through Bezier quadratic curves.
			fill_rounded_rect(painter, Gfx::IntRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE),
				Color::from_rgb(e_background(value)));
		} else {
			painter.fill_rect(Gfx::IntRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE), Color::from_rgb(e_background(value)));
		}
		if (value) {
			const String strValue = String::format("%d", value);
			auto font = GUI::FontDatabase::the().get_by_name((value < 100) ?
				"Liza Bold 36" : (value < 1000) ? "Liza Bold 24" : "Pebbleton Bold");
			const int w = font->width(strValue), h = font->glyph_height();
			painter.draw_text(Gfx::IntRect(xOffset + (TILE_SIZE - w) / 2, yOffset + (TILE_SIZE / 2 - h / 2), w, h),
				strValue, *font, Gfx::TextAlignment::TopLeft, Color::from_rgb(e_foreground(value)));
		}
	}
	void draw_final(GUI::Painter &painter, const Gfx::IntRect &rect) {
		if (e_win || e_lose) {
			auto bkg = Color::from_rgb(COLOR_OVERLAY);
			bkg.set_alpha(0x80); // ~50%
			painter.fill_rect(rect, bkg);
			const String center = (e_win) ? "You won!" : "Game Over!";
			auto font = GUI::FontDatabase::the().get_by_name("Liza Bold 36");
			const int w = font->width(center), h = font->glyph_height();
			painter.draw_text(Gfx::IntRect(rect.width() / 2 - w / 2, rect.height() / 2 - h, w, h),
				center, *font, Gfx::TextAlignment::TopLeft, Color::from_rgb(COLOR_FINAL));
		}
		const String strScore = String::format("Score: %d", e_score);
		const String strReset = "ESC to Restart!";
		auto font = GUI::FontDatabase::the().get_by_name("Katica Bold");
		int w = font->width(strReset), h = font->glyph_height();
		painter.draw_text(Gfx::IntRect(TILE_MARGIN, rect.height() - h * 2, w, h),
			strReset, *font, Gfx::TextAlignment::TopLeft, Color::from_rgb(COLOR_TEXT));
		w = font->width(strScore);
		painter.draw_text(Gfx::IntRect(rect.width() - w - TILE_MARGIN, rect.height() - h* 2, w, h),
			strScore, *font, Gfx::TextAlignment::TopLeft, Color::from_rgb(COLOR_TEXT));
	}
	explicit Widget() {
		q_tiles_rounded = true;
		q_show_background = true;
		e_init(KeyCode::Key_Escape, KeyCode::Key_Left, KeyCode::Key_Right, KeyCode::Key_Up, KeyCode::Key_Down);
	}
	virtual void paint_event(GUI::PaintEvent &paintEvent) override {
		GUI::Painter painter(*this);
		auto rect = paintEvent.rect();
		painter.add_clip_rect(rect);
		if (q_show_background)
			painter.fill_rect(rect, Color::from_rgb(COLOR_BOARD));
		else
			painter.fill_rect(rect, palette().color(background_role()));
		for (int y = 0; y < LINE_SIZE; ++y)
			for (int x = 0; x < LINE_SIZE; ++x)
				draw_tile(painter, rect, e_board[x + y * LINE_SIZE], x, y);
		draw_final(painter, rect);
	}
	virtual void keydown_event(GUI::KeyEvent &keyEvent) override {
		e_key(keyEvent.key());
		update();
	}
public:
	void set_show_background(bool show_background) { q_show_background = show_background; }
	void set_tiles_rounded(bool tiles_rounded) { q_tiles_rounded = tiles_rounded; }
	bool is_show_background() const { return q_show_background; }
	bool is_tiles_rounded() const { return q_tiles_rounded; }
};

int main(int argc, char *argv[]) {
	auto application = GUI::Application::construct(argc, argv);

	const String title = "2048-Serenity";
	auto window = GUI::Window::construct();
	window->set_double_buffering_enabled(false);
	window->set_title(title);
	window->set_rect(100, 100, 340, 400);

	auto &widget = window->set_main_widget<Widget>();
	auto menubar = GUI::MenuBar::construct();
	auto &main_menu = menubar->add_menu(title);
	main_menu.add_action(GUI::Action::create("Reset", {Mod_Ctrl, Key_R}, [&](auto &) {
		e_key(KeyCode::Key_Escape);
		widget.update();
	}));
	main_menu.add_separator();
	main_menu.add_action(GUI::CommonActions::make_quit_action([](auto &) {
		GUI::Application::the()->quit(0);
	}));
	auto &view_menu = menubar->add_menu("View");
	auto background_action = GUI::Action::create_checkable("Background", [&](auto &action) {
		widget.set_show_background(action.is_checked());
		widget.update();
	});
	background_action->set_checked(widget.is_show_background());
	auto tiles_action = GUI::Action::create_checkable("Round Tiles", [&](auto &action) {
		widget.set_tiles_rounded(action.is_checked());
		widget.update();
	});
	tiles_action->set_checked(widget.is_tiles_rounded());
	view_menu.add_action(*background_action);
	view_menu.add_action(*tiles_action);
	auto &help_menu = menubar->add_menu("Help");
	help_menu.add_action(GUI::Action::create("About...", [&](auto &) {
		GUI::MessageBox::show(window,
			"2048 Game, Version: 1.0, 27-Sep-2020, \xC2\xA9 EXL (exl@bk.ru), https://github.com/EXL/2048",
			title, GUI::MessageBox::Type::Information);
	}));

	application->set_menubar(move(menubar));
	window->set_icon(Gfx::Bitmap::load_from_file("/res/icons/16x16/app-2048-Serenity-16.png"));
	window->show();

	return application->exec();
}
