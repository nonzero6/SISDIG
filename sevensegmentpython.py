import tkinter as tk
from tkinter import ttk # Themed Tkinter Widget
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

def update_display():
    # Get binary inputs
    w = int(entry_w.get())
    x = int(entry_x.get())
    y = int(entry_y.get())
    z = int(entry_z.get())

    # Determine decimal value
    decimal_value = (w * 8 + x * 4 + y * 2 + z * 1) % 10

    # Seven segment binary mapping
    seven_segment_map = [
        "1111110",  # 0
        "0110000",  # 1
        "1101101",  # 2
        "1111001",  # 3
        "0110011",  # 4
        "1011011",  # 5
        "1011111",  # 6
        "1110000",  # 7
        "1111111",  # 8
        "1111011",  # 9
    ]

    binary_result = seven_segment_map[decimal_value]

    # Update binary result display
    result_label.config(text=f"Hasil Biner: {binary_result}")

    # Draw seven-segment display
    draw_seven_segment(binary_result)

def draw_seven_segment(binary_result):
    ax.clear()
    segments = [
        ((0.2, 0.8), (0.8, 0.8)),  # Top
        ((0.8, 0.8), (0.8, 0.5)),  # Upper-right
        ((0.8, 0.5), (0.8, 0.2)),  # Lower-right
        ((0.2, 0.2), (0.8, 0.2)),  # Bottom
        ((0.2, 0.5), (0.2, 0.2)),  # Lower-left
        ((0.2, 0.8), (0.2, 0.5)),  # Upper-left
        ((0.2, 0.5), (0.8, 0.5)),  # Middle
    ]

    for i, segment in enumerate(segments):
        start, end = segment
        color = "red" if binary_result[i] == "1" else "white"
        ax.plot([start[0], end[0]], [start[1], end[1]], color=color, linewidth=4)

    ax.axis("off")
    ax.set_aspect("equal")
    canvas.draw()

# Create main application window
root = tk.Tk()
root.title("Seven Segment Display")

# Create input frame
input_frame = ttk.LabelFrame(root, text="Masukkan nilai biner untuk w, x, y, z")
input_frame.pack(padx=15, pady=15, fill="x")

# Input fields
entry_w = ttk.Entry(input_frame, width=3)
entry_w.grid(row=0, column=1, padx=5)

entry_x = ttk.Entry(input_frame, width=3)
entry_x.grid(row=0, column=2, padx=5)

entry_y = ttk.Entry(input_frame, width=3)
entry_y.grid(row=0, column=3, padx=5)

entry_z = ttk.Entry(input_frame, width=3)
entry_z.grid(row=0, column=4, padx=5)

# Input labels
label_w = ttk.Label(input_frame, text="w:")
label_w.grid(row=0, column=0, padx=5, sticky="e")

label_x = ttk.Label(input_frame, text="x:")
label_x.grid(row=0, column=1, padx=5, sticky="e")

label_y = ttk.Label(input_frame, text="y:")
label_y.grid(row=0, column=2, padx=5, sticky="e")

label_z = ttk.Label(input_frame, text="z:")
label_z.grid(row=0, column=3, padx=5, sticky="e")

# Button to update display
update_button = ttk.Button(root, text="Tampilkan Seven Segment", command=update_display)
update_button.pack(pady=10)

# Result label
result_label = ttk.Label(root, text="Hasil Biner: 0000000", font=("Arial", 12))
result_label.pack(pady=5)

# Create matplotlib figure
fig, ax = plt.subplots(figsize=(4, 4))
canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack()

# Start application
root.mainloop() 