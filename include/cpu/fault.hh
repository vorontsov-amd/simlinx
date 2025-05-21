#pragma once

enum class Fault {
  NoFault,
  NotImplemented,
  IllegalInstruction,
  LoadAccessFault,
  StoreAccessFault,
  TheEndOfTask
};

enum class PageFault {
  NoFault,
  InvalidPage,
  WButNotR,
  ILessThenZero,
  AccessType,
  AccessBit,
  DirtyBit,
  SuperPage
};