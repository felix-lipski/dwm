/* See LICENSE file for copyright and license details. */

static char *paletteHexes[16] = {
 "#121212", "#ffffdd", "#4477aa", "#0033FF",
 "#00AA77", "#77AA00", "#DDBB00", "#FF5500",
 "#CC2200", "#73413b", "#223b54", "#6600DD",
 "#220099", "#332211", "#223b54", "#225533"
};


enum {
	Black, White, Gray, Blue,
	Turqoise, Green, Yellow, Orange,
	Red, DarkBrown, DarkGray
};

typedef struct {
	Cursor cursor;
} Cur;

typedef struct Fnt {
	Display *dpy;
	unsigned int h;
	XftFont *xfont;
	FcPattern *pattern;
	struct Fnt *next;
} Fnt;

enum { ColFg, ColBg, ColBorder }; /* Clr scheme index */
typedef XftColor Clr;

typedef struct {
	unsigned int w, h;
	Display *dpy;
	int screen;
	Window root;
	Drawable drawable;
	GC gc;
	Clr *scheme;
	Fnt *fonts;
	Clr *palette;
} Drw;

/* Drawable abstraction */
Drw *drw_create(Display *dpy, int screen, Window win, unsigned int w, unsigned int h);
void drw_resize(Drw *drw, unsigned int w, unsigned int h);
void drw_free(Drw *drw);

/* Fnt abstraction */
Fnt *drw_fontset_create(Drw* drw, char *fonts[], size_t fontcount);
void drw_fontset_free(Fnt* set);
unsigned int drw_fontset_getwidth(Drw *drw, const char *text);
unsigned int drw_fontset_getwidth_clamp(Drw *drw, const char *text, unsigned int n);
void drw_font_getexts(Fnt *font, const char *text, unsigned int len, unsigned int *w, unsigned int *h);

/* Colorscheme abstraction */
void drw_clr_create(Drw *drw, Clr *dest, const char *clrname);
Clr *drw_scm_create(Drw *drw, char *clrnames[], size_t clrcount);
/* Clr *drw_palette_create(Drw *drw, char *clrnames[], size_t clrcount); */
int drw_palette_create(Drw *drw, Clr *palette);

/* Cursor abstraction */
Cur *drw_cur_create(Drw *drw, int shape);
void drw_cur_free(Drw *drw, Cur *cursor);

/* Drawing context manipulation */
void drw_setfontset(Drw *drw, Fnt *set);
void drw_setscheme(Drw *drw, Clr *scm);

/* Drawing functions */
void drw_color(Drw *drw, int indx);
void drw_rect(Drw *drw, int x, int y, unsigned int w, unsigned int h, int filled, int invert);
void drw_dither(Drw *drw);
int drw_text(Drw *drw, int x, int y, unsigned int w, unsigned int h, unsigned int lpad, const char *text, int invert);
void drw_button(Drw *drw, int x, int y, int w, int h);
void drw_button_pressed(Drw *drw, int x, int y, int w, int h);

/* Map functions */
void drw_map(Drw *drw, Window win, int x, int y, unsigned int w, unsigned int h);
