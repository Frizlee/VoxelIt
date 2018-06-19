#include <VoxelIt/MeshShapeConverter.hpp>
#include <fstream>
#include <unordered_set>
using namespace vit;
using namespace std;
using glm::vec2;
using glm::vec3;
using glm::tvec3;
using glm::vec4;
using glm::tvec4;
using glm::dot;

MeshShapeConverter::MeshShapeConverter(float voxelSize, bool overrideSize)
    : mVoxelSize(voxelSize), mOverrideSize(overrideSize)
{
}

shared_ptr<Shape> VOXELIT_API MeshShapeConverter::getShapeFromMesh(shared_ptr<const Mesh> mesh)
{
    unordered_set<Voxel> voxels;
    auto bBox = mesh->getBoundingBox();
    auto faces = mesh->getFaces();
    auto vertices = mesh->getVertices();
    bBox.lower -= vec3(mVoxelSize, mVoxelSize, mVoxelSize);
    bBox.upper += vec3(mVoxelSize, mVoxelSize, mVoxelSize);
    tvec3<int32_t> planesLower = bBox.lower / mVoxelSize;
    tvec3<int32_t> planesUpper = bBox.upper / mVoxelSize;
    int32_t width = planesUpper.x - planesLower.x;
    int32_t height = planesUpper.y - planesLower.y;
    int32_t depth = planesUpper.z - planesLower.z;
    vector<uint8_t> xyPlane(width * height);
    vector<uint8_t> zyPlane(depth * height);
    vector<uint8_t> xzPlane(width * depth);

    int32_t xyCount = 0;
    int32_t zyCount = 0;
    int32_t xzCount = 0;
    int i = 0;

    for (auto& face : faces)
    {
        if (face.getIndexCount() != 3)
            throw runtime_error("Unsupported mesh format");

        // clear planes
        fill(begin(xyPlane), end(xyPlane), 0);
        fill(begin(zyPlane), end(zyPlane), 0);
        fill(begin(xzPlane), end(xzPlane), 0);
        xyCount = 0;
        zyCount = 0;
        xzCount = 0;

        auto indices = face.getIndices();
        auto a = vertices[indices[0]].getPosition();
        auto b = vertices[indices[1]].getPosition();
        auto c = vertices[indices[2]].getPosition();

        // xy Plane
        tvec4<int32_t> xyBBox = (getTriangleBoundingBox({ a.x, a.y }, { b.x, b.y }, { c.x, c.y })
            + vec4(-mVoxelSize, -mVoxelSize, mVoxelSize, mVoxelSize)) / mVoxelSize;

        for (int32_t j = xyBBox.y; j < xyBBox.w; ++j)
        {
            for (int32_t i = xyBBox.x; i < xyBBox.z; ++i)
            {
                auto rectOrig = vec2(i * mVoxelSize, j * mVoxelSize);

                if (checkIntersect(rectOrig, mVoxelSize, vec2(a.x, a.y), vec2(b.x, b.y), vec2(c.x, c.y)))
                {
                    xyPlane[(j - planesLower.y) * width + (i - planesLower.x)] = 1;
                    ++xyCount;
                }
            }
        }

        // zy Plane
        tvec4<int32_t> zyBBox = (getTriangleBoundingBox({ a.z, a.y }, { b.z, b.y }, { c.z, c.y })
            + vec4(-mVoxelSize, -mVoxelSize, mVoxelSize, mVoxelSize)) / mVoxelSize;

        for (int32_t j = zyBBox.y; j < zyBBox.w; ++j)
        {
            for (int32_t i = zyBBox.x; i < zyBBox.z; ++i)
            {
                auto rectOrig = vec2(i * mVoxelSize, j * mVoxelSize);

                if (checkIntersect(rectOrig, mVoxelSize, vec2(a.z, a.y), vec2(b.z, b.y), vec2(c.z, c.y)))
                {
                    zyPlane[(j - planesLower.y) * depth + (i - planesLower.z)] = 1;
                    ++zyCount;
                }
            }
        }

        // xz Plane
        tvec4<int32_t> xzBBox = (getTriangleBoundingBox({ a.x, a.z }, { b.x, b.z }, { c.x, c.z })
            + vec4(-mVoxelSize, -mVoxelSize, mVoxelSize, mVoxelSize)) / mVoxelSize;

        for (int32_t j = xzBBox.y; j < xzBBox.w; ++j)
        {
            for (int32_t i = xzBBox.x; i < xzBBox.z; ++i)
            {
                auto rectOrig = vec2(i * mVoxelSize, j * mVoxelSize);

                if (checkIntersect(rectOrig, mVoxelSize, vec2(a.x, a.z), vec2(b.x, b.z), vec2(c.x, c.z)))
                {
                    xzPlane[(j - planesLower.z) * width + (i - planesLower.x)] = 1;
                    ++xzCount;
                }
            }
        }


        // Create voxels.
        if (xyCount >= zyCount && xyCount >= xzCount)
        {
            for (int32_t j = xyBBox.y; j < xyBBox.w; ++j)
            {
                for (int32_t i = xyBBox.x; i < xyBBox.z; ++i)
                {
                    if (xyPlane[(j - planesLower.y) * width + (i - planesLower.x)] != 1)
                        continue;

                    int32_t z = planeFunc(a, b, c, i * mVoxelSize, j * mVoxelSize, mVoxelSize) / mVoxelSize;
                    voxels.insert(Voxel({ i, j, z }));
                }
            }
        }
        else if (zyCount >= xyCount && zyCount >= xzCount)
        {
            for (int32_t j = zyBBox.y; j < zyBBox.w; ++j)
            {
                for (int32_t i = zyBBox.x; i < zyBBox.z; ++i)
                {
                    if (zyPlane[(j - planesLower.y) * depth + (i - planesLower.z)] != 1)
                        continue;

                    auto newA = vec3(a.z, a.y, a.x);
                    auto newB = vec3(b.z, b.y, b.x);
                    auto newC = vec3(c.z, c.y, c.x);
                    int32_t x = planeFunc(newA, newB, newC, i * mVoxelSize, j * mVoxelSize, mVoxelSize) / mVoxelSize;
                    voxels.insert(Voxel({ x, j, i }));
                }
            }
        }
        else if (xzCount >= xyCount && xzCount >= zyCount)
        {
            for (int32_t j = xzBBox.y; j < xzBBox.w; ++j)
            {
                for (int32_t i = xzBBox.x; i < xzBBox.z; ++i)
                {
                    if (xzPlane[(j - planesLower.z) * width + (i - planesLower.x)] != 1)
                        continue;

                    auto newA = vec3(a.x, a.z, a.y);
                    auto newB = vec3(b.x, b.z, b.y);
                    auto newC = vec3(c.x, c.z, c.y);
                    int32_t y = planeFunc(newA, newB, newC, i * mVoxelSize, j * mVoxelSize, mVoxelSize) / mVoxelSize;
                    voxels.insert(Voxel({ i, y, j }));
                }
            }
        }
    }

    vector<Voxel> output;
    copy(begin(voxels), end(voxels), back_inserter(output));

    return make_shared<Shape>(mVoxelSize, output);
}

