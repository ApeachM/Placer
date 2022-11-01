#ifndef PLACER_INCLUDE_DATASTRUCTURES_STRUCTURES_H_
#define PLACER_INCLUDE_DATASTRUCTURES_STRUCTURES_H_
#include <unordered_map>
#include <vector>
#include "db.h"
#include "Die.h"

namespace Placer {
using namespace odb;
class Instance;
class Net;
class Pin;

/// data storages
struct data_storage {
  std::vector<Instance> instances;
  std::vector<Net> nets;
  std::vector<Pin> pins;
  Die die;
};

/// data mapping from db to data_storage
struct data_mapping {
  std::unordered_map<dbInst *, Instance *> inst_map;
  std::unordered_map<dbNet *, Net *> net_map;
  /// mapping for terminals on instance (pins on cell)
  std::unordered_map<dbITerm *, Pin *> pin_map_i;
  /// mapping for terminals on blocks (includes fixed pins on die)
  std::unordered_map<dbBTerm *, Pin *> pin_map_b;
};
}
#endif //PLACER_INCLUDE_DATASTRUCTURES_STRUCTURES_H_
