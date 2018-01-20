#pragma once
#include "shared.h"

namespace wot_stream::internal {

    class Source {
    public:
        Source(const std::string &id, const std::string &name);
        ~Source();

        std::string GetName() const;

    private:
        obs_source * source;
    };
} // namespace wot_stream::internal