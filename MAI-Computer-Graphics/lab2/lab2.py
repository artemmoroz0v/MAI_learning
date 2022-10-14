import PySimpleGUI as sg
import matplotlib.pyplot as plt
import numpy as np
def draw_plot(a=2, b=3, c=4):
    list_tmp = [a, b, c]
    list_tmp.sort()
    x, y, z = np.indices((list_tmp[2] + 3, list_tmp[2] + 3, list_tmp[2] + 3))
    cube1 = (x < a + 2) & (y < b + 2) & (z < c + 2) & (1 < x) & (1 < y) & (1 < z)
    colors = np.empty(cube1.shape, dtype=object)
    colors[cube1] = 'blue'
    ax = plt.figure().add_subplot(projection='3d')
    ax.voxels(cube1, facecolors=colors, edgecolor='r')
    plt.show()
layout = [
    [sg.Text('Length (a):'), sg.InputText()],
    [sg.Text('Weight (b):'), sg.InputText()],
    [sg.Text('Height (c):'), sg.InputText()],
    [sg.Button('Plot'), sg.Button('Exit'), sg.Button('Enter')]]
window = sg.Window('___Setting window___', layout)
while True:
    event, values = window.read()
    if event in (sg.WIN_CLOSED, 'Exit'):
        break
    elif event == 'Plot':
        draw_plot()
    elif event == 'Enter':
        draw_plot(int(values[0]), int(values[1]), int(values[2]))
window.close()
