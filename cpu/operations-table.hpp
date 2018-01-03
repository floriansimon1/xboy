#ifndef OPERATIONS_TABLE_HPP
#define OPERATIONS_TABLE_HPP

#include <memory>

#include "operation.hpp"
#include "operations/nop.hpp"

const std::shared_ptr<Operation> operationsTable[] = {
  std::make_shared<Nop>()
};

#endif

