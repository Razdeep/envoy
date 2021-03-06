#pragma once

#include "envoy/network/connection_handler.h"
#include "envoy/registry/registry.h"
#include "envoy/server/active_udp_listener_config.h"

namespace Envoy {
namespace Server {

class ActiveRawUdpListenerFactory : public Network::ActiveUdpListenerFactory {
public:
  ActiveRawUdpListenerFactory(uint32_t concurrency);

  Network::ConnectionHandler::ActiveUdpListenerPtr
  createActiveUdpListener(uint32_t worker_index, Network::UdpConnectionHandler& parent,
                          Event::Dispatcher& disptacher, Network::ListenerConfig& config) override;

  bool isTransportConnectionless() const override { return true; }

private:
  const uint32_t concurrency_;
};

// This class uses a protobuf config to create a UDP listener factory which
// creates a Server::ConnectionHandlerImpl::ActiveUdpListener.
// This is the default UDP listener if not specified in config.
class ActiveRawUdpListenerConfigFactory : public ActiveUdpListenerConfigFactory {
public:
  ProtobufTypes::MessagePtr createEmptyConfigProto() override;

  Network::ActiveUdpListenerFactoryPtr
  createActiveUdpListenerFactory(const Protobuf::Message&, uint32_t concurrency) override;

  std::string name() const override;
};

DECLARE_FACTORY(ActiveRawUdpListenerConfigFactory);

} // namespace Server
} // namespace Envoy
