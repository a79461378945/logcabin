/* Copyright (c) 2011-2012 Stanford University
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR(S) DISCLAIM ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL AUTHORS BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <gtest/gtest.h>
#include <thread>

#include "Core/ThreadId.h"

namespace LogCabin {
namespace Core {

namespace ThreadId {
namespace Internal {
extern __thread uint64_t id;
extern uint64_t nextId;
}
}

namespace {

class CoreThreadIdTest : public ::testing::Test {
  public:
    CoreThreadIdTest()
    {
        ThreadId::Internal::id = 0;
        ThreadId::Internal::nextId = 1;
    }
};

// Helper function that runs in a separate thread.  It reads its id and
// saves it in the variable pointed to by its argument.
static void readThreadId(uint64_t* p) {
    *p = ThreadId::get();
}

TEST_F(CoreThreadIdTest, basics) {
    uint64_t value;
    EXPECT_EQ(1U, ThreadId::get());
    EXPECT_EQ(1U, ThreadId::get());
    std::thread thread1(readThreadId, &value);
    thread1.join();
    EXPECT_EQ(2U, value);
    std::thread thread2(readThreadId, &value);
    thread2.join();
    EXPECT_EQ(3U, value);
}

} // namespace LogCabin::Core::<anonymous>
} // namespace LogCabin::Core
} // namespace LogCabin
