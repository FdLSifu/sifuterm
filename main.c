#include <vte/vte.h>

#define TERM_FONT "SF Mono Regular 14"

static void set_font(VteTerminal *terminal)
{
	PangoFontDescription *descr;
	if ((descr = pango_font_description_from_string(TERM_FONT)) == NULL)
		return;

	vte_terminal_set_font(terminal, descr);
	pango_font_description_free(descr);
}

int main(int argc, char *argv[])
{
	GtkWidget *window, *terminal;

	/* Initialise GTK, the window and the terminal */
	gtk_init(&argc, &argv);
	terminal = vte_terminal_new();
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "myterm");

	/* Start a new shell */
	gchar **envp = g_get_environ();
	gchar **command = (gchar *[]){g_strdup(g_environ_getenv(envp, "SHELL")), NULL };
	g_strfreev(envp);
	vte_terminal_spawn_sync(VTE_TERMINAL(terminal),
			VTE_PTY_DEFAULT,
			NULL,       /* working directory  */
			command,    /* command */
			NULL,       /* environment */
			0,          /* spawn flags */
			NULL, NULL, /* child setup */
			NULL,       /* child pid */
			NULL, NULL);


	/* Configure temrinal */
	// unlimited scrollback
	vte_terminal_set_scrollback_lines(VTE_TERMINAL(terminal),-1);
	// Set font
	set_font(VTE_TERMINAL(terminal));

	/* Connect some signals */
	g_signal_connect(window, "delete-event", gtk_main_quit, NULL);
	g_signal_connect(terminal, "child-exited", gtk_main_quit, NULL);

	/* Put widgets together and run the main loop */
	gtk_container_add(GTK_CONTAINER(window), terminal);
	gtk_widget_show_all(window);
	gtk_main();
}

