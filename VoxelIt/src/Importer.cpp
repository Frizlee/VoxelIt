#include <VoxelIt/Importer.hpp>
#include <algorithm>
using namespace vit;
using namespace std;


Importer::Importer()
{
}

shared_ptr<Resource> Importer::import(experimental::filesystem::path filePath)
{
    try
    {
        auto ext = filePath.extension().generic_string();
        transform(begin(ext), end(ext), begin(ext), ::tolower);
        auto importer = mImporters.at(ext);
        return importer->import(filePath);
    }
    catch (out_of_range)
    {
        // TODO: better exceptions.
        throw std::runtime_error("Unsupported resource file extension!");
    }
}

void Importer::registerImporter(shared_ptr<IResourceImporter> importer)
{
    auto extensions = importer->getSupportedExtensions();

    for (auto& ext : extensions)
        mImporters.insert({ ext, importer });
}

