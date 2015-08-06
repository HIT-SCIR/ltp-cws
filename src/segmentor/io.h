#ifndef __LTP_SEGMENTOR_IO_H__
#define __LTP_SEGMENTOR_IO_H__

#include <iostream>
#include "framework/io.h"
#include "segmentor/settings.h"
#include "segmentor/instance.h"
#include "segmentor/preprocessor.h"

namespace ltp {
namespace segmentor {

class SegmentReader: public framework::LineCountsReader {
private:
  const Preprocessor& preprocessor;
  bool segmented;
  bool trace;
public:
  SegmentReader(std::istream& _ifs,
      const Preprocessor& processor,
      bool segmented = false,
      bool trace = false);

  Instance* next();
  // read instance from input file line by line
};

class SegmentWriter {
private:
  std::ostream& ofs;
public:
  SegmentWriter(std::ostream& ofs);

  void write(const Instance* inst);
  void debug(const Instance* inst);
};


}       //  end for namespace segmentor
}       //  end for namespace ltp

#endif    //  end for __LTP_SEGMENTOR_READER_H__
