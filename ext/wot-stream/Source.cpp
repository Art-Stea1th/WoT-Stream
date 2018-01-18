#include "Source.h"

namespace WotStream::Internal {

	Source::Source(const string &id, const string &name) {
		_source = obs_source_create(id.c_str(), name.c_str(), nullptr, nullptr);
	}

	Source::~Source() {
		obs_source_release(_source);
	}

	string Source::GetName() const {
		return obs_source_get_name(_source);
	}
}