/* A very basic raytracer example.

from Scratchapixel at
https://www.scratchapixel.com/code.php?id=3

Instructions to compile this program:
c++ -o raytracer -O3 -Wall raytracer.cpp */
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>

// Windows doesn't define these values by default, Linux does
#if defined __linux__ || defined __APPLE__ || defined __CYGWIN__
// already defined
#else
#define M_PI 3.141592653589793
#define INFINITY 1e8
#endif

#define MAX_RAY_DEPTH 10    // This variable controls the maximum recursion depth

template<typename T>
class Vec3
{
public:
    T x, y, z;
    Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
    Vec3(T xx) : x(xx), y(xx), z(xx) {}
    Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

    Vec3& normalize()
    {
        T nor2 = length2();
        if (nor2 > 0)
        {
            T invNor = 1 / sqrt(nor2);
            x *= invNor, y *= invNor, z *= invNor;
        }

        return *this;
    }

    Vec3<T> operator * (const T &f) const
    {
        return Vec3<T>(x * f, y * f, z * f);
    }

    Vec3<T> operator * (const Vec3<T> &v) const
    {
        return Vec3<T>(x * v.x, y * v.y, z * v.z);
    }

    T dot(const Vec3<T> &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    Vec3<T> operator - (const Vec3<T> &v) const
    {
        return Vec3<T>(x - v.x, y - v.y, z - v.z);
    }

    Vec3<T> operator + (const Vec3<T> &v) const
    {
        return Vec3<T>(x + v.x, y + v.y, z + v.z);
    }

    Vec3<T>& operator += (const Vec3<T> &v)
    {
        x += v.x, y += v.y, z += v.z; return *this;
    }

    Vec3<T>& operator *= (const Vec3<T> &v)
    {
        x *= v.x, y *= v.y, z *= v.z; return *this;
    }

    Vec3<T> operator - () const
    {
        return Vec3<T>(-x, -y, -z);
    }

    T length2() const
    {
        return x * x + y * y + z * z;
    }

    T length() const
    {
        return sqrt(length2());
    }

    friend std::ostream & operator << (std::ostream &os, const Vec3<T> &v)
    {
        os << "[" << v.x << " " << v.y << " " << v.z << "]";
        return os;
    }
};

typedef Vec3<float> Vec3f;

class Sphere
{
public:
    Vec3f center;                       // position of the sphere
    float radius, radius2;              // sphere radius and radius^2
    Vec3f surfaceColor, emissionColor;  // surface color and emission (light)
    float transparency, reflection;     // surface transparency and reflectivity

    Sphere( const Vec3f &c, const float &r, const Vec3f &sc, const float &refl = 0, const float &transp = 0, const Vec3f &ec = 0)
    {
        center = c;
        radius = r;
        radius2 = r * r;
        surfaceColor = sc;
        emissionColor = ec;
        transparency = transp;
        reflection=  refl;
    }

