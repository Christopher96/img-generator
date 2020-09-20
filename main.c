#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

void draw_pixel(GdkRGBA color, guint x, guint y, cairo_t *cr) {
    cairo_rectangle (cr, x, y, 1, 1);
    gdk_cairo_set_source_rgba (cr, &color);

    cairo_fill (cr);
}

gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
    GtkStyleContext *context;
    context = gtk_widget_get_style_context (widget);

    guint width = gtk_widget_get_allocated_width (widget);
    guint height = gtk_widget_get_allocated_height (widget);

    gtk_render_background (context, cr, 0, 0, width, height);

    GdkRGBA color = {
        .red = 0.5,
        .blue = 0.5,
        .green = 0.5,
        .alpha = 1
    };


    return FALSE;
}

// gcc main.c -o main `pkg-config --cflags --libs gtk+-3.0`
int main(int argc, char **argv) {
    GtkWidget *window, *drawing_area;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    drawing_area = gtk_drawing_area_new ();
    gtk_widget_set_size_request (drawing_area, 100, 100);
    g_signal_connect (G_OBJECT (drawing_area), "draw", G_CALLBACK (draw_callback), NULL);

    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
