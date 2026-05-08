#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;

    bool operator<(const Point& other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Cross product: (A - O) x (B - O)
double cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y)
         - (A.y - O.y) * (B.x - O.x);
}

// Euclidean distance
double dist(const Point& A, const Point& B) {
    double dx = A.x - B.x;
    double dy = A.y - B.y;
    return sqrt(dx * dx + dy * dy);
}

// Andrew's Monotone Chain Convex Hull
vector<Point> convexHull(vector<Point>& pts) {
    int n = pts.size();

    sort(pts.begin(), pts.end());

    vector<Point> hull(2 * n);

    int k = 0;

    // Lower hull
    for (int i = 0; i < n; i++) {
        while (k >= 2 &&
               cross(hull[k - 2], hull[k - 1], pts[i]) <= 0) {
            k--;
        }
        hull[k++] = pts[i];
    }

    // Upper hull
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t &&
               cross(hull[k - 2], hull[k - 1], pts[i]) <= 0) {
            k--;
        }
        hull[k++] = pts[i];
    }

    hull.resize(k - 1);

    return hull;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Point> points;

    for (int i = 0; i < N; i++) {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        double xmin = min(x1, x2);
        double xmax = max(x1, x2);
        double ymin = min(y1, y2);
        double ymax = max(y1, y2);

        // Add 4 corners
        points.push_back({xmin, ymin});
        points.push_back({xmin, ymax});
        points.push_back({xmax, ymin});
        points.push_back({xmax, ymax});
    }

    // Remove duplicate points
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());

    // Compute convex hull
    vector<Point> hull = convexHull(points);

    // Compute perimeter
    double perimeter = 0.0;

    int m = hull.size();

    for (int i = 0; i < m; i++) {
        perimeter += dist(hull[i], hull[(i + 1) % m]);
    }

    cout << fixed << setprecision(10) << perimeter << '\n';

    return 0;
}