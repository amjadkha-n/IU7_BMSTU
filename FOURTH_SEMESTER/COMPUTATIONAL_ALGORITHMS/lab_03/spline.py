class PiecewiseSpline():
    """
    Represents a piecewise cubic spline segment.

    Attributes:
        a (float): Coefficient a of the spline segment.
        b (float): Coefficient b of the spline segment.
        c (float): Coefficient c of the spline segment.
        d (float): Coefficient d of the spline segment.
        prev_x (float): Previous x-coordinate for the spline segment.

    Methods:
        count_in_x(self, x): Computes the interpolated value of the spline segment at the given x-coordinate.
    """
    def __init__(self, a, b, c, d, prev_x):
        """
        Initializes the PiecewiseSpline with the specified coefficients and previous x-coordinate.

        Args:
            a (float): Coefficient a of the spline segment.
            b (float): Coefficient b of the spline segment.
            c (float): Coefficient c of the spline segment.
            d (float): Coefficient d of the spline segment.
            prev_x (float): Previous x-coordinate for the spline segment.
        """
        self.a = a
        self.b = b
        self.c = c
        self.d = d
        self.prev_x = prev_x

    def count_in_x(self, x):
        """
        Computes the interpolated value of the spline segment at the given x-coordinate.

        Args:
            x (float): The x-coordinate at which to compute the interpolated value.

        Returns:
            float: The interpolated value of the spline segment at the given x-coordinate.
        """
        return self.a + self.b * (x - self.prev_x) + self.c * (x - self.prev_x) ** 2 + self.d * (x - self.prev_x) ** 3
class Spline():
    """
    Represents a spline interpolation.

    Attributes:
        x (list): List of x-coordinates from the input table.
        y (list): List of corresponding y-coordinates from the input table.
        ledge (float): Left edge condition for the spline.
        redge (float): Right edge condition for the spline.
        splines (list): List of piecewise cubic spline segments.

    Methods:
        build_spline(self): Constructs the spline interpolation based on the input data.
        aproximate_value(self, aprox_x): Computes the interpolated value at the specified x-coordinate.
    """
    def __init__(self, table, ledge, redge):
        """
        Initializes the Spline with the input table and edge conditions.

        Args:
            table (list): Input table containing x, y pairs.
            ledge (float): Left edge condition for the spline.
            redge (float): Right edge condition for the spline.
        """
        self.x = [x[0] for x in table]
        self.y = [y[1] for y in table]
        self.ledge = ledge
        self.redge = redge
        self.splines = []
        self.build_spline()

    def build_spline(self):
        """
        Constructs the spline interpolation based on the input data.
        """
        N = len(self.x)
        h = [self.x[i] - self.x[i - 1] for i in range(1, N)]

        ksi = [0 for _ in range(N - 1)]
        et = [self.ledge / 2 for _ in range(N - 1)]

        for i in range(1, len(ksi)):
            A = h[i - 1]
            B = -2 * (h[i - 1] + h[i])
            D = h[i]
            F = -3 * ((self.y[i + 1] - self.y[i]) / h[i] - (self.y[i] - self.y[i - 1]) / h[i - 1])
            ksi[i] = D / (B - A * ksi[i - 1])
            et[i] = (A * et[i - 1] + F) / (B - A * ksi[i - 1])

        c = [0 for _ in range(N)]
        c[N - 1] = self.redge / 2
        c[0] = self.ledge / 2

        for i in range(len(ksi) - 1, 0, -1):
            c[i] = ksi[i] * c[i + 1] + et[i]

        a = [self.y[i - 1] for i in range(1, N)]
        b = [(self.y[i] - self.y[i - 1]) / h[i - 1] - 1 / 3 * h[i - 1] * (c[i] + 2 * c[i - 1]) for i in range(1, N)]
        d = [(c[i] - c[i - 1]) / (3 * h[i - 1]) for i in range(1, N)]

        for i in range(N - 1):
            self.splines.append(PiecewiseSpline(a[i], b[i], c[i], d[i], self.x[i]))

    def aproximate_value(self, aprox_x):
        """
        Computes the interpolated value at the specified x-coordinate.

        Args:
            aprox_x (float): The x-coordinate for which to compute the interpolated value.

        Returns:
            float: The interpolated value at the specified x-coordinate.
        """
        pos = 0
        for i in range(1, len(self.x)):
            if self.x[i] >= aprox_x:
                break
            else:
                pos += 1

        if pos == 10:
            pos -= 1
        return self.splines[pos].count_in_x(aprox_x)
