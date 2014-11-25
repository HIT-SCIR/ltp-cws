#ifndef __LTP_SEGMENTOR_WRITER_H__
#define __LTP_SEGMENTOR_WRITER_H__

#include <iostream>
#include "segmentor/instance.h"

namespace ltp {
namespace segmentor {

class SegmentWriter {
public:
  SegmentWriter(std::ostream & _ofs) : ofs(_ofs) {}

  void write(const Instance * inst) {
    int len = inst->predicted_words.size();
    for (int i = 0; i < len; ++ i) {
      ofs << inst->predicted_words[i];
      if (i+1==len) ofs << std::endl;
      else ofs << "\t";
    }
  }

  void debug(const Instance * inst) {
    int len = inst->size();
    ofs << "_instance_debug_" << std::endl;
    ofs << "FORMS: ";
    for (int i = 0; i < len; ++ i) {
      ofs << inst->forms[i] << "|";
    }
    ofs << std::endl;

    ofs << "TAGS: ";
    for (int i = 0; i < inst->tags.size(); ++ i) {
      ofs << inst->tags[i] << "|";
    }
    ofs << std::endl;

    ofs << "TAGS(index): ";
    for (int i = 0; i < inst->tagsidx.size(); ++ i) {
      ofs << inst->tagsidx[i] << "|";
    }
    ofs << std::endl;

    ofs << "PREDICTED TAGS: ";
    for (int i = 0; i < inst->predicted_tags.size(); ++ i) {
      ofs << inst->predicted_tags[i] << "|";
    }
    ofs << std::endl;

    ofs << "PREDICTED TAGS(index): ";
    for (int i = 0; i < inst->predicted_tagsidx.size(); ++ i) {
      ofs << inst->predicted_tagsidx[i] << "|";
    }
    ofs << std::endl;

    ofs << "WORDS: ";
    for (int i = 0; i < inst->words.size(); ++ i) {
      ofs << inst->words[i] << "|";
    }
    ofs << std::endl;

    ofs << "PREDICTED WORDS: ";
    for (int i = 0; i < inst->predicted_words.size(); ++ i) {
      ofs << inst->predicted_words[i] << "|";
    }
    ofs << std::endl;
  }
private:
  std::ostream & ofs;
};

}       //  end for namespace segmentor
}       //  end for namespace ltp
#endif    //  end for __LTP_SEGMENTOR_WRITER_H__
