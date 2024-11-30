#pragma once

#include "modm/platform/spi/spi_master_1_dma.hpp"

namespace modm::platform {
template <class DmaChannelRx, class DmaChannelTx>
class SpiMaster1_DmaBlock: public SpiMaster1_Dma<DmaChannelRx, DmaChannelTx> {
public:
	static modm::ResumableResult<uint8_t>
	transfer(uint8_t data) {
        return {modm::rf::Stop, SpiMaster1_Dma<DmaChannelRx, DmaChannelTx>::transferBlocking(data)};
    }

	static modm::ResumableResult<void>
	transfer(const uint8_t *tx, uint8_t *rx, std::size_t length) {
        SpiMaster1_Dma<DmaChannelRx, DmaChannelTx>::transferBlocking(tx, rx, length);
        return modm::rf::Stop;
    }
};
}
