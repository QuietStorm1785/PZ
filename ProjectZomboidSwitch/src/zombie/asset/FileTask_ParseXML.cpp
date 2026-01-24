#include <string>
#include "zombie/asset/FileTask_ParseXML.h"

namespace zombie {
namespace asset {

FileTask_ParseXML::FileTask_ParseXML(const std::type_info& type, const std::string& filename, std::shared_ptr<IFileTaskCallback> callback, std::shared_ptr<FileSystem> fs)
    : FileTask(fs, callback), m_type(type), m_filename(filename)
{
    // No additional logic needed
}

std::string FileTask_ParseXML::getErrorMessage() {
    return m_filename;
}
}

void FileTask_ParseXML::done() {
    m_filename.clear();
}


void* FileTask_ParseXML::call() {
    try {
        auto pt = new boost::property_tree::ptree();
        boost::property_tree::read_xml(m_filename, *pt);
        return pt; // The caller is responsible for deleting the returned ptree*
    } catch (const std::exception& ex) {
        // Optionally log the error
        return nullptr;
    }
}

} // namespace asset
} // namespace zombie
