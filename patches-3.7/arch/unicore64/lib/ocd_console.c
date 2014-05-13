/*
 *  To be used if there's no graphics device in board, and only ocd
 *  available for text output.
 */
#include <linux/console.h>
#include <linux/vt_kern.h>
#include <linux/module.h>

#include <arch/asm-debug.h>

#define OCD_CON_COLUMNS			80
#define OCD_CON_ROWS			25

static const char *ocd_con_startup(void)
{
	return "OCD(On-Chip-Debugger) console";
}

static void ocd_con_init(struct vc_data *vc, int init)
{
	vc->vc_can_do_color = 1;
	if (init) {
		vc->vc_cols = OCD_CON_COLUMNS;
		vc->vc_rows = OCD_CON_ROWS;
	} else
		vc_resize(vc, OCD_CON_COLUMNS, OCD_CON_ROWS);
}

static void ocd_con_putc(struct vc_data *vc, int c, int ypos, int xpos)
{
	uc64_debug_puts((char *)&c, 1);
}

static void ocd_con_putcs(struct vc_data *vc, const unsigned short *s,
			int n, int ypos, int xpos)
{
	static int ypos_last;
	char c = '\n';

	while (ypos > ypos_last) {
		uc64_debug_puts(&c, 1);
		ypos_last++;
	}
	ypos_last = ypos;

	/* For each element in *s (16bit in an unsigned short type):
	 * High 8-bit is color, low 8-bit is char,
	 * and only char is useful here. */
	while (*s && (n > 0)) {
		uc64_debug_puts((char *)s, 1);
		s++;
		n--;
	}
}

static int ocd_con_scroll(struct vc_data *vc, int t, int b, int dir, int cnt)
{
	char c = '\n';
	uc64_debug_puts(&c, 1);
	return 0;
}

static int ocd_con_dummy(void)
{
	return 0;
}

/*
 *  The console switch structure for the ocd console
 *
 *  Most of the operations are dummies.
 */
#define	DUMMY			(void *)ocd_con_dummy

const struct consw ocd_con = {
	.owner =		THIS_MODULE,
	.con_startup =		ocd_con_startup,
	.con_init =		ocd_con_init,
	.con_deinit =		DUMMY,
	.con_clear =		DUMMY,
	.con_putc =		ocd_con_putc,
	.con_putcs =		ocd_con_putcs,
	.con_cursor =		DUMMY,
	.con_scroll =		ocd_con_scroll,
	.con_bmove =		DUMMY,
	.con_switch =		DUMMY,
	.con_blank =		DUMMY,
	.con_font_set =		DUMMY,
	.con_font_get =		DUMMY,
	.con_font_default =	DUMMY,
	.con_font_copy =	DUMMY,
	.con_set_palette =	DUMMY,
	.con_scrolldelta =	DUMMY,
};
