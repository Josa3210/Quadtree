//
// This class represents a Quadtree data structure which stores axis-aligned bounding boxes with metadata.
// The space complexity of this data structure is O(N) where N is the number of objects stored.
// Created by Joeri on 11/23/2023.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H


#include <vector>
#include <ostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <list>
#include "axisAlignedBoundingBox.h"
#include "unordered_set_extension.h"
#include "object.h"

// The Quadtree class is templated on the type of metadata associated with each object.
template<typename MetadataType> using objectSet = std::unordered_set<object<MetadataType>, object_hash<MetadataType>>;

// This class is our actual quadtree
// It stores AABB’s together with some metadata
// Space Complexity: O(N)
template<typename MetadataType>
class Quadtree {
private:
    axisAlignedBoundingBox bounds; // stores the bounding box of the current Quadtree node
    unsigned int region_capacity;  // the maximum number of objects that can be stored in a single region

    // A vector that stores the objects contained in the current Quadtree node
    std::vector<object<MetadataType>> objects = std::vector<object<MetadataType>>();
    std::vector<object<MetadataType>> allObjects = std::vector<object<MetadataType>>();

    // variable that keeps track of whether the region has been divided into four sub-regions
    bool divided = false;

    // northEast, southEast, southWest, and northWest are pointers to the four sub-regions of the current region
    Quadtree<MetadataType> *northEast = nullptr;
    Quadtree<MetadataType> *southEast = nullptr;
    Quadtree<MetadataType> *southWest = nullptr;
    Quadtree<MetadataType> *northWest = nullptr;

    // Responsible for dividing the current region into four equal sub-regions.
    // It calculates the origin, length, and height of the new sub-regions based on the current region's bounding box.
    // It then creates new Quadtree objects for each sub-region and updates the respective pointers.
    // Finally, it sets the divided flag to true.
    void divide() {
        point origin = bounds.getOrigin();
        float length = bounds.getLength();
        float height = bounds.getHeight();

        axisAlignedBoundingBox ne = axisAlignedBoundingBox(origin + point(length / 2, 0), length / 2, height / 2);
        this->northEast = new Quadtree<MetadataType>(ne, this->region_capacity);
        axisAlignedBoundingBox se = axisAlignedBoundingBox(origin + point(length / 2, height / 2), length / 2, height / 2);
        this->southEast = new Quadtree<MetadataType>(se, this->region_capacity);
        axisAlignedBoundingBox sw = axisAlignedBoundingBox(origin + point(0, height / 2), length / 2, height / 2);
        this->southWest = new Quadtree<MetadataType>(sw, this->region_capacity);
        axisAlignedBoundingBox nw = axisAlignedBoundingBox(origin, length / 2, height / 2);
        this->northWest = new Quadtree<MetadataType>(nw, this->region_capacity);

        this->divided = true;
    };

    // Responsible for redistributing the objects that are currently stored in the region when it has been divided.
    void redivideObjects() {
        // It creates a new vector newVec and copies the objects from the current region's objects vector.
        auto newVec = this->objects;

        // It then clears the original objects vector.
        this->objects.clear();

        // It iterates through each object in newVec and checks if it belongs to any of the four sub-regions.
        auto it = newVec.begin();
        while (it != newVec.end()) {
            object<MetadataType> object = *it;
            axisAlignedBoundingBox aabb = object.box;
            // If it does, the object is inserted into the appropriate sub-region using the insert function.
            if (this->northEast->bounds.contains(aabb)) {
                northEast->insert(object);
            } else if (this->southEast->bounds.contains(aabb)) {
                southEast->insert(object);
            } else if (this->southWest->bounds.contains(aabb)) {
                southWest->insert(object);
            } else if (this->northWest->bounds.contains(aabb)) {
                northWest->insert(object);

                // Otherwise, the object is inserted back into the current region using insert function.
            } else {
                this->insert(object);
            }
            it++;
        }
    };

public:
    // Constructor
    // `bounds` specifies the edges of the region that the quadtree covers.
    // `region_capacity` specifies the maximum number of objects in a single region.
    Quadtree<MetadataType>(const axisAlignedBoundingBox &bounds, unsigned int region_capacity) : bounds(bounds), region_capacity(region_capacity) {};

    // Default constructor
    Quadtree<MetadataType>() : bounds(axisAlignedBoundingBox()), region_capacity(0) {};

    // This method inserts the given metadata and AABB into the quadtree.
    void insert(object<MetadataType> object) {
        axisAlignedBoundingBox aabb = object.box;
        if (!this->bounds.contains(aabb)) return; // Throws exception if the given AABB is outside the bounds of the quadtree
        if (!divided) {
            if (this->objects.size() < this->region_capacity) {
                this->objects.push_back(object); // Add the object to the current region if it has space
            } else {
                this->objects.push_back(object); // Add the object to the current region
                divide(); // Divide the quadtree into four subregions
                redivideObjects(); // Move objects that overlap the subregions to the correct subregion
            }
        } else {
            if (this->northEast->bounds.contains(aabb)) {
                northEast->insert(object); // Recursively insert the object into the northeast subregion
            } else if (this->southEast->bounds.contains(aabb)) {
                southEast->insert(object); // Recursively insert the object into the southeast subregion
            } else if (this->southWest->bounds.contains(aabb)) {
                southWest->insert(object); // Recursively insert the object into the southwest subregion
            } else if (this->northWest->bounds.contains(aabb)) {
                northWest->insert(object); // Recursively insert the object into the northwest subregion
            } else {
                this->objects.push_back(object); // Add the object to the current region if it does not fit inside any subregion
            }
        }
    };

