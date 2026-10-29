#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Vec3
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

Vec3 operator+(const Vec3& a, const Vec3& b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
Vec3 operator-(const Vec3& a, const Vec3& b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
double dot(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
Vec3 cross(const Vec3& a, const Vec3& b)
{
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
Vec3 normalize(const Vec3& v)
{
    double len = std::sqrt(dot(v, v));
    if (len <= 1e-9) return {0.0, 0.0, 0.0};
    return {v.x / len, v.y / len, v.z / len};
}

static bool project(const Vec3& p, const Vec3& cam, const Vec3& look,
                    const Vec3& right, const Vec3& up, int& sx, int& sy)
{
    Vec3 rel = p - cam;
    double depth = dot(rel, look);
    if (depth <= 0.05) return false;

    double x = 40.0 + (dot(rel, right) / depth) * 26.0;
    double y = 16.0 - (dot(rel, up) / depth) * 18.0;
    sx = static_cast<int>(std::round(x));
    sy = static_cast<int>(std::round(y));
    return true;
}

static void drawLine(std::vector<std::string>& frame, int x1, int y1, int x2, int y2, char ch)
{
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        if (x1 >= 0 && x1 < static_cast<int>(frame[0].size()) &&
            y1 >= 0 && y1 < static_cast<int>(frame.size()))
        {
            frame[y1][x1] = ch;
        }

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

static void drawSegment(std::vector<std::string>& frame, const Vec3& a, const Vec3& b,
                        const Vec3& cam, const Vec3& look, const Vec3& right, const Vec3& up, char ch)
{
    int ax, ay, bx, by;
    if (project(a, cam, look, right, up, ax, ay) &&
        project(b, cam, look, right, up, bx, by))
    {
        drawLine(frame, ax, ay, bx, by, ch);
    }
}

static void render(double yaw, double pitch)
{
    const int W = 80;
    const int H = 32;
    std::vector<std::string> frame(H, std::string(W, ' '));

    const double distance = 7.0;
    Vec3 target{0.0, 0.8, 0.0};
    Vec3 cam{
        std::sin(yaw) * distance,
        1.6 + pitch * 1.2,
        std::cos(yaw) * distance
    };

    Vec3 look = normalize(target - cam);
    Vec3 right = normalize(cross(look, Vec3{0.0, 1.0, 0.0}));
    Vec3 up = normalize(cross(right, look));

    // Floor grid.
    for (double x = -3.0; x <= 3.0; x += 1.5)
        drawSegment(frame, {x, 0.0, -3.0}, {x, 0.0, 3.0}, cam, look, right, up, '+');
    for (double z = -3.0; z <= 3.0; z += 1.5)
        drawSegment(frame, {-3.0, 0.0, z}, {3.0, 0.0, z}, cam, look, right, up, '+');

    // Small block in the scene.
    Vec3 blockCenter{2.0, 0.45, -1.8};
    double s = 0.45;
    Vec3 corners[8] = {
        {blockCenter.x - s, blockCenter.y - s, blockCenter.z - s},
        {blockCenter.x + s, blockCenter.y - s, blockCenter.z - s},
        {blockCenter.x + s, blockCenter.y + s, blockCenter.z - s},
        {blockCenter.x - s, blockCenter.y + s, blockCenter.z - s},
        {blockCenter.x - s, blockCenter.y - s, blockCenter.z + s},
        {blockCenter.x + s, blockCenter.y - s, blockCenter.z + s},
        {blockCenter.x + s, blockCenter.y + s, blockCenter.z + s},
        {blockCenter.x - s, blockCenter.y + s, blockCenter.z + s}
    };
    int edges[12][2] = {
        {0,1},{1,2},{2,3},{3,0},
        {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}
    };
    for (auto& e : edges)
        drawSegment(frame, corners[e[0]], corners[e[1]], cam, look, right, up, '+');

    // Stick figure.
    drawSegment(frame, {0.0, 0.65, 0.0}, {0.0, 1.35, 0.0}, cam, look, right, up, '#');
    drawSegment(frame, {0.0, 1.15, 0.0}, {-0.55, 1.05, 0.0}, cam, look, right, up, '#');
    drawSegment(frame, {0.0, 1.15, 0.0}, {0.55, 1.05, 0.0}, cam, look, right, up, '#');
    drawSegment(frame, {0.0, 0.65, 0.0}, {-0.22, 0.0, 0.0}, cam, look, right, up, '#');
    drawSegment(frame, {0.0, 0.65, 0.0}, {0.22, 0.0, 0.0}, cam, look, right, up, '#');

    int hx, hy;
    if (project({0.0, 1.55, 0.0}, cam, look, right, up, hx, hy))
    {
        if (hx >= 0 && hx < W && hy >= 0 && hy < H) frame[hy][hx] = '@';
    }

    std::cout << "+---- stick-figure smoke test ----+\n";
    for (const auto& row : frame)
    {
        std::cout << row << "\n";
    }
    std::cout << "+----------------------------------+\n";
}

int main()
{
    double yaw = 0.35;
    double pitch = 0.15;

    std::cout << "Commands: a/d rotate view, w/s tilt, q quit.\n";

    std::string line;
    while (true)
    {
        render(yaw, pitch);
        std::cout << "\n";

        if (!std::getline(std::cin, line)) break;
        if (line == "q" || line == "quit") break;

        for (char c : line)
        {
            if (c == 'a') yaw += 0.15;
            else if (c == 'd') yaw -= 0.15;
            else if (c == 'w') pitch += 0.15;
            else if (c == 's') pitch -= 0.15;
        }
    }

    return 0;
}
