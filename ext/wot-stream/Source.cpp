#include "Source.h"

namespace wot_stream::internal {

    Source::Source(const std::string &id, const std::string &name) {
        source = obs_source_create(id.c_str(), name.c_str(), nullptr, nullptr);
    }

    Source::~Source() { obs_source_release(source); }

    std::string Source::GetName() const { return obs_source_get_name(source); }

} // namespace wot_stream::internal