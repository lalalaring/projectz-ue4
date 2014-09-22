#include "przCorePCH.h"
#include "utils/Registrable.h"

#include "utils/Services.h"
#include "utils/IUniqueIdRegistry.h"
#include "utils/LOG_ANSI.h"

namespace prz {
    namespace utl {

        ZRegistrable::ZRegistrable() : mId(kNoId) {
        }

        ZRegistrable::~ZRegistrable() {
            if (IsRegistered()) {
                LOGE("id = %d wasn't released", mId);
            }
        }

        ZIdType ZRegistrable::GetId() const {
            return mId;
        }

        void ZRegistrable::SetId(ZIdType id) {
            mId = id;
        }

        bool ZRegistrable::IsRegistered() const {
            return mId != kNoId;
        }

    }
}