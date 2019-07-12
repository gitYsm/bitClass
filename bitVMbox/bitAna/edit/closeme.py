import matplotlib.pyplot as plt
def handle_close(evt):
    print('Closed Figure!')

fig = plt.figure()
fig.canvas.mpl_connect('close_event', cdhandle_close)
plt.text(0.35, 0.5, 'Close Me!', dict(size=50))
plt.show()