//
// Created by Joeri on 11/23/2023.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H


#include <vector>
#include <ostream>
#include <utility>
#include <unordered_set>
#include <list>
#include "axisAlignedBoundingBox.h"
#include "unordered_set_extension.h"
#include "object.h"

// This class is our actual quadtree
// It stores AABB’s together with some metadata
// Space Complexity: O(N)
template<typename MetadataType>
class Quadtree {
private:
    axisAlignedBoundingBox bounds;
    unsigned int region_capacity;

    std::vector<object<MetadataType>> objects;

    bool divided = false;

    Quadtree<MetadataType> *northEast = nullptr;
    Quadtree<MetadataType> *southEast = nullptr;
    Quadtree<MetadataType> *southWest = nullptr;
    Quadtree<MetadataType> *northWest = nullptr;

    void divide() {
        point origin = bounds.getOrigin();
        double length = bounds.getLength();
        double height = bounds.getHeight();

        axisAlignedBoundingBox ne = axisAlignedBoundingBox(origin + point(length / 2, -height / 2), length / 2, height / 2);
        this->northEast = new Quadtree<MetadataType>(ne, this->region_capacity);
        axisAlignedBoundingBox se = axisAlignedBoundingBox(origin + point(length / 2, height / 2), length / 2, height / 2);
        this->southEast = new Quadtree<MetadataType>(se, this->region_capacity);
        axisAlignedBoundingBox sw = axisAlignedBoundingBox(origin + point(-length / 2, height / 2), length / 2, height / 2);
        this->southWest = new Quadtree<MetadataType>(sw, this->region_capacity);
        axisAlignedBoundingBox nw = axisAlignedBoundingBox(origin + point(-length / 2, -height / 2), length / 2, height / 2);
        this->northWest = new Quadtree<MetadataType>(nw, this->region_capacity);

        this->divided = true;
    };

    void redivide() {
        auto it = objects.begin();
        while (it != objects.end()) {
            std::tuple<axisAlignedBoundingBox, MetadataType> object = *it;
            axisAlignedBoundingBox aabb = object.box;
            if (this->northEast->bounds.contains(aabb)) {
                northEast->insert(aabb, object.value);
                it = objects.erase(it);
            } else if (this->southEast->bounds.contains(aabb)) {
                southEast->insert(aabb, object.value);
                it = objects.erase(it);
            } else if (this->southWest->bounds.contains(aabb)) {
                southWest->insert(aabb, object.value);
                it = objects.erase(it);
            } else if (this->northWest->bounds.contains(aabb)) {
                northWest->insert(aabb, object.value);
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
    Quadtree<MetadataType>(const axisAlignedBoundingBox &bounds, unsigned int region_capacity) : bounds(bounds), region_capacity(region_capacity) {};

    Quadtree<MetadataType>() : bounds(axisAlignedBoundingBox()), region_capacity(0) {};

    // This method inserts the given metadata and
    // AABB into the quadtree.
    void insert(const axisAlignedBoundingBox &aabb, const MetadataType &meta) {
        if (!this->bounds.contains(aabb)) return; // Throws exception
        if (!divided) {
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

    bool isDivided() const {
        return divided;
    };

    const axisAlignedBoundingBox &getBounds() const {
        return bounds;
    }

    unsigned int getRegionCapacity() const {
        return region_capacity;
    }

    const std::vector<object<MetadataType>> &getObjects() const {
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

    void show(std::string str) {
        str += "  ";
        std::cout << str << "Quadtree:" << std::endl;
        std::cout << str << "Bounds( Origin: (" << this->bounds.getOrigin().getX() << ", " << this->bounds.getOrigin().getY() << "), Length: " << this->bounds.getLength() << ", Height: "
                  << this->bounds.getHeight() << std::endl;
        std::cout << str << "Objects: ";
        auto it = this->objects.begin();
        while (it != objects.end()) {
            std::cout << "(" << std::get<0>(*it) << ", " << std::get<1>(*it) << "), ";
            it++;
        }
        std::cout << std::endl;
        if (this->isDivided()) {
            std::cout << str << "Is divided: " << std::endl;
            this->getNorthEast()->show(str);
            this->getSouthEast()->show(str);
            this->getSouthWest()->show(str);
            this->getNorthWest()->show(str);
        } else {
            std::cout << str << "Is not divided" << std::endl;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Quadtree &quadtree) {
        os << "bounds: " << quadtree.bounds << ", region_capacity: " << quadtree.region_capacity << ", divided: " << quadtree.divided << ", northEast: " << quadtree.northEast << ", southEast: "
           << quadtree.southEast << ", southWest: " << quadtree.southWest << ", northWest: " << quadtree.northWest;
        return os;
    }

    // This method should return a std::unordered_set of all items inside the given AABB.
    // The given AABB may span multiple square regions of the quadtree.
    // The worst-case time-complexity of this method should be O(log(N)) for a Quadtree with N leaf nodes
    // TODO: You should decide the element type of the std::unordered_set
    // Your set should contain the AABB and the Metadata of all objects in the given region.
    std::unordered_set<object<MetadataType>> query_region(const axisAlignedBoundingBox &aabb) const {
        std::unordered_set<object<MetadataType>> items = std::unordered_set<object<MetadataType>>();

        // The region to query is not in this (section) of the quadtree
        if (!collides(this->bounds, aabb)){
            return {};
        }

        // Gather all child in this region and ones that collide with it
        // --> Even if 1 single point is in the queried region, it might be possible that an aabb collides with it
        auto objectIt = this->objects.begin();
        while (objectIt != this->objects.end()) {
            auto object = *objectIt;
            axisAlignedBoundingBox box = object.box;
            MetadataType data = object.value;
            if (collides(aabb, box)) {
                items.insert(data);
            }
            objectIt++;
        }

        if (!this->isDivided()) return items;

        items = merge(items, this->getNorthEast()->query_region(aabb));
        items = merge(items, this->getSouthEast()->query_region(aabb));
        items = merge(items, this->getSouthWest()->query_region(aabb));
        items = merge(items, this->getNorthWest()->query_region(aabb));

        return items;
    }
};


#endif //QUADTREE_QUADTREE_H