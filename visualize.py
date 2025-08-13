import numpy as np
import matplotlib
matplotlib.use('Qt5Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def load_points_from_file(filename):
    try:
        points = np.loadtxt(filename)
        if points.ndim == 1:
            points = points.reshape(1, -1)
        return points
    except IOError:
        print(f"File {filename} hasn't been found.")
        return np.empty((0, 3))
    except ValueError as e:
        print(f"File format error in {filename}: {str(e)}.")
        return np.empty((0, 3))
    except Exception as e:
        print(f"Unexpected error in {filename}: {str(e)}.")
        return np.empty((0, 3))

plane_points = np.array([
    [0.5, -0.3300, 0.9830],    # Plane №1
    [0.5, -0.3300, 0.2269],
    [-0.5, -0.3300, 0.2269],
    [0.06159, -0.6232, 0.9830], # Plane №2
    [0.31881, 0.43885, 0.9830],
    [0.6643, 0.3551, -0.2269]
])

file_points1 = load_points_from_file('points_wrong.txt')
file_points2 = load_points_from_file('points_good.txt')

fig = plt.figure(figsize=(20, 10))

ax1 = fig.add_subplot(121, projection='3d')
ax1.set_title("График 1: Ложные точки")

ax2 = fig.add_subplot(122, projection='3d')
ax2.set_title("График 2: Валидные точки")

def plot_scene(ax, file_points, elevation, azimut, filename):
    ax.scatter(plane_points[:3,0], plane_points[:3,1], plane_points[:3,2], 
               c='red', s=100, label='Точки плоскости 1')
    ax.scatter(plane_points[3:,0], plane_points[3:,1], plane_points[3:,2], 
               c='blue', s=100, label='Точки плоскости 2')

    if len(file_points) > 0:
        ax.scatter(file_points[:,0], file_points[:,1], file_points[:,2], 
                   c='green', s=1, alpha=0.7, label=f'Точки из файла {filename}')

    y_val = -0.3300
    xx, zz = np.meshgrid(np.linspace(-1, 1, 10), np.linspace(-1, 1, 10))
    yy = np.full_like(xx, y_val)
    ax.plot_surface(xx, yy, zz, color='red', alpha=0.2)

    p1, p2, p3 = plane_points[3:6]
    v1 = p2 - p1
    v2 = p3 - p1
    cp = np.cross(v1, v2)
    a, b, c = cp

    if np.allclose(cp, 0):
        print("Points are collinear, a plane can't be formed.")
    else:
        d = -np.dot(cp, p1)
        
        if np.isclose(a, 0, atol=1e-6) and np.isclose(b, 0, atol=1e-6):
            # Parralel to XY
            z_val = p1[2]
            xx, yy = np.meshgrid(np.linspace(-1, 1, 10), np.linspace(-1, 1, 10))
            zz = np.full_like(xx, z_val)
        elif np.isclose(a, 0, atol=1e-6):
            # Parallel to X
            yy, zz = np.meshgrid(np.linspace(-1, 1, 10), np.linspace(-1, 1, 10))
            xx = (-b * yy - c * zz - d) / a if not np.isclose(a, 0) else np.zeros_like(yy)
        else:
            # Default case
            xx, yy = np.meshgrid(np.linspace(-1, 1, 10), np.linspace(-1, 1, 10))
            zz = (-a * xx - b * yy - d) / c
        
        ax.plot_surface(xx, yy, zz, color='blue', alpha=0.2)

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.legend()
    ax.view_init(elev=elevation, azim=azimut)

plot_scene(ax1, file_points1, 31, 177, 'points_wrong.txt')
plot_scene(ax2, file_points2, 41, 177, 'points_good.txt')

plt.tight_layout(rect=[0.008, 0.015, 0.993, 0.963], h_pad=0.2, w_pad=0.008)
plt.show()