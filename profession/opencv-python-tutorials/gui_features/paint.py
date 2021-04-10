import cv2
import numpy as np


class PaintApp:
    """ A simple Paint application. """

    def __init__(self, config):
        self.config = config
        self.window_name = self.config.window_name
        self.canvas = self._get_init_canvas(self.config.canvas_shape)
        cv2.namedWindow(self.window_name)

        self.color = self.config.default_color
        self.brush_size = self.config.default_brush_size

        self.drawing = False  # true if the mouse is pressed
        self._ix, self._iy = -1, -1
        self.cache = []

        self.set_callbacks()

    def _get_init_canvas(self, shape):
        img = np.ones(shape, dtype=np.uint8) * 255
        return img

    def _update_cache(self, canvas):
        if len(self.cache) >= self.config.max_cache_history:
            self.cache.pop(0)

        self.cache.append(canvas)

    def undo(self):
        if len(self.cache) > 0:
            self.canvas = self.cache.pop(-1)

    def draw(self, event, x, y, flags, param):
        if event == cv2.EVENT_LBUTTONDOWN:
            self._update_cache(self.canvas.copy())
            self.drawing = True
            cv2.circle(self.canvas, (x, y), self.brush_size // 2, self.color, -1)
            self._ix, self._iy = x, y
        elif event == cv2.EVENT_MOUSEMOVE:
            if self.drawing:
                cv2.line(self.canvas, (self._ix, self._iy), (x, y), self.color, self.brush_size, lineType=cv2.LINE_AA)
                self._ix, self._iy = x, y
        elif event == cv2.EVENT_LBUTTONUP:
            self.drawing = False

    def change_color(self, x):
        r = cv2.getTrackbarPos("R", self.window_name)
        g = cv2.getTrackbarPos("G", self.window_name)
        b = cv2.getTrackbarPos("B", self.window_name)
        self.color = (b, g, r)

    def change_brush_size(self, x):

        brush_trackbar_value = cv2.getTrackbarPos("Brush Size", self.window_name)

        if brush_trackbar_value <= 0:
            self.brush_size = 1
        else:
            self.brush_size = brush_trackbar_value

    def set_callbacks(self):
        # set mouse callback to draw
        cv2.setMouseCallback(self.window_name, self.draw)

        # create trackbars for color change
        cv2.createTrackbar("R", self.window_name, self.color[2], 255, self.change_color)
        cv2.createTrackbar("G", self.window_name, self.color[1], 255, self.change_color)
        cv2.createTrackbar("B", self.window_name, self.color[0], 255, self.change_color)

        # create trackbar for brush radius change
        cv2.createTrackbar(
            "Brush Size", self.window_name, self.brush_size, self.config.max_brush_size, self.change_brush_size
        )

    def show(self):
        cv2.imshow(self.window_name, self.canvas)

    def release(self):
        cv2.destroyAllWindows()

    def run(self):
        while True:
            self.show()

            k = cv2.waitKey(self.config.refresh_frame_interval) & 0xFF

            if k == ord("r"):
                # press 'r' to reset the canvas
                self._update_cache(self.canvas)
                self.canvas = self._get_init_canvas(self.config.canvas_shape)
            elif k == ord("u"):
                # press 'u' to undo the drawing
                self.undo()
            elif k == ord("+"):
                # press '+' to increase the brush size
                self.brush_size += 1
                self.brush_size = min(self.brush_size, self.config.max_brush_size)
                cv2.setTrackbarPos("Brush Size", self.window_name, self.brush_size)
            elif k == ord("-"):
                # press '-' to increase the brush size
                self.brush_size -= 1
                self.brush_size = max(self.brush_size, self.config.min_brush_size)
                cv2.setTrackbarPos("Brush Size", self.window_name, self.brush_size)
            elif k == 27:
                # press 'Esc' to quit the demo
                break

        self.release()


class PaintAppConfig:
    """ The config for the Paint application. """

    def __init__(self):
        self.window_name = "paint"
        self.canvas_shape = (512, 512, 3)
        self.default_color = (0, 0, 0)
        self.default_brush_size = 5
        self.min_brush_size = 1
        self.max_brush_size = 100
        self.refresh_frame_interval = 1
        self.max_cache_history = 50


if __name__ == "__main__":
    config = PaintAppConfig()
    app = PaintApp(config)
    app.run()