shared_ptr<Mesh> VOXELIT_API MeshShapeConverter::getMeshFromShape(shared_ptr<const Shape> shape)
{
    auto voxels = shape->getVoxels();
    auto voxelSize = shape->getVoxelSize();
    vector<Face> faces;
    vector<Vertex> vertices;

    for (auto it = begin(voxels); it != end(voxels); ++it)
    {
        auto i = static_cast<uint16_t>((it - begin(voxels)) * 8);
        auto i1 = static_cast<uint16_t>(i + 1);
        auto i2 = static_cast<uint16_t>(i + 2);
        auto i3 = static_cast<uint16_t>(i + 3);
        auto i4 = static_cast<uint16_t>(i + 4);
        auto i5 = static_cast<uint16_t>(i + 5);
        auto i6 = static_cast<uint16_t>(i + 6);
        auto i7 = static_cast<uint16_t>(i + 7);
        auto pos = it->getPosition();

        // Front
        vertices.push_back(Vertex({ pos.x * voxelSize, pos.y * voxelSize, pos.z * voxelSize + voxelSize }));
        vertices.push_back(Vertex({ pos.x * voxelSize, pos.y * voxelSize + voxelSize, pos.z * voxelSize + voxelSize }));
        vertices.push_back(Vertex({ pos.x * voxelSize + voxelSize, pos.y * voxelSize, pos.z * voxelSize + voxelSize }));
        vertices.push_back(Vertex({ pos.x * voxelSize + voxelSize, pos.y * voxelSize + voxelSize, pos.z * voxelSize + voxelSize }));

        // Back
        vertices.push_back(Vertex({ pos.x * voxelSize, pos.y * voxelSize, pos.z * voxelSize }));
        vertices.push_back(Vertex({ pos.x * voxelSize, pos.y * voxelSize + voxelSize, pos.z * voxelSize }));
        vertices.push_back(Vertex({ pos.x * voxelSize + voxelSize, pos.y * voxelSize, pos.z * voxelSize }));
        vertices.push_back(Vertex({ pos.x * voxelSize + voxelSize, pos.y * voxelSize + voxelSize, pos.z * voxelSize }));

        //front
        faces.push_back(Face({ i, i2, i1 }));
        faces.push_back(Face({ i1, i2, i3 }));
        //back
        faces.push_back(Face({ i6, i4, i7 }));
        faces.push_back(Face({ i7, i4, i5 }));
        //left
        faces.push_back(Face({ i4, i, i5 }));
        faces.push_back(Face({ i5, i, i1 }));
        //right
        faces.push_back(Face({ i2, i6, i3 }));
        faces.push_back(Face({ i3, i6, i7 }));
        //top
        faces.push_back(Face({ i1, i3, i5 }));
        faces.push_back(Face({ i5, i3, i7 }));
        //bottom
        faces.push_back(Face({ i4, i6, i }));
        faces.push_back(Face({ i, i6, i2 }));
    }

    return make_shared<Mesh>(vertices, faces);
}

