# Virtio Net P2P, a virtual network point-to-point link {#l4re_servers_virtio_net_p2p}

[comment]: # (This is a generated file. Do not change it.)
[comment]: # (Instead, change capdb.yml.)

The virtual network point-to-point server (p2p) connects two clients with a
virtual network connection. It uses virtio as the transport mechanism. Each
virtual network p2p endpoint implements the device-side of a virtio network
device. Each client can access its endpoint using the driver-side semantics of a
virtio network device.


## Capabilities

* `dataspace`

  Trusted dataspaces

  Multiple capability names can be provided by the `--register-ds` command line
  parameter.

* `svr`

  Server Capability of application. Endpoint for IPC calls

  Mandatory capability.


## Command Line Options

The following command line options are supported:

* `-p <num_usec>`, `--poll <num_usec>`

  Enable polling mode and set the poll interval. IRQ notification is disabled
  for queues while in polling mode.

  Numerical value.
    * Must be a positive integer specified in microseconds.


* `-s <num>`, `--size <num>`

  Set the maximum queue size for the device-side virtio queues.

  Numerical value.
    * Must be a power of 2 in the range of 1 to 32768 inclusive.


  Default: `256`

* `-d <cap_name>`, `--register-ds <cap_name>`

  Register a trusted dataspace capability. If this option is used, it is not
  possible to communicate with the server via dataspaces other than the
  registered ones.

  Can be used multiple times.

  Name of a provided capability that adheres to the dataspace protocol.

## Building and Configuration

The virtual network p2p server can be built using the L4Re build system by
placing this project into the `pkg` directory.

## Starting the service

The virtual network p2p server can be started with Lua like this:

```lua
local p2p = L4.default_loader:new_channel();
L4.default_loader:start(
{
  caps = {
    svr = p2p:svr(),
  },
},
"rom/l4vio_net_p2p [<options>]");
```

First an IPC gate (`p2p`) is created which is used between the virtual network
p2p server and a client to create new virtual ports. The server-side is assigned
to the mandatory `svr` capability of the virtual network p2p server. See the
section below on how to create a new virtual port and connect a client to it.

## Virtual p2p port

Prior to connecting a client to a virtual network p2p server port it has to be
created using the following Lua function. It has to be called on the client side
of the IPC gate capability whose server side is bound to the virtual network p2p
server.

The "key=value" pairs passed to create() can be omitted and their order is not
important.

Call:   `create(0 [, "ds-max=<max>", "mac=<addr>"])`

* `"ds-max=<max>"`

  Specifies the upper limit of the number of dataspaces the client is allowed to
  register with the server for virtio DMA.

  Numerical value.
    * Must be in the range of 1 to 80 inclusive.


  Default: `2`

* `"mac=<addr>"`

  Specify the MAC address of the endpoint where `<mac_address>` is of the form
  xx:xx:xx:xx:xx:xx.

  String value.
    * Must be in the form xx:xx:xx:xx:xx:xx.

If the `create()` call is successful a new capability which references a virtual
network p2p server port is returned. A client uses this capability to talk to
the virtual network p2p server using the virtio network protocol.



## Examples

A couple of examples on how to create ports with different properties are listed
below.

```lua
-- two normal ports with at most 4 data spaces
net0 = p2p:create(0, "ds-max=4")
net1 = p2p:create(0, "ds-max=4")
-- normal port with 4 data spaces and MAC address
net0 = p2p:create(0, "ds-max=4", "mac=11:22:33:44:55:66")
```

