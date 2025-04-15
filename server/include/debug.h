/*
 * Copyright (C) 2012-2017, 2024 Kernkonzept GmbH.
 * Author(s): Alexander Warg <alexander.warg@kernkonzept.com>
 *            Adam Lackorzynski <adam.lackorzynski@kernkonzept.com>
 *
 * License: see LICENSE.spdx (in this directory or the directories above)
 */
#pragma once

#include <l4/re/util/debug>

struct Err : L4Re::Util::Err
{
  Err(Level l = Fatal) : L4Re::Util::Err(l, "net") {}
};

struct Dbg : L4Re::Util::Dbg
{
  enum
  {
    Info = 1,
    Warn = 2,

    Hsi = 0x10000,
    Switch = 0x20000,
  };

  Dbg(unsigned long l = Info, char const *subsys = "")
  : L4Re::Util::Dbg(l, "net", subsys) {}
};
