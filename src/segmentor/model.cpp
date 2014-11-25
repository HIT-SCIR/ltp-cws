#include "model.h"
#include <cstring>

#define SEGMENTOR_MODEL         "otcws"         // for model version lower than 3.2.0
#define SEGMENTOR_MODEL_FULL    "otcws-full"
#define SEGMENTOR_MODEL_MINIMAL "otcws-minimal"

namespace ltp {
namespace segmentor {

Model::Model() :
  full(false) {
}

Model::~Model() {
}

void
Model::save(std::ostream & ofs) {
  // write a signature into the file
  char chunk[16];
  if (full) {
    strncpy(chunk, SEGMENTOR_MODEL_FULL, 16);
  } else {
    strncpy(chunk, SEGMENTOR_MODEL_MINIMAL, 16);
  }

  ofs.write(chunk, 16);

  if (full) {
    ofs.write(reinterpret_cast<const char *>(&end_time), sizeof(int));
  }

  int off = ofs.tellp();

  unsigned labels_offset    = 0;
  unsigned lexicon_offset   = 0;
  unsigned feature_offset   = 0;
  unsigned parameter_offset   = 0;

  write_uint(ofs, 0); //  the label offset
  write_uint(ofs, 0); //  the internal lexicon offset
  write_uint(ofs, 0); //  the features offset
  write_uint(ofs, 0); //  the parameter offset

  labels_offset = ofs.tellp();
  labels.dump(ofs);

  lexicon_offset = ofs.tellp();
  internal_lexicon.dump(ofs);

  feature_offset = ofs.tellp();
  space.dump(ofs);

  parameter_offset = ofs.tellp();
  param.dump(ofs, full);

  ofs.seekp(off);
  write_uint(ofs, labels_offset);
  write_uint(ofs, lexicon_offset);
  write_uint(ofs, feature_offset);
  write_uint(ofs, parameter_offset);
}

bool
Model::load(std::istream & ifs) {
  char chunk[16];
  ifs.read(chunk, 16);

  if (!strcmp(chunk, SEGMENTOR_MODEL_FULL)) {
    full = true;
  } else if (!strcmp(chunk, SEGMENTOR_MODEL) ||
      !strcmp(chunk, SEGMENTOR_MODEL_MINIMAL)) {
    full = false;
  } else {
    return false;
  }

  if (full) {
    ifs.read(reinterpret_cast<char *>(&end_time), sizeof(int));
  } else {
    end_time = 0;
  }

  unsigned labels_offset    = read_uint(ifs);
  unsigned lexicon_offset   = read_uint(ifs);
  unsigned feature_offset   = read_uint(ifs);
  unsigned parameter_offset = read_uint(ifs);

  ifs.seekg(labels_offset);
  if (!labels.load(ifs)) {
    return false;
  }

  ifs.seekg(lexicon_offset);
  if (!internal_lexicon.load(ifs)) {
    return false;
  }

  ifs.seekg(feature_offset);
  if (!space.load(labels.size(), ifs)) {
    return false;
  }

  ifs.seekg(parameter_offset);
  if (!param.load(ifs, full)) {
    return false;
  }

  return true;
}

}     //  end for namespace segmentor
}     //  end for namespace ltp
