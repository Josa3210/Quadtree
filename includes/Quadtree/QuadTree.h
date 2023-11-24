//
// Created by Joeri on 11/23/2023.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H


#include <vector>
#include <ostream>
#include <utility>
#include "AxisAlignedBoundingBox.h"


// This class is our actual quadtree
// It stores AABB’s together with some metadata
// Space Complexity: O(N)
template<typename MetadataType>
class Quadtree {
private:
    AxisAlignedBoundingBox bounds;
    unsigned int region_capacity;

    std::vector<std::tuple<AxisAlignedBoundingBox, MetadataType>> objects;

    bool subdivided = false;

    Quadtree<MetadataType> *northEast = nullptr;
    Quadtree<MetadataType> *southEast = nullptr;
    Quadtree<MetadataType> *southWest = nullptr;
    Quadtree<MetadataType> *northWest = nullptr;

    void divide() {
        Point origin = bounds.getOrigin();
        double length = bounds.getLength();
        double height = bounds.getHeight();

        AxisAlignedBoundingBox ne = AxisAlignedBoundingBox(origin + Point(length / 2, -height / 2), length / 2, height / 2);
        this->northEast = new Quadtree<MetadataType>(ne, this->region_capacity);
        AxisAlignedBoundingBox se = AxisAlignedBoundingBox(origin + Point(length / 2, height / 2), length / 2, height / 2);
        this->southEast = new Quadtree<MetadataType>(se, this->region_capacity);
        AxisAlignedBoundingBox sw = AxisAlignedBoundingBox(origin + Point(-length / 2, height / 2), length / 2, height / 2);
        this->southWest = new Quadtree<MetadataType>(sw, this->region_capacity);
        AxisAlignedBoundingBox nw = AxisAlignedBoundingBox(origin + Point(-length / 2, -height / 2), length / 2, height / 2);
        this->northWest = new Quadtree<MetadataType>(nw, this->region_capacity);

        this->subdivided = true;
    };

    void redivide() {
        auto it = objects.begin();
        while (it != objects.end()) {
            std::tuple<AxisAlignedBoundingBox, MetadataType> object = *it;
            AxisAlignedBoundingBox aabb = std::get<0>(object);
            if (this->northEast->bounds.contains(aabb)) {
                northEast->insert(aabb, std::get<1>(object));
               it = objects.erase(it);
            } else if (this->southEast->bounds.contains(aabb)) {
                southEast->insert(aabb, std::get<1>(object));
               it = objects.erase(it);
            } else if (this->southWest->bounds.contains(aabb)) {
                southWest->insert(aabb, std::get<1>(object));
               it = objects.erase(it);
            } else if (this->northWest->bounds.contains(aabb)) {
                northWest->insert(aabb, std::get<1>(object));
                it = objects.erase(it);
            } else {
                it++;
            }
        }
    };

public:
    // Constructor
    // `bounds` specifies the edges of the region that the quadtree covers.
    // `region_capacity` specifies the maximum number of objects in a single region.
    Quadtree<MetadataType>(const AxisAlignedBoundingBox &bounds, unsigned int region_capacity) : bounds(bounds), region_capacity(region_capacity) {};

    Quadtree<MetadataType>() : bounds(AxisAlignedBoundingBox()), region_capacity(0) {};

    // This method inserts the given metadata and
    // AABB into the quadtree.
    void insert(const AxisAlignedBoundingBox &aabb, const MetadataType &meta) {
        if (!this->bounds.contains(aabb)) return; // Throws exception
        if (!subdivided) {
            if (this->objects.size() < this->region_capacity) {
                this->objects.push_back({aabb, meta});
            } else {
                this->objects.push_back({aabb, meta});
                divide();
                redivide();
            }
        } else {
            if (this->northEast->bounds.contains(aabb)) {
                northEast->insert(aabb, meta);
            } else if (this->southEast->bounds.contains(aabb)) {
                southEast->insert(aabb, meta);
            } else if (this->southWest->bounds.contains(aabb)) {
                southWest->insert(aabb, meta);
            } else if (this->northWest->bounds.contains(aabb)) {
                northWest->insert(aabb, meta);
            } else {
                this->objects.push_back({aabb, meta});
            }
        }
    };

    bool isSubdivided() const {
        return subdivided;
    };

    const AxisAlignedBoundingBox &getBounds() const {
        return bounds;
    }

    unsigned int getRegionCapacity() const {
        return region_capacity;
    }

    const std::vector<std::tuple<AxisAlignedBoundingBox, MetadataType>> &getObjects() const {
        return objects;
    }

    Quadtree<MetadataType> *getNorthEast() const {
        return northEast;
    }

    Quadtree<MetadataType> *getSouthEast() const {
        return southEast;
    }

    Quadtree<MetadataType> *getSouthWest() const {
        return southWest;
    }

    Quadtree<MetadataType> *getNorthWest() const {
        return northWest;
    }

    friend std::ostream &operator<<(std::ostream &os, const Quadtree &quadtree) {
        os << "bounds: " << quadtree.bounds << ", region_capacity: " << quadtree.region_capacity << ", subdivided: " << quadtree.subdivided << ", northEast: " << quadtree.northEast << ", southEast: "
           << quadtree.southEast << ", southWest: " << quadtree.southWest << ", northWest: " << quadtree.northWest;
        return os;
    }
};


#endif //QUADTREE_QUADTREE_H