    // Compute a ray-sphere intersection using the geometric solution
    bool intersect(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const 
    {
        Vec3f l = center - rayorig;
        float tca = l.dot(raydir);
        if (tca < 0) return false;
        float d2 = l.dot(l) - tca * tca;
        if (d2 > radius2) return false;
        float thc = sqrt(radius2 - d2);
        t0 = tca - thc;
        t1 = tca + thc;
        return true;
    }
};

float mix(const float &a, const float &b, const float &mix)
{
    return b * mix + a * (1 - mix);
}

/* This is the main trace function. It takes a ray as argument (defined by its
origin and direction). We test if this ray intersects any of the geometry in the
scene. If the ray intersects an object, we compute the intersection point, the
normal at the intersection point, and shade this point using this information.
Shading depends on the surface property (is it transparent, reflective,
diffuse). The function returns a color for the ray. If the ray intersects an
object that is the color of the object at the intersection point, otherwise it
returns the background color. */
Vec3f trace( const Vec3f &rayorig, const Vec3f &raydir, const std::vector<Sphere> &spheres, const int &depth ) 
{
    float tnear = INFINITY;
    const Sphere* sphere = NULL;

    // find intersection of this ray with the sphere in the scene
    for (unsigned i = 0; i < spheres.size(); ++i)
    {
        float t0 = INFINITY, t1 = INFINITY;
        if (spheres[i].intersect(rayorig, raydir, t0, t1))
        {
            if (t0 < 0)
            {
                t0 = t1;
            }

            if (t0 < tnear)
            {
                tnear = t0;
                sphere = &spheres[i];
            }
        }
    }

    // if there's no intersection return black or background color
    if (!sphere)
    {
        // return Vec3f(0);
        return Vec3f(3);
    }

    // color of the ray, i.e., surface of the object intersected by the ray
    Vec3f surfaceColor = 0;
    Vec3f phit = rayorig + raydir * tnear;              // point of intersection
    Vec3f nhit = phit - sphere->center;      // normal at the intersection point
    nhit.normalize();                              // normalize normal direction
    // If the normal and the view direction are not opposite to each other
    // reverse the normal direction. That also means we are inside the sphere so
    // set the inside bool to true. Finally reverse the sign of IdotN which we
    // want positive.
    // add some bias to the point from which we will be tracing
    float bias = 1e-4;
    bool inside = false;
    if (raydir.dot(nhit) > 0)
    {
        nhit = -nhit, inside = true;
    }

    if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH) 
    {
        float facingratio = -raydir.dot(nhit);
        // change the mix value to tweak the effect
        float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
        // compute reflection direction (not need to normalize because all
        // vectors are already normalized)
        Vec3f refldir = raydir - nhit * 2 * raydir.dot(nhit);
        refldir.normalize();
        Vec3f reflection = trace(phit + nhit * bias, refldir, spheres, depth + 1) * sphere->reflection;
        Vec3f refraction = 0;

        // if the sphere is transparent compute refraction ray (transmission)
        if (sphere->transparency)
        {
            // are we inside or outside the surface?
            float ior = 1.1, eta = (inside) ? ior : 1 / ior;
            float cosi = -nhit.dot(raydir);
            float k = 1 - eta * eta * (1 - cosi * cosi);
            Vec3f refrdir = raydir * eta + nhit * (eta *  cosi - sqrt(k));
            refrdir.normalize();
            refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1);
        }

        // the result is a mix of reflection and refraction
        surfaceColor = sphere->surfaceColor * ( reflection * fresneleffect + refraction * (1 - fresneleffect) * sphere->transparency);
    }
    else
    {
        // it's a diffuse object, no need to raytrace any further
        for (unsigned i = 0; i < spheres.size(); ++i)
        {
            if (spheres[i].emissionColor.x > 0)
            {
                Vec3f transmission = 1;                       // this is a light
                Vec3f lightDirection = spheres[i].center - phit;
                lightDirection.normalize();
                for (unsigned j = 0; j < spheres.size(); ++j)
                {
                    if (i != j)
                    {
                        float t0, t1;
                        if (spheres[j].intersect(phit + nhit * bias, lightDirection, t0, t1)) 
                        {
                            transmission = 0;
                            break;
                        }
                    }
                }

                surfaceColor += sphere->surfaceColor * transmission *
                                    std::max(float(0), nhit.dot(lightDirection)) * 
                                    spheres[i].emissionColor;
            }
        }
    }

    return surfaceColor + sphere->emissionColor;
}

void writeBitmap(const std::string path, const int width, const int height, const u_char* imgData)
{
    const int pad = (4 - (3 * width) % 4) % 4;
    const int filesize = 54 + (3 * width + pad) * height; // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
    char header[54] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0, 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
    for (int i = 0; i < 4; i++)
    {
        header[ 2+i] = (char)((filesize>>(8 * i)) & 255);
        header[18+i] = (char)((width   >>(8 * i)) & 255);
        header[22+i] = (char)((height  >>(8 * i)) & 255);
    }

    char* img = new char[filesize];
    for (int i = 0; i < 54; i++)
    {
        img[i] = header[i];
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            const int ii = 3 * (x + y * width);
            const int i = 54 + 3 * x + y * (3 * width + pad);
            img[i    ] = (char)(imgData[ii + 0]);
            img[i + 1] = (char)(imgData[ii + 1]);
            img[i + 2] = (char)(imgData[ii + 2]);
        }

        for (int p = 0; p < pad; p++)
        {
            img[54 + (3 * width + p) + y * (3 * width + pad)] = 0;
        }
    }

    std::fstream file(path, std::ios::out | std::ios::binary);
    file.write(img, filesize);
    file.close();
    delete[] img;
}