float VOXELIT_API MeshShapeConverter::getVoxelSize() const
{
    return mVoxelSize;
}

void VOXELIT_API MeshShapeConverter::setVoxelSize(float voxelSize)
{
    mVoxelSize = voxelSize;
}

bool VOXELIT_API MeshShapeConverter::getOverrideSize() const
{
    return mOverrideSize;
}

void VOXELIT_API MeshShapeConverter::setOverrideSize(bool overrideSize)
{
    mOverrideSize = overrideSize;
}

vec4 MeshShapeConverter::getTriangleBoundingBox(vec2 a, vec2 b, vec2 c)
{
    vec4 bBox = vec4(a.x, a.y, a.x, a.y);

    if (bBox.x > b.x)
        bBox.x = b.x;

    if (bBox.y > b.y)
        bBox.y = b.y;

    if (bBox.z < b.x)
        bBox.z = b.x;

    if (bBox.z < c.x)
        bBox.z = c.x;

    if (bBox.x > c.x)
        bBox.x = c.x;

    if (bBox.y > c.y)
        bBox.y = c.y;

    if (bBox.w < b.y)
        bBox.w = b.y;

    if (bBox.w < c.y)
        bBox.w = c.y;

    return bBox;
}

bool MeshShapeConverter::checkIntersect(vec2 rectOrig, float width, vec2 a, vec2 b, vec2 c)
{
    return checkPointInRectangle(a, rectOrig, width) ||
        checkPointInRectangle(b, rectOrig, width) ||
        checkPointInRectangle(c, rectOrig, width) ||
        checkPointInTriangle(rectOrig, a, b, c) ||
        checkPointInTriangle(rectOrig + vec2(width, 0.0f), a, b, c) ||
        checkPointInTriangle(rectOrig + vec2(0.0f, width), a, b, c) ||
        checkPointInTriangle(rectOrig + vec2(width, width), a, b, c);
}

bool MeshShapeConverter::checkPointInTriangle(vec2 p, vec2 a, vec2 b, vec2 c)
{
    auto v0 = c - a;
    auto v1 = b - a;
    auto v2 = p - a;

    auto dot00 = dot(v0, v0);
    auto dot01 = dot(v0, v1);
    auto dot02 = dot(v0, v2);
    auto dot11 = dot(v1, v1);
    auto dot12 = dot(v1, v2);

    auto invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    auto u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    auto v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}

bool MeshShapeConverter::checkPointInRectangle(vec2 p, vec2 rectOrig, float width)
{
    auto v = p - rectOrig;
    return v.x <= width && v.x >= 0 &&
        v.y <= width && v.y >= 0;
}

float MeshShapeConverter::planeFunc(vec3 p, vec3 q, vec3 r, float x, float y, float voxelSize)
{
    auto v1 = p - q;
    auto v2 = p - r;
    auto cross12 = cross(v1, v2);

    auto a = cross12.x;
    auto b = cross12.y;
    auto c = cross12.z;

    return (-(a * (x - p.x) + b * (y - p.y)) / c) + p.z - (cross12.z < 0 ? voxelSize : 0.0);
}
