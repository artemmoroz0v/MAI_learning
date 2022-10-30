import PySimpleGUI as sg
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
def draw(apr):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    # Make data
    u = np.linspace(0, 2 * np.pi, apr)
    v = np.linspace(0, np.pi, apr)
    x = np.outer(np.cos(u), np.sin(v))
    y = np.outer(np.sin(u), np.sin(v))
    z = np.outer(np.ones(np.size(u)), np.cos(v))
    # Plot the surface
    ax.plot_surface(x, y, z, color='g')
    plt.show()
layout = [
    [sg.Slider(orientation ='horizontal', key='slider', range=(20,1000))],
    [sg.Button('Exit'), sg.Button('Draw'), sg.Button('Show previous values')]]
window = sg.Window('___Setting window___', layout)
store = []
while True:
    event, values = window.read()
    if event in (sg.WIN_CLOSED, 'Exit'):
        break
    elif event == 'Draw':
        draw(int(values['slider']))
        if int(values['slider']) in store:
            continue
        else:
            store.append(int(values['slider']))
    elif event == 'Show previous values':
        print(store)
window.close()
