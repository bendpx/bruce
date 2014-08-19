/* <bruce/input_dg/input_dg_common.h>

   ----------------------------------------------------------------------------
   Copyright 2013-2014 Tagged

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   ----------------------------------------------------------------------------

   Common implementation functions for dealing with input datagrams that get
   transmitted over bruce's UNIX domain datagram socket.
 */

#pragma once

#include <cstddef>
#include <cstdint>

#include <bruce/anomaly_tracker.h>
#include <bruce/msg.h>
#include <bruce/msg_state_tracker.h>
#include <capped/pool.h>

namespace Bruce {

  namespace InputDg {

    enum { SZ_FIELD_SIZE = 4 };

    enum { API_KEY_FIELD_SIZE = 2 };

    enum { API_VERSION_FIELD_SIZE = 2 };

    /* TODO: remove this */
    enum { OLD_VER_FIELD_SIZE = 1 };

    void DiscardMalformedMsg(const uint8_t *msg_begin, size_t msg_size,
        TAnomalyTracker &anomaly_tracker);

    void DiscardMsgNoMem(TMsg::TTimestamp timestamp, const char *topic_begin,
        const char *topic_end, const void *key_begin, const void *key_end,
        const void *value_begin, const void *value_end,
        TAnomalyTracker &anomaly_tracker);

    TMsg::TPtr TryCreateAnyPartitionMsg(int64_t timestamp,
        const char *topic_begin, const char *topic_end, const void *key_begin,
        size_t key_size, const void *value_begin, size_t value_size,
        Capped::TPool &pool, TAnomalyTracker &anomaly_tracker,
        TMsgStateTracker &msg_state_tracker);

    TMsg::TPtr TryCreatePartitionKeyMsg(int32_t partition_key,
        int64_t timestamp, const char *topic_begin, const char *topic_end,
        const void *key_begin, size_t key_size, const void *value_begin,
        size_t value_size, Capped::TPool &pool,
        TAnomalyTracker &anomaly_tracker, TMsgStateTracker &msg_state_tracker);

  }  // InputDg

}  // Bruce