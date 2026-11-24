// Frame timing probe: lets the presenter log, per host present, how many
// guest frames were published since the previous present and how old the
// newest one is. 0 new guest frames = a repeated frame on screen, 2+ = a
// guest frame that was never shown. Both read as "smooth FPS counter, feels
// wrong" judder.
#pragma once

#include <atomic>
#include <cstdint>

#include <rex/chrono/clock.h>

namespace rex::ui::frame_timing {

inline std::atomic<uint64_t> g_guest_frames{0};
inline std::atomic<uint64_t> g_last_guest_tick{0};

// Called when a guest frame has been written to the presenter mailbox.
inline void NoteGuestFrame() {
  g_last_guest_tick.store(rex::chrono::Clock::QueryHostTickCount(), std::memory_order_relaxed);
  g_guest_frames.fetch_add(1, std::memory_order_release);
}

}  // namespace rex::ui::frame_timing
