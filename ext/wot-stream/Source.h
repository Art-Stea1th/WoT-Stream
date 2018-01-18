#pragma once
#include "shared.h"

namespace WotStream::Internal {

	class Source {
	public:

		Source(const string &id, const string &name);
		~Source();

		string GetName() const;

	private:

		obs_source*  _source;
	};
}