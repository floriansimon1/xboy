#ifndef OPERATIONS_TABLE_HPP
#define OPERATIONS_TABLE_HPP

#include <memory>

#include "operation.hpp"

struct OperationsTable {
  std::shared_ptr<Operation> oneByteOpcodes[256];
  std::shared_ptr<Operation> twoBytesOpcodes[256];

  OperationsTable();
};

#endif

