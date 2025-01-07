import tkinter as tk
import tensorflow as tf
from tkinter import Canvas, Button, Text, PhotoImage
from PIL import Image, ImageDraw, ImageOps
import numpy as np
from keras.models import load_model
import pyperclip
import logging

def configure_logging():
    logging.basicConfig(filename='debug.log', level=logging.DEBUG)

class DigitRecognizerApp:
    def __init__(self, root):
        configure_logging()
        self.root = root
        self.root.title("简单数字手写识别")

        # 创建画布
        self.canvas = Canvas(root, width=280, height=280, bg="white")
        self.canvas.pack()

        # 创建Copy按钮
        self.copy_button = Button(root, text="Copy", command=self.copy_text)
        self.copy_button.pack(side=tk.LEFT)

        # 创建清除按钮
        self.clear_button = Button(root, text="Clear", command=self.clear_text)
        self.clear_button.pack(side=tk.RIGHT)

        # 创建Backspace按钮
        self.backspace_button = Button(root, text="Backspace", command=self.backspace)
        self.backspace_button.pack(side=tk.RIGHT)

        # 创建提交按钮
        self.submit_button = Button(root, text="Submit", command=self.submit_button)
        self.submit_button.pack(side=tk.BOTTOM)

        # 创建文本框
        self.result_text = Text(root, height=2, width=30, font=("Helvetica", 16))
        self.result_text.pack(side=tk.TOP, anchor=tk.CENTER)
        self.result_text.pack(side=tk.LEFT, anchor=tk.CENTER)

        self.canvas.bind("<B1-Motion>", self.draw)
        self.canvas.bind("<ButtonRelease-1>", self.start_timer)

        self.image = Image.new("L", (280, 280), color="white")
        self.draw = ImageDraw.Draw(self.image)

        self.timer_id = None

        root.resizable(False, False)


    def draw(self, event):
        x1, y1 = (event.x - 1), (event.y - 1)
        x2, y2 = (event.x + 1), (event.y + 1)
        self.canvas.create_oval(x1, y1, x2, y2, fill="black", width=10)
        self.draw.line([x1, y1, x2, y2], fill="black", width=10)

        if self.timer_id:
            self.root.after_cancel(self.timer_id)
        self.timer_id = self.root.after(1000, self.submit_canvas)

    def start_timer(self, event):
        if self.timer_id:
            self.root.after_cancel(self.timer_id)
        self.timer_id = self.root.after(1000, self.submit_canvas)

    def clear_text(self):   # 清除文本框内容
        self.result_text.delete("1.0", tk.END)

    def submit_canvas(self):
        self.image = ImageOps.invert(self.image)
        img_resized = self.image.resize((28, 28))
        img_array = np.array(img_resized)
        img_array = img_array.reshape(1, 28, 28, 1)
        img_array = img_array.astype('float32') / 255.0

        # 进行数字识别
        prediction = model.predict(img_array)
        predicted_label = np.argmax(prediction)

        # 显示识别结果
        result_text = f"{predicted_label}"
        self.result_text.insert(tk.END, result_text)

        self.clear_canvas()

    def clear_canvas(self):     # 清除画布
        self.canvas.delete("all")
        self.image = Image.new("L", (280, 280), color="white")
        self.draw = ImageDraw.Draw(self.image)

    def backspace(self):    # 清除最后一个字符
        current_text = self.result_text.get("1.0", tk.END)
        updated_text = current_text[:-2]  # 删除最后一个字符和换行符
        self.result_text.delete("1.0", tk.END)
        self.result_text.insert(tk.END, updated_text)

    def copy_text(self):    # 复制文本框内容到剪贴板
        copied_text = self.result_text.get("1.0", tk.END).strip()
        pyperclip.copy(copied_text)

    def submit_button(self):
        self.submit_canvas()

# 创建主窗口
if __name__ == "__main__":
    model = load_model("mnist_model.h5")
    configure_logging()
    root = tk.Tk()
    root.geometry("550x350")
    app = DigitRecognizerApp(root)
    root.mainloop()
