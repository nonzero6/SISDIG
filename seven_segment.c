#include <gtk/gtk.h>
#include <cairo.h>
#include <string.h>
#include <stdio.h>

static GtkWidget *window;
static GtkWidget *entry;
static GtkWidget *binary_label;
static GtkWidget *drawing_area;

// Representasi seven-segment untuk angka 0-9 dalam bentuk biner
const char *seven_segment[10] = {
    "11111110",  // 0
    "01100000",  // 1
    "11011010",  // 2
    "11110010",  // 3
    "01100110",  // 4
    "10110110",  // 5
    "10111110",  // 6
    "11100000",  // 7
    "11111110",  // 8
    "11110110",  // 9
};

// Fungsi untuk menggambar angka seven-segment
static void draw_seven_segment(GtkWidget *widget, cairo_t *cr, gpointer data) {
    const char *seg = (const char *)data;
    int x = 10, y = 50;  // Posisi awal untuk menggambar

    // Set warna untuk menggambar segmen yang aktif
    cairo_set_source_rgb(cr, 0, 1, 0); // Warna hijau untuk segmen aktif

    // Gambar tujuh-segment berdasarkan biner
    for (int i = 0; i < 8; i++) {
        if (seg[i] == '1') {
            cairo_rectangle(cr, x, y, 15, 15);  // Ukuran segmen
            cairo_fill(cr);
        }
        x += 20;  // Geser posisi untuk segmen berikutnya
    }
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    if (user_data != NULL) {
        draw_seven_segment(widget, cr, user_data);  // Gambar dengan data
    }
    return FALSE;
}

// Fungsi untuk memperbarui UI berdasarkan input
static void on_input_changed(GtkWidget *widget, gpointer user_data) {
    const char *input_text = gtk_entry_get_text(GTK_ENTRY(entry));
    int len = strlen(input_text);

    if (len == 4) {
        // Input terdiri dari 4 bit (wxyz) untuk menampilkan angka seven-segment
        int input_num = strtol(input_text, NULL, 2);  // Mengonversi input biner ke integer

        if (input_num >= 0 && input_num <= 9) {
            // Update label biner
            gtk_label_set_text(GTK_LABEL(binary_label), input_text);

            // Update gambar seven-segment
            gtk_widget_queue_draw(drawing_area);  // Meminta redraw untuk area gambar
        } else {
            // Jika input tidak valid, reset UI
            gtk_label_set_text(GTK_LABEL(binary_label), "Invalid input");
        }
    } else {
        // Jika panjang input tidak 4 bit
        gtk_label_set_text(GTK_LABEL(binary_label), "Enter 4-bit binary (wxyz)");
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Membuat window baru
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Seven Segment Display");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Membuat box vertikal untuk tata letak
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Membuat entry untuk input angka
    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), 4);  // Membatasi panjang input menjadi 4 bit
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    g_signal_connect(entry, "changed", G_CALLBACK(on_input_changed), NULL);

    // Membuat label untuk menampilkan representasi biner
    binary_label = gtk_label_new("Enter 4-bit binary (wxyz)");
    gtk_box_pack_start(GTK_BOX(vbox), binary_label, FALSE, FALSE, 0);

    // Membuat area gambar untuk menggambar angka seven-segment
    drawing_area = gtk_drawing_area_new();
    gtk_box_pack_start(GTK_BOX(vbox), drawing_area, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), NULL);

    // Menampilkan semua widget
    gtk_widget_show_all(window);

    // Menjalankan loop utama GTK
    gtk_main();

    return 0;
}







