import tkinter as tk
import requests
from bs4 import BeautifulSoup
import re
from tkinter import messagebox
from tkinter import ttk
import webview


class MiniBrowser(tk.Frame):
    def __init__(self, parent):
        tk.Frame.__init__(self, parent)
        self.parent = parent
        self.initUI()

    def initUI(self):
        self.parent.title("Mini Browser")

        # Создаем поле для ввода URL-адреса
        self.url_entry = ttk.Entry(self.parent, width=50)
        self.url_entry.pack(side=tk.TOP, padx=10, pady=10)

        # Создаем кнопку "Открыть"
        self.open_button = ttk.Button(
            self.parent, text="Открыть", command=self.open_url)
        self.open_button.pack(side=tk.TOP, padx=10, pady=10)

        # Создаем текстовое поле для отображения HTML-страницы
        self.html_text = tk.Text(self.parent, height=30, width=80)
        self.html_text.pack(side=tk.TOP, padx=10, pady=10)

        # Создаем кнопки для навигации
        self.back_button = ttk.Button(
            self.parent, text="Назад", command=self.back)
        self.back_button.pack(side=tk.LEFT, padx=10, pady=10)

        self.forward_button = ttk.Button(
            self.parent, text="Вперед", command=self.forward)
        self.forward_button.pack(side=tk.LEFT, padx=10, pady=10)

        # Создаем кнопку для сохранения страницы
        self.save_button = ttk.Button(
            self.parent, text="Сохранить", command=self.save)
        self.save_button.pack(side=tk.LEFT, padx=10, pady=10)

    def open_url(self):
        url = self.url_entry.get()

        # Отправляем HTTP-запрос и получаем HTML-страницу
        response = requests.get(url)
        html = response.text

        # Парсим HTML-страницу с помощью BeautifulSoup
        soup = BeautifulSoup(html, 'html.parser')
        self.html_text.delete('1.0', tk.END)
        self.html_text.insert(tk.END, soup.prettify())

    def back(self):
        pass

    def forward(self):
        pass

    def save(self):
        pass


if __name__ == '__main__':
    root = tk.Tk()
    app = MiniBrowser(root)
    app.pack(fill=tk.BOTH, expand=True)
    root.mainloop()