/* Main rendering function. We compute a camera ray for each pixel of the image
trace it and return a color. If the ray hits a sphere, we return the color of
the sphere at the intersection point, else we return the background color.*/
void render(const std::vector<Sphere> &spheres)
{
    unsigned width = 1920, height = 1080;
    // unsigned width = 800, height = 600;
    // unsigned width = 640, height = 480;

    Vec3f *image = new Vec3f[width * height], *pixel = image;

    float invWidth = 1 / float(width), invHeight = 1 / float(height);
    float fov = 30, aspectratio = width / float(height);
    float angle = tan(M_PI * 0.5 * fov / 180.);

    // Trace rays
    for (unsigned y = 0; y < height; ++y)
    {
        std::cout << "\rTracing line " << (y + 1) << " / " << height;

        for (unsigned x = 0; x < width; ++x, ++pixel)
        {
            float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
            float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
            Vec3f raydir(xx, yy, -1);
            raydir.normalize();
            *pixel = trace(Vec3f(0), raydir, spheres, 0);
        }
    }

    std::cout << std::endl << "Done Tracing" << std::endl;

    u_char* imgData = new u_char[3 * width * height];

    unsigned int i = 0;
    for (unsigned y = 0; y < height; y++)
    {
        for (unsigned x = 0; x < width; x++)
        {
            imgData[3 * (x + y * width) + 2] = (u_char)(std::min(float(1), image[i].x) * 255.0f);
            imgData[3 * (x + y * width) + 1] = (u_char)(std::min(float(1), image[i].y) * 255.0f);
            imgData[3 * (x + y * width) + 0] = (u_char)(std::min(float(1), image[i].z) * 255.0f);

            i++;
        }
    }

    std::cout << "Writing Bitmap" << std::endl;

    writeBitmap("raytracer.bmp", width, height, imgData);

    delete [] imgData;
    delete [] image;

    std::cout << "Done" << std::endl;
}

/* In the main function, we will create the scene which is composed of 5 spheres
and 1 light (which is also a sphere). Then, once the scene description is
complete we render that scene, by calling the render() function.*/
int main(int argc, char **argv)
{
    std::vector<Sphere> spheres;

    // position, radius, surface color, reflectivity, transparency, emission color

    // light
    spheres.push_back( Sphere( Vec3f( 0.0,     20, 30),     3,     Vec3f( 0.00, 0.00, 0.00 ), 0, 0.0, Vec3f( 1 ) ) );

    // ground
    spheres.push_back( Sphere( Vec3f( 0.0, -10004, -20), 10000,     Vec3f( 0.0, 1.0, 0.5 ), 0.0, 0.0 ) );

    // scene
    spheres.push_back( Sphere( Vec3f( -8.0,   0, -30),     2,   Vec3f(1.00, 0.00, 0.00), 0.9, 0.0));

    spheres.push_back( Sphere( Vec3f( -4.0,   0, -30),     2,   Vec3f(0.00, 1.00, 0.00), 0.9, 0.0));

    spheres.push_back( Sphere( Vec3f( 0.0,    0, -30),     2,   Vec3f(0.00, 0.00, 1.00), 0.9, 0.0));

    spheres.push_back( Sphere( Vec3f( 4.0,    0, -30),     2,   Vec3f(1.00, 0.00, 1.00), 0.9, 0.0));

    spheres.push_back( Sphere( Vec3f( 8.0,    0, -30),     2,   Vec3f(0.50, 0.50, 0.50), 0.9, 0.0));

    // render scene
    render(spheres);

    return 0;
}
