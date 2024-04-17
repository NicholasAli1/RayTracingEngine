#include "utility.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include <iostream>
using namespace std;



color rayColor(const ray& r, const hittable& world) {
    hitRecord rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unitVector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera
    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);
    auto cameraCenter = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewportWidth, 0, 0);
    auto viewport_v = vec3(0, -viewportHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixelDelta_u = viewport_u / imageWidth;
    auto pixelDelta_v = viewport_v / imageHeight;

    // Calculate the location of the upper left pixel.
    auto viewportUpper_left = cameraCenter - vec3(0, 0, focalLength) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewportUpper_left + 0.5 * (pixelDelta_u + pixelDelta_v);

    // Render
    cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(int j = 0; j < imageHeight; j++) {
        clog << "\rScanlines remaining " << (imageHeight - j) << ' ' << flush;
        for(int i = 0; i < imageWidth; i++) {
            auto pixel_center = pixel00_loc + (i * pixelDelta_u) + (j * pixelDelta_v);
            auto ray_direction = pixel_center - cameraCenter;
            ray r(cameraCenter, ray_direction);

            color pixelColor = rayColor(r, world);
            writeColor(cout, pixelColor);
        }
    }
    clog << "\rDone.                 \n";
}