    // Check if the quadtree is divided into subregions
    [[nodiscard]] bool isDivided() const { return divided; };

    // Get the bounds of the quadtree
    [[nodiscard]] const axisAlignedBoundingBox &getBounds() const { return bounds; }

    // Get the maximum number of objects in a single region
    [[nodiscard]] unsigned int getRegionCapacity() const { return region_capacity; }

    // Check if the quadtree is empty
    [[nodiscard]] bool isEmpty() const { return objects.empty(); };

    // Get a copy of the objects in the quadtree
    std::vector<object<MetadataType>> getObjects() const { return objects; }

    // Get the northeast subregion of the quadtree
    Quadtree<MetadataType> *getNorthEast() const { return northEast; }

    // Get the southeast subregion of the quadtree
    Quadtree<MetadataType> *getSouthEast() const { return southEast; }

    // Get the southwest subregion of the quadtree
    Quadtree<MetadataType> *getSouthWest() const { return southWest; }

    // Get the northwest subregion of the quadtree
    Quadtree<MetadataType> *getNorthWest() const { return northWest; }

    // Print the quadtree nodes and boundaries
    void show(std::string str) {
        str += "  ";
        std::cout << str << "Quadtree:" << std::endl;
        std::cout << str << "Bounds( Origin: (" << this->bounds.getOrigin().getX() << ", " << this->bounds.getOrigin().getY() << "), Length: " << this->bounds.getLength() << ", Height: "
                  << this->bounds.getHeight() << std::endl;
        std::cout << str << "Objects: ";
        auto it = objects.begin();
        while (it != objects.end()) {
            object<MetadataType> object = *it;
            std::cout << "(" << object.box << ", " << object.value << "), ";
            it++;
        }
        std::cout << std::endl;

        // Show subregions if the quadtree is divided
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

    // Overload the output stream operator to print the quadtree information
    friend std::ostream &operator<<(std::ostream &os, const Quadtree &quadtree) {
        os << "bounds: " << quadtree.bounds << ", region_capacity: " << quadtree.region_capacity << ", divided: " << quadtree.divided << ", northEast: " << quadtree.northEast << ", southEast: "
           << quadtree.southEast << ", southWest: " << quadtree.southWest << ", northWest: " << quadtree.northWest;
        return os;
    }

    // This method queries the quadtree for all items that are inside the given axis-aligned bounding box (AABB).
    // The AABB may span multiple square regions of the quadtree.
    // The worst-case time complexity of this method should be O(log(N)) for a quadtree with N leaf nodes.
    // The element type of the std::unordered_set is to be determined.
    // The returned set should contain the AABB and the metadata of all objects within the given region.
    objectSet<MetadataType> query_region(const axisAlignedBoundingBox &aabb) const {
        objectSet<MetadataType> items = {}; // Initialize an empty set to store the items

        // Check if the given AABB collides with this section of the quadtree
        if (!collides(this->bounds, aabb)) {
            return {}; // If there is no collision, return an empty set
        }

        // Iterate over the objects in this quadtree section
        auto objectIt = objects.begin();
        while (objectIt != this->objects.end()) {
            object<MetadataType> object = *objectIt;
            axisAlignedBoundingBox box = object.box;
            MetadataType data = object.value;

            // Check if the object's AABB collides with the given AABB
            if (collides(aabb, box)) {
                items.insert(object); // Insert the object into the set if there is a collision
            }
            objectIt++;
        }

        // If the section is not further divided, return the set of collected objects
        if (!this->isDivided()) return items;

        // Recursively query each child section and merge their results into the set of collected objects
        items = unorderedSet::merge(items, this->getNorthEast()->query_region(aabb));
        items = unorderedSet::merge(items, this->getSouthEast()->query_region(aabb));
        items = unorderedSet::merge(items, this->getSouthWest()->query_region(aabb));
        items = unorderedSet::merge(items, this->getNorthWest()->query_region(aabb));

        return items; // Return the final set of collected objects
    }

    typename std::vector<object<MetadataType>> getAllObjects() {
        std::vector<object<MetadataType>> _allObjects;

        std::move(this->objects.begin(),this->objects.end(),std::back_inserter(_allObjects));
        if (isDivided()){
            std::vector<object<MetadataType>> NEobjects = this->getNorthEast()->getObjects();
            std::move(NEobjects.begin(),NEobjects.end(),std::back_inserter(_allObjects));

            std::vector<object<MetadataType>> SWobjects = this->getNorthEast()->getObjects();
            std::move(SWobjects.begin(),SWobjects.end(),std::back_inserter(_allObjects));

            std::vector<object<MetadataType>> NWobjects = this->getNorthEast()->getObjects();
            std::move(NWobjects.begin(),NWobjects.end(),std::back_inserter(_allObjects));

            std::vector<object<MetadataType>> SEobjects = this->getNorthEast()->getObjects();
            std::move(SEobjects.begin(),SEobjects.end(),std::back_inserter(_allObjects));
        }
        this->allObjects = _allObjects;
        return _allObjects;
    }


    // This function returns an iterator pointing to the beginning of the objects vector.
    typename std::vector<object<MetadataType>>::iterator begin() {return this->getAllObjects().begin(); };

    // This function returns an iterator pointing to the end of the objects vector.
    typename std::vector<object<MetadataType>>::iterator end() { return this->getAllObjects().end(); };

};

#endif //QUADTREE_QUADTREE_H