#include <vector>
#include <iostream>

// The structure for representing the resource
struct Resource {
    std::string name;
    size_t size; // The size of the resource in bytes

    Resource(std::string n, size_t s) : name(n), size(s) {}
};

class AdaptiveCachingSystem {
public:
    // Updating the caching system
    void updateCache();

    // Checking whether the resource can be cached
    bool canCacheResource(size_t currentMemoryUsage, Resource& resource);

    // Кэширование ресурса
    void cacheResource(Resource& resource);

    // Caching a resource
    size_t checkCurrentMemoryUsage();

    // Getting a list of resources to cache
    std::vector<Resource> getResourcesToCache();

    // Loading a resource into memory
    void loadResourceToMemory(Resource& resource);

    // updating the cached resources table
    void updateCacheTable(Resource& resource);

private:
    // Getting the current RAM usage
    size_t getCurrentMemoryUsage();

    // Getting the maximum allowed memory limit
    size_t getMaxMemoryLimit();

    // Загрузка ресурса
    void loadResource(Resource& resource);

    // Loading a resource
    void addToCacheTable(Resource& resource);
};

void AdaptiveCachingSystem::updateCache() {
    auto currentMemoryUsage = checkCurrentMemoryUsage();
    auto resources = getResourcesToCache();

    for (auto& resource : resources) {
        if (canCacheResource(currentMemoryUsage, resource)) {
            cacheResource(resource);
            currentMemoryUsage += resource.size;
        } else {
            break; 
        }
    }
}

bool AdaptiveCachingSystem::canCacheResource(size_t currentMemoryUsage, Resource& resource) {
    return (currentMemoryUsage + resource.size) <= getMaxMemoryLimit();
}

void AdaptiveCachingSystem::cacheResource(Resource& resource) {
    loadResourceToMemory(resource);
    updateCacheTable(resource);
}

size_t AdaptiveCachingSystem::checkCurrentMemoryUsage() {
    return getCurrentMemoryUsage();
}

std::vector<Resource> AdaptiveCachingSystem::getResourcesToCache() {
    std::vector<Resource> resources = {
        Resource("Texture1", 1024 * 1024), // 1 MB
        Resource("Texture2", 2048 * 1024), // 2 MB
        Resource("Audio1", 512 * 1024),    // 512 KB
        Resource("Audio2", 1024 * 1024)    // 1 MB
    };

    // Sorting resources by size, assuming that a smaller size may have a higher caching priority
    std::sort(resources.begin(), resources.end(), [](const Resource& a, const Resource& b) {
        return a.size < b.size;
    });

    // Suppose we want to cache only resources that are frequently used.
// There may be a logic for determining "frequently used" resources, for example:
    std::vector<Resource> frequentlyUsedResources;
    for (const auto& resource : resources) {
        if (isFrequentlyUsed(resource)) {
            frequentlyUsedResources.push_back(resource);
        }
    }

    return frequentlyUsedResources;
}

bool AdaptiveCachingSystem::isFrequentlyUsed(const Resource& resource) {
    // Emulating logic to determine frequency of resource usage

    // Simple heuristic: assume some types of resources are used more frequently
    // For example, assume that textures ("Texture") and audio files ("Audio") are frequently used
    if (resource.name.find("Texture") != std::string::npos) {
        return true; // Textures are used frequently
    }
    if (resource.name.find("Audio") != std::string::npos) {
        // Let's assume audio files are used frequently, but we'll add some randomness
        std::random_device rd;  // Obtain a random seed
        std::mt19937 gen(rd()); // Standard Mersenne Twister generator
        std::uniform_int_distribution<> distrib(1, 10);

        // With a 70% probability consider that the audio file is frequently used
        return distrib(gen) <= 7;
    }

    // By default, assume that other resources are used less frequently
    return false;
}

void AdaptiveCachingSystem::loadResourceToMemory(Resource& resource) {
    std::cout << "Loading resource: " << resource.name << std::endl;
    loadResource(resource);
}

void AdaptiveCachingSystem::updateCacheTable(Resource& resource) {
    std::cout << "Updating cache table for: " << resource.name << std::endl;
    addToCacheTable(resource);
}

size_t AdaptiveCachingSystem::getCurrentMemoryUsage() {
    // This function should return the actual memory usage, it's just a stub here
    return 10 * 1024 * 1024; // 10 MB used
}

size_t AdaptiveCachingSystem::getMaxMemoryLimit() {
    return 100 * 1024 * 1024; // 100 MB max
}

void AdaptiveCachingSystem::loadResource(Resource& resource) {
    std::cout << "Resource loaded: " << resource.name << std::endl;
}

void AdaptiveCachingSystem::addToCacheTable(Resource& resource) {
    std::cout << "Resource added to cache: " << resource.name << std::endl;
}
